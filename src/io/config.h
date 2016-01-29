#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>
#include <QString>

namespace io{

class Config final
{
public:
    Config();
    Config(const Config& src) = delete;
    Config& operator=(const Config& src) = delete;
    ~Config();

    void load();
	QString operator[](QString key) const;

private:
	QJsonObject json_;

};

}
#endif // CONFIG_H
