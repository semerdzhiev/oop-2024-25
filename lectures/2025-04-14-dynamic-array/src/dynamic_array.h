#pragma once

#include <stdexcept>
#include <iosfwd>

namespace examples {

class dynamic_array {
    int* m_data;
    size_t m_allocated;

private:
    static int* copy_array(int* arr, size_t size);

public:
    dynamic_array();
    dynamic_array(size_t size);
    ~dynamic_array();

    dynamic_array(dynamic_array const&);
    dynamic_array& operator=(dynamic_array const&);

    int& at(size_t index);
    const int& at(size_t index) const;

    void swap(dynamic_array& other) noexcept;

    size_t size() const noexcept
    {
        return m_allocated;
    }

    bool empty() const noexcept
    {
        return m_allocated == 0;
    }

    int& operator[] (size_t index) noexcept
    {
        return m_data[index];
    }

    const int& operator[] (size_t index) const noexcept
    {
        return m_data[index];
    }

    bool operator< (const dynamic_array& other) const noexcept;

    bool operator==(const dynamic_array& other) const noexcept;

    bool operator!=(const dynamic_array& other) const noexcept
    {
        return !(*this == other);
    }

    friend std::istream& operator>>(std::istream& is, dynamic_array& arr);
    friend std::ostream& operator<<(std::ostream& os, const dynamic_array& arr);
};

} // namespace fmi
