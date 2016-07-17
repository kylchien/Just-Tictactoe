#include "stateInfo.h"
#include "gameDef.h"
#include "io/simpleReader.h"

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

namespace game{


void swap(StateInfo& lhs, StateInfo& rhs)
{
    std::swap(lhs.score_, rhs.score_);
    std::swap(lhs.board_, rhs.board_);
    std::swap(lhs.history_, rhs.history_);
}


StateInfo::StateInfo(const char* board, double score)
    :score_(score), board_(board)
{}

StateInfo::StateInfo(const std::string& board, double score)
    :score_(score), board_(board)
{}

StateInfo::StateInfo(std::vector<int>& history, double score)
    :score_(score), board_("")
{
    setHistory(history);
}

StateInfo::~StateInfo()
{
    history_.clear();
}


StateInfo::StateInfo(const StateInfo& other)
    :score_(0), board_("")
{
    score_ = other.score_;
    board_ = other.board_;
    setHistory(other.history_ );
}


StateInfo& StateInfo::operator=(StateInfo other)
{
    swap(*this, other);
    return *this;
}


StateInfo::StateInfo(StateInfo&& other)
    :score_(0), board_("")
{
    history_.clear();
    swap(*this, other);
}


StateInfo& StateInfo::operator=(StateInfo&& other)
{
    if(this != &other){
        history_.clear();
        swap(*this, other);
    }
    return *this;
}


void StateInfo::setHistory(const std::vector<int>& history)
{  std::copy(history.begin(), history.end(), history_.begin()); }


/*
std::vector<StateInfo>
StateInfo::readStateInfoFromFile(const std::string& file, StateInfoFormat format)
{
    using std::vector;
    using std::string;

    vector<StateInfo> vec;
    auto strVec = io::SimpleReader::readAll(file);
    for(string& s:strVec){
        if(format == StateInfoFormat::BOARD_VALUE){
            cout << s << endl;
            cout << s.size() << endl;
            int valStrLen = s.size() - (BOARD_SIZE+1);
            double val = std::stod(s.substr(BOARD_SIZE+1, valStrLen));
            vec.emplace_back( StateInfo(
                s.substr(0,BOARD_SIZE), val));
        }
    }
    return vec;
}*/



}//namespace
