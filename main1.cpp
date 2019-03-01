// modified by Zhuoxuan Wang & Maria Gorbunova

#include "BinarySearchTree.h"  // BST ADT
#include "hashEntry.h"
#include "StackADT.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;




void buildTree(const char fileName[], BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing);
int  getSize(int count); //hash
bool isPrime(int n); //hash

void menuMini();
void menu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing);

void printListMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing);
void printDeveloper();
void searchDataMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing);
void searchByIMEI(hashEntry &hashing); //hash
void searchBySerialNum(BinarySearchTree<string, iPhone*> &iPTree2);
//void searchByCapacity(BinarySearchTree<string, iPhone*> &iPTree2);

void deletePhoneMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, Stack<iPhone> &stack, hashEntry &hashing);
void deleteIMEI(BinarySearchTree<string, iPhone*> &iPTree1,BinarySearchTree<string, iPhone*> &iPTree2, Stack<iPhone> &stack, hashEntry &hashing);
void deleteSerialNum(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2,Stack<iPhone> &stack, hashEntry &hashing);
void undoDelete(BinarySearchTree<string, iPhone*> &iPTree1,BinarySearchTree<string, iPhone*> &iPTree2, Stack<iPhone> &stack,hashEntry &hashing);

void addIMEI(BinarySearchTree<string, iPhone*> &iPTree1,BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing);

void rehashing(hashEntry &hashing);

void printTreeIndented1(BinarySearchTree<string, iPhone*> &iPTree);
void display(iPhone * &ip, int level);
void print1(iPhone* &ip, int level);
void print2(iPhone* &ip, int level);
void printPkey(BinarySearchTree<string, iPhone*> &iPTree1);
void printSkey(BinarySearchTree<string, iPhone*> &iPTree2);
void printData2(iPhone* &ip, int level);
void printTreeIndented2(BinarySearchTree<string, iPhone*> &iPTree);
void printData1(iPhone* &ip, int level);

//void addNode(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2);
//void displayIp(iPhone* &ip);

//Zhuoxuan Wang
int main()
{
    ifstream infile;
    int count = 0, size = 0; // hashing
    const char fileName[] = "iPhones.txt";
    infile.open(fileName);
    infile >> count; // reads the first line of the file
    infile.close();
    size = getSize(count); // hashing

    BinarySearchTree<string, iPhone*> iPTree1; // iPTree1 is sorted by priamry key - IMEI
    BinarySearchTree<string, iPhone*> iPTree2; // iPTree2 is sorted by secondary key - Serial number
    hashEntry hashing(size); //hasing

    buildTree(fileName, iPTree1, iPTree2, hashing);
    menu(iPTree1, iPTree2, hashing); // display the main menu
    
    return 0;
}
/**~*~*
 1.buildTree function reads data from a text file
 and inserts them into two BSTs.
 2.insert the primary key into hasing table.
 *~**/
// Zhuoxuan Wang
void buildTree(const char fileName[], BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing)
{
    iPhone *ip = nullptr; // an iphone object pointer
    string imei, capacity, serialNum, model, manuLocn;
    int count=0; // the number of data
    ifstream infile;
    infile.open(fileName);

    cout << "Reading data from " << fileName << " . . . \n";
    if(!infile)
    {
        cout << "Error opening " << fileName << " for reading\n" ;
        exit(111);
    }
    else
    {
        infile >> count; // reads the first line of the file, which is the number of data
        infile.ignore();
        while(!infile.eof()) // if it's not the end of file
        {
            getline(infile, imei, ' ');
            getline(infile, capacity, '\t');
            getline(infile, serialNum, '\t');
            getline(infile, model, '\t');
            getline(infile, manuLocn);
            if(imei.empty()) break;
            
            // dynamically allocated an iphone obejct
            ip = new iPhone(imei, capacity, serialNum, model, manuLocn);
            
            cout << *ip;
            iPTree1.insert(ip->getIMEI(), ip); // insert data to BST1
            iPTree2.insert(ip->getSerialNum(), ip); // insert data to BST2
            hashing.insertEntry(imei, ip); // insert data to hashing table
           
        }
    }
    infile.close(); // close the file
    cout << "\nDone reading!\n\n";
    
}

