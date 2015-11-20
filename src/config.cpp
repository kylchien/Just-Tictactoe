#include "config.h"
#include <QDebug>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Config::Config()
{

}

Config::~Config()
{

}

void Config::load()
{
    try{
        //QCoreApplication::applicationDirPath()
        QFile loadFile(":/game.config");
        if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning("Couldn't open save file.");
        }
        QString content = loadFile.readAll();
        loadFile.close();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(content.toUtf8()));
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << jsonObj["playerX"].toString();

    }
    catch(...){
        qFatal("unknown exception caught!");
    }
}
