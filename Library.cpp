/**********************************************
**Author:Teage Silbert
**Date:3/15/15
**Description:This Program is a simulator of a library
**system allowing the user to create members, books,
**request books, check them out, and accrue and pay fines
**********************************************/

#include "Library.hpp"
#include "Book.hpp"
#include "Patron.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

// default constructor
Library::Library()
{
    currentDate = 0;
    holdings.reserve(100);
    members.reserve(100);
}

/*****************************************
**Description: This function receives a book object and
**puts in the library inventory
**Parameters: Book object
******************************************/
void Library::addBook(Book literature)
{
    holdings.push_back(literature);
}

/*****************************************
**Description: This function receives a patron object and
**puts it in the library members
**Parameters: Patron object
******************************************/
void Library::addMember(Patron client)
{
    members.push_back(client);
}

/*****************************************
**Description: This function checks to see if a member
**id has been used
**Parameters: string to represent the member id
******************************************/
bool Library::memIDUsed(string code)
{
    for(int i = 0; i < members.size(); i++)
    {
        if(code == members[i].getIdNum())
        {
            return false;
            break;
        }
    }
    return true;
}

/*****************************************
**Description: This function checks to see if a book
**id has been used
**Parameters: string to represent the book id
******************************************/
bool Library::bookIDUsed(string code)
{
    for(int i = 0; i < holdings.size(); i++)
    {
        if(code == holdings[i].getIdCode())
        {
            return false;
            break;
        }
    }
    return true;
}

/*****************************************
**Description: This function outputs the books and id codes
**that the library currently has in inventory
******************************************/
void Library::books()
{
    cout << "The books currently in inventory are:" << endl;
    string dashes;
    dashes.assign(68, '-');
    cout << dashes <<endl;

    cout << setw(40) << left << "Book Title" << setw(20) << left << "Book Author" << setw(8) << left << "ID" << endl;
    cout << dashes <<endl;

    // for loop to get all of the titles, authors, and ID codes
    for(int i = 0; i < holdings.size(); i++)
    {
        cout << setw(40) << left << holdings[i].getTitle();
        cout << setw(20) << left << holdings[i].getAuthor();
        cout << setw(8) << left << holdings[i].getIdCode() << endl;
    }
    //formatting
    cout << dashes << endl;
}

/*****************************************
**Description: This function outputs the patrons and id codes
**that the library currently has
******************************************/
void Library::libMembers()
{
    cout << "The current Library Members are:" << endl;
    string dashes;
    dashes.assign(42, '-');
    cout << setw(30) << left << "Member Name: " << setw(8) << left << "Member ID:" << endl;
    cout << dashes << endl;

    //  for loop to go through all members
    for(int i = 0; i < members.size(); i++)
    {
        cout << setw(30) << left << members[i].getName();
        cout << setw(8) << left << members[i].getIdNum() << endl;
    }
    cout << dashes << endl;
}

/*****************************************
**Description: This function outputs information on a specific book
**based upon the code of of the book
**Parameters: string to represent the id code of the book
******************************************/
void Library::viewBookInfo(string code)
{
    // for loop to find the book
    for(int i = 0; i < holdings.size(); i++)
    {
        // if the provided id code matches a book in inventory
        if(code == holdings[i].getIdCode())
          {
              cout << setw(10) << left << "Title: " << holdings[i].getTitle() << endl;
              cout << setw(10) << left << "Author: " << holdings[i].getAuthor() << endl;

                  // if book is on shelf
                  if(holdings[i].getLocation() == ON_SHELF)
                  {
                      cout << setw(8) << left << "Location: " << "On Shelf\n" << endl;
                  }

                  //if book is on hold shelf
                  if(holdings[i].getLocation() == ON_HOLD_SHELF)
                  {
                      cout << setw(8) << left << "Location: " << "On Hold Shelf" << endl;
                      cout << setw(8) << left << "Requested by: " << holdings[i].getRequestedBy()->getName() << "\n" << endl;
                  }

                  // if checked out
                  if(holdings[i].getLocation() == CHECKED_OUT)
                  {
                      cout << setw(8) << left << "Location: " << "Checked Out" << endl;
                      cout << setw(8) << left << "Date Checked Out: " << holdings[i].getDateCheckedOut() << endl;
                      cout << setw(8) << left << "Checked out by: " << holdings[i].getCheckedOutBy()->getName() << "\n" << endl;

                      if((Book::CHECK_OUT_LENGTH + holdings[i].getDateCheckedOut()) - currentDate < 0)
                      {
                          cout << "Book is overdue" << endl;
                      }

                      else
                      {
                          cout << "Book is due in " << (Book::CHECK_OUT_LENGTH + holdings[i].getDateCheckedOut()) - currentDate << " days\n" << endl;
                      }
                  }
          }
    }
}

