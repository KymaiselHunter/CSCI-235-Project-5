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

// int main()
// {
//     //cout << "Test 1" << endl;

//     QuestList questList = QuestList("debug.csv");

//     std::cout << "Testing questQuery:" << std::endl<< std::endl;
//     questList.questQuery("Quest 1");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 2");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 3");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 4");
//     std::cout<<std::endl;

//     //questList.printQuest(questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem());

//     questList.questQuery("Quest 5");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 6");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 7");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 8");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 9");
//     std::cout<<std::endl;

//     questList.questQuery("Quest 12");
//     std::cout<<std::endl;

//     std::cout << "Testing printQuestDetails:" << std::endl<< std::endl;
//     Quest* current = questList.getPointerTo(questList.getPosOf("Quest 1"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;
    
//     current = questList.getPointerTo(questList.getPosOf("Quest 2"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 3"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;


//     //questList.KyleDisplay();

//     //questList.calculatePathwayExperience(current);

//     // std::cout << current->title_ << " dependents:" << endl;
//     // for(int i = 0; i < current->subquests_.size(); i++)
//     // {
//     //     cout << current->subquests_[i] << endl;
//     // }

//     current = questList.getPointerTo(questList.getPosOf("Quest 4"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 5"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 6"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 7"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 8"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

//     current = questList.getPointerTo(questList.getPosOf("Quest 9"))->getItem();
//     questList.printQuestDetails(current);
//     std::cout<<std::endl;

// }

int main()
{
    //cout << "Test 2" << endl;

    QuestList questList = QuestList("quests.csv");

    std::cout << "Testing questQuery:" << std::endl<< std::endl;
    questList.questQuery("My First Backpack");
    std::cout<<std::endl;

    questList.questQuery("Enter The Tavern");
    std::cout<<std::endl;

    questList.questQuery("Talk to the Barkeep");
    std::cout<<std::endl;

    questList.questQuery("Talk to the Chef");
    std::cout<<std::endl;

    questList.questQuery("Talk to the Mysterious Figure");
    std::cout<<std::endl;

    questList.questQuery("House Stew");
    std::cout<<std::endl;

    questList.questQuery("Pest Control");
    std::cout<<std::endl;

    questList.questQuery("Lost and Found");
    std::cout<<std::endl;

    questList.questQuery("The Melodeon");
    std::cout<<std::endl;

    questList.questQuery("Talk to Songcatcher");
    std::cout<<std::endl;

    questList.questQuery("The Melodeon's Song");
    std::cout<<std::endl;

    questList.questQuery("Great. We Have A Melodeon");
    std::cout<<std::endl;

    questList.questQuery("Reunited");
    std::cout<<std::endl;

    questList.questQuery("Auroran Sunset");
    std::cout<<std::endl;

    //questList.KyleDisplay();

     std::cout << "Testing printQuestDetails:" << std::endl<< std::endl;
    Quest* current = questList.getPointerTo(questList.getPosOf("My First Backpack"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;
    
    current = questList.getPointerTo(questList.getPosOf("Enter The Tavern"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Talk to the Barkeep"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;
    
    current = questList.getPointerTo(questList.getPosOf("Talk to the Chef"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Talk to the Mysterious Figure"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("House Stew"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Pest Control"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Lost and Found"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("The Melodeon"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Talk to Songcatcher"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("The Melodeon's Song"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Great. We Have A Melodeon"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Reunited"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;

    current = questList.getPointerTo(questList.getPosOf("Auroran Sunset"))->getItem();
    questList.printQuestDetails(current);
    std::cout<<std::endl;
}