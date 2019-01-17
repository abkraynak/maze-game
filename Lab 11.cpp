#include "library.h"

/*  PLAYER INSTRUCTIONS
 *  -----------------------------
 *  To play, use WASD to move.
 *  R for auto mode
 *  M to switch back to manual
 *  Q at any time to quit program
 *
 *  Player is the pacman
 *  Enemy is the red thing
 *  Cherries are the finish
 */


void main()
{
	// hide_console();
	
	// Image files
	image * finish = image_from_file("finish.bmp");
	image * robot = image_from_file("robot.bmp");
	image * robotdown = image_from_file("robotdown.bmp");
	image * robotleft = image_from_file("robotleft.bmp");
	image * robotright = image_from_file("robotright.bmp");
	image * robotup = image_from_file("robotup.bmp");
	image * enemy = image_from_file("enemy.gif");
	

	/*  Sets up maze window
	 *  Determined by number of rows and columns
	 *  Box size can be easily modified
	 *  --------------------------------------------
	 *  maze.txt
	 *  -- mazeRows = 11;
	 *  -- mazeColumns = 31;
	 *  -- boxSize = 30;
	 *  -- robotSize = 20;
	 *  -- enemySize = 20;
	 *  --------------------------------------------
	 *  maze2.txt 
	 *  -- mazeRows = 24;
	 *  -- mazeColumns = 61;
	 *  -- boxSize = 15;
	 *  -- robotSize = 10;
	 *  -- enemySize = 10;
	 *  --------------------------------------------
	 *  Probably shouldn't try changing the file
	 *  Auto mode works but manual will crash maze2
	 *  But if you must then make the adjustments here
	 */

	// Maze dimensions
	const int mazeRows = 11;
	const int mazeColumns = 31;
	const int boxSize = 30;
	const int robotSize = 20;
	const int enemySize = 20;

	// Auto Mode Speed
	const double autoKeyPressWait = 0;
	const double autoWaitTime = 0;

	// Window dimensions are determined by maze elements
	int windowWidth = mazeColumns * boxSize;
	int windowHeight = mazeRows * boxSize + 40; // The +40 is for the display screen at the bottom

	// Makes window and caption
	make_window(windowWidth, windowHeight);
	set_caption("Maze Game");
	
	// Makes the whole screen the dark-dark grey
	fill_rectangle(0, 0, windowWidth, windowHeight, make_color_int(70, 70, 70));
	
	// Makes the black display screen
	fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
	
	// Writes the text at bottom
	set_pen_color(color::white);
	set_font_size(20);
	move_to(20, windowHeight-20);
	write_string("[Q] Quit", direction::east);
	move_to(110, windowHeight-20);
	write_string("[R] Auto Mode", direction::east);
	
	// Creates the empty array called arr
	string arr[100] = {""};
	ifstream fin;

	// Make changes here for file name
	fin.open("maze.txt");

	// Checks if the file opened properly
	if (fin.fail())
	{
		cout << "Error opening file";
		exit(1);
	}

	// Sets up all the needed variables for calculations
	int startx; // pixel x-value
	int starty; // pixel y-value
	int startxbox; // box number value
	int startybox; // box number value
	int finishx; // pixel x-value
	int finishy; // pixel y-value
	int finishxbox; // box number value
	int finishybox; // box number value
	int enemyx; // pixel x-value
	int enemyy; // pixel y-value
	int enemyxbox; // box number value
	int enemyybox; // box number value
	
	for(int x = 0; x < mazeRows; x++)
	{
		getline(fin, arr[x]);
		for(int y = 0; y < mazeColumns; y++)
		{
			if (arr[x][y] =='#') // Wall
			{
				// Draws the wall box
				set_pen_color(color::black);
				fill_rectangle(y*boxSize, x*boxSize, boxSize, boxSize);
				set_pen_color(color::dark_grey);
				fill_rectangle(y*boxSize+1, x*boxSize+1, boxSize-2, boxSize-2);
			}
			else if (arr[x][y] ==' ') // Open space
			{
				// Draws the open space box
				set_pen_color(color::black);
				fill_rectangle(y*boxSize, x*boxSize, boxSize, boxSize);
				set_pen_color(color::white);
				fill_rectangle(y*boxSize+1, x*boxSize+1, boxSize-2, boxSize-2);
			}
			else if (arr[x][y] =='+') // Starting point
			{
				// Stores both the pixel values and the
				// box values in these variables
				startx=(boxSize*y)+1;
				starty=(boxSize*x)+1;
				startxbox = x;
				startybox = y;

				// Draws the starting point box
				set_pen_color(color::black);
				fill_rectangle(y*boxSize, x*boxSize, boxSize, boxSize);
				draw_image(robotright, startx, starty);
				//set_pen_color(color::white);
				//fill_rectangle(y*boxSize+1, x*boxSize+1, boxSize-2, boxSize-2);
			}
			else if (arr[x][y] =='$') // Ending point
			{
				// Stores both the pixel values and the
				// box values in these variables
				finishx=(boxSize*y)+1;
				finishy=(boxSize*x)+1;
				finishxbox = x;
				finishybox = y;

				// Draws the ending point box
				set_pen_color(color::black);
				fill_rectangle(y*boxSize, x*boxSize, boxSize, boxSize);
				draw_image(finish, y*boxSize + 1, x*boxSize + 1);
				//set_pen_color(color::green);
				//fill_rectangle(y*boxSize+1, x*boxSize+1, boxSize-2, boxSize-2);
			}
			else if (arr[x][y] =='E') // Enemy 
			{
				// Stores both the pixel values and the
				// box values in these variables
				enemyx = (boxSize*y) + 1;
				enemyy = (boxSize*x) + 1;
				enemyxbox = x;
				enemyybox = y;

				// Draws the enemy box
				set_pen_color(color::black);
				fill_rectangle(y*boxSize, x*boxSize, boxSize, boxSize);
				draw_image(enemy, enemyx, enemyy);
				// set_pen_color(color::white);
				// fill_rectangle(y*boxSize+1, x*boxSize+1, boxSize-2, boxSize-2);
				//move_to(enemyx, enemyy);
				//set_pen_width(enemySize);
				//set_pen_color(color::red);
				//draw_point();
			}
		}
	}
	// Closes file
	fin.close();

	// Draws the robot on the start position
	//draw_image(robot, startx, starty);
	//set_pen_width(robotSize);
	//set_pen_color(color::blue);
	//draw_point(startx, starty);

  
	/*  startx/starty are the actual x/y pixel values on window.
	 *  startx/starty are assigned to the (x,y) coordinates of
	 *  the center of the box with '+' (starting box).
	 *  -------------------------------------------------------------
	 *  robotx/roboty are the actual x/y pixel values on window.
	 *  robotx/roboty are initially assigned to startx and starty.
	 *  robotx/roboty will be updated each time that the robot moves.
	 */
	int robotx = startx; int roboty = starty;


	/*  startxbox/startybox are the integer x/y values of the
	 *  position in the array of the box with '+' (starting box).
	 *  -------------------------------------------------------------
	 *  prevx/prevy are the integer x/y vales of the
	 *  positions in the array of the box the robot is currently in.
	 *  prevx/prevy check if there's a # in the array in the 
	 *  box that it wants to move into.
	 *  prevx/prevy will be updated each time that the robot moves.
	 */
	int prevx = startxbox; int prevy = startybox; 


	/*  enemyxbox/enemyybox are the integer x/y values of the
	 *  position in the array of the box with 'E' (enemy box).
	 *  -------------------------------------------------------------
	 *  enemyprevx/enemyprevy are the integer x/y vales of the
	 *  positions in the array of the box the enemy is currently in.
	 *  enemyprevx/enemyprevy check if there's a # in the array in the 
	 *  box that it wants to move into.
	 *  enemyprevx/enemyprevy will be updated each time that the enemy moves.
	 */
	int enemyprevx = enemyxbox; int enemyprevy = enemyybox;

	while(true)
	{
		char c = wait_for_key_typed();

		// Resets the black display screen after each move.
		fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
		
		if (c == 's') // Down Arrow
		{
			if (arr[prevx + 1][prevy] == '#')
			{
				// There is a wall in this box, cannot move there
				// Do nothing
			}
			else
			{
				// Robot moves first
				// Then the enemy moves
				// If their positions are the same, game over

				// Robot's movement
				cout << "You moved down!\n";	
		
				// Draw over old position in white
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);

				// Move to new position and draw point in blue
				// Reassign the variables
				set_pen_color(color::blue);
				roboty = roboty + boxSize;
				move_to(robotx, roboty);
				draw_image(robotdown, robotx, roboty);
				prevx = prevx + 1;

				// Puts the previous movement into the array
				if (arr[prevx][prevy] != 'X')
				{
					// Puts an R in the current position in the array
					arr[prevx][prevy] = 'D';
				}

				// Enemy's movement
				while(true)
				{
					int enemyAutoMovement = random_in_range(1, 4);
					
					if (enemyAutoMovement == 1) // Enemy moves down
					{
						if (arr[enemyprevx + 1][enemyprevy] == '#')
						{
							// Nothing because can't move there
							// Re-run the loop with newly generated value
						}
						else
						{
							// Enemy's movement down
							cout << "Enemy moved down!\n";	
							if ((robotx == enemyx) && (roboty == (enemyy + boxSize)))
							{
								cout << "You lost!";

								// Shows it on the maze
								move_to(enemyx, enemyy);
								set_pen_color(color::white);
								draw_point();
								set_pen_color(color::red);
								enemyy = enemyy + boxSize;
								move_to(enemyx, enemyy);
								draw_point();

								// Shows it on the black display
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								move_to(enemyx, enemyy);
								set_pen_color(color::white);
								fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
								
								enemyy = enemyy + boxSize;
								move_to(enemyx, enemyy);
								draw_image(enemy, enemyx, enemyy);
								enemyprevx = enemyprevx + 1;
								break;
							}
						}
					
					}
					else if (enemyAutoMovement == 2)
					{
						// Right
						if (arr[enemyprevx][enemyprevy + 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved right!\n";	
							move_to(enemyx, enemyy);
							
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyx = enemyx + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 3)
					{
						// Up 
						if (arr[enemyprevx - 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movements
							cout << "Enemy moved up!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyy = enemyy - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 4)
					{
						// Left
						if (arr[enemyprevx][enemyprevy - 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved left!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyx = enemyx - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
		else if (c == 'd')
		{
			// Right Arrow
			if (arr[prevx][prevy + 1] == '#')
			{
				
			}
			else
			{
				// Robot's movements
				cout << "You moved right!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				robotx = robotx + boxSize;
				move_to(robotx, roboty);
				draw_image(robotright, robotx, roboty);
				prevy = prevy + 1;

				// Puts the previous movement into the array
				if (arr[prevx][prevy] != 'X')
				{
					// Puts an R in the current position in the array
					arr[prevx][prevy] = 'R';
				}

				// Enemy's movement
				while(true)
				{
					int enemyAutoMovement = random_in_range(1, 4);
					if (enemyAutoMovement == 1)
					{
						// Down
						if (arr[enemyprevx + 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved down!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyy = enemyy + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					
					}
					else if (enemyAutoMovement == 2)
					{
						// Right
						if (arr[enemyprevx][enemyprevy + 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved right!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyx = enemyx + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 3)
					{
						// Up 
						if (arr[enemyprevx - 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movements
							cout << "Enemy moved up!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyy = enemyy - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 4)
					{
						// Left
						if (arr[enemyprevx][enemyprevy - 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved left!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyx = enemyx - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
		else if (c == 'w')
		{
			// Up Arrow
			if (arr[prevx - 1][prevy] == '#')
			{
				
			}
			else
			{
				cout << "You moved up!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				roboty = roboty - boxSize;
				move_to(robotx, roboty);
				draw_image(robotup, robotx, roboty);
				prevx = prevx - 1;

				// Puts the previous movement into the array
				if (arr[prevx][prevy] != 'X')
				{
					// Puts an R in the current position in the array
					arr[prevx][prevy] = 'U';
				}

				// Enemy's movement
				while(true)
				{
					int enemyAutoMovement = random_in_range(1, 4);
					if (enemyAutoMovement == 1)
					{
						// Down
						if (arr[enemyprevx + 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved down!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyy = enemyy + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					
					}
					else if (enemyAutoMovement == 2)
					{
						// Right
						if (arr[enemyprevx][enemyprevy + 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved right!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							
							enemyx = enemyx + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 3)
					{
						// Up 
						if (arr[enemyprevx - 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movements
							cout << "Enemy moved up!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyy = enemyy - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 4)
					{
						// Left
						if (arr[enemyprevx][enemyprevy - 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved left!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyx = enemyx - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
		else if (c == 'a')
		{
			// Left Arrow
			if (arr[prevx][prevy - 1] == '#')
			{
				
			}
			else
			{
				cout << "You moved left!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				robotx = robotx - boxSize;
				move_to(robotx, roboty);
				draw_image(robotleft, robotx, roboty);
				prevy = prevy - 1;

				// Puts the previous movement into the array
				if (arr[prevx][prevy] != 'X')
				{
					// Puts an R in the current position in the array
					arr[prevx][prevy] = 'L';
				}

				// Enemy's movement
				while(true)
				{
					int enemyAutoMovement = random_in_range(1, 4);
					if (enemyAutoMovement == 1)
					{
						// Down
						if (arr[enemyprevx + 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved down!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyy = enemyy + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					
					}
					else if (enemyAutoMovement == 2)
					{
						// Right
						if (arr[enemyprevx][enemyprevy + 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved right!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyx = enemyx + boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy + 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 3)
					{
						// Up 
						if (arr[enemyprevx - 1][enemyprevy] == '#')
						{
				
						}
						else
						{
							// Enemy's movements
							cout << "Enemy moved up!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyy = enemyy - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevx = enemyprevx - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
					else if (enemyAutoMovement == 4)
					{
						// Left
						if (arr[enemyprevx][enemyprevy - 1] == '#')
						{
				
						}
						else
						{
							// Enemy's movement
							cout << "Enemy moved left!\n";	
							move_to(enemyx, enemyy);
							fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
							enemyx = enemyx - boxSize;
							move_to(enemyx, enemyy);
							draw_image(enemy, enemyx, enemyy);
							enemyprevy = enemyprevy - 1;
							if (robotx == enemyx && roboty == enemyy)
							{
								cout << "You lost!";
								fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
								move_to(windowWidth/2, windowHeight-20);
								set_pen_color(color::white);
								set_font_size(30);
								write_string("You lost!", direction::center);
								return;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
		
		else if (c == 'b')
		{
			if (arr[prevx][prevy] == 'R')
			{
				// Move left
				// put an x in the old position.

				// Robot's movement
				cout << "You moved back left!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				// Move to new position and draw image
				// Reassigns the variables
				robotx = robotx - boxSize;
				move_to(robotx, roboty);
				draw_image(robotleft, robotx, roboty);

				// Puts an X in the current position in the array
				arr[prevx][prevy] = 'X';

				prevy = prevy - 1;
			}
			else if (arr[prevx][prevy] == 'L')
			{
				// Move right
				// put an x in the old position.

				// Robot's movements
				cout << "You moved back right!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				// Move to new position and draw image
				// Reassigns the variables
				robotx = robotx + boxSize;
				move_to(robotx, roboty);
				draw_image(robotright, robotx, roboty);

				// Puts an R in the current position in the array
				arr[prevx][prevy] = 'X';

				prevy = prevy + 1;
			}
			else if (arr[prevx][prevy] == 'U')
			{
				// Move down
				// put an x in the old position.
				
				// Robot's movement
				cout << "You moved back down!\n";	
		
				// Draw over old position in white
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);

				// Move to new position and draw image
				// Reassign the variables
				set_pen_color(color::blue);
				roboty = roboty + boxSize;
				move_to(robotx, roboty);
				draw_image(robotdown, robotx, roboty);

				// Puts the previous movement into the array
				arr[prevx][prevy] = 'X';

				prevx = prevx + 1;
			}
			else if (arr[prevx][prevy] == 'D')
			{
				// Move up
				// put an x in the old position.

				// Robot's movement
				cout << "You moved back up!\n";
				move_to(robotx, roboty);
				fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
				
				roboty = roboty - boxSize;
				move_to(robotx, roboty);
				draw_image(robotup, robotx, roboty);

				// Puts an X in the current position in the array
				arr[prevx][prevy] = 'X';

				prevx = prevx - 1;
			}
			else
			{
				cout << "Cannot move back.\n";
			}
		}
		else if (c == 'r')
		{
			/*  AUTOMATIC MODE
			 *  --------------------------------
			 *  To go back to manual, press M.
			 *  To quit the program, press Q.
			 */

			// Shows "Auto Mode On" on display
			fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
			set_pen_color(color::white);
			set_font_size(30);
			move_to(windowWidth/2, windowHeight-20);
			write_string("Auto Mode On", direction::center);
			set_font_size(20);
		
			// Changes "[R] Auto Mode" to "[M] Manual Mode"
			// on the bottom display.
			cout << "Automatic Mode started\n";
			fill_rectangle(110, windowHeight-40, 190, 40, make_color_int(70, 70, 70));
			move_to(110, windowHeight-20);
			set_pen_color(color::white);
			write_string("[M] Manual Mode", direction::east);
			move_to(startx, starty);
			while(true)
			{
				char d = wait_for_key_typed(autoKeyPressWait);
				if (d == 'm')
				{
					// Ends Automatic Mode
					// Changes "[M] Manual Mode" to "[A] Automatic Mode"
					// on the bottom display.
					cout << "Automatic Mode ended\n";
					fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
					fill_rectangle(110, windowHeight-40, 190, 40, make_color_int(70, 70, 70));
					move_to(110, windowHeight-20);
					set_pen_color(color::white);
					write_string("[R] Auto Mode", direction::east);
					move_to(robotx, roboty);
					break;
				}
				else if (d == 'q')
				{
					// Ends program
					cout << "Game ended\n";
					fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
					move_to(windowWidth/2, windowHeight-20);
					set_pen_color(color::white);
					set_font_size(30);
					write_string("Game ended", direction::center);
					hide_window();
					return;
				}
				else
				{
				// New Lab 12 Auto Mode
					// Check if theres a wall
					// Check if theres an x
					// Check if theres an unexplored square.
						// If so, move there
						// If multiple, pick one at random
							// If none, retrace the steps

					// Enemy's new movement
						// Search the array for the position of the robot each time
						// Move in its direction	
	
					/*
					if (arr[prevx + 1][prevy] == '#' && arr[prevx - 1][prevy] == '#' && arr[prevx][prevy + 1] == '#' && arr[prevx][prevy - 1] == '#')
					{
						// Do nothing because there is a wall in every direction
					}
					else if (arr[prevx + 1][prevy] == '#' && arr[prevx - 1][prevy] == '#' && arr[prevx][prevy + 1] == '#' && arr[prevx][prevy - 1] == '#')
					{
						
					}
					*/













					int autoDecision = random_in_range(1,4);
					if (autoDecision == 1)
					{
						// Down Arrow
						if (arr[prevx + 1][prevy] == '#' || arr[prevx + 1][prevy] == 'X')
						{
					
						}
						else
						{
							// Robot's Movement
							cout << "AUTO Down arrow pressed\n";
							move_to(robotx, roboty);	
							fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
							
							roboty = roboty + boxSize;
							move_to(robotx, roboty);
							draw_image(robotdown, robotx,roboty);
							prevx = prevx + 1;

							// Enemy's movement
							while(true)
							{
								int enemyAutoMovement = random_in_range(1, 4);
								if (enemyAutoMovement == 1)
								{
									// Down
									if (arr[enemyprevx + 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved down!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 2)
								{
									// Right
									if (arr[enemyprevx][enemyprevy + 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved right!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 3)
								{
									// Up 
									if (arr[enemyprevx - 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movements
										cout << "Enemy moved up!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx - 1;
										break;
									}
								}
								else if (enemyAutoMovement == 4)
								{
									// Left
									if (arr[enemyprevx][enemyprevy - 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved left!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy - 1;
										break;
									}
								}
							}
							wait(autoWaitTime);
						}
					}
					else if (autoDecision == 2)
					{
						// Right Arrow
						if (arr[prevx][prevy + 1] == '#' || arr[prevx][prevy + 1] == 'X')
						{
					
						}
						else
						{
							// Robot's movement
							cout << "AUTO Right arrow pressed\n";
							move_to(robotx, roboty);
							fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
							robotx = robotx + boxSize;
							move_to(robotx, roboty);
							draw_image(robotright, robotx, roboty);
							prevy = prevy + 1;

							// Enemy's movement
							while(true)
							{
								int enemyAutoMovement = random_in_range(1, 4);
								if (enemyAutoMovement == 1)
								{
									// Down
									if (arr[enemyprevx + 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved down!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 2)
								{
									// Right
									if (arr[enemyprevx][enemyprevy + 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved right!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 3)
								{
									// Up 
									if (arr[enemyprevx - 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movements
										cout << "Enemy moved up!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx - 1;
										break;
									}
								}
								else if (enemyAutoMovement == 4)
								{
									// Left
									if (arr[enemyprevx][enemyprevy - 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved left!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy - 1;
										break;
									}
								}
							}
							wait(autoWaitTime);
						}
					}
					else if (autoDecision == 3)
					{
						// Up Arrow
						if (arr[prevx - 1][prevy] == '#' || arr[prevx - 1][prevy] == 'X')
						{
					
						}
						else
						{
							// Robot's movement
							cout << "AUTO Up arrow pressed\n";
							move_to(robotx, roboty);
							fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
							roboty = roboty - boxSize;
							move_to(robotx, roboty);
							draw_image(robotup, robotx, roboty);
							prevx = prevx - 1;

							// Enemy's movement
							while(true)
							{
								int enemyAutoMovement = random_in_range(1, 4);
								if (enemyAutoMovement == 1)
								{
									// Down
									if (arr[enemyprevx + 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved down!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 2)
								{
									// Right
									if (arr[enemyprevx][enemyprevy + 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved right!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 3)
								{
									// Up 
									if (arr[enemyprevx - 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movements
										cout << "Enemy moved up!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx - 1;
										break;
									}
								}
								else if (enemyAutoMovement == 4)
								{
									// Left
									if (arr[enemyprevx][enemyprevy - 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved left!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy - 1;
										break;
									}
								}
							}
							wait(autoWaitTime);
						}
					}
					else if (autoDecision == 4)
					{
						// Left Arrow
						if (arr[prevx][prevy - 1] == '#' || arr[prevx][prevy - 1] == 'X')
						{
					
						}
						else
						{
							// Robot's movement
							cout << "AUTO Left arrow pressed\n";
							move_to(robotx, roboty);
							fill_rectangle(robotx, roboty, boxSize-2, boxSize-2, color::white);
							robotx = robotx - boxSize;
							move_to(robotx, roboty);
							draw_image(robotleft, robotx, roboty);
							prevy = prevy - 1;

							// Enemy's movement
							while(true)
							{
								int enemyAutoMovement = random_in_range(1, 4);
								if (enemyAutoMovement == 1)
								{
									// Down
									if (arr[enemyprevx + 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved down!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy + boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx + 1;
										break;
									}
								}
								else if (enemyAutoMovement == 2)
								{
									// Right
									if (arr[enemyprevx][enemyprevy + 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved right!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
									move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy + 1;
											enemyx = enemyx + boxSize;
										break;
									}
								}
								else if (enemyAutoMovement == 3)
								{
									// Up 
									if (arr[enemyprevx - 1][enemyprevy] == '#')
									{
				
									}
									else
									{
										// Enemy's movements
										cout << "Enemy moved up!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyy = enemyy - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevx = enemyprevx - 1;
										break;
									}
								}
								else if (enemyAutoMovement == 4)
								{
									// Left
									if (arr[enemyprevx][enemyprevy - 1] == '#')
									{
				
									}
									else
									{
										// Enemy's movement
										cout << "Enemy moved left!\n";	
										move_to(enemyx, enemyy);
										fill_rectangle(enemyx, enemyy, boxSize-2, boxSize-2, color::white);
										enemyx = enemyx - boxSize;
										move_to(enemyx, enemyy);
										draw_image(enemy, enemyx, enemyy);
										enemyprevy = enemyprevy - 1;
										break;
									}
								}
							}
							wait(autoWaitTime);
						}
					}
					if (robotx == finishx && roboty == finishy)
					{
						move_to(windowWidth/2, windowHeight-20);
						set_pen_color(color::white);
						set_font_size(30);
						write_string("Completed!", direction::center);
						break;
					}
					if (robotx == enemyx && roboty == enemyy)
					{
						move_to(windowWidth/2, windowHeight-20);
						set_pen_color(color::white);
						set_font_size(30);
						write_string("Game Over!", direction::center);
						break;
					}
				}
			}	
		}
		else if (c == 'q')
		{
			// Quit
			cout << "Game ended\n";
			fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
			move_to(windowWidth/2, windowHeight-20);
			set_pen_color(color::white);
			set_font_size(30);
			write_string("Game ended", direction::center);
			hide_window();
			return;
		}

		
		// Testing the array
		for(int a=0; a<mazeRows; a++)
		{
			for(int b=0; b<mazeColumns; b++)
			{
				cout << arr[a][b];
			}
			cout << endl;
		}
		

		if (robotx == finishx && roboty == finishy)
		{
			cout << "You won!";
			fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
			move_to(windowWidth/2, windowHeight-20);
			set_pen_color(color::white);
			set_font_size(30);
			write_string("Completed!", direction::center);

			for(int a=0;a<mazeRows; a++)
			{
				for(int b=0; b<mazeColumns; b++)
				{
					cout << arr[a][b];
				}
				cout << endl;
			}

			wait(1);
			hide_window();
			break;
		}
		if (robotx == enemyx && roboty == enemyy)
		{
			cout << "You lost!";
			fill_rectangle(300, windowHeight-40, windowWidth-600, 40, color::black);
			move_to(windowWidth/2, windowHeight-20);
			set_pen_color(color::white);
			set_font_size(30);
			write_string("You lost!", direction::center);
			break;
		}
	}
}