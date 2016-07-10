#include <time.h>
#include "progressionOutput.h"

CheckProgression::CheckProgression(double stoptime, bool testing)
{
	timestarted = time(&timer);
	tStop = stoptime;
	
}

void CheckProgression::showProgression(double time)
{
    percent = calculateProgression(double time); // Prints the progression
}

int CheckProgression::CheckProgression(double time)
{	double currentTime = time(&timer);
	if (int((time/tStop)*100)%10 == 0 && int((time/tStop)*100) != percent  ){
        cout << int((time/tStop)*100) << "% done| " << curretenTime- start << " Sec used| estimated " << round((curretenTime - start)/(time/tStop) - (curretenTime - start)) << " Sec left" << endl;
        return int((time/tStop)*100);
    }
}

bool CheckProgression::doneTesting()
{
	if(int(time(&timer)-timeStarted)>=testTime){
        cout << "I am estimating it will take approximately " << int(double(time(&timer)-timeStarted)/(t/inputReader->tStop)) << " Sec" << endl << "Test ended" << endl;;
		return true;
    }
	else{return false;}
}