// ap12.11.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Book {
    string udc;
    string author;
    string title;
    int year;
    int quantity;
};
struct Elem {
    Elem* next;
    Elem* prev;
    Book book;
};

void initializeLibrary(Elem*& head);
void addBook(Elem*& head);
void removeBook(Elem*& head);
void printLibrary(Elem* head);
void saveLibraryToFile(Elem* head, const string& filename);
void loadLibraryFromFile(Elem*& head, const string& filename);
void menu(Elem*& head);

void initializeLibrary(Elem*& head) {
    head = nullptr;
}

void addBook(Elem*& head) {
    // Запит користувача на введення даних про нову книгу
    Book newBook;
    cout << "Enter the details of the book:" << endl;
    cout << "UDC: ";
    getline(cin, newBook.udc);
    cout << "Author: ";
    getline(cin, newBook.author);
    cout << "Title: ";
    getline(cin, newBook.title);
    cout << "Year: ";
    cin >> newBook.year;
    cout << "Quantity: ";
    cin >> newBook.quantity;
    cin.ignore(); // Ігноруємо символ нового рядка в буфері введення

    // Створення нового елементу списку
    Elem* newElem = new Elem;
    newElem->book = newBook;
    newElem->next = nullptr;

    // Додавання елементу до списку
    if (head == nullptr) {
        newElem->prev = nullptr;
        head = newElem;
    }
    else {
        Elem* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newElem;
        newElem->prev = current;
    }

    cout << "Book added to the library." << endl;
}

void removeBook(Elem*& head) {
    // Запит користувача на введення номера УДК книги, яку потрібно видалити
    string udc;
    cout << "Enter the UDC of the book to remove: ";
    cin.ignore(); // Ігноруємо символ нового рядка в буфері введення
    getline(cin, udc);

    // Пошук книги за номером УДК та видалення її зі списку
    Elem* current = head;
    bool bookFound = false;

    while (current != nullptr) {
        if (current->book.udc == udc) {
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            }
            else {
                current->prev->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
            }

            delete current;
            cout << "Book removed from the library." << endl;
            bookFound = true;
            break;
        }

        current = current->next;
    }

    if (!bookFound) {
        cout << "Book with the UDC " << udc << " not found in the library." << endl;
    }
}

void printLibrary(Elem* head) {
    // Сортування книг за роком видання
    Elem* current = head;
    while (current != nullptr) {
        Elem* minElem = current;
        Elem* temp = current->next;

        while (temp != nullptr) {
            if (temp->book.year < minElem->book.year) {
                minElem = temp;
            }
            temp = temp->next;
        }

        // Обмін місцями поточного елемента з мінімальним
        if (current != minElem) {
            Book tempBook = current->book;
            current->book = minElem->book;
            minElem->book = tempBook;
        }

        current = current->next;
    }

    // Виведення інформації про книги
    current = head;
    while (current != nullptr) {
        cout << "UDC: " << current->book.udc << endl;
        cout << "Author: " << current->book.author << endl;
        cout << "Title: " << current->book.title << endl;
        cout << "Year: " << current->book.year << endl;
        cout << "Quantity: " << current->book.quantity << endl;
        cout << "-------------------------------" << endl;
        current = current->next;
    }
}

void saveLibraryToFile(Elem* head, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        Elem* current = head;
        while (current != nullptr) {
            file << current->book.udc << endl;
            file << current->book.author << endl;
            file << current->book.title << endl;
            file << current->book.year << endl;
            file << current->book.quantity << endl;
            current = current->next;
        }

        file.close();
        cout << "Library data saved to file: " << filename << endl;
    }
    else {
        cout << "Unable to open the file: " << filename << endl;
    }
}

void loadLibraryFromFile(Elem*& head, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        initializeLibrary(head);

        string udc;
        string author;
        string title;
        int year;
        int quantity;

        while (getline(file, udc) && getline(file, author) && getline(file, title) && file >> year >> quantity) {
            file.ignore(); // Ігноруємо символ нового рядка в буфері введення

            // Створення нового елементу списку
            Elem* newElem = new Elem;
            newElem->book.udc = udc;
            newElem->book.author = author;
            newElem->book.title = title;
            newElem->book.year = year;
            newElem->book.quantity = quantity;
            newElem->next = nullptr;

            // Додавання елементу до списку
            if (head == nullptr) {
                newElem->prev = nullptr;
                head = newElem;
            }
            else {
                Elem* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newElem;
                newElem->prev = current;
            }
        }

        file.close();
        cout << "Library data loaded from file: " << filename << endl;
    }
    else {
        cout << "Unable to open the file: " << filename << endl;
    }
}
  void menu(Elem*& head) {
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "------- Library Menu -------" << endl;
        cout << "1. Initialize Library" << endl;
        cout << "2. Add Book" << endl;
        cout << "3. Remove Book" << endl;
        cout << "4. Print Library" << endl;
        cout << "5. Save Library to File" << endl;
        cout << "6. Load Library from File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Ігноруємо символ нового рядка в буфері введення

        string saveFilename;
        string loadFilename;
        switch (choice) {
        case 1:
            initializeLibrary(head);
            cout << "Library initialized." << endl;
            break;
        case 2:
            addBook(head);
            break;
        case 3:
            removeBook(head);
            break;
        case 4:
            printLibrary(head);
            break;
        case 5:
            cout << "Enter the filename to save the library: ";
            getline(cin, saveFilename);
            saveLibraryToFile(head, saveFilename);
            break;
        case 6:
            cout << "Enter the filename to load the library: ";
            getline(cin, loadFilename);
            loadLibraryFromFile(head, loadFilename);
            break;
        case 7:
            exitMenu = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << endl;
    }
}

int main() {
    Elem* head = nullptr;
    menu(head);
    return 0;
}