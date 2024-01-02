#include "headers/interface.h"

#include <iostream>

using namespace std;

int support_choice()
{
    int choix;

debut_demande:

    cout << "Quel support voulez vous utiliser ? [1] Barre [2] Plaque \n";
    cin >> choix;

    if ((!(cin)) || (choix != 1 && choix != 2))
    {
        cout << "Erreur : vous avez entré un support pas possible, veuillez réessayer :\n";
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore(10, '\n');

        goto debut_demande;
    }

    return choix;
}

int material_choice()
{
    int choix;

debut_demande:

    cout << "De quel matériel souhaitez vous le support ? [1] Cuivre [2] Fer [3] Verre [4] Polystyrène \n";
    cin >> choix;

    if ((!(cin)) || (choix > 4 || choix < 1))
    {
        cout << "Erreur : vous avez choisi un matériel pas disponible, veuillez réessayer :\n";
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore(10, '\n');
        goto debut_demande;
    }

    return choix;
}