/*****************************************
**Description: This function outputs information on a specific patron
**based upon the code of of the patron
**Parameters: string to represent the id code of the patron
******************************************/
void Library::viewPatronInfo(string memID)
{
    // for loop to cycle through all members
    for(int i = 0; i < members.size(); i++)
    {
        // if the provided member id matches a patron of the library
        if(memID == members[i].getIdNum())
        {
            // vector of book pointers
            vector<Book*> pPatron;

            // output member information
            cout << setw(8) << left << "Name: " << members[i].getName() << endl;
            cout << setw(8) << left << "ID: " << members[i].getIdNum() << endl;
            cout << setw(8) << left << "Fines: $" << setprecision(5) << members[i].getFineAmount() << endl;

            // set pointers to the books the member has checked out
            pPatron = members[i].getCheckedOutBooks();

            // output books checked out by member
            cout << "Books currently Checked out: " << endl;

            // output titles the patron currently has checked out
            for(int i = 0; i < pPatron.size(); i++)
            {
                 cout << pPatron[i]->getTitle() << endl;
            }

            //clear vector
            pPatron.clear();
        }
    }

}

/*****************************************
**Description: This function increments the date of the library
**and also checks to see if any books are overdue and if so calls the
**function to increase fines
******************************************/
void Library::incrementCurrentDate()
{
    //increment current date
    currentDate++;

    //vector of book object pointers
    vector<Book*> fines;

    // set vector to the have all checked out books
    for(int i = 0; i < members.size(); i++)
    {
        fines = members[i].getCheckedOutBooks();

        //checks to see if checked out books are overdue
        for(int x = 0; x < fines.size(); x++)
        {
            if(currentDate - fines[x]->getDateCheckedOut() > 21)
            {
                members[i].amendFine(.10);
            }
        }
    }
    // clear the vector
    fines.clear();
}

/*****************************************
**Description: This function outputs the current date
******************************************/
void Library::day()
{
    cout << "Current Date is: " << currentDate;
    cout << "\n" << endl;
}

/*****************************************
**Description: This function checks out books to a specific patron
**Parameters: two strings, one representing a patron id
**and the other representing a book id
******************************************/
void Library::checkOutBook(string memID, string bookID)
{
    int date = currentDate;
    // locate book in library
    for(int i = 0; i < holdings.size(); i++)
    {
        // if book is found
        if(bookID == holdings[i].getIdCode())
        {
            // if book is checked out
            if(holdings[i].getLocation() == CHECKED_OUT)
            {
                cout << "I'm sorry that book is currently checked out\n" << endl;
            }
            // if book is on hold for another patron
            if(holdings[i].getLocation() == ON_HOLD_SHELF)
            {
                    if(memID == holdings[i].getRequestedBy()->getIdNum())
                    {
                        for(int j = 0; j < members.size(); j++)
                        {
                            if(memID == members[j].getIdNum())
                            {
                                holdings[i].setLocation(CHECKED_OUT);
                                holdings[i].setDateCheckedOut(date);

                                // point to patron object
                                Patron* plibMem;
                                // set pointer to location of member
                                plibMem = &members[j];
                                // pointer to book object
                                Book* pBook;
                                // set pointer to location of book
                                pBook = &holdings[i];

                                // inform user of the book checked out and when it is due
                                cout << "'" <<holdings[i].getTitle() << "' has been checked out by: " << plibMem->getName() << endl;
                                cout << "\n" << plibMem->getName() << " has 21 days to return the book before late fees will start to accrue\n" << endl;
                                //check out book to member and add the book to the patron
                                holdings[i].setCheckedOutBy(plibMem);
                                members[j].addBook(pBook);
                                break;
                            }
                        }

                    }

                    else
                    {
                        cout << "I'm sorry that book is on hold for another patron\n" << endl;
                    }
        }
            //if book is available
            if(holdings[i].getLocation() == ON_SHELF)
            {

                //change location and set the date checked out
                holdings[i].setLocation(CHECKED_OUT);
                holdings[i].setDateCheckedOut(date);

                // add to book to patron
                for(int x = 0; members.size(); x++)
                {
                    // if member id is valid
                    if(memID == members[x].getIdNum())
                    {
                        // point to patron object
                        Patron* plibMem;
                        // set pointer to location of member
                        plibMem = &members[x];
                        // pointer to book object
                        Book* pBook;
                        // set pointer to location of book
                        pBook = &holdings[i];

                        // inform user of the book checked out and when it is due
                        cout << "'" <<holdings[i].getTitle() << "' has been checked out by: " << plibMem->getName() << endl;
                        cout << "\n" << plibMem->getName() << " has 21 days to return the book before late fees will start to accrue\n" << endl;
                        //check out book to member and add the book to the patron
                        holdings[i].setCheckedOutBy(plibMem);
                        members[x].addBook(pBook);
                        break;
                    }
                }
            }
        }

    }
}

