#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <vector>
#include <memory>

using namespace std;

class Block
{
public:
  int xID;
  int yID;

  int ID[2];

  int xPos;
  int yPos;

  int xVel;
  int yVel;

  int xForce;
  int yForce;

  vector<shared_ptr<Block>> neighbors;


  Block(int xID_, int yID_, double x, double y);
  void fillNeighbors(vector<shared_ptr<Block>> &blocks);

};

#endif
