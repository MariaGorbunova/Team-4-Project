
#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H
#include "entry.h"
#include "node.h"
#include <fstream>

class  hashEntry
{
private:
    int tableSize;
    entry* hashTable;
    Node* overFlow;
    int collisions;

public:
    hashEntry(const int tableSizeIn);
    ~hashEntry();
    int Hash(string& key) const; /// hash method
    void insertNode(iPhone* ptrIn); /// insert node to overflow area
    void insertEntry(string& key, iPhone* ptrIn); /// insert data in the hashTable
    void printEntry() const;    /// print all unsorted data from the hashTable and overflow area
    iPhone* searchEntry(string key) const; /// instantly search a key
    bool removeEntry(string key); /// remove data from hashTable and overflow area
    void deleteTable(); /// destroy the table and overflow area
    int getCollisions() const; /// get number of collisions
    int getUsedBuckets() const; /// get number of occupied buckets
    int getUsedEntries() const; /// get number of occupied entries
    float bucketsLoadedFactor() const; /// number of occupied buckets / number of total buckets
    float entriesLoadedFactor() const;  /// number of occupied entries / number of total entries
    void writeFile() const; /// write out an updated file
};

hashEntry::hashEntry(const int tableSizeIn)
{
    tableSize = tableSizeIn;
    hashTable = new entry[tableSize]; /// allocate the hashTable by the size passed in from main
    overFlow = new Node(nullptr); /// dummy node for overflow area
    collisions = 0;
}

hashEntry::~hashEntry()
{
    deleteTable();
}
/* ************************
 
*************************** */


int hashEntry::Hash(string& key) const /// hash function
{
    int sum = 0;
    for(unsigned int i=0; i < key.length(); i++) /// go through the key up to the key lenght
    {
        sum += key[i] - '0'; /// convert string to ASCII value and add up value of all digits
    }
    return (sum*sum*sum)%tableSize; /// return triple of sum and modulus by table size to make sure hash index in range
}

void hashEntry::insertNode(iPhone* ptrIn)/// add new node in overflow area when collisions occur
{
    Node* ptr = overFlow;
    Node* newNode = new Node(ptrIn);

    /// Skip all nodes until the last node
    while (ptr->getNext() != nullptr)
        ptr = ptr->getNext();

    /// Update links to insert the new node
    ptr->setNext(newNode);
    collisions++;
}

void hashEntry::insertEntry(string& key, iPhone* ptrIn)/// insert data to hashTable and overflow area
{
    int index = Hash(key);  /// get index from hash function
    if(hashTable[index].getCount() < bucketsNum) /// if number of available buckets < 3, add data to table
    {
        hashTable[index].setBucket(hashTable[index].getCount(), ptrIn);
        /// if count = 0 (empty buckets) -> add to index 0
        /// if count = 1 (index 0 is occupied) -> add to index 1
        /// if count = 2 (index 0 and 1 are occupied in) -> add to index 2 (full)
        hashTable[index].increseCount();
    }
    else insertNode(ptrIn); /// else bucket counter >= 3, add data to overflow area
}

void hashEntry::printEntry() const /// print data in hashTable and overflow area
{
    for(int i=0; i< tableSize; i++)  /// go from 0 to the table size
    {
        if(hashTable[i].getCount() > 0) /// only print data in the entries have count > 0 (occupied)
        {
            for(int j=0; j< hashTable[i].getCount(); j++) /// go from 0 to number of bucket count
            {
                std::cout << "Index " << i << " bucket " << j << ": "; /// indicator illustrates how table looks like
                hashTable[i].getBucket(j)->displayInfo();
                         /*  << hashTable[i].getBucket(j)->getIMEI() << " "
                          << hashTable[i].getBucket(j)->getCapacity() << " "
                          << hashTable[i].getBucket(j)->getSerialNum() << " "
                          << hashTable[i].getBucket(j)->getModel() << " "
                          << hashTable[i].getBucket(j)->getManuLocn() << std::endl;*/
            }
        }
        //else std::cout << "Index " << i << " are empty" << std::endl;
    }

    if(overFlow->getNext() == nullptr) return; /// return if the overflow area is empty
    Node* ptr = overFlow->getNext();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Overflow area: " << std::endl;

    while(ptr)
    {
        ptr->getData()->displayInfo();
        /*std::cout << ptr->getData()->getIMEI() << " "
                  << ptr->getData()->getCapacity() << " "
                  << ptr->getData()->getSerialNum() << " "
                  << ptr->getData()->getModel() << " "
                  << ptr->getData()->getManuLocn() << std::endl; */
        ptr = ptr->getNext();
    }
}

