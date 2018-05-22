//
//  Memory.hpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#ifndef Memory_hpp
#define Memory_hpp

#include <iostream>
#include <iomanip>

class Memory{
public:
    Memory();
    Memory(const int frame, const int  page, const int  process, const int id);
    
    ~Memory();
    void setPID(const int  process);
    void setPageNumber(const int  page);
    void setCount(const int  id);
    
    int getPageNumber()const;
    int getPID()const;
    int getCount()const;
    
    void change(const int  page, const int  process, const int  id);
    bool is_empty();
    bool isMatch(int _page, int _PID);
    void display();
private:
    int frameNumber;
    int pageNumber;
    int PID;
    int Count;
};

#include "Memory.cpp"

#endif /* Memory_hpp */
