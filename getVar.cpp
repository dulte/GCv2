#include "getVar.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

getVar::getVar()
{
    infile.open("config/variables.txt");
}

getVar::~getVar()
{
    infile.close();
}

double getVar::get(string varName)
{
    infile.clear();
    infile.seekg(0,ios::beg);
    for (string l; getline(this->infile,l);)
    {
        stringstream ss(l);

        string name;
        double var1;

        ss >> name >> var1;

        if (name == varName){
            return var1;
            }

    }

    cout << "could not find a variable by that name: " << varName << endl;
    return 0;
}
