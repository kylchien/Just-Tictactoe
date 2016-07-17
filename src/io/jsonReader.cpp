#include "jsonReader.h"
#include "../util/runtimeEx.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>
#include <iostream>

using std::cout;
using std::endl;

namespace io{

JsonReader::JsonReader(const QString& filePath)
{
    QFile loadFile(filePath);
	if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::string msg = "cannot open the file: ";
        msg += filePath.toStdString();
        THROW_RUNTIME_EX(msg);
	}
	QString content = loadFile.readAll();

    //cout << endl;
    //cout << "------------------------"<<  endl;
    //cout << content.toStdString();
    //cout << "------------------------"<<  endl;
    //cout << endl;

	loadFile.close();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(content.toUtf8()));
	json_ = jsonDoc.object();
}

JsonReader::~JsonReader(){}

// return all values in string format ;
// hence in game.config please use string as data format
QString JsonReader::operator[](const QString& key) const
{
    if(json_.find(key) == json_.end()){
        qWarning() << "entry '" << key << "' is not found in JsonReader";
		return QString("");
	}
	return json_[key].toString();
}

#define EXPAND_SPECIALIZATION_INSERT_VALUE(T) \
    template<> \
    void JsonReader::insertValue<T>(const QString& key, T val) \
    {   json_.insert(key, QJsonValue(val)); }

EXPAND_SPECIALIZATION_INSERT_VALUE(bool);
EXPAND_SPECIALIZATION_INSERT_VALUE(int);
EXPAND_SPECIALIZATION_INSERT_VALUE(double);
EXPAND_SPECIALIZATION_INSERT_VALUE(QString);




}//namespace
