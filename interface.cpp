#include "headers/interface.hpp"

#include <iostream>

using namespace std;

int support_choice()
{
    int choice;

debut_demande:

    cout << "Which support do you want ? [1] Bar [2] Surface \n";
    cin >> choice;

    if ((!(cin)) || (choice != 1 && choice != 2))
    {
        cout << "Error : you have chosen an unavailable support, please try again :\n";
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore(10, '\n');

        goto debut_demande;
    }

    return choice;
}

int material_choice()
{
    int choice;

debut_demande:

    cout << "Which material do you want ? [1] Copper [2] Iron [3] Glass [4] Polystyrene \n";
    cin >> choice;

    if ((!(cin)) || (choice > 4 || choice < 1))
    {
        cout << "Error : you have chosen an unavailable material, please try again :\n";
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore(10, '\n');
        goto debut_demande;
    }

    return choice;
}
