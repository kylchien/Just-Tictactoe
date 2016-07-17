#ifndef RUNTIMEEX_H
#define RUNTIMEEX_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

namespace util{


class RuntimeException : public std::runtime_error
{
    std::string msg_;
public:
    RuntimeException(const std::string &arg, const char *file, int line):std::runtime_error(arg)
    {
        std::ostringstream o;
        o << "exception thrown: \"" << arg << "\"" << ", in " << file << ":" << line;
        msg_ = o.str();
    }

    ~RuntimeException() throw(){}
    const char *what() const throw()
    { return msg_.c_str(); }

};

}

#define THROW_RUNTIME_EX(arg) throw util::RuntimeException(arg, __FILE__, __LINE__);

#endif
