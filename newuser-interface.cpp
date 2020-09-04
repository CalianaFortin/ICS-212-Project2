
/************************************************************************
*
*  Name:        Josefina Fortin
*
*  Homework:    Project 2
*
*  Class:	ICS 212
*
*  Instructor:  Ravi Narayan
*
*  Date:        November 15, 2018
*
*  File         project2.cpp
*
*  Description:
*    This file utilizes llist.h and is the user interface and main function
*    for database.
*
************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
using namespace std;

void getAddress(char address[], int limit);

#include "llist.h"

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
   std:: cout<<"\n********************YOU ARE NOW IN DEBUG MODE*****************\n";
}
#endif

    int accountNumber;
    char name[25];
    char dump[10];
    char address[80];
    char file[] = "database.txt";
    char userInput = ' ';
    /**char characterCheck = ' ';**/


    /*************************************************************************
    * Note: characterCheck is for getting the \n newline character that
    * the user enters, so that way we don't run into errors of this character
    * being read as another piece of input.
    **************************************************************************/

        cout<<"\n \t \t Welcome to our bank database! \n";
        llist list(file);
    /*************************************************************
    * Note: For this assignment we are required to use a while or
    * do-while loop for the menu. So below I use a loop that looks
    * at the condition of whether or not the user selects the choice
    * of exiting the program (choice 5). So if the user does choose to 
    * exit then the while loop will terminate. Within this while loop
    * I use a switch-case because it is easier to look at each choice made
    * by the user with this rather than constructing many if statements.
    **************************************************************/

        while(userInput != '6')
        {
            std::cout<<"\n \t Here are your options. Please select one of the following: \n";
            std::cout<<"\t 1. Add Record \n";
            std::cout<<"\t 2. Print Record \n";
            std::cout<<"\t 3. Print All Records \n";
            std::cout<<"\t 4. Delete Record \n";
            std::cout<<"\t 5. Reverse Ordering of List\n";
            std::cout<<"\t 6. Quit \n \n";
            std::cout<<"\t Your Choice: ";
            cin>>userInput;

            switch(userInput)
            {
                case '1':
                std::cout<<"\nHello. Please enter the account number: ";
                std::cin>>accountNumber;
                std::cin.getline(dump,100);
                while(std::cin.fail())
                {
                    std::cout<<"Uh-Oh Looks like you didn't enter a number. Please only enter integers. \n";
                    cin.clear();
                    cin.ignore(256,'\n');
                    break;
                }

                std::cout<<"Now enter the name: ";
                std::cin.getline(name,25);
               /** std::cin.get(name,25);
                std::cin.clear();
                std::cin.ignore(256, '\n');**/
                /**name[strlen(name)- 1] = '\0';**/
                std::cout<<"Finally enter the address: (when you are done enter an asterisk [*]) \n";
                getAddress(address, 80);
                cin.getline(dump, 100);
                /**while(characterCheck != EOF && (characterCheck = getchar()!='\n'));**/

                if(list.addRecord(accountNumber, name, address) == 0)
                {
                    std::cout<<"\n Yay! Record was successfully added \n";
                }
                else 
                {
                    std::cout<<"\n Something went wrong. Record was not added.\n";
                }

                break;

                case '2':
                std::cout<<"\nHello. Please enter the account number: ";
                std::cin>>accountNumber;
                std::cin.getline(dump,100);
                if(cin.fail())
                {
                    std::cout<<"Uh-Oh Looks like you didn't enter a number. Please only enter integers. \n";
                    std::cin.clear();
                    std::cin.ignore(256,'\n');
                    break;
                }

                /****************************************************************************
                * Note: If the record is not in our database, then there should be no record
                * to print.
                ******************************************************************************/

                /**while(characterCheck != EOF && (characterCheck = getchar()!='\n'));**/
                if(list.printRecord(accountNumber) == 0)
                {
                    std::cout<<"\n Woo-Hoo! Your record has been printed. \n";
                }
                else
                {
                    std::cout<<"\n Hmm... There was an error. There is no record to print.\n";
                }

                break;

                case '3':
                std::cout<<"\nConnecting to the database, please wait...\n";
                /**while(characterCheck != EOF && (characterCheck = getchar()!='\n'));**/
                std::cout << list;

                break;

                case '4':
                std::cout<<"\nHello. Please enter the account number of the record you want to delete: ";
                std::cin>>accountNumber;
                std::cin.getline(dump,100);
                if(cin.fail())
                {
                    std::cout<<"Uh-Oh Looks like you didn't enter a number. Please only enter integers. \n";
                    std::cin.clear();
                    std::cin.ignore(256,'\n');
                    break;
                }

                /****************************************************************************
       	        * Note: If the record is not in our database, then there should be no record
       	        * to delete.
       	        ******************************************************************************/

                /**while(characterCheck != EOF && (characterCheck = getchar()!='\n'));**/
       	        if(list.deleteRecord(accountNumber) == 0)
       	        {
       	       	    std::cout<<"\n Yes! the record has been deleted.  \n";
       	        }
                else
                {
                    std::cout<<"\n Hmm... There's no record of that account number to delete.\n";
                }

                break;

                case '5':
                std::cout<<"Beginning to reverse your list, please wait...\n";
                list.reverse();

                break;

                case '6':
                std::cout<<"\nGoodbye! Have a nice day :)\n";
                /**writefile(start, "outTest.txt");**/
                break;

                default:
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cout<<"\n Hey that is not a valid choice! Only enter numbers 1-6! \n";
                break;
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

void getAddress(char address[], int limit)
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



