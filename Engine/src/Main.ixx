#include <string_view>
//#include <memory> // including this will fix the issue

import Logger;

int main() {
    Debug::Log::Init();

    LogMessage("Hello {}", "world");
    // LogMessageWithHop("Hello {}", "world");

    return 0;
}
