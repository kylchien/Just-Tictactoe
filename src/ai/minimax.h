#ifndef MINIMAX_H
#define MINIMAX_H

#include <vector>
#include "../player.h"

namespace ai{


class Minimax :public game::Player
{
public:
    Minimax(char mark, bool randomForTie = true);
    virtual ~Minimax();
    virtual int move(const char* state);
	virtual QString getType() const
	{ return QString("Minimax"); }


protected:

    static constexpr float INFI = 9999;
    static constexpr float WIN = 1;
    static constexpr float LOSE = -1;
    static constexpr float DRAW = 0;
    static constexpr int MAX_DEPTH = 9;
    static constexpr float EPSILON = 0.001;
    static constexpr float DEPTH_ADJ = 0.01;	//enforce no-suicide move
    static constexpr float CENTER_ADJ = 0.005;	//put extra weight on centre

    bool random_;
    std::vector<int> tieBreaker_;

	bool approxEqual(float f1, float f2, float epsilon);
    float minimax(const char* state, int depth, bool isMax);


};

}
#endif // MINIMAX_H
