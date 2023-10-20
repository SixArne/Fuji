#include <string_view>
#include <GLFW/glfw3.h>
#include <memory>

import Logger;
import Window;

int main() {
    Debug::Log::Init();

    WindowProperties windowProperties {
        .width{800},
        .height{600},
        .title{"Engine testing window"}
    };

    std::unique_ptr<Window> window = std::make_unique<Window>(windowProperties);
    window->Create();

    while(window->IsRunning()) {
        window->Update();
    }

    return 0;
}
