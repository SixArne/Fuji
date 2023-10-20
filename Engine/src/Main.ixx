// For some reason this also needs to be included?
// but not in visual studio?
#include <string_view>

// including this will fix the issue
//#include <memory>

import Logger;

int main() {
    Debug::Log::Init();

    // You need to include memory for this to work
    LogMessage("Hello {}", "world");

    // This will work without including memory.
    // LogMessageWithHop("Hello {}", "world");

    return 0;
}
