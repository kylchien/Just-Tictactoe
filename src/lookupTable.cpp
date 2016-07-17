#include "lookupTable.h"
#include "gameDef.h"
#include "gameUtil.h"
#include "io/simpleReader.h"


#include <iostream>
#include <sstream>
#include <tuple>

namespace game{


template<class T>
AtomicData<T>::AtomicData(T data):data_{data}
{}


template<class T>
AtomicData<T>::~AtomicData()
{}


template<class T>
void swap(AtomicData<T>& lhs, AtomicData<T>& rhs)
{
    std::swap(lhs.data_, rhs.data_);
}


template<class T>
AtomicData<T>::AtomicData(AtomicData&& other)
{
    swap(*this, other);
}

template<class T>
AtomicData<T>& AtomicData<T>::operator=(AtomicData&& other)
{
    if(this != &other) swap(*this, other);
    return *this;
}


template<class T>
T AtomicData<T>::get() const
{  return data_.load(std::memory_order_acquire);  }


template<class T>
void AtomicData<T>::set(T data)
{  data_.store(data, std::memory_order_release);  }





LookupTable::LookupTable()
{}


LookupTable::~LookupTable()
{
    std::unordered_map<std::string, Double*>::iterator iter;
	for(iter = mapUnique_.begin(); iter != mapUnique_.end(); iter++){
		delete iter->second;
	}
    mapUnique_.clear();
    map_.clear();
}


void LookupTable::addRotatedEntries(const char* s, Double* p)
{
    char state[BOARD_SIZE];
    char rotated[BOARD_SIZE];
    copyBoard(s, state);
    rotateCW90(state, rotated);

    if(isEqual(state, rotated)) return;

    std::string k(rotated, 0, BOARD_SIZE);
    map_.insert( std::make_pair(k,p) );

    for(int i=0; i<2; i++){
        copyBoard(rotated, state);
        rotateCW90(state, rotated);

        std::string key(rotated, 0, BOARD_SIZE);
        map_.insert( std::make_pair(key, p));
	}
}

void LookupTable::set(const char* s, double val)
{
    std::string key(s, 0, BOARD_SIZE);
    set(key, val);
    /*
    std::unordered_map<std::string, Double*>::iterator iter = map_.find(key);
	if(iter == map_.end()){      			
        Double* p = new Double(val);

        mapUnique_.emplace(std::make_pair(key, p));
        map_.emplace(std::make_pair(key, p));

        addRotatedEntries(s, p);

        char mirrorState[BOARD_SIZE];
        mirror(s, mirrorState);
        if(!isEqual(s,mirrorState)){
            map_.insert({std::string(mirrorState, 0, BOARD_SIZE), p});
            addRotatedEntries(mirrorState, p);
        }
	}
	else{
        iter->second->set(val);
    }*/
}

void LookupTable::set(const std::string& state, double val)
{
    std::unordered_map<std::string, Double*>::iterator iter = map_.find(state);
    if(iter == map_.end()){
        Double* p = new Double(val);

        mapUnique_.emplace(std::make_pair(state, p));
        map_.emplace(std::make_pair(state, p));

        const char* s = state.c_str();
        addRotatedEntries(s, p);

        char mirrorState[BOARD_SIZE];
        mirror(s, mirrorState);
        if(!isEqual(s,mirrorState)){
            map_.insert({std::string(mirrorState, 0, BOARD_SIZE), p});
            addRotatedEntries(mirrorState, p);
        }
    }
    else{
        iter->second->set(val);
    }
}

bool LookupTable::get(const char* s, double& output)
{
    std::string key(s, 0, BOARD_SIZE);
	
    std::unordered_map<std::string, Double*>::iterator iter = map_.find(key);
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
    using std::cout;
    using std::endl;

	cout << "mapUnique size: " <<  mapUnique_.size() << "\n";
    cout << "map size: " <<  map_.size() << "\n\n";

    std::unordered_map<std::string, Double*>::iterator iter;
    for(iter = mapUnique_.begin(); iter != mapUnique_.end(); iter++){
		cout << "val = " << iter->second->get() << ", strlen=" << iter->first.size() << "\n";
		cout << iter->first[0] << iter->first[1] << iter->first[2] << "\n";
		cout << iter->first[3] << iter->first[4] << iter->first[5] << "\n";
		cout << iter->first[6] << iter->first[7] << iter->first[8] << "\n";
		cout << endl;
	}
}


void LookupTable::saveData(std::shared_ptr<io::SimpleWriter> sw)
{
    std::unordered_map<std::string, Double*>::iterator iter;
    for(iter = mapUnique_.begin(); iter != mapUnique_.end(); iter++){
        std::stringstream ss;
         ss << iter->first << " " << iter->second->get();
         sw->writeLine(ss.str());
    }
}

void LookupTable::loadData(const std::string& filePath)
{
    auto vec = io::SimpleReader::readData< io::Tuple_board_value >(filePath);
    for(auto tuple : vec){
        set(std::get<0>(tuple), std::get<1>(tuple));
    }
}



}//namespace

