#include "config.h"
#include "util/runtimeEx.h"
#include "jsonReader.h"

#include <typeinfo>
#include <sstream>


namespace io{

Config::Config(const QString& path)
    :path_(path), isInit_(false), config_{nullptr}
{}

Config::~Config()
{ delete config_; }

void Config::set(const QString& key, QString val)
{
    if(isInit_){
		config_->insertValue<QString>(key, val);
	}
    else THROW_RUNTIME_EX("Config is not initialized!");
}

void Config::initialize(const PairQStringVec& vec)
{
    if(!isInit_){
        isInit_= true;
        config_ = new io::JsonReader(path_);
        const io::JsonReader& config = *config_;

        for(auto p:vec){
            const QString key = p.first;
            QString val = config[key];
            if(val == "") set(key, p.second);

        }

    }
}

void Config::initialize()
{
    if(!isInit_){
        config_ = new io::JsonReader(path_);
        isInit_= true;
    }
}



template<typename T> 
T Config::get(const QString& key) const
{ 
	std::stringstream ss;
	ss << "type \"" << typeid(T).name() << "\" is not supported!";
	THROW_RUNTIME_EX(ss.str()); 
}



QString Config::validatingGet(const QString& key) const
{
    if(!isInit_)
        THROW_RUNTIME_EX("Config is not initialized!");
    const io::JsonReader& config = *config_;
    QString val = config[key];
    if(val == ""){
        std::stringstream ss;
        ss << "key \"" << key.toStdString() << "\" is not found in config!";
        THROW_RUNTIME_EX(ss.str());
    }
    return val;
}

template<>
int Config::get(const QString& key) const
{  return validatingGet(key).toInt();  }

template<>
QString Config::get(const QString& key) const
{  return validatingGet(key);  }

template<>
std::string Config::get(const QString& key) const
{  return validatingGet(key).toStdString();  }

template<>
bool Config::get(const QString& key) const
{
    QString val = validatingGet(key).toUpper();

    if( val != "TRUE" && val != "FALSE" && val != "1" && val!= "0" &&
            val != "ON" && val != "OFF"){
        std::stringstream ss;
        ss << "key \"" << key.toStdString() << "\" cannot be converted into valid boolean values!";
        THROW_RUNTIME_EX(ss.str());
    }

    bool rs = false;

    if( val == "TRUE" || val =="1" || val == "ON") rs = true;
    if( val == "FALSE" || val =="0" || val == "OFF") rs = false;

    return rs;
}



}//namespace
