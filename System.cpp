#include <vector>
#include <memory>
#include <iostream>

#include "System.h"
#include "Block.h"
#include "InputReader.h"


using namespace std;

System::System(InputReader* &input)
{
  inputReader = input;
  
}

System::~System()
{
  delete inputReader;
}

void System::init()
{
  cout << "Beginning Initalization" << endl;
  double d = inputReader->d;


  //Makes a vecor with the block objects
  for (int i = 0; i < inputReader->blockHeight; i++)
  {
    for (int j = 0; j < inputReader->blockWidth; j++)
    {
      blocks.push_back(shared_ptr<Block>(new Block(j,i,j*d,i*d)));
    }
  }

  //Makes the blocks make their vector of neighbors
  for (shared_ptr<Block> block: blocks)
  {
    block->fillNeighbors(blocks);
  }

  cout << "Done Initalization" << endl;
}

void System::run()
{
  //Just to check that the neighbors are correct
  for (shared_ptr<Block> block: blocks)
  {
    cout << "----------------" << endl;
    cout << block->xID << "  " << block->yID << endl;
    for (shared_ptr<Block> neighbor : block->neighbors)
    {
      cout << neighbor->xID << "  " << neighbor->yID << endl;
    }
    cout << "->" << block->neighbors.size() << endl;
  }

}
