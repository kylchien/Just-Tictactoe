#include "simpleWriter.h"

#include "util/runtimeEx.h"

#include <utility> //for std::swap
#include <fstream> 

#include <QDateTime>


int io::SimpleWriter::DEFAULT_BATCH_SIZE = 100;

namespace io{

SimpleWriter::SimpleWriter()
{
    filePath_ = ".\\";
	batchSize_ = DEFAULT_BATCH_SIZE;
    autogenName_ = true;
}


SimpleWriter::SimpleWriter(const std::string& path, int batch, bool autogenName)
    :filePath_(path), batchSize_(batch), autogenName_(autogenName)
{
    if(autogenName_ && filePath_.at(filePath_.size()-1) != '\\'){
        filePath_ += "\\";
    }
}


SimpleWriter::~SimpleWriter()
{ flush();}


void swap(SimpleWriter& lhs, SimpleWriter& rhs)
{
    std::swap(lhs.filePath_, rhs.filePath_);
    std::swap(lhs.batchSize_, rhs.batchSize_);
    std::swap(lhs.autogenName_, rhs.autogenName_);
    std::swap(lhs.vec_, rhs.vec_);
}


SimpleWriter::SimpleWriter(SimpleWriter&& other)
    :filePath_(""), batchSize_(0)
{
    vec_.clear();
    swap(*this, other);
}

SimpleWriter& SimpleWriter::operator=(SimpleWriter&& other)
{
    if (this != &other){
        vec_.clear();
        swap(*this, other);
    }
    return *this;
}

void SimpleWriter::flush()
{
	if(vec_.empty()) return;
	
    string fileName = filePath_;
    if(autogenName_){
        string timestamp =
            QDateTime::currentDateTime().toString("yyyyMMdd-hh''mm''ss''zzz").toStdString();
        fileName +=  timestamp + ".txt";
    }

    std::ofstream ofs;
    try{
        ofs.open(fileName, std::ofstream::out);

        if(ofs.is_open()){
            for(size_t i=0; i<vec_.size(); ++i)
                ofs << vec_[i] << "\n";
            ofs.flush();
            ofs.close();
        }
        else{
            std::stringstream ss;
            ss << "Unable to open file:" << fileName;
            THROW_RUNTIME_EX(ss.str());
        }
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }

	vec_.clear();
}

void SimpleWriter::writeLine(const string& line)
{
    vec_.push_back(line);
    if( vec_.size() >= batchSize_)
        flush();
}
	
	
} //namespace io
