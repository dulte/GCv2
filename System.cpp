#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

#include "System.h"
#include "Block.h"
#include "InputReader.h"
#include "ConstantForceBlock.h"
#include "CheckProgression.h"
#include "BottomBlock.h"
#include "Pusher.h"
#include "FrictionBlock.h"


using namespace std;

System::System(InputReader* &input)
{
  inputReader = input;




  // Create output streams
  outFilePositions.open("output/positions.bin", ios::out | ios::binary);
  outFileForce.open("output/force.bin", ios::out | ios::binary);
  outFileVelocity.open("output/velocity.bin", ios::out | ios::binary);
  outFilePusher.open("output/pusher.bin", ios::out | ios::binary);
  outFileNormalForce.open("output/normalforce.bin" ,ios::out | ios::binary);
  outFileState.open("output/state.bin",ios::out | ios::binary);
  outFileBlocksSlipped.open("output/slippedblocks.bin",ios::out | ios::binary);
  outFilePercentageSlipped.open("output/percentSlipped.bin",ios::out | ios::binary);

  outFileVariablesUsed.open("output/variablesUsed.txt");

  outFilePosXYZ.open("output/pos.xyz");


}

System::~System()
{
  delete checkProgress;
  delete pusher;
  outFilePositions.close();
  outFileVelocity.close();

  outFileForce.close();
  outFilePusher.close();
  outFileNormalForce.close();
  outFileState.close();
  outFilePosXYZ.close();
  outFileVariablesUsed.close();
  outFileBlocksSlipped.close();
  outFilePercentageSlipped.close();
}

void System::init()
{
  cout << "Beginning Initalization" << endl;




  //Makes a vecor with the block objects
  for (int i = 0; i < inputReader->blockHeight; i++)
  {
    for (int j = 0; j < inputReader->blockWidth; j++)
    {
      if (i == inputReader->blockHeight-1)
      {
        blocks.push_back(shared_ptr<Block>(new ConstantForceBlock(j,i,inputReader,0,-1)));
      }
      else if (i == 0)
      {

        blocks.push_back(shared_ptr<Block>(new FrictionBlock(j,i,inputReader)));
        // if (j == 0)
        // {
        //   pusher = new Pusher(j,i,inputReader);
        // }
      }
      else
      {
        blocks.push_back(shared_ptr<Block>(new Block(j,i,inputReader)));
      }
      // if (j == inputReader->blockWidth-1)
      // {
      //   blocks.push_back(shared_ptr<Block>(new ConstantForceBlock(j,i,inputReader,1,0)));
      // }
      // else if (j == 0)
      // {
      //   blocks.push_back(shared_ptr<Block>(new ConstantForceBlock(j,i,inputReader,-1,0)));
      // }
      // else
      // {
      //   blocks.push_back(shared_ptr<Block>(new Block(j,i,inputReader)));
      // }
      //blocks.push_back(shared_ptr<Block>(new Block(j,i,inputReader)));

    }
  }

  //Makes the blocks make their vector of neighbors
  for (shared_ptr<Block> block: blocks)
  {
    block->fillNeighbors(blocks);
  }

  inputReader->dumpToFile(outFileVariablesUsed);

  cout << "Done Initalization" << endl;
}




