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
    for(int i = 0; i < (int)(holdings.size()); ++i){
        cout << holdings[i].getAuthor() << endl;
        cout << holdings[i].getTitle() << endl;
        cout << holdings[i].getIdCode() << endl;
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
    cout << "Input the patron's id: " << endl;
    cin.getline(buf, sizeof(buf));
    idNum = buf;
    cout << "name: " << name << " id: " << idNum << endl;
    Patron *patron = new Patron(idNum, name);
    members.push_back(*patron);
    
    cout << "The library has members: " << endl;
    for(int i = 0; i < (int)(members.size()); ++i){
        cout << members[i].getName() << endl;
        cout << &members[i] << endl;
    }
    
}

void Library::checkOutBook(string patronID, string bookID)
{


    bool findBook = false;
    bool findPatron = false;
    int memberPos = 0;

    cout << "Input patronID: " << patronID << " bookID: " << bookID << endl;
    
    for(int i = 0; (int)(members.size()); ++i){
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

    for(int i = 0; i < (int)(holdings.size()); ++i){
        if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_SHELF){
            findBook = true;

            holdings[i].setCheckedOutBy(&members[memberPos]);
            holdings[i].setDateCheckedOut(currentDate);
            holdings[i].setLocation(CHECKED_OUT);
            members[memberPos].addBook(&holdings[i]);
            
        }
        else if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_HOLD_SHELF){
            if (holdings[i].getRequestedBy() == &members[memberPos]) {
                findBook = true;

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


    bool findBook = false;
    bool findPatron = false;
    

    for(int i = 0; i < (int)(holdings.size()); ++i){
        if (bookID == holdings[i].getIdCode() && holdings[i].getLocation() == CHECKED_OUT) {
            findBook = true;


            for (int j = 0; j< (int)(members.size()); ++j) {
                if(members[j].getIdNum() == holdings[i].getCheckedOutBy()->getIdNum()){
                    findPatron = true;
                    holdings[i].setCheckedOutBy(NULL);
                    holdings[i].setDateCheckedOut(0);
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
    bool findBook = false;
    bool findPatron = false;
    int patronPos = 0;
    
    for(int i = 0; i < (int)(members.size()); ++i){
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
    for(int i = 0; i < (int)(holdings.size()); ++i){
        if(bookID == holdings[i].getIdCode() && holdings[i].getLocation() == ON_SHELF){
            findBook = true;
            holdings[i].setRequestedBy(&members[patronPos]);
            holdings[i].setLocation(ON_HOLD_SHELF);
            cout << "The book is requested by the Patron: " << members[patronPos].getName() << endl;
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
        }
        
    }

    if(findBook == false)
        cout << "Book not found." << endl;

}

void Library::incrementCurrentDate()
{


    vector<Book *> listOfCheckedOut;
    int checkedOutDate;
    int checkedOutDays;
    
    

    currentDate++;
    
    for(int i = 0; i < (int)members.size(); ++i){
        listOfCheckedOut = members[i].getCheckedOutBooks();
        for (int j = 0; j < (int)(listOfCheckedOut.size()); ++j) {
            checkedOutDate = listOfCheckedOut[j]->getDateCheckedOut();
            checkedOutDays = currentDate - checkedOutDate;
            if(checkedOutDays > Book::CHECK_OUT_LENGTH){
                members[i].amendFine(0.1);
            }
        }
        
    }
    
   
}

void Library::payFine(string patronID, double payment)
{


    bool findPatron = false;
    for(int i = 0; i < (int)(members.size()); ++i){
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

    bool find = false;
    vector<Book*> listOfChckedOut;
    
    
    for(int i = 0; i < (int)(members.size()); ++i){
        if (patronID == members[i].getIdNum()) {
            listOfChckedOut = members[i].getCheckedOutBooks();
            cout << "Patron name: " << members[i].getName() << endl;
            cout << "Patron ID: " << members[i].getIdNum() << endl;
            cout << "List of checked out books: " << endl;
            for (int j = 0; j < (int)(listOfChckedOut.size()); ++j) {
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

    Patron *patron;
    bool find = false;
    int dateOfCheckOut;
    int daysOfCheckedOut;
    
    

    for(int i = 0; i < (int)(holdings.size()); ++i){
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
                int daysLeft = Book::CHECK_OUT_LENGTH - daysOfCheckedOut;
                (daysLeft >=0)?(cout << "there is " << daysLeft << " due." << endl):(cout << "It is over due by " << -daysLeft << endl);
                

            
        }
    }

}
    if(find == false){

            cout << "There is no this book in the library." << endl;
            return;
    }
    

    
}
