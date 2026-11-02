#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    double price;
    int quantity;
};

// Order structure
struct Order {
    string customerName;
    vector<Book> books;
};

// User structure
struct User {
    string username;
    string password;
};

bool exitProgram = false;

// Function prototypes
void displayMenu();
void manageAdmin(vector<Book>& books, vector<Order>& orders);
void manageCustomer(vector<Order>& orders, vector<Book>& books);
void registerUser(vector<User>& users);
bool loginUser(vector<User>& users);
void logoutUser();
void addBook(vector<Book>& books);
void saveBookDetails(const vector<Book>& books);
void viewBook(vector<Book>& books);
void loadBookDetails(vector<Book>& books);
void saveBookDetails(const vector<Book>& books);
void viewBookOrders(const vector<Order>& orders);
double calculateTotalPrice(const Order& order, int& discountPercentage);
void addQuotations(vector<Book>& books, vector<Order>& orders );
void printQuotation(const Order& order, int discountPercentage);
void clearConsole();
void exitProgramFunction();


int main() {
    vector<Book> books;
    vector<Order> orders;
    vector<User> users;

    ifstream usersFileIn("users.txt");
    string username, password;
    if (usersFileIn.is_open()) {
       while (usersFileIn >> username >> password) {
           users.push_back({username, password});
    }
           usersFileIn.close();
    } else {
    cerr << "Unable to open users.txt for reading." << endl;
    }

    int loginSelection;
    cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t   **    * ****** ******* **    * *****      **         "<<endl;
	cout<<"\t\t\t   ***   * **        *    **    * **   *    ** *        "<<endl;
	cout<<"\t\t\t   ** *  * *****     *    ******* *****    ******       "<<endl;
	cout<<"\t\t\t   **  * * **        *    **    * ** *    **     *      "<<endl;
	cout<<"\t\t\t   **    * ******    *    **    * **   * **       *     "<<endl;
    cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                    BOOK SHOP                           "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t    ----- Welcome to Nethra Bookshop -----              "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                                                        "<<endl;
	cout<<"\t\t\t                                                        "<<endl;


    do {
        cout << "           1. Login       " << endl;
        cout << "                          " << endl;
        cout << "           2. Register    " << endl;
        cout << "                          " << endl;
        cout << "           Enter your selection: ";
        cin >> loginSelection;

        if (loginSelection == 1) {
            clearConsole();
            if (!loginUser(users)) {
                main();

            }
        } else if (loginSelection == 2) {
            clearConsole();
            registerUser(users);
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (loginSelection != 1); // user login
    int selection;
    do {
        //clearConsole();
        displayMenu();  // admin status
        cout << " Selecte a item: ";
        cin >> selection;

        switch (selection) {
            case 1:
                clearConsole();
                manageAdmin(books, orders);
                break;
            case 2:
                clearConsole();
                manageCustomer(orders, books);
                break;
            case 3:
                clearConsole();
                cout << " Thank You. Good Bye!"   << endl;
                return 0;
                break;
            default:
                cout << "  Invalid selection. Please try again." << endl;
        }
    } while (selection != 3);

    return 0;
}

// ... (rest of the functions remain the same)

bool loginUser(vector<User>& users) {
    string username, password;
    cout << "\n **** User Login ****\n" <<endl;
    cout << "                         " <<endl;
    cout << "  Enter username: ";
    cin >> username;
    cout << "                         " <<endl;
    cout << "  Enter password: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            if (username.find("admin") == 0) {
                cout << "\n  Admin login successful. Welcome, " << username << "!" << endl;
            } else {
                cout << "\n  Login successful. Welcome, " << username << "!"       << endl;
            }
            return true;
        }
    }

    cout << "\n  Login failed. Invalid username or password." << endl;
    return false;
}

void registerUser(vector<User>& users) {
    string username, password;
    cout << "\n **** User Registration ****\n" << endl;
    cout << "                               "   <<endl;
    cout << "\n  Enter desired username: ";
    cin >> username;

    // Check if the username is already taken
    for (const auto& user : users) {
        if (user.username == username) {
            cout << "\n  Username already taken. Please choose a different one." << endl;
            return;
        }
    }

    cout << "\n  Enter password: ";
    cin >> password;

    // Add new user
    users.push_back({username, password});
    cout << "\n  Registration successful. Welcome, " << username << "!" << endl;

    ofstream usersFileOut("users.txt");
    if (usersFileOut.is_open()) {
        for (const auto& user : users) {
            usersFileOut << user.username << " " << user.password << endl;
        }
        usersFileOut.close();
    } else {
        cerr << "\n  Unable to open users.txt for writing." << endl;
    }
}

