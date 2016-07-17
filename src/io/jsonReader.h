#ifndef UTIL_JSONREADER_H
#define UTIL_JSONREADER_H

#include <QJsonObject>
#include <QString>


namespace io{

class JsonReader final{
public:
    JsonReader(const QString& filePath);
    ~JsonReader();

    JsonReader(const JsonReader& src) = delete;
    JsonReader& operator=(const JsonReader& src) = delete;

    QString operator[](const QString& key) const;

    template<typename T>
    void insertValue(const QString& key, T val);

    //void load();  //add later?
    //dump()

private:
    QJsonObject json_;

};


}
#endif
