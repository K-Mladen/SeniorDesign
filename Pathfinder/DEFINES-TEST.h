#ifdef TESTMODE_ON //define TESTMODE_ON in .ino file only in order to enable for whole robot
//TESTCASE shall be an array of numbers in brackets, terminated by -1, which includes at least one 0 to mark the end of the maze.
struct test_globals {
  int iter;
  test_globals(){
	  iter = 0;
  }
};

test_globals tg;

//Uncomment any of these that are appropriate
  #define NOROBOT

//Uncomment only one of the following lines for the desired test case.
  //#define CPTEST5X5MAZESIM
  //#define CPTEST7X7SNAKESNLADDERS
  //#define CPTESTGIVENCP5X5  
  #define TESTTURNS  


  #ifdef CPTEST5X5MAZESIM
    // in this case, the robot follows the maze inserted on the 10/3 page in my lab notebook.
	// It should return the following critical path: {21,22,17,18,13,8,3,4,9,10,5,0 (NULL)}
	#undef TESTCASE
	#define TESTCASE {21,22,23,24,25,20,25,24,19,24,23,22,17,18,13,14,15,14,13,8,3,4,9,10,5,0,5,10,9,4,3,2,1,6,1,2,3,8,13,18,17,12,7,12,11,12,17,22,21,16,21,-1}
  #endif
  
  #ifdef CPTEST7X7SNAKESNLADDERS
    //in this case, the robot moves across all squares of the 7x7 grid, right to left, up, left to right, up, repeat
	//Objective is to find the critical path -- which is identical to the given path
	#undef TESTCASE
    #define TESTCASE {43,44,45,46,47,48,49,42,41,40,39,38,37,36,29,30,31,32,33,34,35,28,27,26,25,24,23,22,15,16,17,18,19,20,21,14,13,12,11,10,9,8,1,2,3,4,5,6,7,0,-1}
  #endif
	
  #ifdef CPTESTGIVENCP5X5
    //Critical path is already set -- Can the robot return the correct turn sequence?
	// {Left, Right, Left, Right, Forward, Forward, Forward, Left, Left, Right, Right, Forward, (Forward)}
    #undef TESTCASE
    #define TESTCASE {21,22,17,18,13,8,3,4,9,10,5,0}
  #endif

  #ifdef TESTTURNS
    // Can the robot track which square it is in from the given turn sequence?
	// Result should be {21,22,17,18,13,8,3,4,9,10,5,0} for 5x5
    #undef TESTCASE
    #define _L_ 0
	#define _F_ 1
	#define _R_ 2
	#define TESTCASE {_L_,_R_,_L_,_R_,_F_,_F_,_F_,_L_,_L_,_R_,_R_,_F_,_F_}
  #endif


#undef TESTMODE_ON //This precompiler code will only run once  
#endif
