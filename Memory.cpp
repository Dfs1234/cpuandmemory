//
//  Memory.cpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#include "Memory.hpp"

Memory::Memory()
    :frameNumber(0), pageNumber(0), PID(0), Count(0){};

Memory::Memory(const int frame, const int  page, const int  process, const int id)
    :frameNumber(frame), pageNumber(page), PID(process), Count(id){};

Memory::~Memory(){}
void Memory::setPID(const int  process){ PID = process;}
void Memory::setPageNumber(const int  page){ pageNumber = page; }
void Memory::setCount(const int id){ Count = id; };

int Memory::getPageNumber()const{ return pageNumber; }
int Memory::getPID()const{ return PID; }
int Memory::getCount()const{ return Count; }

void Memory::change(const int  page, const int  process, const int  id){
    pageNumber = page;
    PID = process;
    Count = id;
}

bool Memory::is_empty(){
    return Count == -1 ? true : false;
}


bool Memory::isMatch(int _page, int _PID){
    return ( pageNumber == _page && PID==_PID )? true: false;
}

void Memory::display(){
    const char separator  = ' ';
    const int numWidth  = 6;
    std::cout << std::right << std::setw(numWidth-1) << std::setfill(separator) << frameNumber;
    std::cout << std::right << std::setw(numWidth) << std::setfill(separator) << pageNumber;
    std::cout << std::right << std::setw(numWidth) << std::setfill(separator) << PID ;
    std::cout << std::right << std::setw(numWidth) << std::setfill(separator) << Count << std::endl;
}
