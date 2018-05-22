//
//  OSystem.hpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#ifndef OSystem_hpp
#define OSystem_hpp

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include "Process.hpp"
#include "Memory.hpp"

class OSystem{
public:
    OSystem();
    OSystem(int numberOfHardDisk);
    ~OSystem();
    
    void setTable(long int size);
    void setNumberOfHardDisk(const int numberOfHardDisk);
    void setCPU();
    void getHighQueue(int _level);
    //for commands;
    void setNewProcess();
    void quantum();
    void CPU_terminate();
    void moveToDisk(int number, std::string fileName);
    void returnFromDisk(int diskNumber);
    void tableRemove(int PID);
    void tableChange(int newPage, int PID); // for new process arrvias
    void tableChange(int newPage);
    
    //display
    void displayReadyQueueAndCPU();
    void displayHardDisk();
    void displayTable();
    
private:
    std::vector<Process> levelZero;
    std::vector<Process> levelOne;
    std::vector<Process> levelTwo;
    std::vector<Process> CPU;
    std::vector<std::list <Process> > hardDisk;
    std::vector<Memory> table;
    int key; //id of the process
    bool is_CPU_empty();
    int countID; //count for memory table
    //bool is_empty(std::vector<Process> *temp);
};

#include "OSystem.cpp"

#endif /* OSystem_hpp */
