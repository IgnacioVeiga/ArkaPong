#include "Core/Utils/Coordinator.h"
#include "Core/Component/AnimationComponent.h"
#include "Core/Component/AudioComponent.h"
#include "Core/Component/Background/ImageBackgroundComponent.h"
#include "Core/Component/Background/SolidColorBackgroundComponent.h"
#include "Core/Component/Background/TileBackgroundComponent.h"
#include "Core/Component/RigidBodyComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/TextComponent.h"
#include "Core/Component/TransformComponent.h"
#include "Core/Manager/FontManager.h"
#include "Core/Manager/TextureManager.h"
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <fstream>

namespace
{
    // Keep the JSON schema explicit so a future scene editor can evolve without
    // depending on SDL runtime types or raw pointer values.
    nlohmann::json SerializeVec2(const Vec2& value)
    {
        return {{"x", value.x}, {"y", value.y}};
    }

    Vec2 DeserializeVec2(const nlohmann::json& value, const Vec2& fallback = Vec2())
    {
        if (!value.is_object()) {
            return fallback;
        }

        return {
            value.value("x", fallback.x),
            value.value("y", fallback.y)
        };
    }

    nlohmann::json SerializeRect(const SDL_Rect& value)
    {
        return {{"x", value.x}, {"y", value.y}, {"w", value.w}, {"h", value.h}};
    }

    SDL_Rect DeserializeRect(const nlohmann::json& value, const SDL_Rect& fallback = SDL_Rect{0, 0, 0, 0})
    {
        if (!value.is_object()) {
            return fallback;
        }

        return {
            value.value("x", fallback.x),
            value.value("y", fallback.y),
            value.value("w", fallback.w),
            value.value("h", fallback.h)
        };
    }

    nlohmann::json SerializeFRect(const SDL_FRect& value)
    {
        return {{"x", value.x}, {"y", value.y}, {"w", value.w}, {"h", value.h}};
    }

    SDL_FRect DeserializeFRect(const nlohmann::json& value, const SDL_FRect& fallback = SDL_FRect{0, 0, 0, 0})
    {
        if (!value.is_object()) {
            return fallback;
        }

        return {
            value.value("x", fallback.x),
            value.value("y", fallback.y),
            value.value("w", fallback.w),
            value.value("h", fallback.h)
        };
    }

    nlohmann::json SerializeColor(const SDL_Color& value)
    {
        return {{"r", value.r}, {"g", value.g}, {"b", value.b}, {"a", value.a}};
    }

    SDL_Color DeserializeColor(const nlohmann::json& value, const SDL_Color& fallback = SDL_Color{255, 255, 255, 255})
    {
        if (!value.is_object()) {
            return fallback;
        }

        return {
            static_cast<Uint8>(value.value("r", fallback.r)),
            static_cast<Uint8>(value.value("g", fallback.g)),
            static_cast<Uint8>(value.value("b", fallback.b)),
            static_cast<Uint8>(value.value("a", fallback.a))
        };
    }

    std::string SerializeAudioType(const AudioType type)
    {
        return type == AudioType::BGM ? "bgm" : "sfx";
    }

    AudioType DeserializeAudioType(const std::string& type)
    {
        return type == "bgm" ? AudioType::BGM : AudioType::SFX;
    }

    std::string ResolveSceneName(
        const nlohmann::json& sceneJson,
        const std::string& overrideSceneName)
    {
        if (!overrideSceneName.empty()) {
            return overrideSceneName;
        }

        return sceneJson.value("scene_name", "");
    }
}

void Coordinator::Init()
{
    // Create pointers to each manager
    mEntityManager = std::make_unique<EntityManager>();
    mComponentManager = std::make_unique<ComponentManager>();
    mSystemManager = std::make_unique<SystemManager>();
}

// Entity methods
Entity Coordinator::CreateEntity(const std::string &entity_name,
                                 const std::string &scene_name,
                                 const std::string &tag,
                                 const std::string &sub_tag)
{
    const Entity entity = mEntityManager->CreateEntity();
    AddComponent<BaseComponent>(
        entity,
        {true,
         entity_name,
         scene_name,
         tag,
         sub_tag});
    return entity;
}

void Coordinator::DestroyEntity(const Entity entity)
{
    if (HasComponent<TextComponent>(entity))
    {
        auto &textComponent = GetComponent<TextComponent>(entity);
        if (textComponent.texture != nullptr)
        {
            SDL_DestroyTexture(textComponent.texture);
            textComponent.texture = nullptr;
        }
    }

    mEntityManager->DestroyEntity(entity);
    mComponentManager->EntityDestroyed(entity);
    mSystemManager->EntityDestroyed(entity);
}

