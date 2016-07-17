#ifndef GAMEDEF_H
#define GAMEDEF_H

#include <QString>

namespace game{

static constexpr int BOARD_SIZE = 9;
static constexpr int INVALID = -1;

static constexpr char MARK_X = 'x';
static constexpr char MARK_O = 'o';
static constexpr char MARK_E = '~';


enum class GameMode{HH = 0, HM = 1, MH = 2, MM = 3};

static QString GAME_CONFIG_PATH = "C:\\Project\\Just-Tictactoe\\game.config";
//static QString GAME_CONFIG_PATH = "S:\\data\\Just-Tictactoe\\game.config";

static QString QLEARNING_CONFIG_PATH = "C:\\Project\\Just-Tictactoe\\qLearning.config";
//static QString QLEARNING_CONFIG_PATH = "S:\\data\\Just-Tictactoe\\qLearning.config";


static QString NUM_OF_GAMES = "num_of_games";
static QString PLAYER_X = "player_x";
static QString PLAYER_O = "player_o";
static QString SAVE_GAME_MODE = "save_game_mode";
static QString SAVE_DATA_PATH = "save_data_path";
static QString SAVE_BATCH_SIZE = "save_batch_size";


static QString QLEARNING_TRAINING_MODE = "training_mode";
static QString QLEARNING_LOAD_TRAINING_DATA_ON_START = "load_training_data_on_start";
static QString QLEARNING_TRAINING_DATA_PATH = "training_data_path";
static QString QLEARNING_SAVE_TRAINING_DATA = "save_training_data";

}

#endif // GAMEDEF_H

