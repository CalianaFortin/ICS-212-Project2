/*****************************************************************
//
// NAME:        Caliana Fortin
//
// HOMEWORK:    project
//
// CLASS:	ICS 212
//
// INSTRUCTOR:  Ravi Narayan
//
// DATE:       dec 12, 2019
//
// FILE:       user-interface.c
//
// DESCRIPTION: This file contains the user-interface function that
//              presents the user with a menu of choices
//
*****************************************************************/

#include <iostream>
#include <climits>
#include "record.h"
#include "llist.h"


#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>

 
using namespace std;

void getaddress (char [ ], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:
//                 This function is used to run and execute the program.
//
//  Parameters:    int argc, char * argv[]
//
//  Return values: 0, this acts like an exit to the program
//
****************************************************************/

int main(int argc, char * argv[])
{

/*************************************************************
* Note: For when we run debug, we need to check if the argument
* entered is 2, ie hw3 debug, then this means we are in debug mode
* an error is printed and we exit the program.
**************************************************************/
#ifdef DEBUG
{
   cout<<"\n-----------------YOU ARE NOW IN DEBUG MODE-----------------\n";
}
#endif


    char Usr_input[12], name[50], address[100], garbage[10];
    int accountno, loopFlag, flag, returnVal;
    flag = 1;
    loopFlag = 1; /* used to exit the outer loop */
    char filename[] = "database.txt";
    llist mylist(filename);

    cout<<"\n \t \t Welcome to our bank database! \n";

    /* For extra credit 
    // llist copylist(mylist);
    // cout << copylist;
    */

    while(loopFlag == 1)
    {
        cout << "\n";
        cout << "----------------------------------------------------\n";
        cout << "|            Please Enter an option 1-7            |\n";
        cout << "|                                                  |\n";
        cout << "|       (1) ADD a new record                       |\n";
        cout << "|       (2) MODIFY a record                        |\n";
        cout << "|       (3) PRINT a record                         |\n";
        cout << "|       (4) PRINT ALL records                      |\n";
        cout << "|       (5) DELETE a record                        |\n";
        cout << "|       (6) REVERSE the list                       |\n";
        cout << "|       (7) QUIT the program                       |\n";
        cout << "|                                                  |\n";
        cout << "----------------------------------------------------\n";

       cin >> Usr_input;

       if(strcmp(Usr_input, "1") == 0)
       {
           cout << "Please enter the account number\n";
           cin >> accountno;
           cin.getline(garbage, 100);
          while(cin.fail() && flag == 1)
          {
                cout<<"Uh-Oh Looks like you didn't enter a number. Please only enter integers. \n";
                cin.clear();
                cin >> accountno;
                cin.getline(garbage, 100);                  
                flag = 0;
           }

           
           cout << "Please enter your name" << endl;
           cin.getline(name, 25);
           
           cout << "Please enter your address" << endl;
           cout << "When you are done enter '*' and return to finish inputting" << endl;
           cin.get(address, 80, '*');
           cin.getline(garbage, 100);

           returnVal = mylist.addRecord(accountno, name, address);
           cout << returnVal <<endl;
           if (returnVal ==  -1)
           {
               cout << "The record could not be added, or was a duplicate" << endl;
           }
           else if(returnVal == 0)
           {
               cout << endl << "Your record was added!" << endl;
           }




       }
       else if(strcmp (Usr_input, "2") == 0)
       {
           cout << "Please enter the account number you want to modify" << endl;
           cin >> accountno;
           cin.getline(garbage, 100);
           
           cout << "Please enter your new address" << endl;
           cout << "When you are done enter '*' and return to finish inputting" << endl;
           cin.get(address, 80, '*');
           cin.getline(garbage, 100);

           returnVal = mylist.modifyRecord(accountno, address);
           
           if(returnVal == 1) 
           {
               cout << endl << "The List is empty. There is nothing to modify."<< endl;
           }
           if(returnVal == -1)
           {
               cout << endl << "There is no record with that number." << endl; 
           }
           if(returnVal == 0)
           {
               cout << endl << "Your record was modified!" << endl;
           }
       }
       else if(strcmp (Usr_input, "3") == 0)
       {
           cout << "Please enter the account number you would like to print." << endl;
           cin >> accountno;
           cin.getline(garbage, 100);
           returnVal = mylist.printRecord(accountno);
           if(returnVal == 1)
           {
               cout << endl << "The list is empty, there was nothing to print."<< endl;
           }
           if(returnVal == -1) 
           {
               cout << endl << "There is not record with that number." << endl;
           }
           if(returnVal == 0) 
           {
               cout << endl << "Your record was printed." << endl;
           }
       }
       else if(strcmp (Usr_input, "4") == 0) 
       {
           cout << mylist;
       }
       else if(strcmp (Usr_input, "5") == 0)
       {
           cout << "Please enter the account number you wish to delete." << endl;
           cin >> accountno;
           cin.getline(garbage, 100);
           returnVal = mylist.deleteRecord(accountno);
           if (returnVal == 1) 
           {
               cout << endl << "The list is empty, there is nothing to delete." << endl;
           }
           if (returnVal == -1) 
           {
               cout << endl << "There is no record with that number." << endl;
           }
           if (returnVal == 0) 
           {
               cout << endl << "The record was deleted." << endl;
           }

       }
       else if(strcmp (Usr_input, "6") == 0) 
       {
           mylist.reverse();
           cout << endl << "Your list has been reversed. The only available option is the printall." << endl;
           cout << endl << "Please select 6 to restore the order." << endl;
       }

       else if(strcmp (Usr_input, "7") == 0)
       {
           loopFlag = 0;
           cout << endl << "Your bank records have been added to a file." << endl;
           cout << "Goodbye!" << endl;
       }
       else 
       {
           cout << "Invalid choice." << endl;
       }

    }    
   
    return 0;
}

/**************************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:
//                 This function is used to read the address the user inputs
//                 when asked in addRecord. This allows the user to enter
//                 lines for the address.
//
//  Parameters:    char address[], int limit
//
//  Return values: none
//
**************************************************************************/

/***************************************************************
* Note:
* For this method, I use a while loop since the user is going to enter
* multiple lines of input. The condition for this loop is if the user decides
* to enter a * then they are done inputting the address, and we break
* from the while loop.
******************************************************************/

void getaddress(char address[], int limit)
{
    char addressDone;
    int lengthOfAddress;

    #ifdef DEBUG
    {
     	cout<<"**********************DEBUG MESSAGE*****************************\n";
        cout<<"Hey there! You called the getAddress function \n";
        cout<<"This is the address: \n";
        cout<< address<<"\n";
        cout<<"**********************************************************\n";
    }
    #endif

    /**We need to keep track of the length of the address since
    we cannot exceed the limit (which the amount of characters)**/

    lengthOfAddress = 0;

    /**while the character within the string array is not equal to
    * then the user can input as many characters for the
    address (as long it is less than the limit)**/

    while((addressDone = getchar()) != '*' && (lengthOfAddress + 1) < limit)
    {
     	address[lengthOfAddress++] = addressDone;
    }

    address[lengthOfAddress]='\0';

}





