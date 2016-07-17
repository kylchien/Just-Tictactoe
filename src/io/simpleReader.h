#ifndef SIMPLE_READER_H
#define SIMPLE_READER_H

#include <string>
#include <vector>

namespace io{

using Tuple_board_value = std::tuple<std::string, double>;

class SimpleReader{

    SimpleReader();
    ~SimpleReader();

    SimpleReader(const SimpleReader& other) = delete;
    SimpleReader& operator=(const SimpleReader& other) = delete;

public:

    static bool canBeOpen(const std::string& filePath);

    static std::vector<std::string> readAll(const std::string& filePath);

    template <class T>
    static std::vector<T> readData(const std::string& filePath);
};


}//namespace

#endif
