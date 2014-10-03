
#ifndef RSTATE
#define RSTATE

class RoboState {
  public:
  //constructors and destructors
  RoboState();
  RoboState(int m);
  ~RoboState();
  
  //control
  setMapSize(int m);
  step(int facing);
  FirstSquare();
  //move(int facing, int distance);
  
  //state info
  getMapSize();
  getX();
  getY();
  getIndex();
  
  private:
    int n,entry, x,y,facing,index;
	calX(int i);
	calY(int i);
	calN(int iX,int iY);
};

#endif