void Coordinator::MarkEntityForDeletion(const Entity entity)
{
    entitiesToDelete.push_back(entity);
}

void Coordinator::ProcessPendingDeletions()
{
    for (const Entity entity : entitiesToDelete)
    {
        DestroyEntity(entity);
    }
    entitiesToDelete.clear();
}

bool Coordinator::EntityExists(Entity entity) const
{
    return mEntityManager->EntityExists(entity);
}

std::vector<Entity> Coordinator::GetAllEntities() const
{
    return mEntityManager->GetAllEntities();
}

std::vector<Entity> Coordinator::GetEntitiesByScene(const std::string& scene_name)
{
    std::vector<Entity> result;

    for (const Entity entity : GetAllEntities())
    {
        if (!HasComponent<BaseComponent>(entity))
        {
            continue;
        }

        const auto& base = GetComponent<BaseComponent>(entity);
        if (base.scene_name == scene_name)
        {
            result.push_back(entity);
        }
    }

    return result;
}

nlohmann::json Coordinator::SerializeEntity(Entity e)
{
    nlohmann::json j;

    if (!EntityExists(e))
    {
        j["error"] = "entity not found";
        return j;
    }

    // BaseComponent as an example of serialization
    if (HasComponent<BaseComponent>(e))
    {
        const auto &base = GetComponent<BaseComponent>(e);
        j["BaseComponent"] = {
            {"active", base.active},
            {"entity_name", base.entity_name},
            {"scene_name", base.scene_name},
            {"tag", base.tag},
            {"sub_tag", base.sub_tag}};
    }

    if (HasComponent<TransformComponent>(e))
    {
        const auto &transform = GetComponent<TransformComponent>(e);
        j["TransformComponent"] = {
            {"position", SerializeVec2(transform.position)},
            {"scale", SerializeVec2(transform.scale)},
            {"rotation", transform.rotation}
        };
    }

    if (HasComponent<SpriteComponent>(e))
    {
        const auto &sprite = GetComponent<SpriteComponent>(e);
        j["SpriteComponent"] = {
            {"texture_path", sprite.texturePath},
            {"src_rect", SerializeRect(sprite.srcRect)},
            {"dest_rect", SerializeFRect(sprite.destRect)},
            {"flip", static_cast<int>(sprite.flip)}
        };
    }

    if (HasComponent<TextComponent>(e))
    {
        const auto &text = GetComponent<TextComponent>(e);
        j["TextComponent"] = {
            {"text", text.text},
            {"color", SerializeColor(text.color)},
            {"position", SerializeVec2(text.position)},
            {"alignment", static_cast<int>(text.alignment)},
            {"font_path", text.fontPath},
            {"font_size", text.fontSize}
        };
    }

    if (HasComponent<AudioComponent>(e))
    {
        const auto &audio = GetComponent<AudioComponent>(e);
        j["AudioComponent"] = {
            {"audio_path", audio.audioPath},
            {"type", SerializeAudioType(audio.type)},
            {"is_playing", audio.isPlaying},
            {"loop", audio.loop},
            {"channel", audio.channel}
        };
    }

    if (HasComponent<RigidBodyComponent>(e))
    {
        const auto &rigidBody = GetComponent<RigidBodyComponent>(e);
        j["RigidBodyComponent"] = {
            {"collider", SerializeFRect(rigidBody.collider)},
            {"velocity", SerializeVec2(rigidBody.velocity)},
            {"acceleration", SerializeVec2(rigidBody.acceleration)},
            {"mass", rigidBody.mass},
            {"is_static", rigidBody.isStatic},
            {"use_gravity", rigidBody.useGravity}
        };
    }

    if (HasComponent<AnimationComponent>(e))
    {
        const auto &animation = GetComponent<AnimationComponent>(e);
        j["AnimationComponent"] = {
            {"current_frame", animation.currentFrame},
            {"frame_count", animation.frameCount},
            {"frame_width", animation.frameWidth},
            {"frame_height", animation.frameHeight},
            {"animation_speed", animation.animationSpeed},
            {"elapsed_time", animation.elapsedTime},
            {"loop", animation.loop},
            {"is_playing", animation.isPlaying}
        };
    }

    if (HasComponent<SolidColorBackgroundComponent>(e))
    {
        const auto &background = GetComponent<SolidColorBackgroundComponent>(e);
        j["SolidColorBackgroundComponent"] = {
            {"color", SerializeColor(background.color)}
        };
    }

    if (HasComponent<ImageBackgroundComponent>(e))
    {
        const auto &background = GetComponent<ImageBackgroundComponent>(e);
        j["ImageBackgroundComponent"] = {
            {"texture_path", background.texturePath},
            {"width", background.width},
            {"height", background.height}
        };
    }

    if (HasComponent<TileBackgroundComponent>(e))
    {
        const auto &background = GetComponent<TileBackgroundComponent>(e);
        j["TileBackgroundComponent"] = {
            {"texture_path", background.texturePath},
            {"tile_texture_width", background.tileTextureWidth},
            {"tile_texture_height", background.tileTextureHeight},
            {"tile_width", background.tileWidth},
            {"tile_height", background.tileHeight},
            {"map_width", background.mapWidth},
            {"map_height", background.mapHeight},
            {"tiles", background.tiles}
        };
    }

    return j;
}