//Maria
// This function gets the size of hash table
int getSize(int count)
{
    //given a number n, find the next closest prime number above n
    int nextPrime = 2*count;
    bool found = false;

    //loop continuously until isPrime returns true for a number above n
    while (!found)
    {
        nextPrime++;
        if (isPrime(nextPrime))
            found = true;
    }

    return nextPrime;

}
//Maria
//given a number n, determine if it is prime
bool isPrime(int n)
{

    //loop from 2 to n/2 to check for factors
    for(int i = 2; i <= n/2; i++)
    {
        if(n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
           return false;
    }

    return true;
}

/**~*~*
 menuMini function displays the main menu whenever it's called
 *~**/
// Zhuoxuan Wang
void menuMini()
{
    cout << "--------------------- MAIN MENU --------------------\n";
    cout << "|L - List.                                         |\n";
    cout << "|S - Search.                                       |\n";
    cout << "|A - Add new data.                                 |\n";
    cout << "|D - Delete data.                                  |\n";
    cout << "|F - Hash statistics.                              |\n";
    cout << "|H - Help.                                         |\n";
    cout << "|E - Exit & save the File.                         |\n";
    cout << "----------------------------------------------------\n";
}
/**~*~*
 menu function gets the user's choice
 *~**/
// Zhuoxuan Wang
void menu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing)
{
    char choice;
    Stack<iPhone> *stack = new Stack<iPhone>; // a pointer points to dynamically allocated stack (for undoDelete)
    menuMini();
    do
    {
        cout << "Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice); // converts the user's input to uppercase letter
        
        switch(choice)
        {
            case 'L':
                cout << "L - List." << endl;
                printListMenu(iPTree1, iPTree2, hashing); // goes to the list sub-menu
                break;
            case 'S':
                cout << "S - Search." << endl;
                searchDataMenu(iPTree1, iPTree2, hashing); // goes to the search sub-menu
                break;
            case 'A':
                cout << "A - Add new data. " << endl;
                addIMEI(iPTree1, iPTree2, hashing); // goes to addIMEI function
                break;
            case 'D':
                cout << "D - Delete data. " << endl;
                deletePhoneMenu(iPTree1, iPTree2, *stack, hashing); // goes to the delete sub-menu
                break;
            case 'H':
                cout << "H - Help." << endl;
                menuMini(); // displays the main menu
                break;
            case 'E':
                cout << "E - Exit the Main Menu and save to the File." << endl;
                iPTree1.clear(); // free BST1
                iPTree2.clear(); // free BST2
                hashing.writeFile(); // update the output file
                //hashing.deleteTable(); // free hashing table
                delete stack; // free stack
                exit(1);
                break;
            case 'F':
                // displays the hash statistics
                cout << "F - Hash statistics." << endl;
                cout << "Loaded factor for buckets: " << hashing.bucketsLoadedFactor() << '%' << endl;
                cout << "Loaded factor for entries: " << hashing.entriesLoadedFactor() << '%' <<endl;
                cout << "Number of the collisions: " << hashing.getCollisions() << endl;
                break;
            default:
                cout << "Wrong choice" << endl;
        }
    } while (isalpha(choice)); // check if choice is a letter
}/**~*~*
 printListMenu function:
 - List unsorted data
 - List data sorted by the primary key
 - List data sorted by the secondary key
 - Special print, as an indented list
 - Hidden print option
 *~**/
void printListMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing)
{
    char choice;
        cout << "--------------------- List Menu --------------------\n";
        cout << "|U - List unsorted data.                           |\n";
        cout << "|M - List data sorted by the primary key.          |\n";
        cout << "|V - List data sorted by the secondary key.        |\n";
        cout << "|F - Special print tree1 as an indented list.      |\n";
        cout << "|G - Special print tree2 as an indented list.      |\n";
        cout << "|H - Print developers.                             |\n";
        cout << "|B - Back to the main menu.                        |\n";
        cout << "----------------------------------------------------\n";
    do
    {
        
        cout << "Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice); // converts the user's input to uppercase letter
        switch(choice)
        {
            case 'U':
                cout << "U - List unsorted data." << endl;
                hashing.printEntry(); // prints unsorted data from hashing table
                break;
            case 'M':
                cout << "M - List data sorted by the primary key." << endl;
                printPkey(iPTree1); // prints data sorted by the primary key - IMEI
                break;
            case 'V':
                cout << "V - List data sorted by the secondary key." << endl;
                printSkey(iPTree2); // prints data sorted by the secondary key - Serial number
                break;
            case 'F':
                cout << "F - Special print tree1 as an indented list." << endl;
                printTreeIndented1(iPTree1); // prints BST1(sorted by IMEI)as an idented list
                break;
            case 'G':
                cout << "G - Special print tree2 as an indented list." << endl;
                printTreeIndented2(iPTree2); // prints BST1(sorted by Serial number)as an idented list
                break;
            case 'H':
                cout << "H - Print developers." << endl;
                printDeveloper(); // prints the name of developers
                break;
            case 'E':
                cout << "Back to the main menu." << endl;
                menuMini(); // goes back to the main menu
                break;
            default:
                cout << "Wrong choice" << endl;
        }
    }while (isalpha(choice) && choice != 'E');
}
/**~*~*
 searchDataMenu displays the search sub-menu
 *~**/
// Zhuoxuan Wang
void searchDataMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing)
{
    char choice;
    
    cout << "-------------------- Search Menu -------------------\n";
    cout << "|I - Search an IMEI Number.                         |\n";
    cout << "|C - Search by serial number.                       |\n";
    cout << "|E - Back to the main menu.                         |\n";
    cout << "----------------------------------------------------\n";
    do
    {
        cout<<"Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice); // converts the user's choice to an uppercase letter
        switch(choice)
        {
            case 'I':
                cout << "I - Search an IMEI Number." << endl;
                searchByIMEI(hashing); // calls searchByIMEI function to search IMEI from hashing table
                break;
            case 'C':
                cout << "C - Search by Serial Number." << endl;
                searchBySerialNum(iPTree2); // calls searchByIMEI function to search serial num from BST2
                break;
            case 'E':
                cout << "Back to the main menu" << endl;
                menuMini(); // goes back to the main menu
                break;
        }
    }while(isalpha(choice) && choice != 'E');
}

// Zhuoxuan Wang
/**~*~*
 searchByIMEI is a search manager 
 that prompts the user to enter the IMEI,
 Then using hash table prints the info on screen
 *~**/
void searchByIMEI(hashEntry &hashing)
{
    iPhone ip;
    string str = "";
    bool success = false;

    do
    {
       cout << "Please enter the information that you want to search:" << endl;
       cin >> str;
        while(str.length() != 15)
        {
            cout << "The IMEI number must have 15 numbers!" << endl;
            cout << "Please enter a IMEI to search: ";
            cin >> str;
        }
       if (str != "")
           success = true;
       cin.clear();          // to clear the error flag
       cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
       //ip.setIMEI(str);
       hashing.searchEntry(str);
    } while (!success);

    if(!success)
        cout << "Not found!" <<endl;
}
// Zhuoxuan Wang
/**~*~*
 searchBySerialNum is a search manager
 that prompts the user to enter the Serial Number,
 Then using second BST prints the info on screen
 *~**/
void searchBySerialNum(BinarySearchTree<string, iPhone*> &iPTree2)
{
    iPhone ip;
    string serialNum = "";
    bool success = false;

    //cout << "Do you want to search a data(Enter Y to start): ";
    //cin >> choice;
    //choice = toupper(choice);

    do
    {
        cout << "Please enter the information that you want to search:" << endl;
        cin >> serialNum;
        while(serialNum.length() != 12)
        {
            cout << "The Serial Number number must have 12 characters!" << endl;
            cout << "Please enter Serial Number to search: ";
            cin >> serialNum;
        }
        if (serialNum != "")
            success = true;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
        ip.setSerialNum(serialNum);
        iPTree2.printSameKey(display, ip.getSerialNum()); // printData2
    } while (!success);

}
/**~*~*
 deletePhoneMenu displays the delete sub-menu
 *~**/
