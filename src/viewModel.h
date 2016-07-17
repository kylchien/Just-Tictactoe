#ifndef VIEW_H
#define VIEW_H

#include "engine.h"

#include <memory>

#include <QObject>
#include <QVariant>

namespace game{

class ViewModel final : public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<Engine> engine_;
    QVariantList connectedBlocks_;
    QVariantList loadedBoard_;
    static bool isInit;
    void notifyPlayers();

public:
    ViewModel();
    ~ViewModel();

    ViewModel(const ViewModel& src) = delete;
    ViewModel& operator= (const ViewModel& src) = delete;

    Q_INVOKABLE void restart();
    Q_INVOKABLE void createPlayers();
    Q_INVOKABLE void setGameMode(int mode);
    Q_INVOKABLE bool isHumanTurn() const;
    Q_INVOKABLE QChar getCurrentTurn() const;
    Q_INVOKABLE void loadBoard(std::string boardInfo);

    //easy for testing
    std::shared_ptr<Engine> getEngine()
    { return engine_; }

signals:
    void changingBoard(int pos, char mark);
    void loadingBoard(QVariantList list);
    void sendingfinishingMsg(QString message);
    void markingConnectingBlocks(QVariantList list);
    void notfyingPlayer(char mark, const char* state);

public slots:
    void updateBoard(int pos);


};

}//namespace
#endif
