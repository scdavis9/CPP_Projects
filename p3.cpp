#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size; // Implictly this->size;
}

void printPerson(Person* person, ostream& os) {
    os << person->first << ' ' << person->last << ": height=" << person->height << ", weight=" << person->weight << '\n';
}

/*
    PersonList list = // ...
    list.printByHeight(std::cout);
    ofstream file = // ...
    list.printByHeight(file);
*/

void PersonList::printByHeight(ostream &os)
{
    Person* current = headHeightList;
    while(current != nullptr) {
        printPerson(current, os);
        current = current->nextHeight;    
    }

}

void PersonList::printByWeight(ostream &os)
{
    Person* current = headWeightList;
    while(current != nullptr) {
        printPerson(current, os);
        current = current->nextWeight;    
    }
}

// Returns a pointer to a person with matching first and last name, if a person exists in list.
// Otherwise return nullptr
Person* PersonList::findPerson(string first, string last) {
    Person* current = headHeightList;
    while(current != nullptr) {
        if(current->first == first && current->last == last) { //current pointer to the actual person 
            return current;
        }

        current = current->nextHeight;
    }
    return nullptr;
}

bool PersonList::exists(string first, string last)
{
    bool exists = findPerson(first, last) != nullptr;
    return exists;
}

int PersonList::getHeight(string first, string last) {
    Person* searchResult = findPerson(first, last);

    if(searchResult!=nullptr) {
        return searchResult->height;
    }

    return -1;
}

int PersonList::getWeight(string first, string last) {
    Person* searchResult = findPerson(first, last); // pointer to person allows access to all of the variables within

    if(searchResult!=nullptr) {
        return searchResult->weight;
    }

    return -1;
}

// Get pointer to element in height order which precedes a person with a given first and last name
// If no person with the given first and last name exists or if such a person is the first element of the list, return nullptr
Person* PersonList::findPredecessorHeight(string first, string last) {
    Person* current = headHeightList;

    if (current == nullptr)
        return nullptr;

    while(current->nextHeight != nullptr) {
        Person* next = current->nextHeight;
        if(next->first == first && next->last == last) {
            return current;
        }

        current = next;
    }
    return nullptr;
}

// Get pointer to element in weight order which precedes a person with a given first and last name
// If no person with the given first and last name exists or if such a person is the first element of the list, return nullptr
Person* PersonList::findPredecessorWeight(string first, string last) {
    Person* current = headWeightList;

    if (current == nullptr)
        return nullptr;

    while(current->nextWeight != nullptr) {
        Person* next = current->nextWeight;
        if(next->first == first && next->last == last) {
            return current;
        }

        current = next;
    }
    return nullptr;
}

// Get pointer to element which in height order would precede a person of a given height and weight if such a person were inserted
// If no such element exists, return nullptr
Person* PersonList::insertionPredecessorHeight(int height, int weight) {
    Person* prev = nullptr;
    Person* current = headHeightList;

    while(current != nullptr) {
        if(current->height < height || (current->height == height && current->weight > weight)) {
            return prev;
        }

        prev = current;
        current = current->nextHeight;
    }
    return prev;
}

// Get pointer to element which in weight order would precede a person of a given height and weight if such a person were inserted
// If no such element exists, return nullptr
Person* PersonList::insertionPredecessorWeight(int height, int weight) {
    Person* prev = nullptr;
    Person* current = headWeightList;

    while(current != nullptr) {
        if(current->weight > weight || (current->weight == weight && current->height < height)) {
            return prev;
        }

        prev = current;
        current = current->nextWeight;
    }
    return prev;
}

