
#include <iostream>  // Allows input and output by using cin and cout.
#include <fstream>   // reads data from an external file
#include <string>    // string allows me to work with text.
#include <vector>    // helps store multiple jokes in a dynamic list.
#include <cstdlib>   // Provides rand() and srand() for random numbers.
#include <ctime>     // Gives time() to initialise the random generator.

using namespace std;

// AI acknowledgement:
// Tool: AI ChatGPT 
// Prompt: How can I make my program pick jokes randomly from my list instead of 
// showing all of them? Can you explain how it works in detail and give me an example?
// Each joke is written on one line in my text file. How can I make the program show the question,
// and answer on separate lines? Can you explain how to do this and give me an example?
 

int main() {

    // Checks the current time as guidance to pick a random joke
    srand(time(0));

   // This creates a list to store the jokes from the list provided
    vector<string> jokes;

    // This creates a variable to hold 1 joke at a time
    string joke;

    // This opens the text file containing the jokes
    ifstream jokeFile("randomJokes.txt");

    // This checks if the file was opened correctly
    if (!jokeFile.is_open()) {

        // Display an error if the file cannot be found or opened.
        cout << "Error: RandomJokes.txt could not be opened" << endl;

        // IF the file is missing, it will exit the program.
        return 1;
    }

    // Read the file one line at a time until there are no lines left to read.
    while (getline(jokeFile, joke)) {

        // verifies if the current line is empty
        if (!joke.empty()) {

            // adds each joke to the list one by one
            jokes.push_back(joke);
        }
    }

    // The file will close after all the jokes have been loaded
    jokeFile.close();

    // This checks if the vector currently contains any jokes
    if (jokes.empty()) {

        // Lets the user know if the file isnt containing any valid jokes
        cout << "Error: The file doesn`t contain any jokes." << endl;

        // Exit the program because there are no jokes to display.
        return 1;
    }

    // Shows all the jokes successfully loaded.
    cout << "Successfully loaded " << jokes.size() << " jokes!" << endl;

    // Create a string variable to store the user's command.
    string command;

    // Asks the user to enter a command for Alexa.
    cout << "\nWhat do you want to ask Alexa?" << endl;

    // Reads all the command, including spaces.
    getline(cin, command);

    // Verifies if the user has asked for a joke.
    // This allows both capital and lower case letters "Alexa".
    if (command == "Alexa, tell me a joke" ||
        command == "alexa, tell me a joke") {

       // Pick a random joke number from the list.
       // Makes sure that the number is not bigger than the list.
        int randomIndex = rand() % jokes.size();

        // Store the selected joke in a separate string.
        string selectedJoke = jokes[randomIndex];

        // This finds where the question mark is positioned in the joke
        size_t questionMark = selectedJoke.find('?');

        // This checks if the joke contains a question mark
        if (questionMark != string::npos) {

            // Starts a new line after the question mark.
            // This separates the question from the joke`s answer
            selectedJoke.insert(questionMark + 1, "\n");
        }

        // This will output the selected joke.
        cout << "\nAlexa: " << selectedJoke << endl;

    } else {

        // Replies with a message if the command is not recognised
        cout << "\nAlexa: Sorry, I don't understand that command." << endl;
    }

    // Return 0 to indicate that the program finished successfully.
    return 0;
}
