#include "Core/Core.h"
#include "Components/BrickComponent.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/GameScene.h"
#include "Systems/RoundSystem.h"

int main(int argc, char* argv[])
{
    Core::AddInitCallback([]()
    {
        Core::GetCoordinator().RegisterComponent<BrickComponent>();
        Core::GetCoordinator().RegisterSystem<RoundSystem>()->Init();
    });

    Core::Init("config.json", DEFAULT_GAME_TITLE);
    if (!Core::is_game_on)
        return 1;

    Core::GetSceneManager().Add(TITLE_SCENE, std::make_unique<MainMenuScene>());
    Core::GetSceneManager().Add(ROUND_SCENE, std::make_unique<GameScene>());
    Core::GetSceneManager().Init(TITLE_SCENE);

    Core::Run();

    return 0;
}