nlohmann::json Coordinator::SerializeScene(const std::string& scene_name)
{
    nlohmann::json scene = {
        {"scene_name", scene_name},
        {"entities", nlohmann::json::array()}
    };

    std::vector<Entity> entities = GetEntitiesByScene(scene_name);
    std::sort(
        entities.begin(),
        entities.end(),
        [this](const Entity lhs, const Entity rhs)
        {
            const auto& leftBase = GetComponent<BaseComponent>(lhs);
            const auto& rightBase = GetComponent<BaseComponent>(rhs);
            return leftBase.entity_name < rightBase.entity_name;
        });

    for (const Entity entity : entities)
    {
        scene["entities"].push_back(SerializeEntity(entity));
    }

    return scene;
}

Entity Coordinator::DeserializeEntity(const nlohmann::json &j)
{
    if (!j.contains("BaseComponent"))
        throw std::runtime_error("Invalid JSON: missing BaseComponent");

    const auto &base = j["BaseComponent"];

    Entity e = CreateEntity(
        base.value("entity_name", "Unnamed"),
        base.value("scene_name", "Default"),
        base.value("tag", "Untagged"),
        base.value("sub_tag", ""));

    // Assign values to the component
    if (HasComponent<BaseComponent>(e))
    {
        auto &comp = GetComponent<BaseComponent>(e);
        comp.active = base.value("active", true);
        comp.entity_name = base.value("entity_name", "");
        comp.scene_name = base.value("scene_name", "");
        comp.tag = base.value("tag", "");
        comp.sub_tag = base.value("sub_tag", "");
    }

    if (j.contains("TransformComponent"))
    {
        const auto &transform = j["TransformComponent"];
        AddComponent(
            e,
            TransformComponent{
                DeserializeVec2(transform.value("position", nlohmann::json::object())),
                DeserializeVec2(transform.value("scale", nlohmann::json::object()), Vec2(1.0f, 1.0f)),
                transform.value("rotation", 0.0f)
            });
    }

    if (j.contains("SpriteComponent"))
    {
        const auto &sprite = j["SpriteComponent"];
        const std::string texturePath = sprite.value("texture_path", "");
        SDL_Texture *texture = texturePath.empty() ? nullptr : TextureManager::LoadTexture(texturePath);

        AddComponent(
            e,
            SpriteComponent{
                texture,
                DeserializeRect(sprite.value("src_rect", nlohmann::json::object())),
                DeserializeFRect(sprite.value("dest_rect", nlohmann::json::object())),
                static_cast<SDL_RendererFlip>(sprite.value("flip", static_cast<int>(SDL_FLIP_NONE))),
                texturePath
            });
    }

    if (j.contains("TextComponent"))
    {
        const auto &text = j["TextComponent"];
        const std::string fontPath = text.value("font_path", "");
        const int fontSize = text.value("font_size", 0);
        TTF_Font *font = (fontPath.empty() || fontSize <= 0) ? nullptr : FontManager::GetFont(fontPath, fontSize);

        AddComponent(
            e,
            TextComponent{
                text.value("text", ""),
                DeserializeColor(text.value("color", nlohmann::json::object())),
                font,
                DeserializeVec2(text.value("position", nlohmann::json::object())),
                nullptr,
                true,
                static_cast<Side>(text.value("alignment", static_cast<int>(Side::LEFT))),
                fontPath,
                fontSize
            });
    }

    if (j.contains("AudioComponent"))
    {
        const auto &audio = j["AudioComponent"];
        AddComponent(
            e,
            AudioComponent{
                audio.value("audio_path", ""),
                DeserializeAudioType(audio.value("type", std::string("sfx"))),
                audio.value("is_playing", false),
                audio.value("loop", false),
                audio.value("channel", -1)
            });
    }

    if (j.contains("RigidBodyComponent"))
    {
        const auto &rigidBody = j["RigidBodyComponent"];
        AddComponent(
            e,
            RigidBodyComponent{
                DeserializeFRect(rigidBody.value("collider", nlohmann::json::object())),
                DeserializeVec2(rigidBody.value("velocity", nlohmann::json::object())),
                DeserializeVec2(rigidBody.value("acceleration", nlohmann::json::object())),
                rigidBody.value("mass", 1.0f),
                rigidBody.value("is_static", false),
                rigidBody.value("use_gravity", true),
                nullptr
            });
    }

    if (j.contains("AnimationComponent"))
    {
        const auto &animation = j["AnimationComponent"];
        AddComponent(
            e,
            AnimationComponent{
                animation.value("current_frame", 0),
                animation.value("frame_count", 0),
                animation.value("frame_width", 0),
                animation.value("frame_height", 0),
                animation.value("animation_speed", 0),
                animation.value("elapsed_time", 0),
                animation.value("loop", false),
                animation.value("is_playing", false)
            });
    }

    if (j.contains("SolidColorBackgroundComponent"))
    {
        const auto &background = j["SolidColorBackgroundComponent"];
        AddComponent(
            e,
            SolidColorBackgroundComponent{
                DeserializeColor(background.value("color", nlohmann::json::object()))
            });
    }

    if (j.contains("ImageBackgroundComponent"))
    {
        const auto &background = j["ImageBackgroundComponent"];
        const std::string texturePath = background.value("texture_path", "");
        SDL_Texture *texture = texturePath.empty() ? nullptr : TextureManager::LoadTexture(texturePath);

        AddComponent(
            e,
            ImageBackgroundComponent{
                texture,
                background.value("width", 0),
                background.value("height", 0),
                texturePath
            });
    }

    if (j.contains("TileBackgroundComponent"))
    {
        const auto &background = j["TileBackgroundComponent"];
        const std::string texturePath = background.value("texture_path", "");
        SDL_Texture *texture = texturePath.empty() ? nullptr : TextureManager::LoadTexture(texturePath);

        AddComponent(
            e,
            TileBackgroundComponent{
                texture,
                background.value("tile_texture_width", 0),
                background.value("tile_texture_height", 0),
                background.value("tile_width", 0),
                background.value("tile_height", 0),
                background.value("map_width", 0),
                background.value("map_height", 0),
                background.value("tiles", std::vector<int>{}),
                texturePath
            });
    }

    return e;
}

