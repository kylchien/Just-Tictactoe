#ifndef CONFIG_H
#define CONFIG_H

#include <utility>
#include <vector>

#include <QString>


namespace io{

class JsonReader;

class Config{

public:
    Config(const QString& path);
    ~Config();

    Config(const Config& src) = delete;
    Config& operator=(const Config& src) = delete;

	template<typename T> 
	T get(const QString& key) const;
    
	void set(const QString& key, QString val);
	

    using PairQStringVec = std::vector< std::pair<QString, QString> >;

    void initialize(const PairQStringVec& vec);
    void initialize();


	
private:
    QString path_;
    bool isInit_;
    io::JsonReader* config_;

    inline QString validatingGet(const QString& key) const;

};



}//namespace


#endif
