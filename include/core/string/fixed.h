// Copyright (C) 2018, 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include "core/utility/common.h"
#include "core/utility/span.h"

namespace core {

struct fixed_string_error : public std::runtime_error
{
    using rt = std::runtime_error;
    using rt::rt;
};

template<size_t N>
class fixed_string
{
public:
    using Self = fixed_string<N>;
    using Array = std::array<char,N>;
    constexpr static size_t Size = N;

    fixed_string()
	: m_arr()
    { }
    
    fixed_string(string_view view)
    {
	if (view.size() > N)
	    throw std::runtime_error("string to long to fit into fixed string");
	std::copy(view.begin(), view.begin() + view.size(), m_arr.begin());
	std::fill(m_arr.begin() + view.size(), m_arr.end(), 0);
    }

    fixed_string(const Array& arr)
    {
	std::copy(arr.begin(), arr.end(), m_arr.begin());
    }

    operator string() const { return string(begin(), end()); }

    bool operator==(const Self& other) const
    { return m_arr == other.m_arr; }

    bool operator==(const Array& other) const
    { return m_arr == other; }

    bool operator==(const string& other) const
    { return !strncmp(begin(), other.c_str(), size()); }

    bool operator!=(const Self& other) const
    { return m_arr != other.m_arr; }

    bool operator!=(const Array& other) const
    { return m_arr != other; }

    bool operator!=(const string& other) const
    { return not (*this == other); }

    bool operator<(const Self& other) const
    { return m_arr < other.m_arr; }

    bool operator<(const Array& other) const
    { return m_arr < other; }

    constexpr size_t size() const { return Size; }
    const char *begin() const { return m_arr.begin(); }
    const char *end() const { return m_arr.end(); }
    std::span<char> span() { return { m_arr.begin(), m_arr.end() }; }
    
    char *begin() { return m_arr.begin(); }
    char *end() { return m_arr.end(); }
    
    char operator[](index_t i) const { return m_arr[i]; }
    char& operator[](index_t i) { return m_arr[i]; }

    template<class Archive>
    void serialize(Archive& archive)
    { archive(m_arr); }
    
private:
    std::array<char,Size> m_arr;
};

template<size_t N>
std::ostream& operator<<(std::ostream& os, const fixed_string<N>& str)
{
    return os << string(str);
}

}; // end ns core