void System::run()
{
  //Makes the arrays used to hold data for output to file
  double velocity[inputReader->blockWidth];
  double positions[inputReader->blockWidth];
  double force[inputReader->blockWidth];
  double normalForce[inputReader->blockWidth];
  double state[inputReader->blockWidth];
  double percentSlipped[inputReader->blockWidth];

  vector<double> pusherVec;
  vector<double> slippedBlocks;


  //Initalizating the object that shows progression
  checkProgress = new CheckProgression(inputReader->tStop, inputReader->test);

  //Some variables used in the Main Loop
  double t = 0;
  unsigned int counter = 0;
  bool pusherRestMessageRead = false;
  bool connectorRestMessageRead = false;



  cout << "Beginning Calculation" << endl;
  cout << "With: " << inputReader->blockWidth << "x" << inputReader->blockHeight  << " Blocks" << endl;
  cout << "Simulating " << inputReader->tStop << " Seconds" << endl;

  //Can push the first blocks to check the internal propeties of the system
  pokeSide(0);


  //Main Loop:
  while (t<inputReader->tStop)
  {


    if (t>=inputReader->restBeforePushTime && !pusherRestMessageRead)
    {
      cout << "Beginning to Push" << endl;
      pusherRestMessageRead = true;
      for (shared_ptr<Block> block: blocks)
      {
        if (block->xID == 0 && (block->yID == 0)) //Initalizating pusher
        {
          pusher = new Pusher(block->xID,block->yID,block->xPos,inputReader);
        }
      }
    }
    if (t>=inputReader->restBeforeConnectTime && !connectorRestMessageRead)
    {
      cout << "Connecting Connectors" << endl;
      connectorRestMessageRead = true;
      for (shared_ptr<Block> block: blocks)
      {
        block->setResting(false);
      }

    }



    if (checkProgress->doneTesting(t))
    {
      break;
    }
    checkProgress->showProgression(t);
    //cout << int((t/inputReader->tStop)*100) << endl;



    //First part of Velocity Verlet
    for (shared_ptr<Block> block: blocks)
    {

      block->xPos +=  block->xVel*inputReader->dt + 0.5*(block->xForce/inputReader->m)*inputReader->dt*inputReader->dt;
      block->xVel +=  0.5*block->xForce*inputReader->dt/inputReader->m;


      block->yPos +=  block->yVel*inputReader->dt + 0.5*(block->yForce/inputReader->m)*inputReader->dt*inputReader->dt;
      block->yVel +=  0.5*block->yForce*inputReader->dt/inputReader->m;

    }

    //Force calculation:
    for (shared_ptr<Block> block: blocks)
    {
      block->calculateForces();

      if (pusher != NULL){
      if ((block->xID == pusher->xID && block->yID == pusher->yID) && t >= inputReader->restBeforePushTime)
      {
        block->xForce += pusher->calculatePusher(block->xPos);

      }
      }
    }


    //Integration loop: Velocity Verlet second part:
    for (shared_ptr<Block> block: blocks)
    {
      // double eps = 1e-4;
      // block->xVel +=  block->xForce*inputReader->dt/inputReader->m;
      // block->xPos +=  block->xVel*inputReader->dt;
      //
      // block->yVel +=  block->yForce*inputReader->dt/inputReader->m;
      // block->yPos +=  block->yVel*inputReader->dt;

      block->xVel +=  0.5*block->xForce*inputReader->dt/inputReader->m;
      block->yVel +=  0.5*block->yForce*inputReader->dt/inputReader->m;



      if (block->yID == 0)
      {
        //if (block->xID == 20){cout << block->xVel << endl;}

        positions[block->xID] = block->xPos;
        velocity[block->xID] = block->xVel;
        force[block->xID] = block->xForce;
        normalForce[block->xID] = block->returnNormalForce();
        state[block->xID] = block->getState();
        percentSlipped[block->xID] = block->getPercentageSlipped();


      }


    }








    if ((counter%inputReader->writeFrequency) == 0)
    {

      writeArrayToFile(outFilePositions,positions,inputReader->blockWidth);
      writeArrayToFile(outFileVelocity,velocity,inputReader->blockWidth);
      writeArrayToFile(outFileForce,force, inputReader->blockWidth);
      writeArrayToFile(outFileNormalForce, normalForce, inputReader->blockWidth);
      writeArrayToFile(outFileState,state,inputReader->blockWidth);
      writeArrayToFile(outFilePercentageSlipped,percentSlipped,inputReader->blockWidth);


      // outFilePosXYZ << inputReader->numberOfBlocks <<"\n"  << t << "\n";
      //
      // for (int p = 0; p < blocks.size(); p++)
      // {
      //   outFilePosXYZ << p << " " << blocks[p]->xPos << " " << blocks[p]->yPos << " " << 0 << "\n";
      // }
      if (pusher != NULL)
      {
        pusherVec.push_back(pusher->getPusherForce()/inputReader->downPushForce);
      }
      double k = 0;
      for (int j = 0; j < inputReader->blockWidth; j++)
      {
        k+=state[j];
      }
      slippedBlocks.push_back(int(inputReader->blockWidth-k));

    }




    t += inputReader->dt;

    counter++;
  }
  //Cheks Poissons Ratio
  double x0, x1, z0,z1;
  for (shared_ptr<Block> block: blocks)
  {
    if (block->xID == 0 && block->yID == round((inputReader->blockHeight-1)/2))
    {
      x0 = block->xPos;
    }
    else if (block->xID == inputReader->blockWidth -1 && block->yID == round((inputReader->blockHeight-1)/2))
    {
      x1 = block->xPos;
    }

    if (block->yID == 0 && block->xID == round((inputReader->blockWidth-1)/2))
    {
      z0 = block->yPos;
    }
    else if (block->yID == inputReader->blockHeight-1 && block->xID == round((inputReader->blockWidth-1)/2))
    {
      z1 = block->yPos;
    }



  }

  if (pusherVec.size() > 0)
  {
    writeVectorToFile(outFilePusher,pusherVec);
  }

  writeVectorToFile(outFileBlocksSlipped,slippedBlocks);


  double dz = ((z1-z0) - (inputReader->d)*(inputReader->blockHeight-1))/inputReader->blockWidth;
  double dx = ((x1-x0) - (inputReader->d)*(inputReader->blockWidth-1))/inputReader->blockHeight;
  cout << "Poissons Ratio ble beregnet til: " << -dx/dz << " | Forventet er: 1/3" << endl;
  cout << "Youngs modulus ble beregnet til: " << (inputReader->downPushForce/inputReader->blockHeight)/((dz)*0.006) << " |  Forventet er: " << (4./3.)*(inputReader->k)/(0.006) <<endl;

  cout << "dx: " << dx << "  " << "dz: " << dz <<   endl;

  checkProgress->dumpTimeToFile(outFileVariablesUsed);




  // for (shared_ptr<Block> block: blocks)
  // {
  //   if (block->yID == 0){
  //   cout << "-----------------------" << endl;
  //   cout << block->xID << "  " << block->yID << "  |  " << velocity[block->xID] << "  " << block->xVel << endl;
  //   cout << block->xID << "  " << block->yID << "  |  " << positions[block->xID] << "  " << block->xPos << endl;
  //   cout << block->xID << "  " << block->yID << "  |  " << force[block->xID] << "  " << block->xForce << endl;
  //   }
  // }



}



//Writes arrays to Files
void System::writeArrayToFile(ofstream & outFile, double * array, int numBlocks)
{
	outFile.write(reinterpret_cast<char*>(array), numBlocks*sizeof(double));
}

void System::pokeSide(double factor)
{
  for(shared_ptr<Block> block: blocks)
  {
    if (block->xID == 0)
    {
      block->xPos = factor*inputReader->d;
    }
  }
}

void System::writeVectorToFile(ofstream &file, vector<double> v)
{
  double a[v.size()];

  for (int i = 0; i < v.size(); i++)
  {
    a[i] = v[i];
  }
  writeArrayToFile(file,a,int(v.size()));
}
