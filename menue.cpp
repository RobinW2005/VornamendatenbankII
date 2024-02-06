#include "Name.hpp"
#include "menue.hpp"
#include <iostream>

void menueAusgeben(){
    std::cout << "[1] Histogramm\n"
              << "[2] Ausgabe zweigeschlechtlicher Namen\n"
              << "[3] Wahrscheinlichkeit eines Names an eines der Geschlechter vergeben zu sein\n";
};

void menueAbfragen(){
    menueAusgeben();

    unsigned int choice;
    std::cin >> choice;

    if (choice < 4)
    {
        auswahl(choice);
    }
};

void auswahl(unsigned int choice){
    Year Data;
    switch(choice)
    {
        case 1: {
            std::string requestedname;
            std::cout << "Zu welchem Namen soll das Histogramm ausgeben werden?\n";
            std::cin >> requestedname;
            Data.createHistogramm(requestedname);
            break;
        }

        case 2: {
            int jahr;
            std::cout << "In welchem Jahr soll nach gleichen Namen gesucht werden?\n";
            std::cin >> jahr;
            Data.searchingSameName(jahr);
            break;
        }

        case 3: {
            std::string requestedname;
            int year;
            std::cout << "Nach welchem Namen soll gesucht werden?\n";
            std::cin >> requestedname;
            std::cout << "In welchem Jahr soll gesucht werden?\n";
            std::cin >> year;
            Data.data[year - 1880].probilityOfName(requestedname);
            break;
        }
    }
};
