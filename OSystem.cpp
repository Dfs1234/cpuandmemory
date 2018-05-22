//
//  OSystem.cpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#include "OSystem.hpp"

OSystem::OSystem():
    key(0), countID(0) {}

OSystem::OSystem(int numberOfHardDisk){
    hardDisk.resize(numberOfHardDisk);
    key = 0;
    countID = 0;
}

OSystem::~OSystem(){}

void OSystem::setTable(long int size){
    for(int i = 0; i < size; i++){
        Memory temp(i, -1, -1, -1);
        table.push_back(temp);
    }
}

void OSystem::setNumberOfHardDisk(const int numberOfHardDisk){
    hardDisk.resize(numberOfHardDisk);
}

//find new process from readyQueue
void OSystem::setCPU(){
    if(levelZero.size() > 0){
        CPU.push_back(levelZero[0]);
        levelZero.erase(levelZero.begin());
    }else if(levelOne.size() > 0){
        CPU.push_back(levelOne[0]);
        levelOne.erase(levelOne.begin());
    }else if(levelTwo.size() != 0){
        CPU.push_back(levelTwo[0]);
        levelTwo.erase(levelTwo.begin());
    }
} 

//if higher process move to ready queue, change cpu
void OSystem::getHighQueue(int _level){
    if (!is_CPU_empty() && CPU[0].getLevel() > _level){
        if(CPU[0].getLevel() == 1){
            levelOne.insert(levelOne.begin(), CPU[0]);
        }else{
            levelTwo.insert(levelTwo.begin(), CPU[0]);
        }
        CPU.erase(CPU.begin());
        setCPU();
    }
}

//Use for A command;
void OSystem::setNewProcess(){
    Process temp(++key, 0 , 0);
    levelZero.push_back(temp);
    
    if(is_CPU_empty()){
        setCPU();
    }else{
        getHighQueue(0);
    }
    tableChange(0, key);
}

//Use for Q command set quantum
void OSystem::quantum(){
    if (!is_CPU_empty() && CPU[0].getLevel() != 2){
        Process temp;
        temp = CPU[0];
        if(temp.getLevel() == 0){
            temp.setLevel(1);
            levelOne.push_back(temp);
        }else if(temp.getLevel() == 1){
            if(temp.getNumberOfQuantum() == 0){
                temp.setNumberOfQuantum(1);
                levelOne.push_back(temp);
            }
            else{
                temp.setLevel(2);
                temp.setNumberOfQuantum(-1);
                levelTwo.push_back(temp);
            }
        }
        CPU.erase(CPU.begin());
        setCPU();
    }
}

//Use for t command: remove element from cpu ,and find new process
void OSystem::CPU_terminate(){
    if(!is_CPU_empty()){
        tableRemove(CPU[0].getKey());
        CPU.erase(CPU.begin());
        setCPU();
    }
}

//command d
void OSystem::moveToDisk(int number, std::string fileName){
    if(!is_CPU_empty()){
        Process temp;
        temp = CPU[0];
        temp.setReadinFile(fileName);
        hardDisk[number].push_back(temp);
        CPU.erase(CPU.begin());
        setCPU();
    }
}

//command D
void OSystem::returnFromDisk(int diskNumber){
    if(hardDisk[diskNumber].size() > 0){
        switch(hardDisk[diskNumber].front().getLevel()){
            case 0:
                levelZero.push_back(hardDisk[diskNumber].front());
                hardDisk[diskNumber].erase(hardDisk[diskNumber].begin());
                if(is_CPU_empty()){
                    setCPU();
                }else{
                    getHighQueue(0);
                }
                break;
            case 1:
                levelOne.push_back(hardDisk[diskNumber].front());
                hardDisk[diskNumber].erase(hardDisk[diskNumber].begin());
                if(is_CPU_empty()){
                    setCPU();
                }else{
                    getHighQueue(1);
                }
                break;
            case 2:
                levelTwo.push_back(hardDisk[diskNumber].front());
                hardDisk[diskNumber].erase(hardDisk[diskNumber].begin());
                if(is_CPU_empty()){
                    setCPU();
                }
                break;
            default:
                break;
        }
    }
}

void OSystem::tableChange(int newPage, int PID){
    bool haveChange = false;
    for(int i = 0; i < table.size(); i++){
        if(table[i].isMatch(newPage, PID)){
	    table[i].change(newPage, PID, ++countID);
            haveChange = true;
            break;
        }
    }
    if(!haveChange){
        for(int i = 0; i < table.size(); i++){
            if(table[i].is_empty()){
                table[i].change(newPage, PID, ++countID);
                haveChange = true;
                break;
            }
        }
    }
    if(!haveChange){
        int min = 0;
        for(int i = 1; i < table.size(); i++){
            if(table[min].getCount() > table[i].getCount() ){
                min = i;
            }
        }
        table[min].change(newPage, PID, ++countID);
    }
}

void OSystem::tableRemove(int PID){
    for(int i = 0; i < table.size(); i++){
        if(table[i].getPID() == PID){
            table[i].change(-1, -1, -1);
        }
    }
}
// commands m
void OSystem::tableChange(int newPage){
    bool haveChange = false;
    for(int i = 0; i < table.size(); i++){
        if(table[i].isMatch(newPage, CPU[0].getKey())){
	    table[i].change(newPage, CPU[0].getKey(), ++countID);
            haveChange = true;
            break;
        }
    }
    if(!haveChange){
        for(int i = 0; i < table.size(); i++){
            if(table[i].is_empty()){
                table[i].change(newPage, CPU[0].getKey(), ++countID);
                haveChange = true;
                break;
            }
        }
    }
    if(!haveChange){
        int min = 0;
        for(int i = 1; i < table.size(); i++){
            if(table[min].getCount() > table[i].getCount() ){
                min = i;
            }
        }
        table[min].change(newPage, CPU[0].getKey(), ++countID);
    }
}


bool OSystem::is_CPU_empty(){ return CPU.size() == 0 ? true: false; }

//bool OSystem::is_empty(std::vector<Process> *temp){ return temp.size() == 0 ? true: false; }

void OSystem::displayReadyQueueAndCPU(){
    std::cout<<"CPU:\n";
    for(auto i : CPU){
        i.display();
    }
    std::cout<<"levelZero:\n";
    for(auto i : levelZero){
        i.display();
    } 
    std::cout<<"levelOne:\n";
    for(auto i : levelOne){
        i.display();
    }
    std::cout<<"levelTwo:\n";
    for(auto i : levelTwo){
        i.display();
    }
}

void OSystem::displayHardDisk(){
    for(int i = 0; i < hardDisk.size(); i++){
        std::cout<<"Disk" << i << ": \n";
        std::cout<<"First queue is using disk, others are wating.\n";
        for (auto j : hardDisk[i]) {
            j.displayReadingFile();
        }
    }
}

void OSystem::displayTable(){
    const char separator  = ' ';
    const int numWidth  = 6;
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "Frame ";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << " Page";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << " Pid";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << " Count" << std::endl;
    
    for (auto i : table) {
        i.display();
    }
}
