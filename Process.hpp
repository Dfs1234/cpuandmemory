//
//  Process.hpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#ifndef Process_hpp
#define Process_hpp

#include <iostream>
#include <string>

class Process{
public:
    Process();
    Process(int _key, int _level, int _numberOfQuantum);
    Process(int _key, int _level);
    Process(int _key);
    ~Process();
    void setKey(const int _key);
    void setLevel(const int _level);
    void setNumberOfQuantum(const int _numberOfQuantum);
    void setReadinFile(const std::string fileName);
    //void setNext(Node *temp);
    
    int getKey()const;
    int getLevel()const;
    int getNumberOfQuantum()const;
    std::string getReadingFile() const;
    //Node *getNext();
    
    void display();
    void displayReadingFile();
    
private:
    int numberOfQuantum;
    int key;
    int level;
    std::string readingFile;
    //Node *next;
};

#include "Process.cpp"

#endif /* Process_hpp */
