#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include "gameDef.h"

#include <unordered_map>
#include <atomic>
#include <string>

namespace game{

template <class T>
class LookupTable
{


class SyncData
{
    SyncData(T d);
    ~SyncData();

    SyncData(const SyncData& other) = delete;
    SyncData& operator=(const SyncData& other) = delete;

    SyncData(SyncData&& other);
    SyncData& operator=(SyncData&& other);

    void update(T d);
    T get() const;

private:
    std::atomic<T> data_;
};


//protected:
  //  std::unordered_map<std::string, SyncData<T>* > map_;
    //std::unordered_map<std::string, SyncData<T>* > mapUnique_;

    //void addRotatedEntries(const char* state, SyncData<T>* f);


public:
    LookupTable();
    ~LookupTable();

    LookupTable(const LookupTable& src) = delete;
    LookupTable& operator=(const LookupTable& src) = delete;

    //void update(const char* state, T val);
    //bool get(const char* state, T& output);

    //void dump();
    //void loadDump(std::string file);

    //void print();

};


}
#endif // LOOKUPTABLE_H
