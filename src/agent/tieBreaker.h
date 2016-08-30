#ifndef TIE_BREAKER_H
#define TIE_BREAKER_H

#include "../gameDef.h"
#include "util/random.h"

#include <vector>

#include <qDebug>

namespace agent{

class TieBreaker
{

protected:
    double bestVal_;
    double initVal_;
    int bestPos_;
    std::vector<int> arena_;

public:

    TieBreaker()
        :bestVal_(-1), initVal_(-1), bestPos_(-1)
    {}

    TieBreaker(double initVal)
        :bestVal_(initVal), initVal_(initVal), bestPos_(-1)
    {}

    ~TieBreaker()
    {}

    TieBreaker(const TieBreaker& other) = delete;

    TieBreaker& operator=(const TieBreaker& other) = delete;

    void setInitVal(double val)
    {
        initVal_ = val;
        bestVal_ = val;
    }

    void reset()
    {
        bestVal_ = initVal_;
        bestPos_ = -1;
        arena_.clear();
    }

    bool approxEqual(double f1, double f2)
    {
        double diff = ((f1 - f2)>0)?(f1 - f2):((f1 - f2)*-1);
        return diff < game::EPSILON;
    }

    inline int getBestPos() const
    {
        if(arena_.size() > 1){
            int idx = util::Random::uniformInt(0, (int)arena_.size()-1);
            return arena_[idx];
        }
        return bestPos_;
    }

    void add(int pos, double val)
    {
        if(arena_.empty()){
            bestVal_ = val;
            bestPos_ = pos;
            arena_.push_back(pos);
        }
        else if(approxEqual(bestVal_, val)){
            arena_.push_back(pos);
        }
        else if(val > bestVal_){
            bestVal_ = val;
            bestPos_ = pos;
            arena_.clear();
            arena_.push_back(pos);
        }
    }

    void add(int pos, double val, char mark)
    {
        if(arena_.empty()){
            bestVal_ = val;
            bestPos_ = pos;
            arena_.push_back(pos);
        }
        else if(approxEqual(bestVal_, val)){
            arena_.push_back(pos);
        }
        else if(
            (mark == game::MARK_X && val > bestVal_) ||
            (mark == game::MARK_O && val < bestVal_) )
        {
            bestVal_ = val;
            bestPos_ = pos;
            arena_.clear();
            arena_.push_back(pos);
        }

        //qDebug() << "bestPos: " << bestPos_ << ", bestVal: " << bestVal_ << ", arena size: " << arena_.size();
    }


};



}//namespace agent
#endif
