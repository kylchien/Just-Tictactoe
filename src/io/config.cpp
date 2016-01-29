#include "config.h"

#include <stdexcept>

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;
using namespace io;

Config::Config()
{
	QFile loadFile(":/game.config");
	if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		string msg = "cannot open the resource file game.config!!!";
		throw runtime_error(msg);
	}
	QString content = loadFile.readAll();
	loadFile.close();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(content.toUtf8()));
	json_ = jsonDoc.object();
}

Config::~Config(){}

//return all values in string format (hence in game.config please use string as data format)
QString Config::operator[](QString key) const
{
    if(json_.find(key) == json_.end()){
        qWarning() << "entry '" << key << "' is not not found in Config";
		return QString("");
	}
	return json_[key].toString();
}
