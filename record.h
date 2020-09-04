/*****************************************************************
//
//  NAME:        Caliana Fortin
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 10, 2019 
//
//  FILE:        record.h
//
//  DESCRIPTION:
//  This file contains the structure record.
//
****************************************************************/

#ifndef _RECORDH_
#define _RECORDH_

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};


#endif


