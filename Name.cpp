#include "Name.h"
#include <istream>
#include <fstream>
#include <iomanip>

NameYear::NameYear(int index)
{
    int intJahr = index + 1880;
    std::string Jahr = std::to_string(intJahr);
    std::ifstream ifs ("/home/robinw/linuxhome/GdP/Prüfung/names/yob" + Jahr + ".txt");
    std::string temp;
    while (std::getline(ifs, temp))
    {
        std::string name;
        char gender;
        int count;

        stringSplit(temp, name, gender, count);
        names.emplace_back(name, gender, count);
    }
}

Year::Year() {
    for (int i = 0; i < 143; i++)
    {
        data[i] = NameYear(i);
    }
}

std::ostream &operator<<(std::ostream& os, const Name& obj) {
    os << obj.name << ", " << obj.gender << ", " << obj.count << std::endl;
    return os;
}

void NameYear::stringSplit(std::string &line, std::string &name, char &gender, int &count)
{
    size_t pos1 = line.find(',');
    name = line.substr(0,pos1);
    size_t pos2 = line.find(',',pos1+1);
    gender = line.substr(pos1+1, 1)[0];
    std::string temp = line.substr(pos2+1, line.length()-pos2+1);
    count = stoi(temp);
}

//Kopffunktion für die Ausgabe des Histogramms
void Year::histogramm(const std::string &name) {
    int namecount[143]; //Erstellt einen Array, der mit der Anzahl der Namen in den Jahren befüllt wird
    for (int i = 0; i < 143; i++){
        namecount[i] = data[i].nameCount(name, data[i]);
    }
    int cutdata[29];
    arrayDataCut(namecount, cutdata);
    //Sucht die Anzahl der Namen in den Jahren und befüllt den Array mit diesen Werten
    histogrammOut(cutdata, name);
}

void Year::histogrammOut(int cutdata[29], std::string name) {
    int maxValue = 0;
    for (int i = 0; i < 29; ++i) {
        if (cutdata[i] > maxValue) {
            maxValue = cutdata[i];
        }
    }
    for (int i = 0; i < 29; i++) {
        cutdata[i] = cutdata[i]/(maxValue/10);
    }

    for (int row = 10; row >= 0; --row) {
        if (row == 0) {
            for (int i = 0; i < 29; i++) {
                std::cout << "--";
            }
            std::cout << "-";
            break;
        }

        if (row == 10) {
            std::cout << row;
        } else {
            std::cout << row << " ";
        }

        for (int col = 0; col < 29; ++col) {
            if (cutdata[col] >= row) {
                std::cout << "+ ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\nDas Histogramm wird im Maßstab: " << maxValue/10 << " ausgeben!\n";
}

//verschmaltert die Breite meiner Daten
void Year::arrayDataCut(int counts[143], int cutdata[29]){
    for (int i = 0; i < 29; i++) {
        cutdata[i] = 0;
    }
    for (int i = 0; i < 29; i++){
        for (int j = 0; j < 5; j++){
            cutdata[i] += counts[j+(i*5)];
        }
    }
    for (int i = 0; i < 3; i++) {
        cutdata[29] += counts[139+i];
    }
}

//Soll für das Histogramm die Vectoren nach meinem eingebenen Vector filtern und dann die Anzahl des jeweiligen Names zurückgeben
int NameYear::nameCount(std::string name, NameYear &myYear) {
    int temp = 0;
    for (size_t i = 0; i < myYear.names.size(); i++) { //Durchsucht ein Jahr nach meinem Namen
        if (name == names[i].name) {
            temp += names[i].count;
        }
    }
    return temp; //gibt die Gesamtanzahl des Namens in diesem Jahr zurück
}

//Soll in einem Jahr nach zweimal dem gleichen Namen suchen und dann die Daten von den Namen ausgeben
void Year::sameNameSearch(int jahr) {
    for(size_t i = 0; i < data[jahr-1880].names.size(); i++) {
        for (size_t j = i + 1; j < data[jahr-1880].names.size(); j++) {
            if (data[jahr-1880].names[i].name == data[jahr-1880].names[j].name) {
                std::cout << "gleicher Name gefunden: \n"
                          << data[jahr-1880].names[i]
                          << data[jahr-1880].names[j]
                          << "\n";
            }
        }
    }
}

void NameYear::probilityOfName(std::string name, NameYear &myYear) {
    double total = nameCount(name, myYear);
    double pos1;
    double pos2;

    for (size_t i = 0; i < myYear.names.size(); i++) {
        if (myYear.names[i].name == name) {
            pos1 = i;
            break;
        }
    }
    for (size_t i = pos1+1; i < myYear.names.size(); i++) {
        if (myYear.names[i].name == name) {
            pos2 = i;
            break;
        }
    }
    double probability1 = (myYear.names[pos1].count / total)*100;
    double probability2 = (myYear.names[pos2].count / total)*100;

    std::cout << total << "," << myYear.names[pos1].count << "," << myYear.names[pos2].count << "\n";
    std::cout << "Die Wahrscheinlichkeit, dass " << name << " in diesem Jahr weiblich vergeben ist, ist: " << std::setprecision(precision(probability1)) << probability1 <<"%.\n";
    std::cout << "Die Wahrscheinlichkeit, dass " << name << " in diesem Jahr männlich vergeben ist, ist: " << std::setprecision(precision(probability2)) << probability2 <<"%.\n";
}

int NameYear::precision(double probability) {
    int n;
    if (probability < 1) {
        n = 2;
    }
    else {if (probability < 10) {
            n = 3;
        }
        else {
            n = 4;
        }
    }
    return n;
}