void logoutUser() {
    cout << "\n  Logout successful." << endl;
}

void displayMenu() {
    cout << " Choose your position. \n"<<endl;
    cout << "                        " <<endl;
    cout << " 1. Admin               " <<endl;
    cout << "                        " <<endl;
    cout << " 2. Customer            " <<endl;
    cout << "                        " <<endl;
    cout << " 3. Exit                " <<endl;
    cout << "                        " <<endl;
}

void addBook(vector<Book>& books) {
    Book newBook;
    cout << "\n ____Add Book____ \n" << endl;
    cout << "  Enter title: ";
    cin.ignore();
    getline(cin, newBook.title);

    // Check book availability
    auto existingBook = find_if(books.begin(), books.end(),
            [&newBook](const Book& existing) {
                    return existing.title == newBook.title;
            });
    if (existingBook != books.end()) {
            cout << "  Book is already exists. Cannot add the same book again.\n" << endl;
    } else {
            cout << "  Enter author: ";
            getline(cin, newBook.author);
            cout << "  Enter price: Rs.";
            cin >> newBook.price;

            books.push_back(newBook);
            cout << "\n  Book added successfully!" << endl;

            ofstream outFile("bookdetails.txt");
            if (outFile.is_open()) {
                for (const auto& book : books) {
                        outFile << book.title << "\n"
                        << book.author << "\n"
                        << book.price << endl;
                }
                outFile.close();
                cout << "\n  Book details saved to bookdetails.txt  " << endl;
            } else {
                cerr << "Unable to open bookdetails.txt for writing." << endl;
            }
        }
}

void loadBookDetails(vector<Book>& books) {
    ifstream inFile("bookdetails.txt");
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            Book book;
            getline(inFile, book.title);
            getline(inFile, book.author);
            inFile >> book.price;
            books.push_back(book);
        }
        inFile.close();
        cout << "\n  Book details loaded from bookdetails.txt " << endl;
    } else {
        cerr << "  Unable to open bookdetails.txt for reading." << endl;
    }
}

void viewBook(vector<Book>& books) {
    cout << "\n ____View Books____\n" << endl;
    for (const auto& book : books) {
            cout << "Title: " << book.title      << endl;
            cout << "\tAuthor: " << book.author  << endl;
            cout << "\tPrice: Rs." << book.price << endl;
    }
}

void searchBook(vector<Book>& books) {
    string searchBook;
    cout << "\n ____Search Books____\n" << endl;
    cout << "  Enter search book: ";
    cin.ignore();
    getline(cin, searchBook);

    cout << "\n  Search results:" << endl;
    for (const auto& book : books) {
        if (book.title.find(searchBook) != string::npos || book.author.find(searchBook) != string::npos) {
            cout << "Title: " << book.title    <<endl;
            cout << "\tAuthor: " << book.author <<endl;
            cout << "\tPrice: Rs." << book.price << endl;
        }
    }
}

void saveBookDetails(const vector<Book>& books) {
    ofstream outFile("bookdetails.txt");
    if (outFile.is_open()) {
        for (const auto& book : books) {
            outFile << book.title << "\n" << book.author << "\n" << book.price << endl;
        }
        outFile.close();
        cout << "\n  Book details saved to bookdetails.txt   " << endl;
    } else {
        cerr << " Unable to open bookdetails.txt for writing." << endl;
    }
}


void viewBookOrders(const vector<Order>& orders) {
    ifstream orderFileIn("order.txt");
    if (orderFileIn.is_open()) {
        string line;
        cout << "\n ____View Book Orders____" << endl;

        while (getline(orderFileIn, line)) {
            cout << line << endl;
        }

        orderFileIn.close();
    } else {
        cerr << "  Unable to open order.txt for reading." << endl;
    }
}