// Zhuoxuan Wang
void deletePhoneMenu(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2,Stack<iPhone> &stack, hashEntry &hashing )
{
    char choice;
    

    cout << "-------------------- Delete Phone Menu -------------------\n";
    cout << "O - Delete iPhone by IMEI.                                |" << endl;
    cout << "X - Delete iPhone by Serial Number.                       |" << endl;
    cout << "U - Undo delete.                                          |" << endl;
    cout << "E - Back to the main menu.                                |" << endl;
    cout << "----------------------------------------------------------\n";

    do
    {
        cout<<"Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice); // converts the user's choice to the uppercase letter
        switch(choice)
        {
            case 'O':
                cout << "O - Delete iPhone by IMEI." << endl;
                // calls the deleteIMEI function to delete by IMEI
                deleteIMEI(iPTree1,iPTree2, stack, hashing);
                break;
            case 'X':
                cout << "X - Delete iPhone by Serial Number." << endl;
                // calls the deleteSerialNum function to delete by serial number
                deleteSerialNum(iPTree1,iPTree2, stack, hashing );
                break;
            case 'U':
                cout << "U - undo delete. " << endl;
                undoDelete(iPTree1, iPTree2, stack, hashing); // undoes the user's deletion
                break;
            case 'E':
                cout << "B - Back to the main menu" << endl;
                menuMini(); // goes back to the main menu
                break;
        }
        
    }while(isalpha(choice) && choice != 'E');
}

// Modified by Maria
/**~*~*
 deleteIMEI manager prompt a user to enter the IMEI of 
 the phone he/she wants to delete.
 The phone is deleted from the both BSTs and hash table
 *~**/
void deleteIMEI(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2,Stack<iPhone> &stack, hashEntry &hashing)
{
    iPhone *ip;
    ip = new iPhone();
    string imei;

    cout << "Please enter a IMEI to delete: ";
    cin >> imei;
    while(imei.length() != 15)
    {
        cout << "The IMEI number must have 15 numbers!" << endl;
        cout << "Please enter a IMEI to delete: ";
        cin >> imei;
    }
    ip->setIMEI(imei);
    iPTree1.getEntry(imei, ip);
    
    cout << *ip << endl;
    if(iPTree1.remove(imei,ip)&& iPTree2.remove(ip->getSerialNum(),ip)  && hashing.removeEntry(imei))
    {
        cout << "Deleted successfully." << endl;
        stack.push(*ip);
    }
    else
        cout << "Deletion failed." << endl;
}

// Angela
/**~*~*
 deleteSerialNum manager prompts the user to insert the 
 Serial number of the phone they want to be deleted.
 If it is a unique serial number, the phone is deleted from BSTs and hash table.
 If it is not unique, it prints al the duplicates and asks to enter IMEI
 *~**/
void deleteSerialNum(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2,Stack<iPhone> &stack, hashEntry &hashing)
{
    iPhone *ip, *ip2;
    ip = new iPhone();
    ip2 = new iPhone();
    string serialNum, imei;

    cout << "Please enter a serial number to delete: ";
    cin >> serialNum;
    while(serialNum.length() != 12 )
    {
        cout << "The Serial number must have 12 characters!" << endl;
        cout << "Please enter a Serial Number to delete: ";
        cin >> serialNum;
    }
    ip->setSerialNum(serialNum);

    Stack<iPhone*> s = iPTree2.findDuplicates(ip->getSerialNum());

    if (s.getCount() > 1 )
    {
        //string imei;
        cout << "Found duplicates. Please select the IMEI that you wish to delete." << endl;
        while (s.getCount() > 0)
        {
            s.pop(ip2);
            cout << *ip2;
        }
        cout << "Please enter IMEI of your choice: " << endl;
        cin >> imei;
        
        while(imei.length() != 15)
        {
            cout << "The IMEI number must have 15 numbers!" << endl;
            cout << "Please enter a IMEI to delete: ";
            cin >> imei;
        }

        ip->setIMEI(imei);
        iPTree1.getEntry(imei, ip);
    }
    else
        iPTree2.getEntry(serialNum, ip);
    
    //cout << *ip;
   
    
    if(iPTree1.remove(ip->getIMEI(),ip) && iPTree2.remove(serialNum, ip) && hashing.removeEntry(ip->getIMEI()))
    {
        cout << *ip << " \nRemoved successfully." << endl;
        stack.push(*ip);
    }
    else
        cout << "Deletion fails." << endl;
}

