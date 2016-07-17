#ifndef STATEINFO_H
#define STATEINFO_H

#include <vector>
#include <string>

namespace game{

enum class StateInfoFormat{
    BOARD_VALUE = 0,
    HISTORY_VALUE
};

class StateInfo{

    double score_;
    std::string board_;
    std::vector<int> history_;

public:
    StateInfo(const char* board, double score=0);
    StateInfo(const std::string& board, double score=0);
    StateInfo(std::vector<int>& history, double score=0);
    ~StateInfo();

    StateInfo(const StateInfo& other);
    StateInfo& operator=(StateInfo other);

    StateInfo(StateInfo&& other);
    StateInfo& operator=(StateInfo&& other);

    inline void setScore(double score)
    { score_ = score; }

    inline double getScore() const
    { return score_;}

    void setHistory(const std::vector<int>& history);

    inline const std::vector<int>& getHistory() const
    { return history_; }

    inline void setBoard(const char* board)
    { board_ = std::move(std::string(board)); }

    inline void setBoard(const std::string& board)
    { board_ = board; }

    inline const std::string& getBoard() const
    { return board_; }

    friend void swap(StateInfo& lhs, StateInfo& rhs);

    //static std::vector<StateInfo>
    //readStateInfoFromFile(const std::string& file, StateInfoFormat format);
};

}

#endif
