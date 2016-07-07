#include <iostream>
#include <fstream>

#include "System.h"
#include "InputReader.h"

using namespace std;

ofstream outFileParameters("output/parameters.txt", ios::out);

int main(){



  InputReader* inputReader = new InputReader();
  System* systemObj = new System(inputReader);


  // Output parameters to file
	outFileParameters << "nx " << inputReader->blockWidth << "\n";
  outFileParameters << "dt " << inputReader->dt << "\n";

  systemObj->init();
  systemObj->run();

  cout << "Simulation Done" << endl;

  return 0;
}
