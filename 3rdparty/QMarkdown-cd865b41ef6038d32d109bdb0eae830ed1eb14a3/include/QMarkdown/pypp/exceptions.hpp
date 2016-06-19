#ifndef PYPP_EXCEPTIONS_HPP
#define PYPP_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace pypp {

class Exception : public std::exception
{
public:
    Exception() :
        msg()
    {}
    Exception(const std::string &msg) :
        msg(msg)
    {}

    const char *what() const noexcept
    {
        return this->msg.c_str();
    }

protected:
    std::string msg;

};

class StandardError : public Exception
{
public:
    using Exception::Exception;
};

class LookupError : public StandardError
{
public:
    using StandardError::StandardError;
};

class IndexError : public LookupError
{
public:
    using LookupError::LookupError;
};

class KeyError : public LookupError
{
public:
    using LookupError::LookupError;
};

class TypeError : public StandardError
{
public:
    using StandardError::StandardError;
};

class ValueError : public StandardError
{
public:
    using StandardError::StandardError;
};

} // namespace pypp

#endif // EXCEPTIONS_HPP

