/***********************************************
 * Library.hpp
 * Created by Matthew D Mayberry on 3/11/15
 * CS161_400_W2015_Final_Project
 ***********************************************/

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
using namespace std;

class Patron;  // forward declarations
class Book;

class Library
{
private:
    vector<Book> holdings; // a list of Books the library has
    vector<Patron> members; // a list of Patrons the library has
    int currentDate; // stores the current date represented as an integer number of "days" since the Library object was created
    
public:
    Library(); // initalizes currentDate to zero
    void addBook(); // prompts user for book info (including ID) and uses it to create a Book object, which is added to holdings
    void addMember(); // prompts the user for patron info (including ID) and uses it to create a Patron object, which is added to members
    
    // check if the book is not in the library, checked out, or on hold.  otherwise update the Book's checkedOutBy, dateCheckedOut and Location
    void checkOutBook(string patronID, string bookID);
    
    // check if the book is not in the library, the book is already requested, or checked out by Patron requesting it.  Otherwise update requested by, Location to on hold, and print that the Book is on request for the Patron
    void returnBook(string bookID);
    
    void requestBook(string patronID, string bookID);
    void incrementCurrentDate();
    void payFine(string patronID, double payment);
    void viewPatronInfo(string patronID);
    void viewBookInfo(string bookID);
    
};

#endif