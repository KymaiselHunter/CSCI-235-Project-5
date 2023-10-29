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

    questList.questQuery("Quest 2");
    std::cout<<std::endl;

    questList.questQuery("Quest 3");
    std::cout<<std::endl;

    questList.questQuery("Quest 4");
    std::cout<<std::endl;

    

    questList.questQuery("Quest 5");
    std::cout<<std::endl;

    questList.questQuery("Quest 6");
    std::cout<<std::endl;

    questList.questQuery("Quest 7");
    std::cout<<std::endl;

    questList.questQuery("Quest 8");
    std::cout<<std::endl;

    questList.questQuery("Quest 9");
    std::cout<<std::endl;

    // std::cout << "Testing printQuestDetails:" << std::endl<< std::endl;
    // Quest* current = questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem();
    // questList.printQuestDetails(current);
    // std::cout<<std::endl;

}