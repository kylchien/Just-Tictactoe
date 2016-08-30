#ifndef SIMPLE_WRITER_H
#define SIMPLE_WRITER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace io{



class SimpleWriter{

public:
    SimpleWriter();
    SimpleWriter(const string& path, int batch, bool autogenName=true);
    ~SimpleWriter();

    SimpleWriter(const SimpleWriter& other) = delete;
    SimpleWriter& operator=(const SimpleWriter& other) = delete;

    SimpleWriter(SimpleWriter&& other);
    SimpleWriter& operator=(SimpleWriter&& other);

    void writeLine(const string& line);
	void flush();
	
    inline string getPath() const
    {  return filePath_; }

    inline void setPath(const string& path)
    {  filePath_ = path; }

    inline size_t getBatchSize() const
    {  return batchSize_;  }

    inline void setBatchSize(int batch)
    {  batchSize_ = batch; }

    inline bool getAutogenName() const
    {  return autogenName_; }

    inline void setAutogenName(bool autoGenName)
    {  autogenName_ = autoGenName;  }

    friend void swap(SimpleWriter& lhs, SimpleWriter& rhs);

protected:
    string filePath_;
    size_t batchSize_;
    bool autogenName_;
	vector<string> vec_;

private:
    static int DEFAULT_BATCH_SIZE;

	
};

}//io
#endif // SIMPLE_WRITER_H
