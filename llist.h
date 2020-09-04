/*****************************************************************
//
//  NAME:        Caliana Fortin
//
//  HOMEWORK:    project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 9, 2019
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//    This file utilizes the record.h file and contains the database with
//    necessary method definitions
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include "record.h"

using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist&); //EXTRA CREDIT: copy constructor
    ~llist();
    int addRecord(int, char [ ],char [ ]);
    int printRecord(int);
    // replace printAllRecords() with the << operator
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();

    llist& operator=(const llist&); //EXTRA CREDIT: overload assignment operator
    friend ostream & operator<<(ostream&, const llist&);

};

#endif
