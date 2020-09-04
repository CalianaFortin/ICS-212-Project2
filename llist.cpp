/*****************************************************************
//
// NAME:        Caliana Fortin
//
// HOMEWORK:    Project
//
// CLASS:	ICS 212
//
// INSTRUCTOR:  Ravi Narayan
//
// DATE:        September 29, 2019
//
// FILE:        llist.cpp
//
// DESCRIPTION: This file contains the definitions for the 6 functions used
//              in user_interface
//
******************************************************************/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>

#include "llist.h"
#include "record.h"

using namespace std;


/*******************************************************************************
//
// EXTRA CREDIT(copy constructor)
//
// Function name: llist
//
// Description: copy constructor for llist class, makes a duplicate llist
//
// Parameter: list(const llist&): The original llist
//
*******************************************************************************/

llist::llist(const llist& list)
{
    struct record* begin;
    struct record* copyList;

    begin = list.start;
    
    if(begin == NULL)
    {
        this->start = NULL;
    }
    else
    {
        this->start = new record;
        this->start->accountno = begin->accountno;
        strcpy(this->start->name, begin->name);
        strcpy(this->start->address, begin->address);
        this->start->next = NULL;

        if(begin->next != NULL)
        {
            copyList = start;
            begin = begin->next;

            while(begin->next != NULL)
            {
                copyList->next = new record;
                copyList->next->accountno = begin->accountno;
                strcpy(copyList->next->name, begin->name);
                strcpy(copyList->next->address, begin->address);
                copyList->next->next = NULL;
                begin = begin->next;
                copyList = copyList->next;
            }

            copyList->next = new record;
            copyList->next->accountno = begin->accountno;
            strcpy(copyList->next->name, begin->name);
            strcpy(copyList->next->address, begin->address);
            copyList->next->next = NULL;
        }
    }
}


/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:    Constructor for llist class
//
//  Parameters:    none
//
//  Return values: n/a
//
****************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "test.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:    Constructor for llist class
//
//  Parameters:    char * fileN
//
//  Return values: n/a
//
****************************************************************/

llist::llist(char * fileN)
{
    start = NULL;
    strcpy(filename, fileN);
    readfile();
}

/*****************************************************************
//
//  Function name: llist::cleanup
//
//  DESCRIPTION:    Constructor for releasing memory
//
//  Parameters:    none
//
//  Return values: n/a
//
****************************************************************/

void llist::cleanup()
{
    record * release;
    record * pointerToStart;

    #ifdef DEBUG
    {
     	cout<<"**************************DEBUG MESSAGE****************************\n";
        cout<<"Hey there! You called the cleanup function \n";
        cout<<"**********************************************************\n";
    }
    #endif

    pointerToStart = start;

    while(pointerToStart != NULL)
    {
     	release = pointerToStart;
        pointerToStart = pointerToStart->next;
        delete release;
    }


}


/*****************************************************************
//
//  Function name: llist~llist
//
//  DESCRIPTION:    Destructor for llist class
//
//  Parameters:    const llist& list
//
//  Return values: n/a
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: llist::reverse
//
//  DESCRIPTION:   list reversal is called
//
//  Parameters:    none
//
//  Return values: none void
//
****************************************************************/

void llist::reverse()
{
    #ifdef DEBUG
    {
        std::cout<<"***************************DEBUG MESSAGE**********************\n";
        std::cout<<"Hey there! You called the Reverse  function \n";
        std::cout<<"**********************************************************\n";
    }
    #endif

    if(start != NULL)
    {
        reverse(start);
    }


}

/*****************************************************************
//
//  Function name: record* llist::reverse (private)
//
//  DESCRIPTION:   How reverse function works, to change order of list
//
//  Parameters:    record* immediate
//
//  Return values: valueForReturn
//
****************************************************************/

record* llist::reverse(record* record)
{
    #if DEBUG == 1
        cout << "----- DEBUG writefile -----" << endl;
        cout << "record * : " << record << endl;
    #endif
     
    if (record->next != NULL)
    {
        (reverse(record->next))->next = record;
        record->next = NULL;
    }
    else
    {
        start = record;
    }
     
