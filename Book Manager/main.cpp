
#include <iostream>  //  displays messages and get user input.
#include <fstream>   // Allows us to read and write files.
#include <string>    // Allows us to store text.
#include <vector>    // Allows us to store multiple books.
#include <sstream>   // Helps us separate information using commas.
#include <iomanip>   // Helps us display books in organised columns.
#include <limits>    // Helps us handle incorrect number inputs.

using namespace std;

// AI acknowledgement:
// Tool used : OpenAI ChatGPT (https://chatgpt.com)
// Prompt: "How do i adapt my code to asign a location, shelf and isle to a book.
// Help me formulate my explinary comments."

// Create a structure to store information about each book.
struct Book {
    string title;       // This contains the name of the book.
    string author;      // This contains the name of the author.
    int pages;          // This is the page number.
    string id;          // This asigns a unique book id.. like 001, 005
    bool available;     // True = in stock, false = out of stock.
};

// Create a list that will hold all books.
vector<Book> books;

// Name of the file containing the book information.
const string filename = "bookData.txt";

// Read all books from the text file.
void loadBooks() {

    // This opens the file to read the book information and details.
    ifstream file(filename);

    // Checks if the files open correcntly
    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt!" << endl;
        return;
    }

    // Clear the list before loading the books.
    books.clear();

    // Save each line read from the file.
    string line;

    // Read the file one line at a time.
    while (getline(file, line)) {

        // Skip empty lines.
        if (line.empty()) {
            continue;
        }

        // This separates the book details from each line.
        stringstream ss(line);

        // Create a new book to store it`s details
        Book book;

        // Store the details as text before changing them
        string pagesText;
        string availableText;

        // This reads each book`s details and separates them by commas 
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, pagesText, ',');
        getline(ss, book.id, ',');
        getline(ss, availableText, ',');

        // This will convert the page number from text to an integer.
        try {
            book.pages = stoi(pagesText);
        } catch (...) {
            // Extra step to skip the book of the page number doesnt exist.
            continue;
        }

        // Convert the availability text into a true or false value.
        book.available = (availableText == "true");

        // If the user returns a book, this adds the book to our list.
        books.push_back(book);
    }

    // Close the file after reading all books.
    file.close();
}

// updates the new book information back to the file. if a book has been borrowed or returned.
bool saveBooks() {

    // Opens my file to write the updated information.
    ofstream file(filename);

    // This will check if the file opened correctly.
    if (!file.is_open()) {
        cout << "Error: Could not save bookData.txt!" << endl;
        return false;
    }

    // Go through each book in the list.
    for (const Book& book : books) {

        // Save the book information separated by commas.
        file << book.title << ","
             << book.author << ","
             << book.pages << ","
             << book.id << ","
             << (book.available ? "true" : "false")
             << endl;
    }

    // Closes the file and checks if the writing was completed correctly.
    file.close();

    if (file.fail()) {
        cout << "Error: Could not finish saving the books!" << endl;
        return false;
    }

    return true;
}

// Displayw every book in the library
void displayBooks() {

    cout << "\n================ LIBRARY BOOK LIST ================\n";

    // Display the column headings.
    cout << left
         << setw(6) << "ID"
         << setw(28) << "TITLE"
         << setw(24) << "AUTHOR"
         << setw(10) << "PAGES"
         << "STATUS" << endl;

    cout << string(82, '-') << endl;

    // outputs all the information for each book
    for (const Book& book : books) {

        cout << left
             << setw(6) << book.id
             << setw(28) << book.title
             << setw(24) << book.author
             << setw(10) << book.pages
             << (book.available ? "In Stock" : "Out of Stock")
             << endl;
    }
}

// This helps find the book using it`s id.
Book* findBook(string id) {

    // Check each book until we find a matching ID.
    for (Book& book : books) {

        if (book.id == id) {
            return &book; // Return the matching book.
        }
    }

    // Return empty if the book is not found
    return nullptr;
}

// This outputs the location of a book in the library.
void showLocation(string id) {

    // Convert the book ID into a number.
    int number = stoi(id);

    // Calculate a shelf, row and position using the ID.
    // Each shelf has 2 rows and each row can hold 5 books.
    int shelf = ((number - 1) / 10) + 1;
    int row = (((number - 1) % 10) / 5) + 1;
    int position = ((number - 1) % 5) + 1;

    cout << "\nBook Location:" << endl;
    cout << "Shelf: " << shelf << endl;
    cout << "Row: " << row << endl;
    cout << "Position: " << position << endl;
}

