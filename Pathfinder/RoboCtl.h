

class RoboCtl { 
  public:
    //Constructor and destructors
	 RoboCtl();
	 ~RoboCtl();
	 
	 //Movement Controls
	 bool RightTurn();
	 bool LeftTurn();
	 bool StepForward();
	 bool Reverse();
	 
	 //Status
	 int getFacing();
	 int getM();
	 int getN();
	 
	 private:
	   int facing;
	 
};