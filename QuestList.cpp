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

//gonna need the vector data type for quest query and paramerterized construcotr
#include <vector>   

//include for taking a file in paramerterized constructor
#include <fstream>

//constructors
/**
    Default Constructor
*/
QuestList::QuestList(): DoublyLinkedList<Quest*>()
{
}

/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/
QuestList::QuestList(const std::string &pFileName) : DoublyLinkedList<Quest*>()
{
    item_count_ = 0;
    //get access to file
    std::ifstream questListParameters(pFileName);

    //check for failure to open file
    if(questListParameters.fail())
    {
        std::cerr << "File cannot be opened for reading." << std::endl;
        exit(1);//exit if failed to open
    }

    //remove first line
    std::string line;
    getline(questListParameters,line);

    //gonna need bool so we can set first_
    //i removed this as doubly linkedList may already take care of this
    //bool firstItem = true;

    while(getline(questListParameters, line))
    {
        //Title, Description, Completion, EXP, DEPENDENCIES, SUBQUESTS
        //  0       1           2           3       4           5

        //loop to get info from line
        std::vector<std::string> lineInformation;

        while(line.find(",") != -1)
        {
            lineInformation.push_back(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);
        }
        lineInformation.push_back(line);

        //now we create quests
        //first we need to create the depencies and subs as undiscovered, if they do exists
        std::vector<Quest*> dep = {};
        std::vector<Quest*> sub = {};

        //if there are dependencies
        if(lineInformation[4].find("NONE"))
        {
            while(lineInformation[4].find(";") != -1)
            {
                if(this->contains(lineInformation[4].substr(0, lineInformation[4].find(";"))))
                {
                    dep.push_back(this->getPointerTo(this->getPosOf(lineInformation[4].substr(0, lineInformation[4].find(";"))))->getItem());
                }
                else 
                {
                    Quest * newQuest = new Quest(lineInformation[4].substr(0, lineInformation[4].find(";")));
                    
                    //attempt to fix my last 10 points
                    this->addQuest(newQuest);

                    dep.push_back(newQuest);
                }
                lineInformation[4] = lineInformation[4].substr(lineInformation[4].find(";") + 1);
            }
            //get the last one too
            if(this->contains(lineInformation[4]))
            {
                dep.push_back(this->getPointerTo(this->getPosOf(lineInformation[4]))->getItem());
            }
            else
            {
                Quest * newQuest = new Quest(lineInformation[4]);

                //attempt to fix my last 10 points
                this->addQuest(newQuest);

                dep.push_back(newQuest);
            }     
        }

        //now same thing for subquests
        if(lineInformation[5].find("NONE") == -1)
        {
            while(lineInformation[5].find(";") != -1)
            {
                if(this->contains(lineInformation[5].substr(0, lineInformation[5].find(";"))))
                {
                    sub.push_back(this->getPointerTo(this->getPosOf(lineInformation[5].substr(0, lineInformation[5].find(";"))))->getItem());
                }
                else
                {
                    Quest * newQuest = new Quest(lineInformation[5].substr(0, lineInformation[5].find(";")));

                    //attempt to fix my last 10 points
                    this->addQuest(newQuest);

                    sub.push_back(newQuest);
                }
                
                lineInformation[5] = lineInformation[5].substr(lineInformation[5].find(";") + 1);
            }
            //they fixed it so damn no more substr
            //get the last one too
            //remove the space at the end
            //lineInformation[5] = lineInformation[5].substr(0, lineInformation[5].length()-1);
            if(this->contains(lineInformation[5]))
            {
                sub.push_back(this->getPointerTo(this->getPosOf(lineInformation[5]))->getItem());
            }
            else
            {
                Quest * newQuest = new Quest(lineInformation[5]);

                //attempt to fix my last 10 points
                this->addQuest(newQuest);

                sub.push_back(newQuest);
            }        
        }

        //finally now that have been instantiated, we can add the main quest;
        Quest * newMainQuest = new Quest(lineInformation[0], lineInformation[1], std::stoi(lineInformation[2]), std::stoi(lineInformation[3]), dep, sub);
        
        addQuest(newMainQuest);
    }
    questListParameters.close();
}

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
            
            //because both ptrs are suppose to be taking the same place, we can delete the old one the value at the old ptr and replace it with the new one
            //replaces it with the value held in this depdency
            *update = *pQuest;

            //now for the part that i had to fix later
            //i also forgot that pQuest is not the same as update, so we have to make pQuest now into update
            //to avoid memory leak, delete pQuest
            delete pQuest;
            //now we make the ptr of pQuest point to the old ptr
            pQuest = update;
             
        }
        else return false;
        // else if(this->getPointerTo(this->getPosOf(pQuest->title_))->getItem()->description_ != "NOT DISCOVERED")
        // {
        //     //i also had to add this one to fix my code, for context quest 1 is added through debug but quest 4 also adds it as a dependcy
        //     //i was thinking of making the quest 4 dependency point to quest 1, but im realizing i dont need to do that here and i can do that that in parmeterized construcotr

        //     //i came back to this as i was having issue with print quest details where quest 1 was made in the parmeterized constructor but in the subquest for quest 3, 
        // }
    }
    else
    {
        //add using parent class function
        this->insert(this->item_count_, pQuest);
    }

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
bool QuestList::addQuest(const std::string & pTitle, const std::string & pDescription, const bool &pCompleted, const int &pEXP, const std::vector<Quest*> &pDependcies, const std::vector<Quest*> &pSubquests)
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
bool QuestList::dependenciesComplete(const Quest *pQuest) const
{
    for(int i = 0; i < pQuest->dependencies_.size(); i++)
    {   
        if(pQuest->dependencies_[i]->completed_ == false)
        {
            // std::cout << pQuest->dependencies_[i]->title_ << " c : ";
            // std::cout << pQuest->dependencies_[i]->completed_ << std::endl;
            return false;
        } 
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
    if(this->dependenciesComplete(pQuest) == false || pQuest->completed_ == true) return false;
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
            if(dependenciesComplete(iterator)) pReady.push_back(iterator);
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
    if(this->dependenciesComplete(currQuest))
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
        std::cout << "Ready: " << readyVector[i]->title_ << std::endl;
    }

    for(int i = 0; i < notReadyVector.size(); i++)
    {
        std::cout << "  " << notReadyVector[i]->title_ << std::endl;
    }

    std::cout << "  " << pTitle << std::endl;
}

