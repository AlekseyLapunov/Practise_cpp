#include <string>
#include <utility>

class HeavyToCopy {
public:
    HeavyToCopy() {}

    HeavyToCopy(const std::string& payload) {
        m_body = payload;
    }

    HeavyToCopy(const HeavyToCopy& other) {
        m_body = other.m_body;
    }

    HeavyToCopy& operator=(const HeavyToCopy& other) {
        m_body = other.m_body;
        return *this;
    }

    std::string m_body;
};

class HeavyToCopy_Move {
public:
    HeavyToCopy_Move() {}

    HeavyToCopy_Move(const std::string& payload) {
        m_body = payload;
    }

    HeavyToCopy_Move(const HeavyToCopy_Move& other) {
        m_body = other.m_body;
    }

    HeavyToCopy_Move& operator=(const HeavyToCopy_Move& other) {
        m_body = other.m_body;
        return *this;
    }

    HeavyToCopy_Move(HeavyToCopy_Move&& other) noexcept {
        m_body = std::move(other.m_body);
    }

    HeavyToCopy_Move& operator=(HeavyToCopy_Move&& other) noexcept {
        m_body = std::move(other.m_body);
        return *this;
    }

    std::string m_body;
};