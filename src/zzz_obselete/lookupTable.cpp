#include "lookupTable.h"
#include "gameDef.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace game{

template <class T>
LookupTable<T>::SyncData::SyncData(T d)
    :data_(d)
{}


template <class T>
LookupTable<T>::SyncData::~SyncData()
{}

template <class T>
LookupTable<T>::SyncData::SyncData(SyncData&& other)
{ std::swap(data_, other.data_); }


template <class T>
typename LookupTable<T>::SyncData&
LookupTable<T>::SyncData::operator=(SyncData&& other)
{
    if(this != &other ){
        std::swap(data_, other.data_);
    }
    return *this;
}


template <class T>
void LookupTable<T>::SyncData::update(T d)
{
    data_.store(d, std::memory_order_release);
}


template <class T>
T LookupTable<T>::SyncData::get() const
{
    return data_.load(std::memory_order_acquire);
}


template <class T>
LookupTable<T>::LookupTable()
{}


template <class T>
LookupTable<T>::~LookupTable()
{
    /*
    io::Save save("C:\\Project\\Just-Tictactoe", 5000);
    unordered_map<string, SyncFloat*>::iterator iter;

    for(iter = mapUnique_.begin(); iter != mapUnique_.end(); iter++){
        std::stringstream ss;
        ss << iter->first << " " << iter->second->get();
        save.takeData(ss.str());

        delete iter->second;
    }*/

}
/*
void LookupTable::addRotatedEntries(const char* s, SyncFloat* pf)
{
    char state[BOARD_SIZE+1];
    copyBoard(s, state);
    state[BOARD_SIZE] = '\0';
	
    for(int i=0; i<4; i++){
        map_.emplace(state, pf);
        char rotate[BOARD_SIZE];
        rotateCW90(state, rotate);
        copyBoard(rotate, state);
    }
}

void LookupTable::update(const char* s, float val)
{
    char state[BOARD_SIZE+1];
    copyBoard(s, state);
    state[BOARD_SIZE] = '\0';
    string key(state);

    unordered_map<string, SyncFloat*>::iterator iter = map_.find(key);
    if(iter == map_.end()){
        SyncFloat* pf = new SyncFloat(val);
        mapUnique_.emplace(key, pf);
        map_.emplace(key, pf);

        char rotate90[BOARD_SIZE];
        rotateCW90(state, rotate90);
        if(!isEqual(state,rotate90)){
            addRotatedEntries(state, pf);
            char mirrorState[BOARD_SIZE];
            mirror(state, mirrorState);
            if(!isEqual(state, mirrorState)){
                addRotatedEntries(mirrorState, pf);
            }
        }
    }
    else{
        iter->second->update(val);
    }
}


bool LookupTable::get(const char* s, float& output)
{
    char state[BOARD_SIZE+1];
    copyBoard(s, state);
    state[BOARD_SIZE] = '\0';
    string key(state);

    unordered_map<string, SyncFloat*>::iterator iter = map_.find(key);
    if(iter == map_.end()){
        return false;
    }
    else{
        output = iter->second->get();
        return true;
    }
}

void LookupTable::print()
{
    cout << "mapUnique size: " <<  mapUnique_.size() << "\n";
    cout << "map size: " <<  map_.size() << "\n\n";

    unordered_map<string, SyncFloat*>::iterator iter;
    for(iter = map_.begin(); iter != map_.end(); iter++){
        cout << "val = " << iter->second->get() << ", strlen=" << iter->first.size() << "\n";
        cout << iter->first[0] << iter->first[1] << iter->first[2] << "\n";
        cout << iter->first[3] << iter->first[4] << iter->first[5] << "\n";
        cout << iter->first[6] << iter->first[7] << iter->first[8] << "\n";
        cout << endl;
    }
}
*/


}

