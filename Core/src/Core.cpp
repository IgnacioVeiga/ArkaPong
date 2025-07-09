#include "Core/Core.h"

namespace Core {
    Coordinator& GetCoordinator() {
        static Coordinator instance;
        return instance;
    }

    SceneManager& GetSceneManager() {
        static SceneManager instance;
        return instance;
    }

    Window& GetWindow() {
        static Window instance;
        return instance;
    }
}
