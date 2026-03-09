#pragma once

#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <cassert>
#include <typeindex>
#include "Core/System/System.h"
#include "Core/Entity/Entity.h"

class SystemManager {
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        const auto typeKey = std::type_index(typeid(T));
        assert(mSystems.find(typeKey) == mSystems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        mSystems.insert({typeKey, system});
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const auto typeKey = std::type_index(typeid(T));
        assert(mSystems.find(typeKey) != mSystems.end() && "System used before registered.");

        // Set the signature for this system
        mSignatures[typeKey] = signature;
    }

    void EntityDestroyed(const Entity entity) const {
        // Erase a destroyed entity from all system lists
        // mEntities is a set so no check needed
        for (auto const &pair: mSystems) {
            auto const &system = pair.second;
            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(const Entity entity, const Signature entitySignature) {
        // Notify each system that an entity's signature changed
        for (auto const &pair: mSystems) {
            auto const &typeKey = pair.first;
            auto const &system = pair.second;
            auto signatureIt = mSignatures.find(typeKey);
            if (signatureIt == mSignatures.end()) {
                continue;
            }
            auto const &systemSignature = signatureIt->second;

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature) {
                system->mEntities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else {
                system->mEntities.erase(entity);
            }
        }
    }

    template<typename T>
    std::shared_ptr<T> GetSystem() {
        const auto typeKey = std::type_index(typeid(T));
        auto it = mSystems.find(typeKey);
        if (it == mSystems.end()) {
            return nullptr;
        }
        return std::static_pointer_cast<T>(it->second);
    }

private:
    // Map from a stable type key to a signature
    std::unordered_map<std::type_index, Signature> mSignatures{};

    // Map from a stable type key to a system pointer
    std::unordered_map<std::type_index, std::shared_ptr<System> > mSystems{};
};
