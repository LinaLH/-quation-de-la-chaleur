#include "headers/interface.hpp"

#include <iostream>

using namespace std;

int support_choice()
{
    int choice;

request:

    // Display the prompt for the user
    cout << "Which support do you want ? [1] Bar [2] Surface \n";

    // Take user input
    cin >> choice;

    // Check if the input is valid
    if ((!(cin)) || (choice != 1 && choice != 2))
    {
        // If not, display an error message and clear the input
        cout << "Error : you have chosen an unavailable support, please try again :\n";
        cin.clear();
        cin.ignore(10, '\n');

        // Go back to the beginning of the function and ask again
        goto request;
    }

    // Return the user's choice
    return choice;
}

int material_choice()
{
    int choice;

request:

    // Display the prompt for the user
    cout << "Which material do you want ? [1] Copper [2] Iron [3] Glass [4] Polystyrene \n";

    // Take user input
    cin >> choice;

    // Check if the input is valid
    if ((!(cin)) || (choice > 4 || choice < 1))
    {
        // If not, display an error message and clear the input
        cout << "Error : you have chosen an unavailable material, please try again :\n";
        cin.clear();
        cin.ignore(10, '\n');

        // Go back to the beginning of the function and ask again
        goto request;
    }

    // Return the user's choice
    return choice;
}
