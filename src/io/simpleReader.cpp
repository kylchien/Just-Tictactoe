#include "simpleReader.h"
#include "util/runtimeEx.h"

//debug
#include <iostream>

#include <tuple>
#include <sstream>
#include <typeinfo>
#include <fstream>

using std::cout;
using std::endl;

namespace io{

SimpleReader::SimpleReader()
{}


SimpleReader::~SimpleReader()
{}


bool SimpleReader::canBeOpen(const std::string& filePath)
{
    bool res = false;
    try{
        static std::ifstream ifs;
        ifs.open(filePath.c_str(), std::ifstream::in);
        res = ifs.is_open();
        ifs.close();
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }
    return res;
}

std::vector<std::string> SimpleReader::readAll(const std::string& filePath)
{
    std::vector<std::string> vec;

    try{
        static std::ifstream ifs;
        ifs.open(filePath.c_str(), std::ifstream::in);

        if(ifs.is_open()){
            std::string line;
            while(ifs >> line){
                double d;
                ifs >> d;
                cout << d << endl;
                vec.emplace_back(line);
            }
            ifs.close();
        }
        else{
            std::stringstream ss;
            ss << "Unable to open file:" << filePath;
            THROW_RUNTIME_EX(ss.str());
        }
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }

    return vec;
}

template <class T>
std::vector<T> SimpleReader::readData(const std::string&)
{
    std::stringstream ss;
    ss << "type \"" << typeid(T).name() << "\" is not supported!";
    THROW_RUNTIME_EX(ss.str()); ;
}



template <> std::vector<Tuple_board_value>
SimpleReader::readData(const std::string& filePath)
{
    std::vector<Tuple_board_value> vec;
    try{
        std::ifstream ifs;
        ifs.open(filePath.c_str(), std::ifstream::in);

        if(ifs.is_open()){
            std::string board;
            double val;
            while(ifs >> board){
                ifs >> val;
                vec.emplace_back(std::make_tuple(board, val));
            }
            ifs.close();
        }
        else{
            std::stringstream ss;
            ss << "Unable to open file:" << filePath;
            THROW_RUNTIME_EX(ss.str());
        }
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }
    return vec;
}




}//namespace
