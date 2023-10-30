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

    //questList.printQuest(questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem());

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

    questList.questQuery("Quest 12");
    std::cout<<std::endl;

    std::cout << "Testing printQuestDetails:" << std::endl<< std::endl;
    Quest* current = questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;
    
    current = questList.getPointerTo(questList.getPosOf("Quest 2"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 3"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;


    //questList.KyleDisplay();

    //questList.calculatePathwayExperience(current);

    // std::cout << current->title_ << " dependents:" << endl;
    // for(int i = 0; i < current->subquests_.size(); i++)
    // {
    //     cout << current->subquests_[i] << endl;
    // }

    current = questList.getPointerTo(questList.getPosOf("Quest 4"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 5"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 6"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 7"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 8"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Quest 9"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

}