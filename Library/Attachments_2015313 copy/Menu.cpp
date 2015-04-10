/***********************************************
 * Menu.cpp
 * Created by you sheng chang
 ************************************************/

#include <iostream>
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"
using namespace std;

int main()
{
    
    int selection = 0;
    Library library;
    string bookId;
    string patronId;
    double payment;
    
    
    do
    {
        cout << "Select an option from the list below (1 - 10): " << endl;
        cout << "1) Add book" << endl;
        cout << "2) Add member" << endl;
        cout << "3) Check out book" << endl;
        cout << "4) Return book" << endl;
        cout << "5) Request book" << endl;
        cout << "6) Pay fine" << endl;
        cout << "7) Increment current date" << endl;
        cout << "8) View patron info" << endl;
        cout << "9) View book info" << endl;
        cout << "10) Quit" << endl;
        cin >> selection;
    
        switch (selection)
        {
            case 1:
                cin.get();
                library.addBook();
                break;
                
            case 2:
                
                cin.get();
                library.addMember();
                break;
           
            case 3:
                
                cin.get();
                cout<<"Input your patronID: "<<endl;
                cin >> patronId;
                cout <<"Input the bookId: " << endl;
                cin >> bookId;
                library.checkOutBook(patronId, bookId);
                break;
            
            case 4:
                cin.get();
                cout <<"Input bookId: " << endl;
                cin >> bookId;
                library.returnBook(bookId);
                break;
            
            case 5:
                cin.get();
                cout << "Input your patronID: " << endl;
                cin >> patronId;
                cout << "Input the bookID: " << endl;
                cin >> bookId;
                library.requestBook(patronId, bookId);
                break;
            
            case 6:
                cin.get();
                cout<<"Input your patronID: "<<endl;
                cin >> patronId;
                cout <<"Input your pay fine amount: " << endl;
                cin >> payment;
                library.payFine(patronId, payment);
                break;
            
            case 7:
                library.incrementCurrentDate();
                break;
            
            case 8:
                cin.get();
                cout << "input the patron id: " << endl;
                cin >> patronId;
                library.viewPatronInfo(patronId);
                break;
            
            case 9:
                
                cin.get();
                cout << "Input the book id: "<< endl;
                cin >> bookId;
                library.viewBookInfo(bookId);
                
                break;
            
                
        }
    
        
    }while (selection != 10);
    


    return 0;
}

