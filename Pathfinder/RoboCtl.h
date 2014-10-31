

class RoboCtl: private RoboState, private CrPath, private Driver
               private Sensors::Pings, private Sensors::RS{ 
  public:
    //Constructor and destructors
	 RoboCtl();
	 ~RoboCtl();
	 
	 //Decision Making
	 bool Setcourse
	 
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