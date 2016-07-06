#include <vector>
#include <memory>

#include "Block.h"
#include "InputReader.h"

using namespace std;

class System
{
public:
  vector<shared_ptr<Block>> blocks;
  InputReader* inputReader;
  vecor<double> eqDistModifier; //Modifies the equilibrium distance
  vector<double> springConstModifier: //Modifies the spring constant

  System(InputReader* &input);
  ~System();

  void run();
  void init();

};
