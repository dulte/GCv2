#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Block.h"
#include "SaveState.h"

using namespace std;


SaveState::SaveState(){};
SaveState::~SaveState(){};


void SaveState::saveState(vector<shared_ptr<Block>> &blocks)
{
  outFile.open("states/state.txt");//bin", ios::out | ios::binary);


  for (shared_ptr<Block> block: blocks)
  {
    outFile << block->xPos << " " << block->yPos << " " << block->xForce << " " << block->yForce << endl;
  }
  outFile.close();

  cout << "State Saved" << endl;

}


void SaveState::loadState(vector<shared_ptr<Block>> &blocks){

  inFile.open("states/state.txt");//bin", ios::out | ios::binary);


  std::vector<double> xForce;
  std::vector<double> yForce;
  std::vector<double> xPos;
  std::vector<double> yPos;

  inFile.clear();
  inFile.seekg(0,ios::beg);
  for (string l; getline(this->inFile,l);)
  {
      stringstream ss(l);
      double xP;
      double yP;
      double xF;
      double yF;

      ss >> xP >> yP >> xF >> yF;

      xPos.push_back(xP);
      yPos.push_back(yP);
      xForce.push_back(xF);
      yForce.push_back(yF);

  }

  if (!(blocks.size() == xPos.size()))
  {
    cout << "Noe gikk galt da du skulle 'Load State'" << endl;
  }

  for (int i = 0; i < blocks.size(); i++)
  {
    blocks[i]->xPos = xPos[i];
    blocks[i]->yPos = yPos[i];

    blocks[i]->xForce = xForce[i];
    blocks[i]->xForce = xForce[i];
  }
  inFile.close();

  cout << "State Loaded" << endl;

}
