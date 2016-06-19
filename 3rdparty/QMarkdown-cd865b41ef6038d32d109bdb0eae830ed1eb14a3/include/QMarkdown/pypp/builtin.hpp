#ifndef PYPP_BUILTIN_HPP
#define PYPP_BUILTIN_HPP

#include <algorithm>

#include <QList>

namespace pypp {

template <typename T, typename Func>
inline T map(const Func &func, const T &in)
{
    T result;
    for ( const auto &value : in ) {
        result.push_back(func(value));
    }
    return result;
}

template <typename T>
inline T reversed(const T &in)
{
    T result;
    result.reserve(in.size()); // reserve is new in Qt 4.7
    std::reverse_copy(in.begin(), in.end(), std::back_inserter(result));
    return result;
}

template <typename T>
inline T sorted(const T &in, bool reverse=false)
{
    T result = in;
    std::sort(result.begin(), result.end());
    if ( reverse ) {
        std::reverse(result.begin(), result.end());
    }
    return result;
}

template <typename T, typename Comp>
inline T sorted(const T &in, Comp comp)
{
    T result = in;
    std::sort(result.begin(), result.end(), comp);
    return result;
}

}

#endif // PYPP_BUILTIN_HPP

