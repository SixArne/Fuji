module;

#include <memory>
#include <chrono>

export module Application;

import Window;
import Logger;


export class Application {
public:
    explicit Application(const WindowProperties& windowProperties);
    ~Application() = default;

    void Start();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

private:
    std::unique_ptr<Window> m_Window;

    float m_DeltaTime{};
};

Application::Application(const WindowProperties &windowProperties)
    : m_Window{std::make_unique<Window>(windowProperties)}
{
    m_Window->Create();
}

void Application::Start() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    const float fixedTimeStepSec{0.02f};
    const float desiredFPS{144.f};
    const int frameTimeMS{static_cast<int>(std::roundf(1000 / desiredFPS))};
    float lag = 0.0f;

    while (m_Window->IsRunning()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime).count();
        // TODO: Fix irregular framerate.

        lastTime = currentTime;
        lag += m_DeltaTime;

        while (lag >= fixedTimeStepSec) {
            lag -= fixedTimeStepSec;
        }

        m_Window->Update();

        const auto nextFrameTime = lastTime + std::chrono::milliseconds(frameTimeMS);
        if (currentTime < nextFrameTime) // update when current frame time is actually smaller than desired frame time.
        {
            const auto sleepTime = nextFrameTime - currentTime;
            std::this_thread::sleep_for(sleepTime);
        }
        lastTime = nextFrameTime;
    }
}