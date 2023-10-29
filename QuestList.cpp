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
        //or if it does exist AND has not been discovered AND the new quest is not "NOT DISCOVERED", update it
        if(!this->contains(pQuest->dependencies_[i]->title_) || 
        (!this->contains(pQuest->dependencies_[i]->title_) 
        && getPointerTo(this->getPosOf(pQuest->dependencies_[i]->title_))->getItem()->description_ == "NOT DISCOVERED" 
        && pQuest->dependencies_[i]->description_ != "NOT DISCOVERED")) 
        {
            addQuest(pQuest->dependencies_[i]);
        }
    }

    //loop through subquest vector
    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        //if the dependency does not exist, add it
        //or if it does exist but has not been discovered AND the new quest is not "NOT DISCOVERED", update it
        if(!this->contains(pQuest->subquests_[i]->title_) ||
        (!this->contains(pQuest->subquests_[i]->title_) 
        && getPointerTo(this->getPosOf(pQuest->subquests_[i]->title_))->getItem()->description_ == "NOT DISCOVERED" 
        && pQuest->subquests_[i]->description_ != "NOT DISCOVERED")) 
        {
            addQuest(pQuest->subquests_[i]);
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

/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::depenciesComplete(const Quest *pQuest) const
{
    for(int i = 0; i < pQuest->dependencies_.size(); i++)
    {
        if(pQuest->dependencies_[i]->completed_ == false) return false;
    }
    return true;
}

/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
bool QuestList::questAvailable(const Quest *pQuest) const
{
    if(this->depenciesComplete(pQuest) == false || pQuest->completed_ == true) return false;
    else return true;
}

/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest(const Quest *pQuest) const
{
    std::cout << pQuest->title_ << ": ";

    if(pQuest->completed_) std::cout << "Complete";
    else std::cout << "Not Complete";

    std::cout << "\n" << pQuest->description_ << "\n" << std::endl;
}

//gonna need the vector data type for the next method
#include <vector>   

//helper function for recursion in the next func
//Kyle's Function for recursive help
/**
    @param: A quest pointer to a quest
    @param: A vector to the ptrs of ready quests
    @param: A vector to the ptrs of not ready Quests
    @post:  uses recursion to add the not ready quests at the lowest level first, also adds readied quests to the ready vecotr
*/
void QuestList::recursiveQuestQuery(Quest *pQuest, std::vector<Quest*> &pReady, std::vector<Quest*> &pNotReady)
{
    //loop through the dependencies
    for(int i = 0 ; i < pQuest->dependencies_.size(); i++)
    {
        //make an iterator ptr for each iteration in the for loop and to pass through the recursive call if needed
        Quest *iterator = pQuest->dependencies_[i];
        
        //if this dependecy is competed, ignore it
        if(iterator->completed_ == true) continue;
        else
        {
            //if the dependecies are complete, add to the ready to go funcs
            //if they aren't that means that it should be added to the not ready vector
            //but call this function recursively to get the depencies of this depencies added first
            if(depenciesComplete(iterator)) pReady.push_back(iterator);
            else
            {
                recursiveQuestQuery(iterator, pReady, pNotReady);
                pNotReady.push_back(iterator);
            }
        }
    }
}

/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
            [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
            [Dependency2]
            [Quest Title]
            
    If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string &pTitle)
{
    //first lets take the test case that it does not exist
    if(!this->contains(pTitle))
    {
        std::cout << "Query: " << pTitle << "\nNo such quest." << std::endl;
        return;//if this dont exist, leave
    }

    //the rest of the cases rely on this quest, so lets get a pointer to the quest of this title
    Quest *currQuest = getPointerTo(this->getPosOf(pTitle))->getItem();

    //second case, the quest it already complete
    if(currQuest->completed_ == true)
    {
        std::cout << "Query: " << pTitle << "\nQuest Complete" << std::endl;
        return;//if this it's already completed, leave
    }

    //third case, the quest is already available
    if(this->depenciesComplete(currQuest))
    {
        std::cout << "Query: " << pTitle << "\nReady: " << pTitle << std::endl;
        return;//if this it's already completed, leave
    }

    //the last cases are have to do with having required depencies
    //it says to do this part recursivel for quests that have incomplete dependecies
    //what?? what even method would we be calling for that? questQuery??, im not getting that, so imma not do that for now //i only understand using a helper function for recursion
    //come back later, for now i can onlyy see using quest available
    std::vector<Quest*> readyVector;
    std::vector<Quest*> notReadyVector;

    recursiveQuestQuery(currQuest, readyVector, notReadyVector);
    
    std::cout << "Query: " << pTitle << std::endl;
    for(int i = 0; i < readyVector.size(); i++)
    {
        std::cout << "Ready: " << readyVector[i] << std::endl;
    }

    for(int i = 0; i < notReadyVector.size(); i++)
    {
        std::cout << "  " << notReadyVector[i] << std::endl;
    }

    std::cout << "  " << pTitle << std::endl;
}