void addQuotations(vector<Book>& books, vector<Order>& orders ) {
       Order newOrder;
       cout << "\n ____Prepare Quotations____\n" << endl;
       cout << "  Enter customer name: ";
       cin.ignore();
       getline(cin, newOrder.customerName);

       int bookChoice;
       int totalPrice1 = 0;
   do {
       // Display available books
       cout << "\n  Select a book to add to the order (0 to finish):" << endl;
       for (size_t i = 0; i < books.size(); ++i) {
           cout << i + 1 << ". " << books[i].title << " by " << books[i].author << "\tPrice: Rs." << books[i].price << endl;
       }
       cin >> bookChoice;

       if (bookChoice > 0 && bookChoice <= static_cast<int>(books.size())) {
           int quantity;
           cout << "\n  Enter quantity for the selected book: ";
           cin >> quantity;

           if (quantity > 0) {

               books[bookChoice - 1].quantity = quantity;

               // Add the book with quantity to the order
               newOrder.books.push_back(books[bookChoice - 1]);
               cout << "\n  Book added to the order." << endl;
           } else {
               cout << "\n  Invalid quantity. Please enter a quantity greater than 0." << endl;
           }
       } else if (bookChoice != 0) {
           cout << "\n  Invalid choice. Please try again." << endl;
       }
   } while (bookChoice != 0);

   orders.push_back(newOrder);
   cout << "\n  Quotations prepared successfully!" << endl;

   // Display added item quantities
   cout << "\n  Added Item Quantities:" << endl;
   for (const auto& book : newOrder.books) {
           cout << "Title: " << book.title
                << "\tAuthor: " << book.author << "\tPrice: Rs." << book.price
                << "\tQuantity: " << book.quantity << endl;
           totalPrice1 += book.price * book.quantity;
   }

   int discountPercentage = 0;
   double discountedPrice = calculateTotalPrice(newOrder, discountPercentage);

   cout << "\n  Total Price before Discount: Rs." << totalPrice1   << endl;
   cout << "  Discount Percentage: " << discountPercentage << "%"  << endl;
   cout << "  Discount total Price: Rs." << discountedPrice        << endl;

   // Save order details to "order.txt"
   ofstream orderFileOut("order.txt", ios::app);
   if (orderFileOut.is_open()) {
       orderFileOut << "Customer: " << newOrder.customerName << endl;
       orderFileOut << "Added Item Quantities:"              << endl;
       for (const auto& book : newOrder.books) {
               orderFileOut << "Title: " << book.title
                            << "\tAuthor: " << book.author
                            << "\tPrice: Rs." << book.price
                            << "\tQuantity: " << book.quantity << endl;
       }
       orderFileOut << "Total Price before Discount: Rs." << totalPrice1    << endl;
       orderFileOut << "Discount Percentage: " << discountPercentage << "%" << endl;
       orderFileOut << "Discounted Price: Rs." << discountedPrice           << endl;
       orderFileOut.close();
       cout << "\n  Order details saved to order.txt" << endl;
   } else {
       cerr << "  Unable to open order.txt for writing." << endl;
   }
}

void printQuotation(const Order& order, int discountPercentage) {

    cout << "\n ----Quotation----\n" << endl;
    cout << "Customer: " << order.customerName << endl;

    // Display added item quantities with discount
    cout << "\nAdded Item Quantities:\n" << endl;
    for (const auto& book : order.books) {
        cout<< " * Title: " << book.title << endl;
        cout<< " * Author: " << book.author << endl;
        cout<< " * Price: Rs." << book.price << endl;
        cout<< " * Quantity: " << book.quantity << "\tPrice: Rs." << book.price*(1.0 - discountPercentage / 100.0)*book.quantity <<endl;
}
     double totalPrice = calculateTotalPrice(order, discountPercentage);

    cout << " \n * Discount Percentage: " << discountPercentage << "%" << endl;
    cout << " * Discounted Price: Rs." << totalPrice                  << endl;
}

