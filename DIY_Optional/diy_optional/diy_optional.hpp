#pragma once

namespace diy
{

template <class T>
class optional
{
public:
    optional() {}

    template <class U = T>
    optional(U&& value) : m_value(std::forward<T&&>(value)) {}

    constexpr const T& value() const& noexcept
    {
        return m_value;
    }

    constexpr T& value() & noexcept
    {
        return m_value;
    }

    template <class U>
    constexpr T valueOr(U&& defaultValue) const&
    {
        return m_value != nullptr ? **this : static_cast<T>(std::forward<U>(defaultValue));
    }

    template <class U>
    constexpr T valueOr(U&& defaultValue) &&
    {
        return m_value != nullptr ? std::move(**this) : static_cast<T>(std::forward<U>(defaultValue));
    }

    optional& operator=(const T& value) noexcept
    {
        m_value = value;

        return *this;
    }
    
    constexpr T& operator*() & noexcept
    {
        return m_value;
    }
    constexpr const T& operator*() const& noexcept
    {
        return m_value;
    }

private:
    T m_value;

private:
    optional(const optional& other) {}
    optional(optional&& other) {}
    optional& operator= (const optional& other) {}

}; // class optional

} // namespace diy
