

#ifndef RSTATE
#define RSTATE

class RoboState {
  public:
  //constructors and destructors
  RoboState();
  RoboState(int m);
  ~RoboState();
  
  //setup
  
  //control
  int step();
  void turnRight();
  void turnLeft();
  void turnBack();
  
  //move(int facing, int distance);
  
  //state info
  int getX();
  int getX(int i);
  int getY();
  int getY(int i);
  int getIndex();
  int getFacing();
  int getMapSize();
  int areWeBackYet();
  
  
  private:
    int n,entry; //grid descriptors
    int	x,y,facing,index; //robot state
	
	//update state info
	int calX(int i);
	int calY(int i);
	int calIndex(int iX,int iY);
	bool facingAdj();
	
	//init
	int firstSquare();
	void setMapSize(int m);
	
};

#endif