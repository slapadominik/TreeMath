#ifndef TREEMATH_INTERFACE_H
#define TREEMATH_INTERFACE_H
#define MSG_START_PROGRAM "Aplikacja sluzaca do obliczania formul matematycznych w postaci prefixowej.\nDostepne komendy: \nenter <formula> - wykonanie powoduje probe stworzenia drzewa na podstawie podanego wyrazenia \nvars - wypisuje wszystkie zmienne z aktualnie wprowadzonego drzewa \nprint - wypisuje aktualnie wprowadzone drzewo w postaci prefiksowej \ncomp <var0> <var1> <varN> - wyliczenie wartosci wprowadzonej formuly gdzie <varN> to wartosci dla kolejnych zmiennych \njoin <formula> - dolacza drzewo z formuly do istniejacego drzewa"
#define ERROR_MSG_INCORRECT_FORMULA_REPAIRED_TREE "Niepoprawna formula, po naprawie drzewo wyglada nastepujaco:"
#define ERROR_MSG_PARAMS_ARENT_NUMBERS "Blad, podane parametry komendy nie sa liczbami!"

#include <string>
#include <vector>
#include "CTree.h"

class Interface {
public:
    Interface();
    ~Interface();
    void vRunApp();


private:
    CTree *pc_tree;
    bool b_is_number(const std::string &s);
    std::vector<std::string> split(std::string sStringToSplit, char chRegnex);
};


#endif //TREEMATH_INTERFACE_H
