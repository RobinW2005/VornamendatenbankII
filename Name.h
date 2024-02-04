#pragma once
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <array>

//Speichert zu jedem Namen aus einer Datei die drei Daten, Name, Gender und Anzahl
struct Name
{
    Name(std::string name, char gender, unsigned int count)
    :name(std::move(name))
    ,gender(gender)
    ,count(count)
    {};

    std::string name;
    char gender;
    unsigned int count;
    friend std::ostream &operator<<(std::ostream& os, const Name& obj);
};

//Speichert alle Namen aus einer Datei/ eines Jahres in einem Vector ab
struct NameYear
{
    std::vector<Name> names;
    explicit NameYear(int index);
    NameYear()= default;
    static void stringSplit(std::string &line, std::string &name, char &gender, int &count);
    int nameCount(std::string, NameYear &myYear);
    void probilityOfName(std::string name, NameYear &myYear);
    static int precision(double probability);
};

//Speichert alle Jahre/Vectoren in einem Array ab
struct Year
{
    NameYear data[143];
    Year();
    friend std::ostream &operator<<(std::ostream& ausgabe,Year &obj);
    void histogramm(const std::string &name);
    void sameNameSearch(int jahr);
    void histogrammOut(int counts[29], std::string name);
    static void arrayDataCut(int counts[143], int cutdata[29]);
};