// If a person with the given attributes is not in the list, insert this person into the list, and return true.
// If such a person already is in the list, return false, and do nothing.
bool PersonList::add(string first, string last, int height, int weight)
{
    // Check if person is already in the list
    if (this->exists(first, last))
    {
        return false;
    }
    Person *p = new Person(first, last, height, weight);

	// Find elements which will come directly before the person to insert.
    // These are the points in the linked list at which we will insert the new person.
    Person* heightPredecessor = insertionPredecessorHeight(height, weight);
    Person* weightPredecessor = insertionPredecessorWeight(height, weight);

    // If no element in the list will come before the new person, this new person will become the head of the list.
    if (heightPredecessor == nullptr) {
        // The old head of the list now comes direclty after the new person
        p->nextHeight = headHeightList;
        // Update the new head of the list to be the person which we are adding
        headHeightList = p;
    }

    // Otherwise there will be some element in the list which comes before the new person
    else {
        // The person which comes after the predecessor will come after the new person since which will be between this person and the predecessor
        p->nextHeight = heightPredecessor->nextHeight;
        // Update the preceding element so that it's next element is the new person
        heightPredecessor->nextHeight = p;
    }

    if (weightPredecessor == nullptr) {
        p->nextWeight = headWeightList;
        headWeightList = p;
    }
    else {
        p->nextWeight = weightPredecessor->nextWeight;
        weightPredecessor->nextWeight = p;
    }

    size++;
	return true;
}

// Remove a person from the list with the given attributes and return ture or return false if no such person exists.
bool PersonList::remove(string first, string last)
{
    // Check if person is in the list
    Person* temp = findPerson(first, last);
    
    if (temp == nullptr)
        return false;

    // Find predecessors of person
    Person* heightPredecessor = findPredecessorHeight(first, last);
    Person* weightPredecessor = findPredecessorWeight(first, last);

    // If the moribund person is the head of list, then after removal, the new head will be the person which comes after the moribund person
    if (heightPredecessor == nullptr) {
        headHeightList = temp->nextHeight;
    }
    // Otherwise after the moribund person is removed, the person after the moribund person person becomes the person after the preceding person
    else {
        heightPredecessor->nextHeight = temp->nextHeight;
    }

    if (weightPredecessor == nullptr) {
        headWeightList = temp->nextWeight;
    }
    else {
        weightPredecessor->nextWeight = temp->nextWeight;
    }

    delete temp;
    size--;

    return true;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    Person* existPerson = findPerson(first, last);
    if(!existPerson) {
    return false;
    }

    existPerson->first = newFirst;
    existPerson->last = newLast;

    return true;
}

bool PersonList::updateHeight(string first, string last, int height)
{
    Person* existPerson = findPerson(first, last);
    if(!existPerson) {
        return false;
    }
    else {
        int weight = existPerson->weight;
        remove(first, last);
        add(first, last, height, weight);
        return true;
    }
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    Person* existPerson = findPerson(first, last);
    if(!existPerson) {
        return false;
    }
    else {
        int height = existPerson->height;
        remove(first, last);
        add(first, last, height, weight);
        return true;
    }
}

// Empties contents of a PersonList
void PersonList::clear() {
    while(size!=0) {
        remove(headHeightList->first, headHeightList->last);
    }
}

// Helper function which copies the people from source to the "this" PersonList
void PersonList::copy(const PersonList& source) {
    Person* current = source.headHeightList;

    while(current != nullptr) {
        add(current->first, current->last, current->height, current->weight);
        current = current->nextHeight;
    }
}

// Cleans up memory used by a PersonList
PersonList::~PersonList()
{
    clear();
}

PersonList::PersonList(const PersonList &src)
{
    size = 0;
    headHeightList = nullptr;
    headWeightList = nullptr;
    copy(src);
}

// Sets contents of "this" PersonList to be equal to contents of the "src" PersonList
const PersonList &PersonList::operator=(const PersonList &src)
{
    // Self-assignment check:
    // if a is a PersonList then
    // a = a must have no effect
    // Without this check, we may inadvertently clear a list.
    if (this != &src) {
        // Clean up memory which was used by old contents
        clear();
        // Add new contents
        copy(src);
    }

    return *this;
}