    return record;
}

/*record * llist::reverse(record * immediate)
{
    record * valueForReturn;
    record * release;

    if(immediate->next == NULL)
    {
     	valueForReturn = immediate;
    }

    else
    {
     	release = reverse(immediate->next);
        immediate->next->next = immediate;
        immediate->next = NULL;
        valueForReturn = release;
    }

    return (valueForReturn);
}*/

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:    A function to obtain information that the user
//                  inputs. This will record the record and the account
//                  number to delete a record.
//
//  Parameters:    struct record ** toBeDelete, int accountno
//
//  Return values: 0, 1
//
****************************************************************/

int llist::deleteRecord(int accountno)
{
    int valueForReturn;
    record * release = start, *previous;

    #ifdef DEBUG
    {
     	std::cout<<"**********************DEBUG MESSAGE*****************************\n";
        std::cout<<"Hey there! You called the deleteRecord function \n";
        std::cout<<"Here is the accountno ="<< accountno<<"\n";
        std::cout<<"**********************************************************\n";
    }
    #endif

    valueForReturn = 1;

    while(release!= NULL && release->accountno == accountno)
    {
        start  = release->next;
        free(release);
        release = start;
        valueForReturn = 0;
    }

    while(release != NULL)
    {
        while(release != NULL && release->accountno != accountno)
        {
            previous = release;
            release = release->next;
        }
        if (release == NULL)
        {
            valueForReturn = 1;
            break;
        }

     	previous->next = release->next;
        delete release;
        release = previous->next;
        valueForReturn = 0;
    }

    return (valueForReturn);

}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:    A function to obtain information that the user
//                  inputs. This will record a new record, account number
//                  name, and address.
//
//  Parameters:    struct record ** recordToAdd, int accountno, char name[],
//                 char address[]
//
//  Return values: 0, 1, -1
//
****************************************************************/

int llist::addRecord(int accountno, char name[], char address[])
{
    record * nextRecord;
    record * next_deleted;
    record * current;
    record * newRecord;
    record * head;
    int valueForReturn;
    
    newRecord = new record ();
    valueForReturn = 1;
    newRecord->accountno = accountno;
    head = start;
    /****************************************************************
    * Note: We need to get down the information inputted by the user
    * to the new record we created, which is create. We use strcpy
    * since we want to copy all the contents that have been recorded
    * to release.
    ****************************************************************/
    if (start != NULL)
    {
        while(head->next != NULL)
        {
            if(newRecord->accountno == head->accountno)
            {
                next_deleted = head->next->next;
                delete (head->next);
                head->next = next_deleted;
                valueForReturn = -1;
            }
            else 
            {
                head = head->next;
            }
         }
	//cout << "This is the valueForReturn: " << valueForReturn << endl;
    }

    strcpy(newRecord->name, name);
    strcpy(newRecord->address, address);

    
    #ifdef DEBUG
    {
        std::cout<<"************************DEBUG MESSAGE***************************\n";
        std::cout<<"Hey there! You called the addRecord function \n";
        std::cout<<"Here is the accountno ="<< accountno<<"\n";
        std::cout<<"Here is the name:"<< name<<"\n";
        std::cout<<"Here is the address: \n:"<< address<<"\n";
        std::cout<<"**********************************************************\n";
    }
    #endif

 /****************************************************************
    * Note: If the record we are trying add is in empty list, then
    * we check for this in an if statement, and we set the next value of 
    * the record to NULL, and the valueForReturn, becomes 0, indicating
    * it has been added.
    ******************************************************************/


    if(start == NULL)
    {
        newRecord->next = NULL;
        start = newRecord;
        valueForReturn = 0;
    }

    else if ( newRecord->accountno > start->accountno && valueForReturn != -1)
    {
        newRecord->next = start;
        start = newRecord;
        valueForReturn = 0;
    }
    else
    {
       current  = start; 
       nextRecord = start->next;
 
       while(nextRecord != NULL && valueForReturn == 1)
        {
            if(newRecord->accountno < current->accountno && newRecord->accountno > nextRecord->accountno)
            {
                newRecord->next = nextRecord;
                current->next = newRecord;
                valueForReturn = 0;
            }
            current = nextRecord;
            nextRecord = current->next;
        }


    }

    return valueForReturn;

}