std::vector<Entity> Coordinator::DeserializeScene(
    const nlohmann::json& j,
    const std::string& override_scene_name,
    const bool clear_existing_scene)
{
    if (!j.is_object() || !j.contains("entities") || !j["entities"].is_array())
    {
        throw std::runtime_error("Invalid scene JSON: missing entities array");
    }

    const std::string targetSceneName = ResolveSceneName(j, override_scene_name);
    if (clear_existing_scene && !targetSceneName.empty())
    {
        // Clear first so imported entities can safely reuse the same scene name
        // without leaving stale data behind when iterating in an editor workflow.
        for (const Entity entity : GetEntitiesByScene(targetSceneName))
        {
            DestroyEntity(entity);
        }
    }

    std::vector<Entity> createdEntities;
    createdEntities.reserve(j["entities"].size());

    for (const auto& entityJson : j["entities"])
    {
        Entity entity = DeserializeEntity(entityJson);

        if (!targetSceneName.empty() && HasComponent<BaseComponent>(entity))
        {
            auto& base = GetComponent<BaseComponent>(entity);
            base.scene_name = targetSceneName;
        }

        createdEntities.push_back(entity);
    }

    return createdEntities;
}

bool Coordinator::SaveSceneToFile(const std::string& scene_name, const std::string& path)
{
    std::ofstream output(path);
    if (!output.is_open())
    {
        return false;
    }

    output << SerializeScene(scene_name).dump(4);
    return true;
}

std::vector<Entity> Coordinator::LoadSceneFromFile(
    const std::string& path,
    const std::string& override_scene_name,
    const bool clear_existing_scene)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open scene file: " + path);
    }

    nlohmann::json sceneJson;
    input >> sceneJson;
    return DeserializeScene(sceneJson, override_scene_name, clear_existing_scene);
}

std::vector<std::string> Coordinator::GetComponentsOfEntity(Entity entity) const
{
    std::vector<std::string> result;
    for (auto &[typeName, array] : mComponentManager->GetAllComponentArrays())
    {
        if (array->HasData(entity))
        {
            result.push_back(typeName.name());
        }
    }
    return result;
}
