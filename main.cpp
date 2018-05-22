//
//  main.cpp
//  
//
//  Created by Daven Liu on 2018/5/14.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "OSystem.hpp"

bool isNumber(std::string x);

int main(){
    long int page;
    long int frame;
    int numberOfHardDisk = 0; 
    int keyOfprocess = 0;
    
    OSystem OS; 
    do{
	std::cout << "How much RAM memory is there on the simulated computer? ";
    	std::cin >> frame;
        std::cout << "What is the size of page/frame: ";
        std::cin >> page;
    }while(frame < page || page ==0);
    std::cout << "How many hard disk does the simulated have? ";
    std::cin >> numberOfHardDisk;
    
    //remove " " from hardDisk;
    std::string temp2;
    std::getline(std::cin, temp2);
    
    OS.setNumberOfHardDisk(numberOfHardDisk);
    OS.setTable(frame/page);
   
    std::cout << "Please Enter an possible input \nEnter 0 to leave:\n";
    while(true){
        std::string temp;
        std::getline(std::cin, temp);
        std::stringstream getInput(temp);
        std::vector<std::string> input;
        while(getInput >> temp){
            input.push_back(temp);
        }
        if (input.size() == 0 || input[0].length() != 1) {
           std::cout << "Please Enter an possible input: \nEnter 0 to leave\n";
        }else{
        if(input[0][0] == '0')
            break;
        switch (input[0][0]) {
            case 'A':
                if(input.size() != 1){
                    std::cout<<"wrong Input\n";
                    break;
                }
                OS.setNewProcess();
                break;
            case 'Q':
                if(input.size() != 1){
                    std::cout<<"wrong Input\n";
                    break;
                }
                OS.quantum();
                break;
            case 't':
                if(input.size() != 1){
                    std::cout<<"wrong Input\n";
                    break;
                }
                OS.CPU_terminate();
                break;
            case 'd':
                if(input.size() != 3){
                    std::cout<<"wrong Input\n";
                    break;
                }
                if(!isNumber(input[1])){
                    std::cout << "Please Enter an possible input\nEnter 0 to leave:\n";
                    break;
                }
         
                int diskNumber;
                std::stringstream(input[1])  >> diskNumber;
                if(diskNumber < numberOfHardDisk){
                    OS.moveToDisk(diskNumber, input[2]);
                }else{
                    std::cout <<"System does not have disk number : " << diskNumber << "Please Enter an possible input: \n";
                }
                break;
            case 'D':
                if(input.size() != 2){
                    std::cout<<"wrong Input\n";
                    break;
                }
                if(!isNumber(input[1])){
                    std::cout << "Please Enter an possible input\nEnter 0 to leave:\n";
                    break;
                }
                //getInput << input[1];
                int diskNumber2;
                //getInput >> diskNumber2;
                std::stringstream(input[1])  >> diskNumber2;
                if(diskNumber2 < numberOfHardDisk){
                    OS.returnFromDisk(diskNumber2);
                }else{
                    std::cout <<"System does not have disk number : " << diskNumber << "Please Enter an possible input: \n";
                }
                break;
            case 'm':
                if(input.size() != 2){
                    std::cout<<"wrong Input\n";
                    break;
                }
                if(!isNumber(input[1])){
                    std::cout << "Please Enter an possible input\nEnter 0 to leave:\n";
                    break;
                }
                //getInput << input[1];
                int newPage;
                //getInput >> newPage;
                std::stringstream(input[1])  >> newPage;
                OS.tableChange(newPage/page);
                break;
            case 'S':
                if(input.size() != 2){
                    std::cout<<"wrong Input\n";
                    break;
                }
                switch (input[1][0]) {
                    case 'r':
                        OS.displayReadyQueueAndCPU();
                        break;
                    case 'i':
                        OS.displayHardDisk();
                        break;
                    case 'm':
                        OS.displayTable();
                    default:
                        break;
                }
                break;
            default:
                std::cout << "Please Enter an possible input\nEnter 0 to leave:\n";
                break;
        }
        }
    }
    
    return 0;
}

bool isNumber(std::string x){
    for(int i = 0; i < x.length(); i++){
        if ((int)x[i] > 57  || (int)x[i] < 48) {
            return false;
        }
    }
    return true;
}
