//
//  QuestList.cpp
//
//  Defines methods of Questlist.hpp
//
//Name : Kyle Bautista
//Instructor : Dr. Tiziana Ligorio
//Project 5

//

#include "QuestList.hpp"

// //constructors
// /**
//     Default Constructor
// */
// QuestList::QuestList(): DoublyLinkedList<Quest*>()
// {

// }

// /**
//     @param: a reference to string name of an input file
//     @pre: Formatting of the csv file is as follows:
//         Title: A string
//         Description: A string
//         Completion Status: 0 (False) or 1 (True)
//         Experience Points: A non negative integer
//         Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
//         Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
//     Notes:
//         - The first line of the input file is a header and should be ignored.
//         - The dependencies and subquests are separated by a semicolon and may be NONE.
//         - The dependencies and subquests may be in any order.
//         - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
//             - Title: The title of the quest
//             - Description: "NOT DISCOVERED"
//             - Completion Status: False
//             - Experience Points: 0
//             - Dependencies: An empty vector
//             - Subquests: An empty vector
//         - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
//         Hint: update as needed using addQuest()
        

//     @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

// */
// QuestList::QuestList(const std::string &pFileName)
// {

// }

//========================================================
//unique methods
//========================================================

/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string &pTitle) const
{
    if (getLength() == 0) return -1;

    int count = 0;
    Node<Quest*> *iterator = first_;
    while (iterator != nullptr)
    {
        if(iterator->getItem()->title_ == pTitle) return count;
        iterator = iterator->getNext();
        count++;
    }
    return -1;
}

/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string &pTitle) const
{
    if (getLength() == 0) return false;

    Node<Quest*> *iterator = first_;
    while (iterator != nullptr)
    {
        if(iterator->getItem()->title_ == pTitle) return true;
        iterator = iterator->getNext();
    }
    return false;
}

/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
        
    @return: True if the quest was added successfully, False otherwise
*/
bool QuestList::addQuest(Quest* pQuest)
{
    //am i supposed to removed this because i think im suppose to assume the quest is not already in the questList?
    //if it fails the precondition, of having this quest already exist, return false; unless it is undiscovered, then update
    if(this->contains(pQuest->title_) == true)
    {
        if(this->getPointerTo(this->getPosOf(pQuest->title_))->getItem()->description_ == "NOT DISCOVERED" && pQuest->description_ != "NOT DISCOVERED")
        {
            //get the ptr to this undiscovered quest by getting the position of it which is passed into to find the pointer of the node and take it's item
            Quest *update = this->getPointerTo(this->getPosOf(pQuest->title_))->getItem();

            //because both ptrs are suppose to be taking the same place, we can delete the old one and replace it with this new ptr
            //delete the value of the quest ptr
            delete update;
            //replaces it with the value held in this depdency
            *update = *pQuest;
        }
        else return false;
    }
    

    //add using parent class function
    this->insert(this->item_count_, pQuest);
    
    //add dependencies and subquests
    //loop through dependecies vector
    for(int i = 0; i < pQuest->dependencies_.size(); i++)
    {
        //if the dependency does not exist, add it
        //or if it does exist but has not been discovered AND the new quest is not "NOT DISCOVERED", update it
        if(!this->contains(pQuest->dependencies_[i]->title_) ) 
        {
            addQuest(pQuest->dependencies_[i]);
        }
        else if(pQuest->dependencies_[i]->description_ == "NOT DISCOVERED" && pQuest->description_ != "NOT DISCOVERED")
        {
            //get the ptr to this undiscovered quest by getting the position of it which is passed into to find the pointer of the node and take it's item
            Quest *update = this->getPointerTo(this->getPosOf(pQuest->dependencies_[i]->title_))->getItem();

            //because both ptrs are suppose to be taking the same place, we can delete the old one and replace it with this new ptr
            //delete the value of the quest ptr
            delete update;
            //replaces it with the value held in this depdency
            *update = *pQuest->dependencies_[i];
        }
    }

    //loop through dependecies vector
    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        //if the dependency does not exist, add it
        //or if it does exist but has not been discovered AND the new quest is not "NOT DISCOVERED", update it
        if(!this->contains(pQuest->subquests_[i]->title_) ) 
        {
            addQuest(pQuest->subquests_[i]);
        }
        else if(pQuest->subquests_[i]->description_ == "NOT DISCOVERED" && pQuest->description_ != "NOT DISCOVERED")
        {
            //get the ptr to this undiscovered quest by getting the position of it which is passed into to find the pointer of the node and take it's item
            Quest *update = this->getPointerTo(this->getPosOf(pQuest->subquests_[i]->title_))->getItem();

            //because both ptrs are suppose to be taking the same place, we can delete the old one and replace it with this new ptr
            //delete the value of the quest ptr
            delete update;
            //replaces it with the value held in this depdency
            *update = *pQuest->subquests_[i];
        }
    }

    return true;
}

/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
            Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            

    @return: True if the quest was added successfully

*/
bool QuestList::addQuest(std::string pTitle, std::string pDescription, bool pCompleted, int pEXP, std::vector<Quest*> pDependcies, std::vector<Quest*> pSubquests)
{
    //take parameters and put it into a new quest
    Quest * newQuest = new Quest(pTitle, pDescription, pCompleted, pEXP, pDependcies, pSubquests);

    //since the previous method already adds a quest to the list, call the other version of the method and return if it works or not
    return this->addQuest(newQuest);
}