// Maria
/**~*~*
 undoDelete prompts user to confirm the undo
 and restores the deleted object back to BST1 BST2 and hash Table
 *~**/
 void undoDelete(BinarySearchTree<string, iPhone*> &iPTree1,BinarySearchTree<string, iPhone*> &iPTree2, Stack<iPhone> &stack, hashEntry &hashing)
 {
     if (stack.isEmpty())
     {
        cout << "There are no deleted items!" << endl;
         return;
     }

    char choice;
    iPhone *ip = new iPhone();
     string imei;
    cout << "Do you want to undo the deletion?(Enter Y to start)" << endl;
    cin >> choice;
    choice = toupper(choice);
    if(choice == 'Y')
    {
        stack.pop(*ip);
        
        imei=ip->getIMEI();
        cout <<"Insert the deleted iPhone back to the database:\n" <<  *ip << endl;
        iPTree1.insert(ip->getIMEI(), ip);
        iPTree2.insert(ip->getSerialNum(), ip);
        hashing.insertEntry(imei, ip);
    }
}
/**~*~*
 addIMEI function gets the user's input and inserts to BST1, BST2, ans hasing table
 *~**/
// Zhuoxuan Wang
void addIMEI(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2, hashEntry &hashing)
{
    iPhone *ip = nullptr; // declares a pointer points an iphone object
    string imei, capacity, serialNum, model, manuLocn;

    cout << "Please enter a IMEI to insert: ";
    cin >> imei;
    while(imei.length() != 15) // check the length of IMEI numbers
    {
        cout << "The IMEI number must have 15 numbers!" << endl;
        cout << "Please enter a IMEI to insert: ";
        cin >> imei;
    }
    if(hashing.searchEntry(imei)) // searches if the new data is already exsited
    {
        cout << "This IMEI number already exists!" << endl;
    }
    else
    {
        cout<< "Continue inserting the data. " << endl;
        cout << "Please enter a capacity: ";
        cin >> capacity;
        cout << "Please enter a serial number: ";
        cin >> serialNum;
        while(serialNum.length() != 12 )
        {
            cout << "The Serial number must have 12 characters!" << endl;
            cout << "Please enter a Serial Number to add: ";
            cin >> serialNum;
        }
        cout << "Please enter a model: ";
        cin >> model;
        while(model.length() != 9 )
        {
            cout << "The model must have 9 characters!" << endl;
            cout << "Please enter a model to add: ";
            cin >> model;
        }
        cout << "Please enter a manufacture location: ";
        cin >> manuLocn;
        
        ip = new iPhone(imei, capacity, serialNum, model, manuLocn); // creates a dynamically allocated iphone object
        //cout << *ip;

        iPTree1.insert(ip->getIMEI(), ip); // insert the new data into BST1
        iPTree2.insert(ip->getSerialNum(), ip); // insert the new data into BST2
        hashing.insertEntry(imei, ip); // insert the new data into hashing table
        
        cout << *ip << "Inserted successfully!" << endl;
        }
    cout << "You are in the main menu! Don't exit until you want to. " << endl;
    
    /*if (hashing.bucketsLoadedFactor()>75)
    {
        rehashing(hashing);
    }*/
}

// printDeveloper function prints the name of developers
// Zhuoxuan Wang
void printDeveloper()
{
    cout << "This program is written by: " << endl;
    cout << "Maria" << endl;
    cout << "Angela" << endl;
    cout << "Mason" << endl;
    cout << "Vera" << endl;
}

