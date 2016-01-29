#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace io{



class Save
{
public:
	Save();
	Save(string path, int batch);
	~Save();
	void takeData(string data);
	void flush();
	
	static string PATH_DELIMITER;
	static int DEFAULT_BATCH_SIZE;
	
protected:
	string path_;
	int batchSize_;
	vector<string> vec_;

	
};

}//io
#endif // SAVE_H
