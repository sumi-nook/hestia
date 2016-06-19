#ifndef PYPP_SLICE_HPP
#define PYPP_SLICE_HPP

#include <algorithm>
#include <tuple>

#include "./exceptions.hpp"

namespace pypp {

class slice
{
public:
    slice(int stop) :
        start(0), stop(stop)
    {}
    slice(int start, int stop) :
        start(start), stop(stop)
    {}

    template <class T>
    inline T operator ()(const T &obj) const
    {
        int begin, end;
        std::tie(begin, end) = this->normalize(obj);
        if ( begin > end ) {
            return T();
        }

        T result;
        result.reserve(end-begin);
        std::copy(obj.begin()+begin, obj.begin()+end, std::back_inserter(result));
        return result;
    }

    template <class T>
    std::tuple<int, int> normalize(const T &obj) const
    {
        return std::make_tuple(this->normalize(obj, this->start), this->normalize(obj, this->stop));
    }
    template <class T>
    int normalize(const T &obj, int index) const
    {
        if ( index < 0 ) {
            index += obj.size();
        }
        if ( index < 0 ) {
            return 0;
        }
        if ( index >= obj.size() ) {
            return obj.size();
        }
        return index;
    }

private:
    int start;
    int stop;

};

class begin_slice
{
public:
    begin_slice(int start) :
        start(start)
    {}

    template <class T>
    inline T operator ()(const T &obj) const
    {
        int begin = this->normalize(obj, this->start);
        if ( begin >= obj.size() ) {
            return T();
        }

        T result;
        result.reserve(obj.size()-begin);
        std::copy(obj.begin()+begin, obj.end(), std::back_inserter(result));
        return result;
    }

    template <class T>
    int normalize(const T &obj, int index) const
    {
        if ( index < 0 ) {
            index += obj.size();
        }
        if ( index < 0 ) {
            return 0;
        }
        if ( index >= obj.size() ) {
            return obj.size();
        }
        return index;
    }

private:
    int start;
    int stop;

};

} // namespace pypp

#endif // PYPP_SLICE_HPP

