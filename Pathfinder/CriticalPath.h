/*Code by: Mladen Kojic

Description: A quick and dirty method to find the critical path through a maze with the following 
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/



/*
class crPath {
  public:
	//constructors, destructors
	crPath(){};
	~crPath(){};
	
	//public functions
	bool setNextStep(int i);
	int getNextStep(int i);
	int size();
	  
  private:
    vector<int> path;
}
*/

//external header file
#define MAXPATHSIZE 50

#ifndef CRITICALPATH
#define CRITICALPATH

	class crPath {
	public:
	  //constructors, destructors
	  crPath();
	  ~crPath();
	  //public access functions
	  bool setNextStep(int i);
	  int getNextStep(int i);
	  int getSize();
	private:
	  int size;
	  int path[MAXPATHSIZE];
	  
	  int push_back(int i);
	  int pop_back();
	};
  
#endif