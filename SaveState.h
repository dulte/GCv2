#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Block.h"


using namespace std;

class SaveState
{
public:

  ofstream outFile;


  ifstream inFile;

  SaveState();
  ~SaveState();

  void saveState(vector<shared_ptr<Block>> &blocks);
  void loadState(vector<shared_ptr<Block>> &blocks);




};
