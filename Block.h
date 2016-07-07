#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <vector>
#include <memory>

#include "InputReader.h"

using namespace std;

class Block
{
public:
  int xID;
  int yID;

  int ID[2];

  double xPos;
  double yPos;

  double xVel = 0; //Om du faar noen feil i naermeste fremtid, sjekk her
  double yVel = 0;

  double xForce = 0;
  double yForce = 0;

  vector<shared_ptr<Block>> neighbors;
  InputReader* inputReader;
  vector<double> eqDistModifier; //Modifies the equilibrium distance
  vector<double> springConstModifier; //Modifies the spring constant


  Block(int xID_, int yID_, InputReader* &input);
  ~Block();
  void fillNeighbors(vector<shared_ptr<Block>> &blocks);
  virtual void calculateForces();

};

#endif
