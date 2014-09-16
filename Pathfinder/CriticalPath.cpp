/*Code by: Mladen Kojic

Description: A quick and dirty method to find the critical path through a maze with the following 
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/


class crPath {
  public:
	//constructors, destructors
	crPath(){};
	~crPath(){};
	
	//public functions
	bool setNextStep(int i){ 
	  if (path.at(path.size-1)!=int i){
	    path.push_back(i); //next spot and previous spot do not match -- new step in path
		return TRUE;
	  } else {
		path.pop_back();  //next spot and previous spot are the same -- erase current spot
		return FALSE;
	  }
	}
	int getNextStep(int i){
	// to get the critical path here, use something like int i(0); for(i=0;i<(this).size();i++){(this).getNextstep)}
	  return path.at(i);
	}
	int size(){
	  return path.size();
	}

	  
  private:
    vector<int> path;
}