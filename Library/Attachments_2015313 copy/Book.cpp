/***********************************************
 * Book.cpp
 * Created by you sheng chang
 * 
 ***********************************************/

#include "Book.hpp"
#include "Patron.hpp"
using namespace std;


Book::Book()
{
    checkedOutBy = NULL;
    requestedBy = NULL;
    location = ON_SHELF;
    
}

Book::Book(string idc, string t, string a)
{
    idCode = idc;
    title = t;
    author = a;
    checkedOutBy = NULL;
    requestedBy = NULL;
    location = ON_SHELF;
}

string Book::getIdCode()
{
    return idCode; // placeholder for actual return value
}

string Book::getTitle()
{
    return title; // placeholder for actual return value
}

string Book::getAuthor()
{
    return author; // placeholder for actual return value
}

Locale Book::getLocation()
{
    return location;
}

void Book::setLocation(Locale lo)
{
    location = lo;
}

Patron* Book::getCheckedOutBy()
{
    return checkedOutBy; // placeholder for actual return value
}

void Book::setCheckedOutBy(Patron* p)
{
    checkedOutBy = p;
}

Patron* Book::getRequestedBy()
{
    return requestedBy; // placeholder for actual return value
}

void Book::setRequestedBy(Patron* p)
{
    requestedBy = p;
}

int Book::getDateCheckedOut()
{
    return dateCheckedOut; // placeholder for actual return value
}

void Book::setDateCheckedOut(int d)
{
    dateCheckedOut = d;
}