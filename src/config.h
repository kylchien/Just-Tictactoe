#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config
{
public:
    Config();
    Config(const Config& src) = delete;
    Config& operator=(const Config& src) = delete;
    ~Config();

    void load();

};

#endif // CONFIG_H
