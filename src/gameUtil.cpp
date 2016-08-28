#include "gameUtil.h"
#include "util/runtimeEx.h"
#include "io/config.h"

#include <cstdlib>
#include <cstring>

#include <QDebug>

namespace game{


NextStates::NextStates(char mark, const char* curState)
{
    size_ = 0;
    std::vector<int> tempVec;

    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == MARK_E) {
            tempVec.push_back(i);
            size_++;
        }
    }

    //allocate a long array that contains all possible next-states info
    states_ = (char*)std::calloc(size_, sizeof(char)*(BOARD_SIZE+1) );
    if(states_ == nullptr){
        THROW_RUNTIME_EX("Memory allocation failure!");
    }

    int offset = 0;
    for(std::size_t i = 0; i < size_; ++i){
        char* ptr = (char*)states_ + offset;
        std::memcpy(ptr, curState, sizeof(char)* BOARD_SIZE);

        ptr[tempVec.at(i)] = mark;
        ptr[BOARD_SIZE] = (char)tempVec[i];

        offset += BOARD_SIZE + 1;
    }
}


NextStates::~NextStates()
{ std::free(states_); }


void swap(NextStates& lhs, NextStates& rhs)
{
    std::swap(lhs.size_, rhs.size_);
    std::swap(lhs.states_, rhs.states_);
}

NextStates::NextStates(const NextStates& src)
    :size_(0),states_(nullptr)
{
   size_ = src.size_;
   auto chunkSize = sizeof(char)*(BOARD_SIZE+1);
   states_ = (char*)std::calloc(size_, chunkSize);
   std::memcpy(states_, src.states_, size_ * chunkSize);
}

NextStates& NextStates::operator=(NextStates other)
{
    swap(*this, other);
    return *this;
}

NextStates::NextStates(NextStates&& other)
    :size_(0),states_(nullptr)
{
   swap(*this, other);
}

NextStates& NextStates::operator=(NextStates&& other)
{
    if (this != &other){
        if(states_ != nullptr) free(states_);
        states_ = nullptr;
        swap(*this, other);
    }
    return *this;
}


char* NextStates::at(std::size_t idx)
{
    if(idx >= size_){
        THROW_RUNTIME_EX("idx is out of bound!");
    }

    return (char*)states_ + idx * (BOARD_SIZE+1);
}



char determineTurn(const char* curState)
{
    int count = 0;
    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == MARK_X)
            count++;
        else if(curState[i] == MARK_O)
            count--;
    }
    return (count==0) ? MARK_X : MARK_O;
}


void copyBoard(const char* src, char* tgt)
{
    std::memcpy(tgt, src, sizeof(char)* BOARD_SIZE);
}


void push3(std::vector<int>& vec, int i, int j, int k)
{
    vec.push_back(i);
    vec.push_back(j);
    vec.push_back(k);
}


bool isWon(const char* state)
{
	for(int i=0; i<3; ++i){
        if(state[i] != MARK_E && state[i] == state[i+3] && state[i] == state[i+6])
            return true;
        if(state[3*i] != MARK_E && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2])
            return true;
    }
    if(state[0] != MARK_E && state[0] == state[4] && state[0] == state[8])
        return true;
    if(state[2] != MARK_E && state[2] == state[4] && state[2] == state[6])
        return true;
    return false;
}

bool isWon(const char* state, std::vector<int>& winPos)
{
    for(int i=0; i<3; ++i){
        //column check
        if(state[i] != MARK_E && state[i] == state[i+3] && state[i] == state[i+6]){
            push3(winPos, i, i+3, i+6);
            return true;
        }

        //row check
        if(state[3*i] != MARK_E && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2]){
            push3(winPos, 3*i, 3*i+1, 3*i+2);
            return true;
        }
    }
    //diagonal check
    if(state[0] != MARK_E && state[0] == state[4] && state[0] == state[8]){
        push3(winPos, 0,4,8);
        return true;
    }
    if(state[2] != MARK_E && state[2] == state[4] && state[2] == state[6]){
        push3(winPos, 2,4,6);
        return true;
    }

    return false;
}


bool isWon(const char* state, char mark){
    for(int i=0; i<3; ++i){
        if(state[i] == mark && state[i] == state[i+3] && state[i] == state[i+6])
            return true;
        if(state[3*i] == mark && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2])
            return true;
    }
    if(state[0] == mark && state[0] == state[4] && state[0] == state[8])
        return true;
    if(state[2] == mark && state[2] == state[4] && state[2] == state[6])
        return true;
    return false;
}


bool matchHorizon(const char* state, int i)
{
    return state[3*i]==state[3*i+1] && state[3*i]==state[3*i+2];
}

bool matchVertical(const char* state, int i)
{
    return state[i]==state[i+3] && state[i]==state[i+6];
}

bool matchDiagonal(const char* state, int i)
{
    if(i==0)
        return state[0]==state[4] && state[0]==state[8];
    else
        return state[2]==state[4] && state[2]==state[6];
}

/*
bool isWon(const char* state){
    for(int i=0; i<3; ++i)
        if(matchHorizon(state,i) || matchVertical(state,i))
            return true;
    return (matchDiagonal(state,0) || matchDiagonal(state,1));
}*/


