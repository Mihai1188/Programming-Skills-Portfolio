
#include <iostream>  // Allows the program to display messages and get user input.
#include <iomanip>   // Allows the program to display the result with decimals
#include <limits>    // Helps on handlingn incorect inputs.

using namespace std;

// AI acknowledgement:
// Tool:  ChatGPT 
// AI was used to help on how to include emission rates into the calculator and 
// adapt the result according to the selected option.

// This stores the CO2 produced per passenger for each km.
const double CAR_RATE = 0.170;
const double PLANE_RATE = 0.150;
const double BUS_RATE = 0.100;

// this creates a function to calculate CO2 emission
double calculateCO2(double distance, double rate) {

    // This will multiply the distance by CO2 emission
    return distance * rate;
}

// Starts the program
int main() {

    // This saves the user`s choice of transport
    int choice;

    // This saves the distance entered by the user
    double distance;

    // This stores the calculated CO2 emission
    double emissions;

    // Store the name of the transport type selected 
    string transport;

    // Store the CO2 rate for the transpor type selected 
    double rate;

    // This will keep the calculator running until the user decides to exit.
    do {

        // Display the calculator menu.
        cout << "\n========== CO2 CALCULATOR ==========\n";
        cout << "1. Car" << endl;
        cout << "2. Aeroplane" << endl;
        cout << "3. Bus" << endl;
        cout << "4. Exit" << endl;

        // Requests the user to choose the desired transport type
        cout << "\nChoose your transport (1-4): ";
        cin >> choice;

        // This will check if the user enters a valid choice ( number)
        if (cin.fail()) {

            // Clear the input error.
            cin.clear();

            // This removes the incorect imput
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid input! Please enter a number." << endl;
            continue;
        }

        // This exists the calculator if the user chooses option 4.
        if (choice == 4) {
            cout << "\nThank you for using the CO2 Calculator!" << endl;
            break;
        }

        // Verifies which transport type the user has chosen.
        switch (choice) {

            case 1:
                transport = "Car";
                rate = CAR_RATE;
                break;

            case 2:
                transport = "Aeroplane";
                rate = PLANE_RATE;
                break;

            case 3:
                transport = "Bus";
                rate = BUS_RATE;
                break;

            default:
                cout << "\nInvalid option! Please choose 1-4." << endl;
                continue;
        }

        // Ask the user to enter the travel distance.
        cout << "\nEnter the distance in kilometres: ";
        cin >> distance;

        // Check if the distance is a positive number
        if (cin.fail() || distance <= 0) {

            // Clear any input errors.
            cin.clear();

            // Removes any incorect input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid distance! Please enter a number bigger than 0." << endl;
            continue;
        }

        // This calculates the CO2 emission using the function.
        emissions = calculateCO2(distance, rate);

        // Displays the results with 2 decimals.
        cout << fixed << setprecision(2);

        cout << "\n========== YOUR CO2 RESULTS ==========\n";
        cout << "Transport: " << transport << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "CO2 per km: " << rate << " kg" << endl;
        cout << "Total CO2: " << emissions << " kg" << endl;

        cout << "\nThese are estimated CO2 emissions per passenger." << endl;

    } while (choice != 4);

    // End the program successfully.
    return 0;
}