// This allws someone to borrow a book from our stock
void borrowBook() {

    // This will display a book list where the user can choose from
    displayBooks();

    string id;

    // Ask for the ID of the book.
    cout << "\nPlease input the Book ID you want to borrow: ";
    cin >> id;

    // Finds the book requested by the user.
    Book* book = findBook(id);

    // Checks if the ID exists.
    if (book == nullptr) {
        cout << "\nThe book requested was not found! Please check the ID." << endl;
        return;
    }

    // DOutputs the selected book`s information.
    cout << "\nTitle: " << book->title << endl;
    cout << "Author: " << book->author << endl;
    cout << "Pages: " << book->pages << endl;

    // Checks if the book is available
    if (!book->available) {
        cout << "\nStatus: OUT OF STOCK" << endl;
        cout << "Sorry, this book is out of stock. Please come back on a further date." << endl;
        return;
    }

    cout << "\nStatus: IN STOCK" << endl;

    // Outputs information on the book`s location
    showLocation(book->id);

    string answer;

    // Ask the user to confirm borrowing the book.
    cout << "\nWould you like to borrow this book? (Yes/No): ";
    cin >> answer;

    if (answer == "yes" || answer == "Yes") {

        // this changes to book`s status to unavailable.
        book->available = false;

        // Save the changes to the text file.
        if (saveBooks()) {
            cout << "\nCongratulations on borowing this book. Have a good read!" << endl;
        } else {
            // Restore the previous status if saving fail did not work.
            book->available = true;
        }

    } else {
        cout << "\nBorrowing cancelled." << endl;
    }
}

// Allow the user to return a borrowed book.
void returnBook() {

    cout << "\n========== BOOKS  OUT OF STOCK ==========\n";

    bool missingBooks = false;

    // Displays only books that are currently unavailable.
    for (const Book& book : books) {

        if (!book.available) {
            cout << book.id << " - " << book.title
                 << " by " << book.author << endl;

            missingBooks = true;
        }
    }

    // Checks if there are any books that have yet to be returned
    if (!missingBooks) {
        cout << "\nAll books are in stock!" << endl;
        return;
    }

    string id;

    // This asks the user what book he wants to return
    cout << "\nEnter the Book ID you want to return: ";
    cin >> id;

    // Search for the selected book.
    Book* book = findBook(id);

    // Checks if the book actually exists.
    if (book == nullptr) {
        cout << "\nBook loaned, No copy available!" << endl;
        return;
    }

    // Verifi if the book is already available.
    if (book->available) {
        cout << "\nThe Book has already been added to the stock!" << endl;
        return;
    }

    // Changes the book status back to available.
    book->available = true;

    // Saves the new, updated information.
    if (saveBooks()) {
        cout << "\nBook returned, Thank you !" << endl;
        cout << "Thank you for returning " << book->title << "!" << endl;

        // This shows where the returned book belongs as location
        showLocation(book->id);
    } else {
        // Restore the previous status if saving fails.
        book->available = false;
    }
}

// Main function where the program starts.
int main() {

    // Load the books from the text file.
    loadBooks();

    // Stops the program if no books were loaded.
    if (books.empty()) {
        cout << "No books have been loaded. Program shuting down." << endl;
        return 1;
    }

    int choice = 0;

    // The menu will keep displaying until the user chooses exit.
    do {

        cout << "\n========== THE LIBRARY BOOK MANAGER ==========\n";
        cout << "1. View all books" << endl;
        cout << "2. Borrow a book" << endl;
        cout << "3. Return a book" << endl;
        cout << "4. Exit" << endl;

        // Asks the user to choose a option from the menu
        cout << "\nChoose an option (1-4): ";
        cin >> choice;

        // Checks and handles incorrect input like letters
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n Choice Invalid! Please enter a number." << endl;
            continue;
        }

        // the function runs according to the user`s choice
        switch (choice) {

            case 1:
                displayBooks();
                break;

            case 2:
                borrowBook();
                break;

            case 3:
                returnBook();
                break;

            case 4:
                cout << "\n Thanks for using the Book Manager!" << endl;
                break;

            default:
                cout << "\nInvalid Choice! Please choose 1-4." << endl;
        }

    } while (choice != 4);

    // Ends the program successfully.
    return 0;
}
