
class grid {
  public:
  //constructors and destructors
  grid();
  grid(int m);
  ~grid();
  
  //control
  setMapSize(int m);
  step(int facing);
  setMyLoc();
  //move(int facing, int distance);
  
  //state info
  getMapSize();
  getMyLoc();
  
  private:
    int m,n, facing;
};