/***********************************************
 * Book.hpp
 * Created by you sheng chang
 * 
 ***********************************************/

#ifndef BOOK_HPP
#define BOOK_HPP
#include <string>
#include "Patron.hpp"
using namespace std;

class Patron;  // forward declaration


// These three locations are mutually exclusive, but note that
// a Book can be on request for a Patron while being checked
// out to another Patron.  In that case the Book's location is
// CHECKED_OUT, and when it is returned, it's location will
// become ON_HOLD_SHELF.

enum Locale {ON_SHELF, ON_HOLD_SHELF, CHECKED_OUT};


class Book
{
private:
    string idCode;  // Unique identifier for a Book
    string title;  // Book title.  Cannot be assumed to be unique.  Initalized with default
    string author; // Initalized with constructor
    Locale location;
    Patron* checkedOutBy; // pointer to the Patron who has it checked out
    Patron* requestedBy; // pointer to the Patron who has requested it
    int dateCheckedOut; // when a book is checked out, this will be set to the currentDate of the Library
    
public:
    static const int CHECK_OUT_LENGTH = 21; // constant that gives how long a Book can be checked out for
    Book(); 
    Book(string idc, string t, string a);
    string getIdCode();
    string getTitle();
    string getAuthor();
    Locale getLocation();
    void setLocation(Locale lo);
    Patron* getCheckedOutBy();
    void setCheckedOutBy(Patron* p);
    Patron* getRequestedBy();
    void setRequestedBy(Patron* p);
    int getDateCheckedOut();
    void setDateCheckedOut(int d);
};

#endif