//the visit func to make the indented list
// Zhuoxuan Wang
void printData1(iPhone* &ip, int level)
{
    for (int i = 0; i < level - 1; i++)
        cout << "     ";
    cout << level << ". ";
    cout << ip->getIMEI() << endl;

}
//printTreeIndented prints the BST as an indented list by primary key(show level numbers)
// Zhuoxuan Wang
void printTreeIndented1(BinarySearchTree<string, iPhone*> &iPTree)
{
    iPTree.newOrder(printData1);
}
//print serial num as indented list
// Zhuoxuan Wang
void printData2(iPhone* &ip, int level)
{
    //cout << "printData2 called with " << ip << " at level " << level << endl;
    for (int i = 0; i < level - 1; i++)
        cout << "     ";
    cout << level << ". ";
    cout << ip->getSerialNum()<< endl;
}
//printTreeIndented2 prints the BST as an indented list by serial number(show level numbers)
// Zhuoxuan Wang
void printTreeIndented2(BinarySearchTree<string, iPhone*> &iPTree)
{
    iPTree.newOrder(printData2);
}
// helps to print the data from BST2
// Zhuoxuan Wang
void print1(iPhone* &ip, int level)
{
   cout << *ip;
}
// prints the data sorted by the primary key
// Zhuoxuan Wang
void printPkey(BinarySearchTree<string, iPhone*> &iPTree1)
{
    iPTree1.inOrder(print1);
}
// helps to print the data from BST1
//Zhuoxuan Wang
void print2(iPhone* &ip, int level)
{
    cout << *ip;
}
// prints the data sorted by the secondary key
// Zhuoxuan Wang
void printSkey(BinarySearchTree<string, iPhone*> &iPTree2)
{
    iPTree2.inOrder(print2);
}
// helps to print the data that has the same secondary key
// Zhuoxuan Wang
void display(iPhone * &ip, int level)
{
    cout << *ip;
}

/*
void addNode(BinarySearchTree<string, iPhone*> &iPTree1, BinarySearchTree<string, iPhone*> &iPTree2)
{
    char choice;

    cout << "-------------------- Add Node Menu -------------------\n";
    cout << "|Q - Insert a new data by IMEI.                      |\n";
    cout << "|Z - Insert a new data by Capacity.                  |\n";
    cout << "|E – Exit the Add Node Menu.                         |\n";
    cout << "------------------------------------------------------\n";

    do
    {
        cout<<"Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice);
        switch(choice)
        {
            case 'Q':
                cout << "Q - Insert a new data by IMEI." << endl;
                addIMEI(iPTree1);
                break;
            case 'Z':
                cout << "Z - Insert a new data by Capacity." << endl;
                addCapacity(iPTree2);
                break;
            case 'E':
                cout << "E – Exit the Add Node Menu." << endl;
                break;
        }

    }while(isalpha(choice) && choice != 'E');
}*/
/*
 void addCapacity(BinarySearchTree<string, iPhone*> &iPTree2)
{
    iPhone *ip;
    char choice;
    string imei, capacity, serialNum, model, manuLocn;
    cout << "Do you want to insert a new data(Enter Y to start): ";
    cin >> choice;
    choice = toupper(choice);

    while(choice == 'Y')
    {
        cout << "Please enter a capacity to insert: ";
        cin >> capacity;
        cout << "Please enter a IMEI: ";
        cin >> imei;
        while(imei.length() != 15)
        {
            cout << "The IMEI number must have 15 numbers!" << endl;
            cout << "Please enter a IMEI to insert: ";
            cin >> imei;
        }
        cout << "Please enter a serial number: ";
        cin >> serialNum;
        cout << "Please enter a model: ";
        cin >> model;
        cout << "Please enter a manufacture location: ";
        cin >> manuLocn;

        ip = new iPhone(imei, capacity, serialNum, model, manuLocn);
        iPTree2.insert(imei, ip);

        cout << "Do you want to insert a new data(Enter Y to start): ";
        cin >> choice;
        choice = toupper(choice);

    }
} */
/*
void searchByCapacity(BinarySearchTree<string, iPhone*> &iPTree2)
{
    iPhone *ip = new iPhone();
    //char choice;
    string capacity = "";
    bool success = false;


        cout << "Please enter the information that you want to search:" << endl;
        cin >> capacity;
        if (capacity != "")
            success = true;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
        ip->setCapacity(capacity);
        if(iPTree2.getEntry(capacity, ip))
            iPTree2.printSameKey(display, ip->getCapacity());
        else
            cout << "Not found!" << endl;
}
*/
/*
void rehashing(hashEntry &hashing)
{
 int oldhashSize, newSize;
 oldhashSize=hashing.getTableSize();
 newSize=getSize(oldhashSize);
 hashEntry hashing2(newSize);
 
 // copy data into new hash
 // delete old hash
 
}*/

