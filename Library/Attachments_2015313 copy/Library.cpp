/***********************************************
 * Library.hpp
 * Created by you sheng chang
 * 
 ***********************************************/

#include <iostream>
#include "Library.hpp"
#include "Book.hpp"
#include "Library.hpp"

using namespace std;

void displayHoldings(Library *lib);

Library::Library()
{
    holdings = vector<Book>();
    members = vector<Patron>();
    currentDate = 0;
    
}

void Library::addBook()
{
    string title;
    string author;
    string idCode;
    char buf[280];
    
    cout << "Input title of the book: " << endl;
    cin.getline(buf, sizeof(buf));
    title = buf;
   
    
    cout << "Input author of book: " << endl;
    
    cin.getline(buf, sizeof(buf));
    author = buf;
    cout << "Input the book ID Code: " << endl;
    cin >> idCode;
    
    cout << "title: " << title << " author: " << author << "idCode: " << idCode << endl;
    Book *book = new Book(idCode, title, author);
    holdings.push_back(*book);
    
    cout << "holdings has: " << endl;
    for(int i = 0; i < holdings.size(); ++i){
        cout << holdings[i].getAuthor() << endl;
        cout << &holdings[i] << endl;
    }
    
    
    
    
}



void Library::addMember()
{
    string name;
    string idNum;
    char buf[128];
    
    cout << "Input patron's name: " << endl;
    cin.getline(buf, sizeof(buf));
    name = buf;
    cout << "Inpute the patron's id: " << endl;
    cin.getline(buf, sizeof(buf));
    idNum = buf;
    cout << "name: " << name << " id: " << idNum << endl;
    Patron *patron = new Patron(idNum, name);
    members.push_back(*patron);
    
    cout << "The library has members: " << endl;
    for(int i = 0; i < members.size(); ++i){
        cout << members[i].getName() << endl;
        cout << &members[i] << endl;
    }
    
}

void Library::checkOutBook(string patronID, string bookID)
{
    vector<Book>::iterator it;
    vector<Book>::iterator position;
    string bookId;
    bool findBook = false;
    vector<Patron>::iterator pt;
    bool findPatron = false;
    string pId;
    Book book;
    Patron patron;
    int memberPos, bookPos;
    cout << "Input patronID: " << patronID << " bookID: " << bookID << endl;
    
    for(int i = 0; members.size(); ++i){
        if(patronID == members[i].getIdNum()){
            findPatron = true;
            memberPos = i;
            break;
            
        }
    }
 
    if(findPatron == false){
        cout << "Patron is not registered in this library." << endl;
        return;
    }
    for(int i = 0; i < holdings.size(); ++i){
        if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_SHELF){
            findBook = true;
            bookPos = i;
            holdings[i].setCheckedOutBy(&members[memberPos]);
            holdings[i].setDateCheckedOut(currentDate);
            holdings[i].setLocation(CHECKED_OUT);
            members[memberPos].addBook(&holdings[i]);
            
        }
        else if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_HOLD_SHELF){
            if (holdings[i].getRequestedBy() == &members[memberPos]) {
                findBook = true;
                bookPos = i;
                holdings[i].setCheckedOutBy(&members[memberPos]);
                holdings[i].setDateCheckedOut(currentDate);
                holdings[i].setLocation(CHECKED_OUT);
                members[memberPos].addBook(&holdings[i]);
                
            }else{
                cout << "The book is requested by other people and on hold." << endl;
                return;
                
            }

        }
        else if ((bookID == holdings[i].getIdCode())&&
                 (holdings[i].getLocation() == CHECKED_OUT)){
            
            cout << "The book is checked out by other people." << endl;
            return;
            
        }
        
    }
    
    if(findBook == false){
        cout << "The book is not found." << endl;
        return;
    }
    
    
}



void Library::returnBook(string bookID)
{
    vector<Book>::iterator it;
    vector<Book>::iterator position;
    string bookId;
    bool findBook = false;
    vector<Patron>::iterator pt;
    bool findPatron = false;
    string pId;
    Book book;
    Patron *patron;
    int bookPos;
    
    for(int i = 0; i < holdings.size(); ++i){
        if (bookID == holdings[i].getIdCode() && holdings[i].getLocation() == CHECKED_OUT) {
            findBook = true;
            bookPos = i;
            patron = holdings[i].getCheckedOutBy();
            for (int j = 0; j< members.size(); ++j) {
                if(members[j].getIdNum() == holdings[i].getCheckedOutBy()->getIdNum()){
                    findPatron = true;
                    holdings[i].setCheckedOutBy(NULL);
                    holdings[i].setDateCheckedOut(NULL);
                    holdings[i].setLocation(ON_SHELF);
                    members[j].removeBook(&holdings[i]);
                    return;
                }
            }
            if(findPatron == false){
                cout << "Patron is not registered in this library." << endl;
                return;
            }
        }else if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() != CHECKED_OUT){
            findBook = true;
            cout << "This book is not checked out." << endl;
            return;

        }
    }
    
     if(findBook == false){
        cout << "The book is not found." << endl;
        return;
    }

    
}