/*****************************************
**Description: This function requests books for a specific patron
**Parameters: two strings, one representing a patron id
**and the other representing a book id
******************************************/
void Library::requestBook(string memID, string bookID)
{
    // cycle through all books
    for(int i = 0; i < holdings.size(); i++)
    {
        // if book id is valid
        if(bookID == holdings[i].getIdCode())
        {
            // patron pointer
            Patron* reqBy = NULL;


            // if book is already on hold inform user
            if(holdings[i].getLocation() == ON_HOLD_SHELF)
            {
                cout << "I'm sorry, but '" << holdings[i].getTitle() << "' is currently" << endl;
                cout << "on hold for another patron\n" << endl;
            }

            // if book is on the shelf move it to the hold shelf
            if(holdings[i].getLocation() == ON_SHELF)
            {
                holdings[i].setLocation(ON_HOLD_SHELF);

                // inform user that the book is on request for them
                for(int x = 0; x < members.size(); x++)
                {
                    if(memID == members[x].getIdNum())
                    {
                        cout << "'" << holdings[i].getTitle() << "' is on request for " << members[x].getName() << "\n" << endl;
                        //set pointer to location of the member that requested it
                        reqBy = &members[x];

                        // set the book requested
                        holdings[i].setRequestedBy(reqBy);

                        break;
                    }
                }
            }
            //if book is currently checked out
            if(holdings[i].getLocation() == CHECKED_OUT)
            {
                    // if patron already has the book checked out
                    if(memID == holdings[i].getCheckedOutBy()->getIdNum())
                    {
                        cout << "You already have '" << holdings[i].getTitle() << "' checked out." << endl;
                    }
                    // if they don't have it checked out put it on request for them
                    else
                    {
                        for(int c = 0; c < members.size(); c++)
                          {
                            if(members[c].getIdNum() == memID)
                            {
                                cout << "'" << holdings[i].getTitle() << "' is currently checked out, but will be held" << endl;
                                cout << "for " << members[c].getName() << " once it is returned\n" << endl;
                                // pass member location to pointer
                                reqBy = &members[c];
                                //set requested by to patron
                                holdings[i].setRequestedBy(reqBy);
                                break;
                            }
                          }
                    }
            }
        }
    }
}

/*****************************************
**Description: This function returns for a specific patron
**Parameters: a string representing the book ID
******************************************/
void Library::returnBook(string bookID)
{
     // book object pointer
     Book* pReturn;

    // find the book being returned
    for(int i = 0; i < holdings.size(); i++)
    {

        //find the member returning the book
        for(int x = 0; x < members.size(); x++)
        {
            if(holdings[i].getCheckedOutBy()->getIdNum() == members[x].getIdNum())
            {

                //set location of pointer to book being returned
                pReturn = &holdings[i];

                members[x].removeBook(&holdings[i]);

            }
        }
        //check to see if book is requested by another patron
        if(bookID == holdings[i].getIdCode())
        {
                //if the book is not requested by anyone
                if(!holdings[i].getRequestedBy())
                {
                   holdings[i].setLocation(ON_SHELF);
                }
                //if book is requested by another patron
                if(holdings[i].getRequestedBy())
                {
                    holdings[i].setLocation(ON_HOLD_SHELF);
                }

                cout << "Thank you for returning '" << holdings[i].getTitle() << "'\n" << endl;
                break;
        }
    }
}

/*****************************************
**Description: This function allows the user to pay
**the fines of a specific member
**Parameters:string to represent user id and double to
**represent the amount being paid
******************************************/
void Library::payFine(string pID, double amount)
{
    // find member paying the fine
    for(int i = 0; i < members.size(); i++)
    {
        if(pID == members[i].getIdNum())
        {
            // pay the specified amount of the fine
            members[i].amendFine(amount);
            cout << members[i].getName() << " now has " << members[i].getFineAmount() << " balance\n" << endl;
        }
    }


}