bool isWon(const char* state, int pos)
{
    switch (pos){
        case 0:
            if( (state[0] == state[1] && state[0] == state[2]) ||
                (state[0] == state[3] && state[0] == state[6]) ||
                (state[0] == state[4] && state[0] == state[8]) )
                return true;
            return false;

        case 1:
            if( (state[0] == state[1] && state[0] == state[2]) ||
                (state[1] == state[4] && state[1] == state[7]) )
                return true;
            return false;

        case 2:
            if( (state[0] == state[1] && state[0] == state[2]) ||
                (state[2] == state[5] && state[2] == state[8]) ||
                (state[2] == state[4] && state[2] == state[6]) )
                return true;
            return false;

        case 3:
            if( (state[3] == state[4] && state[3] == state[5]) ||
                (state[0] == state[3] && state[0] == state[6]) )
                return true;
            return false;

        case 4:
            if( (state[3] == state[4] && state[3] == state[5]) ||
                (state[1] == state[4] && state[1] == state[7]) ||
                (state[0] == state[4] && state[0] == state[8]) ||
                (state[2] == state[4] && state[2] == state[6]) )
                return true;
            return false;

        case 5:
            if( (state[2] == state[5] && state[2] == state[8]) ||
                (state[3] == state[4] && state[3] == state[5]) )
                return true;
            return false;

        case 6:
            if( (state[0] == state[3] && state[0] == state[6]) ||
                (state[6] == state[7] && state[6] == state[8]) ||
                (state[2] == state[4] && state[2] == state[6]) )
                return true;
            return false;

        case 7:
            if( (state[1] == state[4] && state[1] == state[7]) ||
                (state[6] == state[7] && state[6] == state[8]) )
                return true;
            return false;

        case 8:
            if( (state[2] == state[5] && state[2] == state[8]) ||
                (state[6] == state[7] && state[6] == state[8]) ||
                (state[0] == state[4] && state[0] == state[8]) )
                return true;
            return false;

        default:
            return false;
    }
}


bool isFull(const char* state)
{
    for(int i=0; i<BOARD_SIZE; ++i)
        if(state[i] == MARK_E)
            return false;
    return true;
}


bool isEqual(const char* lhs, const char* rhs)
{
    for(int idx =0; idx < BOARD_SIZE; ++idx){
        if(lhs[idx] != rhs[idx])
            return false;
    }
    return true;
}


inline void count(const char& mark, int& numX, int& numO, int& numE)
{
    if(mark == MARK_X) numX++;
    if(mark == MARK_O) numO++;
    if(mark == MARK_E) numE++;
}

bool matchCount(
    const char* state,
    int i, int j, int k,
    int countX, int countO, int countE)

{
    int numX =0, numO = 0, numE = 0;
    count(state[i], numX, numO, numE);
    count(state[j], numX, numO, numE);
    count(state[k], numX, numO, numE);
    /*
    qDebug() << "in match count:[" << i << j << k << "]";
    qDebug() << "expectX:" << countX << ", actual:" << numX;
    qDebug() << "expectO:" << countO << ", actual:" << numO;
    qDebug() << "expectE:" << countE << ", actual:" << numE;*/
    return numX == countX && numO == countO && numE == countE;
}

int getPos(const char* state, char mark, int i, int j, int k)
{
    if(state[i] == mark) return i;
    if(state[j] == mark) return j;
    if(state[k] == mark) return k;
    return INVALID;
}

bool hasFork(const char* state, char mark)
{
    int numX=0, numO=2, numE=1;
    if(mark == MARK_X){ numX=2; numO=0;}

    int count = 0;
    for(int i=0; i<3; ++i){
        if(matchCount(state, i, i+3, i+6, numX, numO, numE)){
            count++;
            if(count == 2) return true;
        }
        if(matchCount(state, 3*i, 3*i+1, 3*i+2, numX, numO, numE)){
            count++;
            if(count == 2) return true;
        }

    }
    if(matchCount(state, 0, 4, 8, numX, numO, numE)){
        count++;
        if(count == 2) return true;
    }
    if(matchCount(state, 2, 4, 6, numX, numO, numE)){
        count++;
        if(count == 2) return true;
    }
    return false;
}

void rotateCW90(const char* src, char* target)
{
    target[0] = src[6]; target[1] = src[3]; target[2] = src[0];
    target[3] = src[7]; target[4] = src[4]; target[5] = src[1];
    target[6] = src[8]; target[7] = src[5]; target[8] = src[2];
}

void mirror(const char* src, char* target)
{
//state.at(2) << state.at(1) << state.at(0)
//<< state.at(5) << state.at(4) << state.at(3)
//<< state.at(8) << state.at(7) << state.at(6);

    for(int i=0; i<BOARD_SIZE; ++i){
        if(i%3==0)
            target[i] = src[i+2];
        else if(i%3==2)
            target[i] = src[i-2];
        else
            target[i] = src[i];
    }
}




std::shared_ptr<io::SimpleWriter>
makeWriterFromGameConfig(){
    io::Config config(GAME_CONFIG_PATH);
    config.initialize();

    std::string savePath = config.get<std::string>(SAVE_DATA_PATH);
    int batchSize = config.get<int>(SAVE_BATCH_SIZE);
    return std::make_shared<io::SimpleWriter>(savePath, batchSize);
}


}//namespace
