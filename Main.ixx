import Logger;

#include <string_view>  // This must be included for cmake, but in Visual studio it runs without
                        // this line??? Even though cmake uses the msvc compiler

int main() {
    Debug::Log::Init();


    Debug::Log::Trace("[Trace] testing... {}", 123);
    Debug::Log::Debug("[Debug] testing... {}", 123);
    Debug::Log::Warn("[Warn] testing... {}", 123);
    Debug::Log::Error("[Error] testing... {}", 123);
    Debug::Log::Critical("[Critical] testing... {}", 123);

    return 0;
}
