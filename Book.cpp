/**********************************************
**Author:Teage Silbert
**Date:3/15/15
**Description:This Program is a simulator of a library
**system allowing the user to create members, books,
**request books, check them out, and accrue and pay fines
**********************************************/

#include "Book.hpp"
#include "Patron.hpp"
#include <iostream>

using namespace std;

// default constructor
Book::Book()
{
    idCode = "";
    title = "";
    author = "";
}

// constructor taking user input
Book::Book(string idc, string t, string a)
{
    idCode = idc;
    title = t;
    author = a;
}

/*****************************************
**Description: This function returns the author
**of a user created book
******************************************/
string Book::getAuthor()
{
    return author;
}

/*****************************************
**Description: This function returns the title
**of a user created book
******************************************/
string Book::getTitle()
{
    return title;
}

/*****************************************
**Description: This function returns the ID code
**of a user created book
******************************************/
string Book::getIdCode()
{
    return idCode;
}

/*****************************************
**Description: This function sets the location of
**a user created book
**Parameters: Enum of possible locations
******************************************/
void Book::setLocation(Locale Lo)
{
    location = Lo;
}

/*****************************************
**Description: This function returns the location
**of a user created book
******************************************/
Locale Book::getLocation()
{
    // if book is on shelf
    if(location == ON_SHELF)
    {
        return ON_SHELF;
    }

    // if book is on hold shelf
    if(location == ON_HOLD_SHELF)
    {
        return ON_HOLD_SHELF;
    }

    // if book is checked out
    if(location == CHECKED_OUT)
    {
        return CHECKED_OUT;
    }
}

/*****************************************
**Description: This function sets the date that a
**book was checked out
**Parameters: integer representing the current date
**of the library
******************************************/
void Book::setDateCheckedOut(int day)
{
    dateCheckedOut = day;
}

/*****************************************
**Description: This function returns the date a
**book was checked out
******************************************/
int Book::getDateCheckedOut()
{
    return dateCheckedOut;
}

/*****************************************
**Description: This function sets the patron that has
**checked out a book
**Parameters: pointer to a patron object
******************************************/
void Book::setCheckedOutBy(Patron* p)
{
    checkedOutBy = p;
}

/*****************************************
**Description: This function returns the patron who
**has a specific book checked out
******************************************/
Patron* Book::getCheckedOutBy()
{
    return checkedOutBy;
}

/*****************************************
**Description: This function sets the patron that
**currently has a book requested
**Parameters:point to a patron object
******************************************/
void Book::setRequestedBy(Patron* p)
{
    requestedBy = p;
}

/*****************************************
**Description: This function returns the patron
**who has requested a book
******************************************/
Patron* Book::getRequestedBy()
{
    return requestedBy;
}
