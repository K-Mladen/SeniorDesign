
#ifndef RSTATE
#define RSTATE

class RoboState {
  public:
  //constructors and destructors
  RoboState();
  RoboState(int m);
  ~RoboState();
  
  //control
  void step();
  void turnRight();
  void turnLeft();
  void turnBack();
  
  //move(int facing, int distance);
  
  //state info
  int getX();
  int getY();
  int getIndex();
  
  private:
    int n,entry //grid descriptors
    int	x,y,facing,index; //robot state
	
	//update state info
	int calX(int i);
	int calY(int i);
	int calIndex(int iX,int iY);
	void facingadj();
	
	//init
	void FirstSquare();
	void setMapSize(int m);
	
};

#endif