/*****************************************************************
//
//  Function name: printRecord
//
//  DESCRIPTION:    A function to obtain information that the user
//                  inputs. This will record the record to be printed
//                  and the account number.
//
//  Parameters:    struct record * toBePrint, int accountno
//
//  Return values: 0 for success, 1 for fail
//
****************************************************************/


int llist::printRecord( int accountno)
{
    int valueForReturn;
    record * release = start;
    valueForReturn = 1;

    #ifdef DEBUG
    {
     	std::cout<<"*********************DEBUG MESSAGE********************************\n";
        std::cout<<"Hey there! You called the printRecord function \n";
        std::cout<<"Here is the accountno ="<<accountno<<"\n";
        std::cout<<"**********************************************************\n";
    }
    #endif

	while(release != NULL)
        {
            if(accountno == release->accountno)
            {
             	cout<<"\n===================================================================\n";
                cout<<"Account Number: "<< release->accountno<<"\n";
                cout<<"UserName:"<<release->name<<"\n";
                cout<<"Address: \n ";
                cout<<release->address;
                cout<<"\n";
                cout<<"===================================================================\n";
                valueForReturn = 0;

            }

            release = release->next;
        }

    return (valueForReturn);
}

/*****************************************************************
//
//  Function name: operator <<
//
//  DESCRIPTION:    A function that calls to all the records in memory
//                  inputted by the user.
//
//  Parameters:    ostream & print, const llist& list
//
//  Return values: records in database
//
****************************************************************/

ostream& operator<<(ostream& print, const llist& list)
{
     record * immediate = list.start;

    #ifdef DEBUG
    {
        print<<"****************************DEBUG MESSAGE****************************\n";
        print<<"Hey there! You called the printAllRecords function \n";
        print<<"**********************************************************\n";
    }
    #endif

    if(immediate != NULL)
    {
        print<<"\n===================================================================\n";
        print<<"\t \t \t YOUR RECORDS";
        print<<"\n===================================================================\n";

        while(immediate != NULL)
        {
            print<<"\n===================================================================\n";
            print<<"Account Number: "<< immediate->accountno<<"\n";
            print<<"UserName: "<< immediate->name<<"\n";
            print<<"Address:";
            print<< immediate->address;
            print<<"\n";
            print<<"===================================================================\n";

            immediate = immediate->next;
        } 
        return print;

    }
    else
    {
        print<<"Hmm... There's nothing here. The database is empty.";
    }

    return print;
}

/**************************************************************************
//
//  Function name: llist::readfile
//
//  DESCRIPTION:
//                 This function is used to read the record from the text
//         file and store it in an array.
//
//  Parameters:    none;
//
//  Return values: 0 if successful 1 if failure
//
**************************************************************************/

int llist::readfile()
{
    ifstream inputFile;
    /**char accountNumber[100];**/
    char address[80];
    int accountNum;
    int index;
    int index2;
    int valueForReturn;
    char name[80];
    char dump[800];

    valueForReturn = 1;
    inputFile.open(filename);
  
   #ifdef DEBUG
    {
        cout<<"************************DEBUG MESSAGE****************************\n";
        cout<<"Hey there! You called the readfile function \n";
        cout<<"**********************************************************\n";
    }
    #endif

    if(inputFile != NULL)
    {
        valueForReturn = 0;

        while(!inputFile.eof())
        {

            if(inputFile == NULL || inputFile.eof())
            {
                break;
            }
            /* Retrieve the lines of account numbers in the file */

            inputFile.getline(dump, 100);

            /***********************************************************************
            *Note: Since we don’t have a parameter knowing the amount of 
            *records, there’ll be since the user can create as many as they would 
            *like, we have to find a way to know the amount. A function I saw I can 
            *use is a atoi, which is on page 42-43. It converts a string of digits into 
            *its numeric equivalent. So I can use atoi with the account number as 
            *the parameter, within a while loop to retrieve all the account numbers 
            *that were made.
            ************************************************************************/

            accountNum = atoi(dump);

            index = strlen(name)-1;

            inputFile.getline(dump, 100);

            index2 = strlen(address)-1;

            if(name[index] == '\n')
            {
                name[index] = '\0';
            }

            if(address[index2] == '\n')
            {
                address[index] = '\0';
            }

            addRecord(accountNum, name, address);
        }

        inputFile.close();
        return valueForReturn;
    }

    return valueForReturn;
}

