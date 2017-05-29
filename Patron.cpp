/**********************************************
**Author:Teage Silbert
**Date:3/15/15
**Description:This Program is a simulator of a library
**system allowing the user to create members, books,
**request books, check them out, and accrue and pay fines
**********************************************/

#include "Patron.hpp"
#include <iostream>

using namespace std;
// default constructor
Patron::Patron()
{
    idNum = "";
    name = "";
    fineAmount = 0.0;
}

// constructor taking user input
Patron::Patron(string idn, string n)
{
    idNum = idn;
    name = n;
    fineAmount = 0.0;
}

/*****************************************
**Description: This function returns the ID number
**of a user created patron
******************************************/
string Patron::getIdNum()
{
    return idNum;
}

/*****************************************
**Description: This function returns the name
**of a user created patron
******************************************/
string Patron::getName()
{
    return name;
}

/*****************************************
**Description: This function checks out books to a specific patron
**using a vector
**Parameters: pointer to a book object
******************************************/
void Patron::addBook(Book* b)
{
    checkedOutBooks.push_back(b);
}

/*****************************************
**Description: This function returns the books checked out
**by a specific patron
******************************************/
vector<Book*> Patron::getCheckedOutBooks()
{
    return checkedOutBooks;
}

/*****************************************
**Description: This function removes books from a specific
**patrons checked out list
**Parameters:pointer to a book object
******************************************/
void Patron::removeBook(Book* b)
{
    for(int i = 0; i < checkedOutBooks.size(); i++)
    {
        if(b == checkedOutBooks[i])
        {
            checkedOutBooks.erase(checkedOutBooks.begin() + i);

        }
    }
}

/*****************************************
**Description: This function returns the fine amount
**of a user created patron
******************************************/
double Patron::getFineAmount()
{
    return fineAmount;
}

/*****************************************
**Description: This function calculates the fines for
**specific patron if they have an overdue book
**Parameters:double to represent the fine amount
******************************************/
void Patron::amendFine(double fine)
{
    fineAmount += fine;
}
