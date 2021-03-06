/***********************************************
 * Patron.cpp
 * Created by you sheng chang
 * 
 ***********************************************/

#include "Patron.hpp"
using namespace std;

Patron::Patron()
{
	fineAmount = 0;
}

Patron::Patron(string idn, string n)
{
    idNum = idn;
    name = n;
    fineAmount = 0;
}

string Patron::getIdNum()
{
    return idNum; // placeholder for actual return value
}

string Patron::getName()
{
    return name; // placeholder for actual return value
}

vector<Book*> Patron::getCheckedOutBooks()
{
    return checkedOutBooks;
}

void Patron::addBook(Book* b)
{
    checkedOutBooks.push_back(b);
}

void Patron::removeBook(Book* b)
{
    vector<Book*>::iterator it;
    vector<Book*>::iterator start;
    vector<Book*>::iterator end;
    string bookId;
    start = checkedOutBooks.begin();
    end = checkedOutBooks.end();
    for(it = start; it < end; ++it){
        bookId = (*it)->getIdCode();
        if((b->getIdCode()) == bookId)
            checkedOutBooks.erase(it);
        
    }
    
}

double Patron::getFineAmount()
{
    return fineAmount; // placeholder for actual return value
}

void Patron::amendFine(double amount)
{
    fineAmount += amount;
}
