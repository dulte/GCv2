#include <iostream>
#include <cmath>

#include <time.h>
#include "CheckProgression.h"

using namespace std;

CheckProgression::CheckProgression(double stoptime, bool testing)
{
	timeStarted = time(&timer);
	tStop = stoptime;
  isTesting = testing;

}

void CheckProgression::showProgression(double t)
{
  if (!isTesting){
    percent = int(calculateProgression(t,percent)); // Prints the progression
  }
}

int CheckProgression::calculateProgression(double t,int p)
{
  double currentTime = time(&timer);

	if (int((t/tStop)*100)%10 == 0 && int((t/tStop)*100) != p ){
        cout << int((t/tStop)*100) << "% done| " << currentTime- timeStarted << " Sec used| estimated " << round((currentTime - timeStarted)/(t/tStop) - (currentTime - timeStarted)) << " Sec left" << endl;
        percent = int((t/tStop)*100);
        return percent;
  }
  else{return p;}
}

bool CheckProgression::doneTesting(double t)
{
  if (isTesting){
	   if(int(time(&timer)-timeStarted)>=testTime){
          cout << "I am estimating it will take approximately " << int(double(time(&timer)-timeStarted)/(t/tStop)) << " Sec" << endl << "Test ended" << endl;;
		      return true;
     }
	   else{return false;}
  }
  else{return false;}
}
