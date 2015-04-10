/***********************************************
 * Patron.hpp
 * Created by you sheng chang
 * 
 ***********************************************/

#ifndef PATRON_HPP
#define PATRON_HPP

#include <string>
#include <vector>
#include "Book.hpp"

using namespace std;

class Book;  // forward declaration

class Patron
{
private:
    string idNum;
    string name;
    vector<Book*> checkedOutBooks;
    double fineAmount;
public:
    Patron();
    Patron(string idn, string n);
    string getIdNum();
    string getName();
    vector<Book*> getCheckedOutBooks();
    void addBook(Book* b);
    void removeBook(Book* b);
    double getFineAmount();
    void amendFine(double amount);
};

#endif