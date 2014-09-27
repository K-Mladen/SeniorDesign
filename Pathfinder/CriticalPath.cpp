/*Code by: Mladen Kojic

Description: A quick and dirty method to find the critical path through a maze with the following 
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/


/*
#include "CriticalPath.cpp"

bool crPath::setNextStep(int i) { 
	  if (path.at(path.size-1)!=int i){
	    path.push_back(i); //next spot and previous spot do not match -- new step in path
		return TRUE;
	  } else {
		path.pop_back();  //next spot and previous spot are the same -- erase current spot
		return FALSE;
	  }
	}
	
int crPath::getNextStep(int i) {
	// to get the critical path here, use something like int i(0); for(i=0;i<(this).size();i++){(this).getNextstep)}
	  return path.at(i);
	}
	
int crPath::size(){
	  return path.size();
	}
	*/
	
/*Code by: Mladen Kojic
Description: A quick and dirty method to find the critical path through a maze with the following
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/
#include "CriticalPath.cpp"
bool crPath::setNextStep(int i) {
  if (path[(size-1)] != int i){
    push_back(i); //next spot and previous spot do not match -- new step in path
    return TRUE;
  } else {
    pop_back(); //next spot and previous spot are the same -- erase current spot
    return FALSE;
  }
}
int crPath::getNextStep(int i) {
  // to get the critical path here, use something like int i(0); for(i=0;i<(this).size();i++){(this).getNextstep)}
  return path[i];
}
int crPath::getSize(){
  return path.size();
}

int crPath::push_back(int i){
  path[size] = i;
  size++;
}

int crPath::pop_back(){
  path[size] = 0;
  size--;
}