/*******************************************************************************
//   
// Function name: writefile
//   
// Description: This function write data into a file
//   
// Parameter: data(struct record *): pointer to data
//            filename(char []): name of file
//
*******************************************************************************/


int  llist::writefile()
{

    ofstream outputFile;
    record * immediate;

    outputFile.open(filename);
    immediate = start;

    #ifdef DEBUG
    {
        cout<<"*************************DEBUG MESSAGE****************************\n";
        cout<<"Hey there! You called the writefile function \n";
        cout<<"**********************************************************\n";
    }
    #endif

   if(outputFile != NULL)
    {
        while(immediate != NULL)
        {
            outputFile << "Account no: " << immediate->accountno << "\n";
            outputFile << "Name: " << immediate->name<<"\n";
            outputFile << "Address: " << immediate->address <<"\n";
            outputFile <<"\n";

            immediate = immediate->next;
        }

        outputFile.close();
    }
    return 0;

}

/*******************************************************************************
// 
// Function name: modifyRecord 
//
// Description: modify address of record  base on account number
//
// Parameter: uaacount(int): The account number
//            uaddr(char[]); Address of user
//
*******************************************************************************/

int llist::modifyRecord(int uaccountno, char uaddr[])
{
    #ifdef DEBUGMODE
        cout << "************************************" << endl;
        cout << "******* You are on DEBUGMODE *******" << endl;
        cout << "*******     ModifyRecord     *******" << endl;
        cout << "******* Parameters passed in *******" << endl << endl;
        cout << "Account number is: " << uaccountno << endl;
        cout << "Address is: " << endl << uaddr << endl;
        cout << "************************************" << endl;
    #endif
         
    struct record* temp;
    int returnVal;
    int count = 0;
    temp = start;

    if(temp == NULL)
    {
        returnVal = 1;
    }
    else
    {
        while(temp != NULL)
        {
            if((*temp).accountno == uaccountno)
            {
                count ++;
                strcpy((*temp).address, uaddr);
            }
            temp = (*temp).next;
        }
 
        if(count == 0)
        {
            returnVal = -1;
        }
        else
        {
            returnVal = 0;
        }
    }

    return returnVal;
}

/*******************************************************************************
//   
// Function name: operator= //EXTRA CREDIT: overload assignment operator
//   
// Description: overload operator = for copy list to list
//   
// Parameter: list(const llist): llist object
//
// Return: *this: list object
//
*******************************************************************************/

llist& llist::operator=(const llist& list)
{
    struct record* begin;
    struct record* copy_of_list;
            
    begin = list.start;
    
    if(start != NULL)
    {
        cleanup();
    }

    if(begin == NULL)
    {
        this->start = NULL;
    }
    else
    {
        this->start = new record;
        this->start->accountno = begin->accountno;
        strcpy(this->start->name, begin->name);
        strcpy(this->start->address, begin->address);
        this->start->next = NULL;

        if(begin->next != NULL)
        {
            copy_of_list = start;
            begin = begin->next;

            while(begin->next != NULL)
            {
                copy_of_list->next = new record;
                copy_of_list->next->accountno = begin->accountno;
                strcpy(copy_of_list->next->name, begin->name);
                strcpy(copy_of_list->next->address, begin->address);
                copy_of_list->next->next = NULL;
                begin = begin->next;
                copy_of_list = copy_of_list->next;
            }
        
            copy_of_list->next = new record;
            copy_of_list->next->accountno = begin->accountno;
            strcpy(copy_of_list->next->name, begin->name);
            strcpy(copy_of_list->next->address, begin->address);
            copy_of_list->next->next = NULL;
        }
    }

    return *this;
}   

