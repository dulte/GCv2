#include <iostream>

#include "System.h"
#include "InputReader.h"

using namespace std;

int main(){

  InputReader* inputReader = new InputReader();
  System* systemObj = new System(inputReader);

  systemObj->init();
  systemObj->run();

  cout << "hello" << endl;

  return 0;
}
