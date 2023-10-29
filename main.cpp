//
//  Main.cpp
//
//  Tests the rest of the class
//
//Name : Kyle Bautista
//Instructor : Dr. Tiziana Ligorio
//Project 5

//

#include <iostream>
using namespace std;

#include "DoublyLinkedList.hpp"
#include "QuestList.hpp"

int main()
{
    //cout << "Test 1" << endl;

    QuestList questList = QuestList("debug.csv");

    std::cout << "Testing questQuery:" << std::endl<< std::endl;
    questList.questQuery("Quest 1");
    std::cout<<std::endl;

    std::cout << "Testing printQuestDetails:" << std::endl<< std::endl;
    Quest* current = questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    cout << " dsf  " << questList.calculatePathwayExperience(current) << endl;
    cout << " dsf2  " << questList.calculateProjectedExperience(current) << endl;
}