iPhone* hashEntry::searchEntry(string key) const /// instant search from hashTable and overflow area
{
    int index = Hash(key);

    /// Case 1: buckets contain items
    if(hashTable[index].getCount() > 0)
    {
        ///Check the buckets
        for(int i=0; i< hashTable[index].getCount(); i++) /// go from 0 to number of occupied buckets
        {
            if(hashTable[index].getBucket(i)->getIMEI() == key) /// if the key is matched
            {
                std::cout << "Index " << index << " bucket " << i << ": " ;
                hashTable[index].getBucket(i)->displayInfo();
                          /* << hashTable[index].getBucket(i)->getIMEI() << " "
                          << hashTable[index].getBucket(i)->getCapacity() << " "
                          << hashTable[index].getBucket(i)->getSerialNum() << " "
                          << hashTable[index].getBucket(i)->getModel() << " "
                          << hashTable[index].getBucket(i)->getManuLocn() << std::endl;*/
                return hashTable[index].getBucket(i);
            }
        }
        /// Check overflow area
        Node* ptr = overFlow->getNext();
        int n = 1;
        while(ptr && ptr->getData()->getIMEI() != key)
        {
            ptr = ptr->getNext();
            n++;
        }

        /// overflow area doesn't have the item
        if(!ptr)
        {
            std::cout << "Item with this IMEI " << key << " is not in the database. " << std::endl;
            return nullptr;
        }
        else
        {
            std::cout << "Overflow nodes " << n << ": ";
            ptr->getData()->displayInfo();
            /*
                      << ptr->getData()->getIMEI() << " "
                      << ptr->getData()->getCapacity() << " "
                      << ptr->getData()->getSerialNum() << " "
                      << ptr->getData()->getModel() << " "
                      << ptr->getData()->getManuLocn() << std::endl;*/
            return ptr->getData();
        }
    }

    ///case 0: buckets are empty,which means there is no synonym for that index
    ///return immediately no needs to check table or overflow area
    std::cout << "Item  with this IMEI " << key << " is not in the database. " << std::endl;
    return 0;
}

bool hashEntry::removeEntry(string key)
{
    int index = Hash(key);
    //iPhone* delPtr;

    /// case 1: buckets contain items
    /// [*][x][x] wanna remove index the 1st bucket
    /// [*][*][x] wanna remove index the 2nd bucket
    /// [*][*][*] wanna remove index the 3rd bucket
    if(hashTable[index].getCount() > 0)
    {
        ///
        /// case 1.1: item in THE LAST OCCUPIED BUCKET
        /// [*][x][x] wanna remove index the 1st bucket
        /// [*][*][x] wanna remove index the 2nd bucket
        /// [*][*][*] wanna remove index the 3rd bucket
        if(hashTable[index].getBucket(hashTable[index].getCount()-1)->getIMEI() == key)
        {
            hashTable[index].getBucket(hashTable[index].getCount()-1);
       
            hashTable[index].setBucket(hashTable[index].getCount()-1, nullptr);
            //delete delPtr;
            hashTable[index].decreaseCount();
            //std::cout << "Item " << key << " has been deleted." << std::endl;
            return true;
        }

        /// case 1.2: item not in the last available bucket
        /// case 1.2: item not in the last available bucket
        /// [*][*][x] wanna remove index the 1st
        /// [*][*][*] wanna remove index the 1st or 2nd bucket
        else
        {
            for(int i=0; i< hashTable[index].getCount(); i++)
            {
                if(hashTable[index].getBucket(i)->getIMEI() == key)
                {
                    /// set the bucket i points to the same object that the last occupied bucket points to
                    /// [*][*][x] 1st bucket points to same object as 2nd bucket
                    /// [*][*][*] 1st bucket points to same object as 3rd bucket
                    /// [*][*][*] 2nd bucket points to same object as 3rd bucket
                    hashTable[index].getBucket(i);
                    
                    hashTable[index].setBucket(i, hashTable[index].getBucket(hashTable[index].getCount()-1));
                    /// set the last occupied bucket points to null
                    /// [*][*][x] 2nd bucket points to null -> [*][x][x]
                    /// [*][*][*] 3rd bucket points to null -> [*][*][x]
                    hashTable[index].setBucket(hashTable[index].getCount()-1, nullptr);
                    //delete delPtr;
                    hashTable[index].decreaseCount();
                    //std::cout << "Item " << key << " has been removed." << std::endl;
                    return true;
                }
            }
        }

        /// case 2: the item in overflow area
        Node* ptr = overFlow->getNext();
        Node* prePtr = overFlow;
        while(ptr && ptr->getData()->getIMEI() != key) /// traverse through the list until match the key
        {
            prePtr = ptr;
            ptr = ptr->getNext();
        }

        /// case 2.1: overflow area doesn't have the item
        if(!ptr)
        {
            std::cout << "Item " << key << " was not found" << std::endl;
            return false;
        }
        ///case 2.2: overflow has the item
        else
            //delPtr = ptr->getData();
        prePtr->setNext(ptr->getNext()); /// update pointers
        //delete delPtr;
        delete ptr;
        collisions--;
        //std::cout << "Item " << key << " has been removed." << std::endl;
        return true;
    }

    ///case 0: buckets are empty,  which means there is no synonym for that index
    ///return immediately no needs to check table or overflow area
    std::cout << "Item " << key << " does not exist in the database yet." << std::endl;
    return false;
}

