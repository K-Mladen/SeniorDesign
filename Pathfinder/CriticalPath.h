/*Code by: Mladen Kojic

Description: A quick and dirty method to find the critical path through a maze with the following 
assumptions:
the calling code has an indexed grid on the maze such that any walls are on grid boundaries
there are no loops in the maze -- in other words, there is only one path from any point a to point b
*/

#ifndef CRITICALPATH
#define CRITICALPATH

#include "DEFINES.H"

class CrPath {
  public:
    //constructors, destructors
    CrPath(); //class should not be created without initializing
	CrPath(int m);
    ~CrPath();
	setup(int m);
	
    //public access functions
    bool setNextStep(int i);
    int getNextStep(int i);
    int getSize();
	int getCompletionState();
    
  private:
    int size;
    int cpDone;
	int endSquare;
    int path[MAXPATHSIZE];
    
    int push_back(int i);
    int pop_back();
};
  
#endif