//
//  Process.cpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#include "Process.hpp"

Process::Process()
    :key(0), level(0), numberOfQuantum(0), readingFile(""){}

Process::Process(int _key, int _level, int _numberOfQuantum)
    :key(_key), level(_level), numberOfQuantum(_numberOfQuantum), readingFile("") {}

Process::Process(int _key, int _level)
    :key(_key), level(_level), numberOfQuantum(0), readingFile("") {}

Process::Process(int _key)
    :key(_key), level(0) , numberOfQuantum(0), readingFile("") {}

Process::~Process(){
    key = 0;
    level = 0;
    numberOfQuantum =0;
}

void Process::setKey(const int _key){ key = _key; }
void Process::setLevel(const int _level) { level = _level; }
void Process::setNumberOfQuantum(const int _numberOfQuantum){ numberOfQuantum = _numberOfQuantum; }
void Process::setReadinFile(const std::string fileName){ readingFile = fileName; }
//void Node::setNext(Node *temp){ next = temp; }

int Process::getKey()const { return key; }
int Process::getLevel()const { return level; }
int Process::getNumberOfQuantum()const { return numberOfQuantum; }
std::string Process::getReadingFile() const{ return readingFile; }
//Node Node::*getNext() {return next};

void Process::display(){
    std::cout << "Process key: " << key;// << std::endl;
    std::cout << " Process level: " << level;// << std::endl;
    std::cout << " Process number of quantum: " << numberOfQuantum << std::endl;
}

void Process::displayReadingFile(){
    std::cout << "Process key: " << key << std::endl;
    std::cout<< "Reading File: " << readingFile << std::endl;
}
