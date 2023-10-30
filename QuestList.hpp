//
//  QuestList.hpp
//
//  Inherited subclass of DoublyLinkedList
//
//Name : Kyle Bautista
//Instructor : Dr. Tiziana Ligorio
//Project 5

//

#ifndef QuestList_HPP
#define QuestList_HPP
#include "DoublyLinkedList.hpp"//for inheritence

#include <vector>
struct Quest
{
    //memember variables
    std::string title_;
    std::string description_;
    bool completed_;
    int EXP;
    std::vector<Quest*> dependencies_;
    std::vector<Quest*> subquests_;

    //constructors
    /**
        Default Constructor
        @post: Creates a new Quest object with default values (zero-initialized)
    */
    Quest() : 
    title_("N/A"), description_("NOT DISCOVERED"), completed_(false), EXP(0), dependencies_({}), subquests_({}) {}

    /*
    @param: A string reference to a quest title
    @param: A string reference to a quest description
    @param: A boolean representing if the quest is completed
    @param: A vector of Quest pointers representing the quest's dependencies
    @param: A vector of Quest pointers representing the quest's subquests
    @post: Creates a new Quest object with the given parameters
    */ //p stands for parameter
    Quest(std::string pTitle, std::string pDescription = "NOT DISCOVERED", bool pCompleted = false, int pEXP = 0, std::vector<Quest*> pDependcies = {}, std::vector<Quest*> pSubquests = {}) :
    title_(pTitle), description_(pDescription), completed_(pCompleted), EXP(pEXP), dependencies_(pDependcies), subquests_(pSubquests) {}

};

class QuestList : public DoublyLinkedList<Quest*>
{
    public:
        //constructors
        /**
            Default Constructor
        */
        QuestList();

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
       QuestList(const std::string &pFileName);

        //========================================================
        //unique methods
        //========================================================
        
        /**
            @param: A string reference to a quest title
            @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
        */
        int getPosOf(const std::string &pTitle) const;

        /**
            @param: A string reference to a quest title
            @return: True if the quest with the given title is already in the QuestList
        */
        bool contains(const std::string &pTitle) const;

        /**
            @pre: The given quest is not already in the QuestList
            @param:  A pointer to a Quest object
            @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
                    If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
                
            @return: True if the quest was added successfully, False otherwise
        */
        bool addQuest(Quest* pQuest);

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
        bool addQuest(std::string pTitle, std::string pDescription, bool pCompleted, int pEXP, std::vector<Quest*> pDependcies, std::vector<Quest*> pSubquests);
        
        /**
            @param:  A Quest pointer
            @return: A boolean indicating if all the given quest's dependencies are completed
        */
        bool depenciesComplete(const Quest *pQuest) const;

        /**
            @param: A Quest pointer
            @return: A boolean if the given quest is available.
            Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
        */
        bool questAvailable(const Quest *pQuest) const;

        /**
            @param: A Quest pointer
            @post: Prints the quest title and completion status
            The output should be of the form:
            [Quest Title]: [Complete / Not Complete]
            [Quest Description]\n\n
        */
        void printQuest(const Quest *pQuest) const;

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
        void questQuery(const std::string &pTitle); //this was originally const but my recursion changed that// must come back later

        /**
            @return: An integer sum of all the experience gained
            Note: This should only include experience from completed quests 
        */
        int calculateGainedExperience() const;

        /**
            @param: A quest pointer to a main quest
            @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
            Note: Also consider the potential experience if a subquest itself has subquests.
        */
        int calculateProjectedExperience(const Quest *pQuest) const;

        /**
            @param: A quest pointer to a main quest
            @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
            Note: Also consider the experience gained if a completed subquest itself has subquests.  
        */
        int calculatePathwayExperience(const Quest *pQuest) const;

        
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
        void questHistory(const std::string &pFilter = "NONE") const;

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
        void printQuestDetails(const Quest *pQuest);

        //helper function just to visualize the linkedList, going to steal the display code again
        /**
         * @post: prints the titles of all quest withing the list along with their pointer value
        */
        void KyleDisplay() const;

    //private for recrusvie helper function
    private:
        //Kyle's Function for recursive help
        /**
            @param: A quest pointer to a quest
            @param: A vector to the ptrs of ready quests
            @param: A vector to the ptrs of not ready Quests
            @post:  uses recursion to add the not ready quests at the lowest level first, also adds readied quests to the ready vecotr
        */
        void recursiveQuestQuery(Quest *pQuest, std::vector<Quest*> &pReady, std::vector<Quest*> &pNotReady);

        //Another recursive function but for the last func "printQuestDetails"
        /**
            @param: A quest pointer to a quest
            @param: An integer for depth, used to calculate how many indents
            @post:  uses recursion to print a list of subquests
        */
        void recursiveQuestDetails(Quest *pQuest, int depth = 1);
};

#endif //QuestList_HPP