void Library::requestBook(string patronID, string bookID)
{
    vector<Book>::iterator it;
    vector<Book>::iterator position;
    string bookId;
    bool findBook = false;
    vector<Patron>::iterator pt;
    bool findPatron = false;
    string pId;
    Book book;
    Patron patron;
    int patronPos;
    
    for(int i = 0; i < members.size(); ++i){
        if(patronID == members[i].getIdNum()){
            findPatron = true;
            patronPos = i;
            break;
            
        }
    }
    if(findPatron == false){
        cout << "Patron is not registered in this library." << endl;
        return;
    }
    for(int i = 0; i < holdings.size(); ++i){
        if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_SHELF){
            findBook = true;
            holdings[i].setRequestedBy(&members[patronPos]);
            holdings[i].setLocation(ON_HOLD_SHELF);
            cout << "The book is requested by the Patron: " << patron.getName() << endl;
            return;

            
        }
        else if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_HOLD_SHELF){
            findBook = true;
            cout << "This book is already requested by other people." << endl;
            return;
        }
        else if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == CHECKED_OUT){
            findBook = true;
            if(holdings[i].getCheckedOutBy() == &members[patronPos]){
                
                cout << "You already checked out this book." << endl;
                return;

            }else{
                cout << "the book is not available." << endl;
                return;
            }
        }else{
            cout << "Book not found." << endl;
            return;
        }
        
    }

   
}

void Library::incrementCurrentDate()
{
    vector<Patron>::iterator it;
    vector<Patron>::iterator start;
    vector<Patron>::iterator end;
    string id;
    Book book;
    vector<Book *> listOfCheckedOut;
    vector<Book*>::iterator bIt;
    int checkedOutDate;
    int checkedOutDays;
    
    
    start = members.begin();
    end = members.end();
    currentDate++;
    
    for(int i = 0; i < members.size(); ++i){
        listOfCheckedOut = members[i].getCheckedOutBooks();
        for (int j = 0; j < listOfCheckedOut.size(); ++j) {
            checkedOutDate = listOfCheckedOut[j]->getDateCheckedOut();
            checkedOutDays = currentDate - checkedOutDate;
            if(checkedOutDays > listOfCheckedOut[j]->CHECK_OUT_LENGTH){
                members[i].amendFine(0.1);
            }
        }
        
    }
    
   
}

void Library::payFine(string patronID, double payment)
{
    vector<Patron>::iterator it;
    vector<Patron>::iterator start;
    vector<Patron>::iterator end;
    string id;
    bool findPatron = false;
    
    start = members.begin();
    end = members.end();
    
    for(int i = 0; i < members.size(); ++i){
        if(patronID == members[i].getIdNum()){
            findPatron = true;
            members[i].amendFine(-payment);
            cout << "The patron: " << members[i].getName() << "new fine amount is: " << members[i].getFineAmount() << endl;
            break;
        }
    }
    
    
    
    if(findPatron == false){
        cout << "Patron is not registered in this library." << endl;
        return;
    }

 
}

void Library::viewPatronInfo(string patronID)
{
    cout << "viewPatronInfo: " << endl;
    cout << "number of patrons: " << members.size() << endl;
    
    vector<Patron>::iterator it;
    vector<Patron>::iterator start;
    vector<Patron>::iterator end;
    string id;
    bool find = false;
    vector<Book*> listOfChckedOut;
    vector<Book*>::iterator bIt;
    
    
    start = members.begin();
    end = members.end();
    
    for(int i = 0; i < members.size(); ++i){
        if (patronID == members[i].getIdNum()) {
            listOfChckedOut = members[i].getCheckedOutBooks();
            cout << "Patron name: " << members[i].getName() << endl;
            cout << "Patron ID: " << members[i].getIdNum() << endl;
            cout << "List of checked out books: " << endl;
            for (int j = 0; j < listOfChckedOut.size(); ++j) {
                cout << "Book title: " << listOfChckedOut[j]->getTitle() << endl;
            }
            cout << "Library fine: " << members[i].getFineAmount() << endl;
            find = true;
            

        }
    }
    if(!find){
        cout << "The patron is not registered in this labrary." << endl;
        return;
    }
    
}

void Library::viewBookInfo(string bookID)
{
 
    vector<Book>::iterator it;
    vector<Book>::iterator start;
    vector<Book>::iterator end;
    start = holdings.begin();
    end = holdings.end();
    string id;
    Patron *patron;
    bool find = false;
    int dateOfCheckOut;
    int daysOfCheckedOut;
    
    

    for(int i = 0; i < holdings.size(); ++i){
        if(bookID == holdings[i].getIdCode()){
            find = true;
            cout << "bookId: " << holdings[i].getIdCode() << endl;
            cout << "author: " << holdings[i].getAuthor()<< endl;
            cout << "title: " << holdings[i].getTitle() << endl;
            cout << "location: " << holdings[i].getLocation() << endl;
            if (holdings[i].getLocation() == ON_HOLD_SHELF) {
                patron = holdings[i].getRequestedBy();
                cout <<"Patron: " << patron->getName() << " has requested this book." << endl;
                
                
            }else if(holdings[i].getLocation() == CHECKED_OUT){
                patron = holdings[i].getCheckedOutBy();
                cout <<"Patron: " << patron->getName() << "has checked out this book." << endl;
                dateOfCheckOut = holdings[i].getDateCheckedOut();
                daysOfCheckedOut = currentDate - dateOfCheckOut;
                int daysLeft = holdings[i].CHECK_OUT_LENGTH - daysOfCheckedOut;
                (daysLeft >=0)?(cout << "there is " << daysLeft << " due." << endl):(cout << "It is over due by " << -daysLeft << endl);
                

            
        }
    }
        if(find == false){
        
        cout << "There is no this book in the library." << endl;
        return;
    }
    
}


    
}