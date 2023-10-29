import application;
import logger;
import window;
import vulkan.application;

int main() {
    Debug::Log::Init();

    WindowProperties windowProperties {
        .width=800,
        .height=600,
        .title{"Engine testing window"}
    };

    Debug::Log::Trace("Creating window...");
    std::unique_ptr<Application> app = std::make_unique<Application>(windowProperties);
    app->Start();

    auto vulkanApp = std::make_unique<Vulkan::Application>();
    vulkanApp->Init();

    return 0;
}
