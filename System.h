#include <vector>
#include <memory>
#include <fstream>

#include "Block.h"
#include "InputReader.h"
#include "CheckProgression.h"
#include "Pusher.h"

using namespace std;

class System
{
public:
  vector<shared_ptr<Block>> blocks;
  InputReader* inputReader;

  ofstream outFilePositions;
  ofstream outFileForce;
  ofstream outFileVelocity;
  ofstream outFilePusher;
  ofstream outFileNormalForce;
  ofstream outFileState;
  ofstream outFilePosXYZ;
  ofstream outFileBlocksSlipped;

  ofstream outFileVariablesUsed;

  CheckProgression* checkProgress;

  Pusher* pusher;
  //ofstream outFileParameters;

  //Pointer made to hold data arrays
  // double* positions;
  // double* velocity;
  // double* force;

  System(InputReader* &input);
  ~System();

  void run();
  void init();

  //int checkProgress(double time, double tStop, int percent,double curretenTime, double start);
  void writeArrayToFile(ofstream & outFile, double * array, int numBlocks);
  void pokeSide(double factor);
  void writeVectorToFile(ofstream &file, vector<double> v);

};