/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience() const
{
    //i can steal code from the orginal DoublyLinkedList.cpp file
    //below is modified code of the display method
    if (this->getLength() == 0)
    {
        return 0;
    }

    //iterator and int to hold sum of all completed thingys
    Node<Quest*> *iterator = first_;
    int sum = 0;

    while (iterator != nullptr)
    {
        if(iterator->getItem()->completed_ == true) sum += iterator->getItem()->experience_points_;
        iterator = iterator->getNext();
    }
    return sum;
}

/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience(const Quest *pQuest) const
{
    //right off the bat, the note implies recursion
    int sum = pQuest->experience_points_;
    //lowkey, this may not work and may count the same quest multiple times if subquests share a subquest
    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        sum += calculateProjectedExperience(pQuest->subquests_[i]);
    }
    return sum;
}

/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience(const Quest *pQuest) const
{
    //almost the same thing as the previous method but check if the subquest is also completed
    //also different, do not include main quest//wait do i?
    int sum = 0;
    if(pQuest->completed_) sum += pQuest->experience_points_;

    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        if(pQuest->subquests_[i]->completed_)
        {
            sum += calculatePathwayExperience(pQuest->subquests_[i]);
        }
    }
    
    return sum;
}

        
/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
        With filter "COMPLETE":   Only print out the completed quests in the list.
        With filter "INCOMPLETE": Only print out the incomplete quests in the list.
        With filter "AVAILABLE":  Only print out the available quests in the list.
        If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string &pFilter) const
{
    //can also steal the display code for this method
    if (this->getLength() == 0)
    {
        return;
    }
    
    if(pFilter != "NONE" && pFilter != "COMPLETE" && pFilter != "INCOMPLETE" && pFilter != "AVAILABLE")
    {
        std::cout << "Invalid Filter" << std::endl; 
    }

    Node<Quest*> *iterator = first_;

    while (iterator != nullptr)
    {
        if(pFilter == "NONE")
        {
            printQuest(iterator->getItem());
        }
        else if((pFilter == "COMPLETE"))
        {
            if(iterator->getItem()->completed_) printQuest(iterator->getItem());
        }
        else if((pFilter == "INCOMPLETE"))
        {
            if(!iterator->getItem()->completed_) printQuest(iterator->getItem());
        }
        else if((pFilter == "AVAILABLE"))
        {
            if(questAvailable(iterator->getItem())) printQuest(iterator->getItem());
        }
        
        iterator = iterator->getNext();
    }
}
#include <string>

