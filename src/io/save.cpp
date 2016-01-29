#include "save.h"

#include <iostream>
#include <fstream> 
#include <QDateTime>

using namespace io;
using namespace std;

string Save::PATH_DELIMITER = "\\";
int Save::DEFAULT_BATCH_SIZE = 10;

Save::Save()
{
	path_ = "." + PATH_DELIMITER;
	batchSize_ = DEFAULT_BATCH_SIZE;
}

Save::Save(string path, int batch)
{
	path_ = path;
    if(path_[path_.size()-1] !='\\')
		path_ += PATH_DELIMITER;
	batchSize_ = batch;
}

Save::~Save(){ flush();}
	

void Save::flush()
{
	if(vec_.empty()) return;
	
    string fileName = path_ + QDateTime::currentDateTime().toString("yyyyMMdd-hh''mm''ss''zzz").toStdString();
	fileName += ".txt";
	ofstream ofs (fileName, std::ofstream::out);
	for(int i=0; i<vec_.size(); ++i)
        ofs << vec_[i] << "\n";
	ofs.close();
	vec_.clear();
}

void Save::takeData(string data)
{
    vec_.push_back(data);
	if(vec_.size() >= batchSize_) flush();
}
	
	

