#include "Core/Core.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/GameScene.h"

int main(int argc, char* argv[])
{
    Core::Init("config.json", DEFAULT_GAME_TITLE);
    if (!Core::is_game_on)
        return 1;

    Core::GetSceneManager().Add(TITLE_SCENE, std::make_unique<MainMenuScene>());
    Core::GetSceneManager().Add(ROUND_SCENE, std::make_unique<GameScene>());
    Core::GetSceneManager().Init(TITLE_SCENE);

    Core::Run();
    Core::CleanUp();

    return 0;
}
