#include "Name.hpp"
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
void Year::createHistogramm(std::string &name) {
    int countOfNames[143]; //Erstellt einen Array, der mit der Anzahl der Namen in den Jahren befüllt wird
    for (int i = 0; i < 143; i++){
        countOfNames[i] = data[i].findNameCount(name);
    }
    int cutdata[29];
    arrayDataCut(countOfNames, cutdata);
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
int NameYear::findNameCount(std::string name) {
    int temp = 0;
    for (size_t i = 0; i < names.size(); i++) { //Durchsucht ein Jahr nach meinem Namen
        if (name == names[i].name) {
            temp += names[i].count;
        }
    }
    return temp; //gibt die Gesamtanzahl des Namens in diesem Jahr zurück
}

//Soll in einem Jahr nach zweimal dem gleichen Namen suchen und dann die Daten von den Namen ausgeben
void Year::searchingSameName(int jahr) {
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

void NameYear::probilityOfName(std::string name) {
    double totalcount = findNameCount(name);
    double firstpositionofname;
    double secondpositionofname;

    for (size_t i = 0; i < names.size(); i++) {
        if (names[i].name == name) {
            firstpositionofname = i;
            break;
        }
    }
    for (size_t i = firstpositionofname+1; i < names.size(); i++) {
        if (names[i].name == name) {
            secondpositionofname = i;
            break;
        }
    }
    double probability1 = (names[firstpositionofname].count / totalcount)*100;
    double probability2 = (names[secondpositionofname].count / totalcount)*100;

    std::cout << totalcount << "," << names[firstpositionofname].count << "," << names[secondpositionofname].count << "\n";
    std::cout << "Die Wahrscheinlichkeit, dass " << name << " in diesem Jahr weiblich vergeben ist, ist: " << std::setprecision(findPrecision(probability1)) << probability1 <<"%.\n";
    std::cout << "Die Wahrscheinlichkeit, dass " << name << " in diesem Jahr männlich vergeben ist, ist: " << std::setprecision(findPrecision(probability2)) << probability2 <<"%.\n";
}

int NameYear::findPrecision(double probability) {
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