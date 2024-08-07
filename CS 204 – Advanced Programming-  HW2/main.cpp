#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
/******************************************************************************
Sabanci  University CS204 Advanced Programming Homework2 – Matching Pairs using Linked Lists
Coded by: Osman Kantarcioglu    -   30891   - Section:B2
Date: 06/03/2024
******************************************************************************/
using namespace  std;
struct NodeLike
{
    string subject;
    string object;
    NodeLike* next;
};
struct NodeTaken
{
    string name;
    NodeTaken* next;
};
/******************************************************************************
This function is used to print the element of the likeList
******************************************************************************/
void likeListPrinter(NodeLike* head)
{
    NodeLike* currentPosition = head;
    cout << "Likes list:";
    while (currentPosition != NULL)
    {
        cout << " (" << currentPosition->subject << ", " << currentPosition->object << ")";
        currentPosition = currentPosition->next;
    }
    cout << endl;
}
/******************************************************************************
This function is used to print the element of the takenList
******************************************************************************/
void takenListPrinter(NodeTaken* head)
{
    NodeTaken* currentPosition = head;
    cout << "Taken list:";
    while (currentPosition != NULL)
    {
        cout << " " << currentPosition->name;
        currentPosition = currentPosition->next;
    }
    cout << endl << endl;
}
/******************************************************************************
This function is used to check whether subject or object exist in taken list
This condition checks first rule of processing of a “subject likes object” line
******************************************************************************/
bool isAnyOrBothExistInTakenList(NodeTaken* head, string subject, string object)
{
    while (head != NULL)
    {
        if (subject == head->name || object == head->name)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
/******************************************************************************
This function is used to check whether subject and object pair already exist
If subject-object pair is already in the likes linked list as is, this relationship will be
considered as redundant
This condition checks second rule of processing of a “subject likes object” line
******************************************************************************/
bool subjectObjectPairExistInLikes(NodeLike* head, string subject, string object)
{
    while (head != NULL)
    {
        if (head->subject == subject && head->object == object)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
/******************************************************************************
This function is used to check whether there exists a reverse relationship in the
likes linked list such that subject of the input line is the object of a node and
object of the input line is subject of the same node
This condition checks third rule of processing of a “subject likes object” line
******************************************************************************/
bool reverseRelationshipExists(NodeLike* head, string subject, string object)
{
    while (head != NULL)
    {
        if (head->subject == object && head->object == subject)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
/******************************************************************************
This function is used to check whether only the subject of the input line exists
in at least one node in the likes linked list as subject
This condition checks fourth rule of processing of a “subject likes object” line
******************************************************************************/
bool sameSubjectDifferentObject(NodeLike* head, string subject, string object)
{
    while (head != NULL)
    {
        if (head->subject == subject && head->object != object)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
/******************************************************************************
This function is used to check whether subject is in the likes linked list
This condition checks fifth rule of processing of a “subject likes object” line
******************************************************************************/
bool subjectInLikesList(NodeLike* head, string subject)
{
    while (head != NULL)
    {
        if (head->subject == subject)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
/******************************************************************************
This function is used to add element to the end if fifth rule executed (If the subject
is not in the likes linked list and is allowed to be added to it, (i.e., it is not in
the taken linked list), then it should be added to the end of the likes linked list. )
This explanation is taken from homework document
******************************************************************************/
void addElementToEnd(NodeLike*& head, string subject, string object)
{
    NodeLike* newNode = new NodeLike;
    newNode->subject = subject;
    newNode->object = object;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        NodeLike* currentNode = head;
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}
/******************************************************************************
This function is used to insert a new node containing input subject-object pair
in the likes linked list just after the last node that contains this subject’s
name in its subject field. This function iterates when there is at least one node
with same subject but different object name
******************************************************************************/
void insertNewNode(NodeLike*& head, string subject, string object)
{
    NodeLike* currentNode = head;
    NodeLike* lastRepetation = NULL;
    while (currentNode != NULL)
    {
        if (currentNode->subject == subject)
        {
            lastRepetation = currentNode;
        }
        currentNode = currentNode->next;
    }
    NodeLike* toBeAdded = new NodeLike;
    toBeAdded->subject = subject;
    toBeAdded->object = object;
    toBeAdded->next = lastRepetation->next;
    lastRepetation->next = toBeAdded;
}
/******************************************************************************
This function is used to find node to delete according to given subject and object name.
This function is used in the main as a parameter of deleteNodeFromLikeList function
to delete desired node from like list
******************************************************************************/
NodeLike* findDesiredNode(NodeLike* head, string givenSubject, string givenObject)
{
    NodeLike* currentNode = head;
    while (currentNode != NULL)
    {
        if (currentNode->subject == givenSubject && currentNode->object == givenObject)
        {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}
/******************************************************************************
I am inspired from our lecture slides (2.2-pointers-linkedlist, deleting a node section)
This function is used to delete element from like list when reverse relationship is found
******************************************************************************/
void deleteNodeFromLikeList(NodeLike*& head, NodeLike* toBeDeleted)
{
    NodeLike* currentNode;
    if (toBeDeleted == head)
    {
        head = head->next;
        delete toBeDeleted;
    }
    else
    {
        currentNode = head;
        while (currentNode->next != toBeDeleted)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = toBeDeleted->next;
        delete toBeDeleted;
    }
}
/******************************************************************************
I am again inspired from our lecture slides
This function is used to add element to TAKEN LIST in ALPHABETICAL ORDER
******************************************************************************/
void addInAlphabeticalOrder(NodeTaken*& head, string name)
{
    NodeTaken* currentNode = head;
    NodeTaken* tempNode = new NodeTaken;
    if (head == NULL || name < head->name)
    {
        tempNode->name = name;
        tempNode->next = head;
        head = tempNode;
    }
    else
    {
        while (currentNode->next != NULL && currentNode->next->name < name)
        {
            currentNode = currentNode->next;
        }
        tempNode->name = name;
        tempNode->next = currentNode->next;
        currentNode->next = tempNode;
    }
}
/******************************************************************************
This function is used to delete nodes. If a name is added to the taken list,
it can no longer be found in the liked list. Therefore it deletes all nodes
of the object and subject family given in the like list.
******************************************************************************/
void deleteInvalidNames(NodeLike*& headLike, NodeTaken* headTaken)
{
    NodeLike* currentNode = headLike;
    while (currentNode != NULL)
    {
        if (isAnyOrBothExistInTakenList(headTaken, currentNode->subject, currentNode->object))
        {
            NodeLike* toBeDeleted = currentNode;
            deleteNodeFromLikeList(headLike, toBeDeleted);
        }
        currentNode = currentNode->next;
    }
}
/******************************************************************************
I am again inspired from our lecture slides.
This function is used to delete linked list after process has finished.
******************************************************************************/
void deleteLikeList(NodeLike* headLike) {
    if (headLike != NULL)
    {
        deleteLikeList(headLike->next);
        delete headLike;
    }
}
/******************************************************************************
Similar to the previous function. This function is used to delete taken list
 after process has finished.
******************************************************************************/
void deleteTakenList(NodeTaken* headTaken) {
    if (headTaken != NULL)
    {
        deleteTakenList(headTaken->next);
        delete headTaken;
    }
}
int main() {
    //Program starts by asking user to enter a file name for input file
    string fileName;
    cout << "Please enter the file name:" << endl;
    cin >> fileName;
    //Program opens file
    ifstream input;
    input.open(fileName.c_str());
    //Check whether the file is opened successfully or not
    //While file is not opened successfully, get input until user enter correct one
    while (!input.is_open())
    {
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> fileName;
        input.open(fileName.c_str());
    }
    //After opening the file ,places the characters in the matrix (read content into matrix)
    NodeLike* NodeLikeHead = new NodeLike;
    NodeTaken* NodeTakenHead = new NodeTaken;
    NodeLikeHead = NULL;
    NodeTakenHead = NULL;
    int counter = 0;
    string line, subject, object, verb;
    //Read file line by line until end of the file
    while (!input.eof())
    {
        counter++;
        getline(input, line);
        cout << "Read line number (" << counter << "): " << line << endl;
        stringstream ss(line);
        ss >> subject >> verb >> object; //string stream used to avoid space error
        if (isAnyOrBothExistInTakenList(NodeTakenHead, subject, object)) //If any of the subject or the object (or both) of this line is already in the taken linked list
        {
            cout << "Either " << subject << " or " << object << " or both is/are already taken, so the like relation is not added." << endl; // Error message is given.
            likeListPrinter(NodeLikeHead); // Lists are printed.
            takenListPrinter(NodeTakenHead);
        }
        else if (subjectObjectPairExistInLikes(NodeLikeHead, subject, object)) //If subject-object pair is already in the likes linked list.
        {
            cout << subject << " likes " << object << " relation already exists in the likes list, so it is not added to it." << endl;// Error message is given.
            likeListPrinter(NodeLikeHead);// Lists are printed.
            takenListPrinter(NodeTakenHead);
        }
        else if (reverseRelationshipExists(NodeLikeHead, subject, object)) //if there exists a reverse relationship in the likes linked list
        {
            cout << "Match found: " << subject << " likes " << object << " and " << object << " likes " << subject << "." << endl; //Gives messages.
            cout << "Added to taken list: " << subject << endl;
            cout << "Added to taken list: " << object << endl;
            cout << "Any node that has " << subject << " or " << object << " or both in it is removed from the likes list." << endl;
            deleteNodeFromLikeList(NodeLikeHead, findDesiredNode(NodeLikeHead, object, subject)); //Given node is deleted from like list
            addInAlphabeticalOrder(NodeTakenHead, subject); // Subject and object added to taken list in alphabetic order.
            addInAlphabeticalOrder(NodeTakenHead, object);
            deleteInvalidNames(NodeLikeHead, NodeTakenHead); //deletes all nodes of the object and subject family given in the like list.
            likeListPrinter(NodeLikeHead);// lists are printed
            takenListPrinter(NodeTakenHead);
        }
        else if (sameSubjectDifferentObject(NodeLikeHead, subject, object)) //if only the subject of the input line exists in at least one node
        {
            cout << subject << " likes " << object << " relation has been added to the likes list." << endl;
            insertNewNode(NodeLikeHead, subject, object);
            // insert a new node containing input subject-object pair in the likes linked list
            //just after the last node that contains this subject’s name in its subject field
            likeListPrinter(NodeLikeHead);// lists are printed
            takenListPrinter(NodeTakenHead);
        }
        else if (!subjectInLikesList(NodeLikeHead, subject)) //If the subject is not in the likes linked list
        {
            cout << subject << " likes " << object << " relation has been added to the likes list." << endl;
            addElementToEnd(NodeLikeHead, subject, object); //added to the end of the likes linked list.
            likeListPrinter(NodeLikeHead);// lists are printed
            takenListPrinter(NodeTakenHead);
        }
    }
    //Before program finished, I deleted all linked lists.
    deleteLikeList(NodeLikeHead);
    deleteTakenList(NodeTakenHead);
    cout << "Lists are deleted and the program ends successfully.";
}