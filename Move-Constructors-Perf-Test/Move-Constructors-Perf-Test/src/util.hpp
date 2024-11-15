#pragma once

#include <sstream>

namespace util {
    std::string randomString(size_t len) {
        std::stringstream ss;
        for (int i = 0; i < len; i++) {
            ss << (char)(rand() % ('~' - '!') + '!');
        }
        return ss.str();
    }
}