void manageAdmin(vector<Book>& books, vector<Order>& orders )
{
    loadBookDetails(books);
    int selection;
    do {
        cout << "\n ----Manage Books----\n"     << endl;
        cout << "                             " << endl;
        cout << "  1. View Books"               << endl;
        cout << "  2. Add Book"                 << endl;
        cout << "  3. Search Books"             << endl;
        cout << "                             " << endl;
        cout << "\n ----Manage Orders----\n"    << endl;
        cout << "                             " << endl;
        cout << "  4. View Book Quotations"     << endl;
        cout << "  5. Add Quotations"           << endl;
        cout << "  6. Print Quotations"         << endl;
        cout << "  7. Logout"                   << endl;
        cout << "  8. Exit"                    << endl;
        cout << "                             " << endl;
        cout << "  Enter your selection: ";
        cin >> selection;

        switch (selection) {
            case 1:
                clearConsole();
                viewBook(books);
                break;
            case 2:
                clearConsole();
                addBook(books);
                break;
             case 3:
                clearConsole();
                searchBook(books);
                break;
            case 4:
                clearConsole();
                viewBookOrders(orders);
                break;
            case 5:
                clearConsole();
                addQuotations(books, orders );
                break;

             case 6:
             {clearConsole();
            // Check if there are any orders
            if (!orders.empty()) {
            int orderSelection;
            cout << "  Select an order to print quotation:" << endl;
            for (size_t i = 0; i < orders.size(); ++i) {
            cout << i + 1 << ". Order for " << orders[i].customerName << endl;
                        }
            cin >> orderSelection;
            if (orderSelection > 0 && orderSelection <= static_cast<int>(orders.size()))
                            {
            int discountPercentage = 0;  // Initialize discount
            printQuotation(orders[orderSelection - 1], discountPercentage);
                          } else {
            cout << "  Invalid order selection. Please try again." << endl;
                          }
                     } else {
            cout << "  No orders available to print quotations." << endl;
                     }
                     break;
                }
            case 9:
                clearConsole();
                cout << "\n  User logout. Need to login again." << endl;
                main();
                break;
            case 10:
                clearConsole();
                exitProgramFunction();
                break;
            default:
                clearConsole();
                cout << "\n  Invalid selection. Please try again." << endl;
        }
    } while (selection != 10);

}
void manageCustomer(vector<Order>& orders, vector<Book>& books) {
    loadBookDetails(books);
    int selection;
    do {
        cout << "\n ----Book Details----     \n" <<endl;
        cout << "                              " <<endl;
        cout << "  1. View Books               " <<endl;
        cout << "  2. Search Books             " <<endl;
        cout << "                              " <<endl;
        cout << "\n ----Order Books----      \n" <<endl;
        cout << "                              " <<endl;
        cout << "  3. Add quotations           " <<endl;
        cout << "  4. Print Quotations         " <<endl;
        cout << "  5. Logout                   " <<endl;
        cout << "  6. Exit                     " <<endl;
        cout << "                              " <<endl;
        cout << "  Enter your selection: ";
        cin >> selection;

        switch (selection) {
            case 1:
                clearConsole();
                viewBook(books);
                break;
             case 2:
                clearConsole();
                searchBook(books);
                break;
            case 3:
                clearConsole();
                addQuotations(books, orders );
                break;
            case 4:
                 {clearConsole();
                // Check if there are any orders
                if (!orders.empty()) {
                int orderSelection;
                cout << "  Select an order to print quotation:" << endl;
                for (size_t i = 0; i < orders.size(); ++i) {
                cout << i + 1 << ". Order for " << orders[i].customerName << endl;
                          }
                cin >> orderSelection;

                if (orderSelection > 0 && orderSelection <= static_cast<int>(orders.size())) {
                int discountPercentage = 0;  // Initialize discount
                printQuotation(orders[orderSelection - 1], discountPercentage);
                } else {
                cout << "  Invalid order choice. Please try again." << endl;
                    }
                } else {
                cout << "  No orders available to print quotations." << endl;
                     }
                     break;
                }
            case 5:
                clearConsole();
                cout << "\n  User logout. Need to login again." << endl;
                main();
                break;
            case 6:
                clearConsole();
                exitProgramFunction();
                break;
            default:
                clearConsole();
                cout <<""<<selection<<"  Invalid selection. Please try again." << endl;
        }
    } while (selection != 6);
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exitProgramFunction() {
    exitProgram = true;
    cout << "\n  Thank You. Good Bye!" << endl;
}


double calculateTotalPrice(const Order& order, int& discountPercentage) {
    double totalPrice = 0.0;

    for (const auto& book : order.books) {
        totalPrice += book.price * book.quantity;

    }

    // Apply discount based on the total quantity of books
    int totalQuantity = 0;
    for (const auto& book : order.books) {
        totalQuantity += book.quantity;
    }

    if (totalQuantity >= 1 && totalQuantity < 5) {
        // Apply a 5% discount for quantity less than 5
        discountPercentage = 10;
        totalPrice *= 0.9;
    } else if (totalQuantity >= 5) {
        // Apply a 10% discount for quantity 5 or more
        discountPercentage = 15;
        totalPrice *= 0.85;
    } else {
        discountPercentage = 0;
    }

    return totalPrice;
}
