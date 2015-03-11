/*Code by: Mladen Kojic

Description: A quick and dirty method to find the critical path through a maze with the following 
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/


#include "Defines.h"
#include "CriticalPath.h"

CrPath::CrPath(int m) {
	setup(m);
}

CrPath::CrPath() {
	setup(DEFAULTMAPSIZE);
}

void CrPath::setup(int m) {
  int it;
  size = 0;
  cpDone = 0;
  endSquare = m;
    for (it = 0; it<MAXPATHSIZE;it++) {
    path[it] = 0; 
  }
}

CrPath::~CrPath(){}

bool CrPath::setNextStep(int i) {
  if (!cpDone) {
    if(size < 2) {
	  push_back(i);
	  return TRUE;
	}
    if (path[(size-2)] != i){
      push_back(i); //next spot and previous spot do not match -- new step in path
      return TRUE;
    } else {
      pop_back(); //next spot and previous spot are the same -- erase current spot
      return FALSE;
    }
  }
}
int CrPath::getNextStep(int i) {
  // to get the critical path here, use something like int i(0); for(i=0;i<(this).size();i++){(this).getNextstep)}
  return path[i];
}
int CrPath::getSize(){
  return size;
}

int CrPath::push_back(int i){
  path[size] = i;
  size++;
  cpDone = (i==endSquare);
}

int CrPath::pop_back(){
  size--;
  path[size] = 0;
}

int CrPath::getCompletionState(){
	return cpDone;
}