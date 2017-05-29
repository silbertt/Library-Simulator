/**********************************************
**Author:Teage Silbert
**Date:3/15/15
**Description:This Program is a simulator of a library
**system allowing the user to create members, books,
**request books, check them out, and accrue and pay fines
**********************************************/

#include <iostream>
#include <string>
#include "Book.hpp"
#include "Library.hpp"
#include "Patron.hpp"

#include "Library.cpp"
#include "Patron.cpp"
#include "Book.cpp"

using namespace std;

int main()
{
    Library reading;

    cout << "Welcome to the library" << endl;

    // int for menu
    int userChoice = 0;

    // menu for user options
    do
    {   // formatting items
        string dashes;
        string format = "Please choose an option below";
        int formatLength = format.length();
        dashes.assign(formatLength, '-');

        cout << format << endl;
        cout << dashes << endl;
        cout << "1.  View book list" << endl;
        cout << "2.  View library members" << endl;
        cout << "3.  View the current date" << endl;
        cout << "4.  Donate a book to the library" << endl;
        cout << "5.  Add a member to the library" << endl;
        cout << "6.  Check out a book" << endl;
        cout << "7.  Return a book" << endl;
        cout << "8.  Request a book" << endl;
        cout << "9.  Pay a fine" << endl;
        cout << "10. View member information" << endl;
        cout << "11. View book information" << endl;
        cout << "12. Increment Date" << endl;
        cout << "13. Quit" << endl;
        cout << dashes << endl;
        cin >> userChoice;

        // view book list
        if(userChoice == 1)
        {
            reading.books();
        }

        // view library members
        if(userChoice == 2)
        {
            reading.libMembers();
        }

        // view current date
        if(userChoice == 3)
        {
            reading.day();
        }

        // Donate book to library
        if(userChoice == 4)
        {
            cin.ignore();
            string bName, writer, idCode;
            cout << "Please enter the name of the book:" << endl;
            getline(cin, bName);
            cout << "Please enter the Author:" << endl;
            getline(cin, writer);
            cout << "Please enter the ID Code:" << endl;
            cin >> idCode;
            cin.ignore();

            // if ID code is already used
            if(!reading.bookIDUsed(idCode))
            {
                cout << "*********************************************" << endl;
                cout << "*** I'm sorry that code is already in use ***" << endl;
                cout << "*********************************************" << endl;
            }
            else
            {
                // pass data to book object
                Book pages(idCode, bName, writer);
                // set location
                pages.setLocation(ON_SHELF);
                // add book
                reading.addBook(pages);

            }
        }
        // add member to library
        if(userChoice == 5)
        {
            // obtain data from user
            cin.ignore();
            string guestName, guestID;
            cout << "Please enter the name of the patron:" << endl;
            getline(cin, guestName);
            cout << "Please enter the patron ID:" << endl;
            getline(cin, guestID);

            // if code is already in use
            if(!reading.memIDUsed(guestID))
            {
                cout << "*********************************************" << endl;
                cout << "*** I'm sorry that code is already in use ***" << endl;
                cout << "*********************************************" << endl;
            }
            else
            {
                // pass data to patron object
                Patron member(guestID, guestName);

                // add patron to library
                reading.addMember(member);
            }
        }

        // check out book
        if(userChoice == 6)
        {
            string iDMem;
            string iDBook;
            cin.ignore();
            cout << "What is the Book ID you would like to checkout?" << endl;
            getline(cin, iDBook);
            cout << "What is the Member ID checking out the book?" << endl;
            getline(cin, iDMem);

            // check for valid id's
            if(reading.memIDUsed(iDMem) || reading.bookIDUsed(iDBook))
            {
                cout << "I'm sorry we are unable to locate either the\n";
                cout << "Book ID or Member ID\n" << endl;
            }
            else
            {
                reading.checkOutBook(iDMem, iDBook);
            }
        }

        // return book
        if(userChoice == 7)
        {
            string bookID;
            string memID;

            cin.ignore();
            cout << "What is the book ID you are returning?" << endl;
            getline(cin, bookID);

            // if book is not in inventory
            if(reading.bookIDUsed(bookID))
            {
                cout << "I'm sorry we don't currently have that book in our inventory\n" << endl;
            }
            else
            {
                reading.returnBook(bookID);
            }
        }

        // request a book
        if(userChoice == 8)
        {
            string iDMem;
            string iDBook;
            cin.ignore();
            cout << "What is the Book ID you would like to request?" << endl;
            getline(cin, iDBook);
            cout << "What is the Member ID requesting the book?" << endl;
            getline(cin, iDMem);

            // check for valid ID's
            if(reading.memIDUsed(iDMem) || reading.bookIDUsed(iDBook))
            {
                cout << "I'm sorry we are unable to locate either the\n";
                cout << "Book ID or Member ID\n" << endl;
            }
            else
            {
                reading.requestBook(iDMem, iDBook);
            }
        }

        // pay a fine
        if(userChoice == 9)
        {

                string memID;
                double amount = 0.0;
                cin.ignore();
                cout << "What Member ID would you like to pay a fine for?" << endl;
                getline(cin, memID);

            //validate user ID
            if(!reading.memIDUsed(memID))
            {
                cout << "How much would you like to pay?" << endl;
                cin >> amount;
                amount = amount - amount - amount;
                reading.payFine(memID, amount);
            }

            // if no patron at library with given ID
            else
            {
                cout << "I'm sorry we do not have a member with that ID\n" << endl;
            }
        }

        // view patron information
        if(userChoice == 10)
        {
            string iDMem;
            cout << "What is the Members ID Code?" << endl;
            cin >> iDMem;

            //if ID is valid
            if(!reading.memIDUsed(iDMem))
            {
                // pass code to book to locate
                reading.viewPatronInfo(iDMem);
            }
            else
            {
                cout << "I'm sorry the library currently does not have a Member with that code\n" << endl;
            }
        }

        // view book information
        if(userChoice == 11)
        {
            string code;
            cout << "What is the ID Code of the book?" << endl;
            cin >> code;

            if(reading.bookIDUsed(code))
            {
                cout << "I'm sorry the library currently does not have that book\n" << endl;
            }
            else
            {
                // pass code to book to locate
                reading.viewBookInfo(code);
            }
        }
        // increment date
        if(userChoice == 12)
        {
            cout << "Date incremented by 1\n" << endl;
            reading.incrementCurrentDate();
        }

    }
    while(userChoice != 13);



return 0;
}