void hashEntry::deleteTable()
{
    iPhone* delPtr;
    ///delete hash table
    for(int i=0; i < tableSize; i++)
    {
        if(hashTable[i].getCount() > 0) /// only execute when the entries have occupied buckets
        {
            for(int j=0; j < hashTable[i].getCount(); j++)
            {
                delPtr = hashTable[i].getBucket(j); /// let delPtr points to the object
                delete delPtr;
            }
        }
    }

    delete [] hashTable;

    ///delete overflow area
    Node* ptr = overFlow;
    Node* nextPtr;
    while (ptr != NULL)
    {
        delPtr = ptr->getData();
        nextPtr = ptr->getNext();
        delete delPtr;
        delete ptr;
        ptr = nextPtr;
    }
}

int hashEntry::getCollisions() const
{
    return collisions;
}

int hashEntry::getUsedBuckets() const  /// counts number of all occupied buckets
{
    int n = 0;
    for(int i=0; i < tableSize; i++)
        n += hashTable[i].getCount(); /// sum up counter of each entry
    return n;
}

int hashEntry::getUsedEntries() const /// counts number of all occupied entries
{
    int n = 0;
    for(int i=0; i < tableSize; i++)
        if(hashTable[i].getCount()) n++; /// increase count++ when a entry is occupied
    return n;
}

float hashEntry::bucketsLoadedFactor() const /// number of occupied buckets / number of total buckets
{
    return getUsedBuckets()*1.0/(tableSize*bucketsNum)*100;
}

float hashEntry::entriesLoadedFactor() const /// number of occupied entries / number of total entries
{
    return getUsedEntries()*1.0/tableSize*100;
}
//Maria
/* ~*~*~*~
 This function reads data from the hash table into an outputFile
 ~*~*~*~ */
void hashEntry::writeFile() const
{
    string outFilename = "UpdatediPhones.txt";
    ofstream outputFile; //open the output file
    outputFile.open(outFilename.c_str());
    
    //float n = 0;
    // for(int i=0; i < tableSize; i++)
    //   if(hashTable[i].getCount()) n++;
    
    
    outputFile << getUsedBuckets() + getCollisions()  << endl;
    
    
    for(int i=0; i < tableSize; i++)
    {
        if(hashTable[i].getCount() > 0)
        {
            for(int j=0; j< hashTable[i].getCount(); j++)
            {
                outputFile<< hashTable[i].getBucket(j)->getIMEI() << " "
                << hashTable[i].getBucket(j)->getCapacity() << '\t'
                << hashTable[i].getBucket(j)->getSerialNum() << '\t'
                << hashTable[i].getBucket(j)->getModel() << '\t'
                << hashTable[i].getBucket(j)->getManuLocn() << std::endl;
            }
        }
    }
    
    if(overFlow->getNext() == nullptr) return;
    Node* ptr = overFlow->getNext();
    while(ptr->getNext())
    {
        outputFile << ptr->getData()->getIMEI() << " "
        << ptr->getData()->getCapacity() << '\t'
        << ptr->getData()->getSerialNum() << '\t'
        << ptr->getData()->getModel() << '\t'
        << ptr->getData()->getManuLocn() << std::endl;
        
        ptr = ptr->getNext();
    }
    outputFile.close();//close the output file
}
#endif
