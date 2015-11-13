#ifndef MINIMAX_H
#define MINIMAX_H

#include <vector>
#include "../player.h"

namespace ai{


class Minimax :public game::Player
{
public:
    explicit Minimax(char mark, bool randomForTie = true);
    ~Minimax();

    int move(const char* state);

protected:
    static constexpr float INFI = 9999;
    static constexpr float WIN = 1;
    static constexpr float LOSE = -1;
    static constexpr float DRAW = 0;
    static constexpr int MAX_DEPTH = 9;
    static constexpr float EPSILON = 0.001;
    static constexpr float DEPTH_ADJ = 0.01;

    bool random_;
    std::vector<int> tieBreaker_;

    float minimax(const char* state, int depth, bool isMax);


};

}
#endif // MINIMAX_H
