#ifndef GETVAR_H
#define GETVAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
class getVar
{
    public:
        ifstream infile;
        string line;


        getVar();
        ~getVar();
        double get(string varName);

    protected:

    private:
};

#endif // GETVAR_H