/**
    @param: A quest pointer to a subquest
    @param: An integer for depth, used to calculate how many indents
    @post:  uses recursion to print a list of subquests
*/
void QuestList::recursiveQuestDetails(Quest *pQuest, int depth)
{
    std::string output = "";//need an empty string for indentations 
    for(int i = 0; i < depth; i++)
    {
        output += "  ";
    }
    
    output += pQuest->title_;
    output += ": ";

    if(pQuest->completed_) output += "Complete";
    else output += "Not Complete";

    std::cout << output << std::endl;

    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        recursiveQuestDetails(pQuest->subquests_[i], depth + 1);
    }

    //Originally my code looked like this but for some reason the string aint holding my stuffs?
    /*
    std::string output = "";//need an empty string for indentations 
    for(int i = 0; i < depth; i++)
    {
        output += "  ";
    }
    
    output += pQuest->title_;
    output += ": ";

    if(pQuest->completed_) output += "Complete";
    else output += "Not Complete";

    std::cout << output << std::endl;
    */
}

/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printQuestDetails(const Quest *pQuest)
{
    std::cout << pQuest->title_ << " (" << (int)(((double)calculatePathwayExperience(pQuest) / calculateProjectedExperience(pQuest))*100) << "% Complete)" << std::endl;

    for(int i = 0; i < pQuest->subquests_.size(); i++)
    {
        //std::cout << pQuest->subquests_[i]->title_ << std::endl;
        recursiveQuestDetails(pQuest->subquests_[i]);
    }

}

//helper function just to visualize the linkedList, going to steal the display code again
/**
 * @post: prints the titles of all quest withing the list along with their pointer value
*/
void QuestList::KyleDisplay() const
{
    if (getLength() == 0)
    {
        return;
    }
    Node<Quest*> *iterator = first_;
    while (iterator != nullptr)
    {
        std::cout << iterator->getItem()->title_ << " : " << iterator->getItem() << std::endl;
        iterator = iterator->getNext();
    }
    std::cout << std::endl;
}

//same idea as the last display, but include the member variables and subs and deps and their ptrs
/**
 * @post: prints the titles of all quest withing the list along with their pointer value and all their details 
*/
void QuestList::KyleFullDisplay() const
{
    if (getLength() == 0)
    {
        return;
    }
    Node<Quest*> *iterator = first_;
    while (iterator != nullptr)
    {
        std::cout << iterator->getItem()->title_ << " : " << iterator->getItem() << std::endl;
        std::cout << "Descriptions: " << iterator->getItem()->description_ << std::endl;
        std::cout << "Completed: " << iterator->getItem()->completed_ << std::endl;
        std::cout << "Experience Points: " << iterator->getItem()->experience_points_ << std::endl;
        
        if(iterator->getItem()->dependencies_.size() != 0)
        {
            std::cout << "Dependents: \n{"<< std::endl;
            for(int i = 0; i < iterator->getItem()->dependencies_.size(); i++)
            {
                std::cout << "  " << iterator->getItem()->dependencies_[i]->title_ << " : " << iterator->getItem()->dependencies_[i] << std::endl;
            }       
            std::cout << "}"<< std::endl;
        }

        if(iterator->getItem()->subquests_.size() != 0)
        {        
            std::cout << "Subsequents: \n{"<< std::endl;
            for(int i = 0; i < iterator->getItem()->subquests_.size(); i++)
            {
                std::cout << "  " << iterator->getItem()->subquests_[i]->title_ << " : " << iterator->getItem()->subquests_[i] << std::endl;
            }
            std::cout << "}" << std::endl;
        }
        
        std::cout << std::endl;

        iterator = iterator->getNext();
    }
    std::cout << std::endl;
}