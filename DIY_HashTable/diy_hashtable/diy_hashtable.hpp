#pragma once

#include <iostream>
#include <array>

namespace diy
{

template <typename T, size_t max, size_t HashFunction(T&& op), bool KeyValidator(T&& op)>
class hash_table
{
public:
    bool _logEnabled = false;
    std::ostream& _logStream = std::cerr;

public:
    hash_table() = default;
    ~hash_table() {}

public:
    bool find(T&& key)
    {
        if (!KeyValidator(std::forward<T&&>(key)))
        {
            log("Input key is not valid");
            return false;
        }

        if (_logEnabled)
            _logStream << className << " Finding key \"" << key << "\"\n";

        for (size_t i = HashFunction(std::forward<T&&>(key)); i < m_data.size(); i++)
        {
            const Entry& entry = m_data[i];

            switch (entry.status)
            {
            case Entry::Status::never_used:
                return false;
            case Entry::Status::tombstone:
                break;
            case Entry::Status::occupied:
                if (entry.key != key)
                    continue;
                if (_logEnabled && entry.key == key)
                    _logStream << className << " Found \"" << key << "\" at " << i << "\n";
                return true;
            default:
                return false;
            }
        }
    }

    bool insert(T&& key)
    {
        if (!KeyValidator(std::forward<T&&>(key)))
        {
            log("Input key is not valid");
            return false;
        }

        if (_logEnabled)
            _logStream << className << " Trying to insert key \"" << key << "\"\n";

        if (find(std::forward<T&&>(key)))
        {
            log("This key is already in the table");
            return false;
        }

        for (size_t i = HashFunction(std::forward<T&&>(key)); i < m_data.size(); i++)
        {
            const Entry& entry = m_data[i];

            switch (entry.status)
            {
            case Entry::Status::never_used:
            case Entry::Status::tombstone:
                m_data[i].key = key;
                m_data[i].status = Entry::Status::occupied;

                if (_logEnabled)
                    _logStream << className << " Inserted \"" << key << "\" at " << i << "\n";
                return true;
            case Entry::Status::occupied:
                continue;
            default:
                return false;
            }
        }

        return false;
    }

    bool remove(T&& key)
    {
        if (!KeyValidator(std::forward<T&&>(key)))
        {
            log("Input key is not valid");
            return false;
        }

        if (_logEnabled)
            _logStream << className << " Trying to remove key \"" << key << "\"\n";

        if (!find(std::forward<T&&>(key)))
        {
            log("This key is not in the table");
            return false;
        }

        for (size_t i = HashFunction(std::forward<T&&>(key)); i < m_data.size(); i++)
        {
            const Entry& entry = m_data[i];

            switch (entry.status)
            {
            case Entry::Status::never_used:
            case Entry::Status::tombstone:
                continue;
            case Entry::Status::occupied:
                if (entry.key == key)
                {
                    m_data[i].status = Entry::Status::tombstone;
                    if (_logEnabled)
                        _logStream << className << " Deleted \"" << key << "\" at " << i << "\n";
                    return true;
                }
                continue;
            default:
                return false;
            }
        }

        return false;
    }

    void print(std::ostream& ost = std::cout)
    {
        const bool temp = _logEnabled;
        _logEnabled = true;

        log("Printing all table");
        _logStream << "Index\tKey\t\tStatus\n";

        for (size_t i = 0; i < m_data.size(); i++)
        {
            const Entry& entry = m_data[i];
            _logStream << "[" << i << "]\t"
                << entry.key
                << ((entry.key.length() < 8) ? "\t\t" : "\t")
                << (entry.resolve()) << "\n";

        }

        _logEnabled = temp;
    }

private:
    struct Entry
    {
        enum class Status { never_used, tombstone, occupied };

        T key;
        Status status = Status::never_used;

        constexpr std::string resolve() const
        {
            switch (status)
            {
            case Status::never_used:
                return "Never used";
            case Status::tombstone:
                return "Tombstone";
            case Status::occupied:
                return "Occupied";
            default:
                return "Unknown";
            }
        }
    };
    std::array<Entry, max> m_data;

private:
    const std::string& className = "[diy::hash_table]";

    template <typename Output>
    inline void log(const Output& what)
    {
        if (_logEnabled)
            _logStream << className << " " << what << "\n";
    }
}; // class hash_table

} // namespace diy

