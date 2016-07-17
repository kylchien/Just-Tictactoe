#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include "gameDef.h"
#include "io/simpleWriter.h"

#include <unordered_map>
#include <string>
#include <atomic>
#include <memory>


namespace game{

template<class T>
class AtomicData
{
    std::atomic<T> data_;

public:
    AtomicData(T data);
    ~AtomicData();

    //dunno T type, cannot simply data_ = other.data_
    AtomicData(const AtomicData& other) = delete;
    AtomicData& operator=(AtomicData other) = delete;

    AtomicData(AtomicData&& other);
    AtomicData& operator=(AtomicData&& other);

    void set(T d);
    T get() const;

    template<class U>
    friend void swap(AtomicData<U>& lhs, AtomicData<U>& rhs);
};





class LookupTable final{

private:

    using Double = AtomicData<double>;
    std::unordered_map<std::string, Double*> map_;
    std::unordered_map<std::string, Double*> mapUnique_;

    void addRotatedEntries(const char* state, Double* f);

public:
    LookupTable();
    ~LookupTable();

	LookupTable(const LookupTable& src) = delete;
	LookupTable& operator=(const LookupTable& src) = delete;

    void set(const char* state, double val);
    void set(const std::string& state, double val);
    bool get(const char* state, double& output);
	
    //for small size debugging
    void print();

    void saveData(std::shared_ptr<io::SimpleWriter> sw);

    void loadData(const std::string& filePath);

    //to merge different weight of data we need to take weighting
    //void mergeData(const std::string& filePath);

};




}
#endif // LOOKUPTABLE_H
