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

}