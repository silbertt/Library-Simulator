/**********************************************
**Author:Teage Silbert
**Date:3/15/15
**Description:This Program is a simulator of a library
**system allowing the user to create members, books,
**request books, check them out, and accrue and pay fines
**********************************************/

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>

class Patron;  // forward declarations
class Book;

class Library
{
private:
    std::vector<Book> holdings;
    std::vector<Patron> members;
    int currentDate;
public:
    Library();
    void day();
    void addBook(Book);
    void addMember(Patron);
    void libMembers();
    void books();
    void checkOutBook(std::string patronID, std::string bookID);
    void returnBook(std::string bookID);
    void requestBook(std::string patronID, std::string bookID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    bool memIDUsed(std::string patronID);
    bool bookIDUsed(std::string bookID);
    void viewBookInfo(std::string bookID);
};

#endif
