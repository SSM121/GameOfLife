#include <iostream> // used to print each iteration. You know the standard input output stuff
#include <string>  //used to pseudo clear the screen
#include <atomic> //used to sync the 2 threads for this program
#include <thread> //one thread is handling the board. The other is simply waiting for a key to be pressed.
//this will signify the exit. This could be handled in different ways such as older windows headers but
//this is what I can come up with at the time. Perhaps 2.0 will have a better way of achieving this.
#include <cstdio> //used for getchar pause
#include <chrono> //used for timing
#include <random> //used to create a random starting board


/*********************************************************************************
 *Project: The Game of life
 *Summary: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *Implementation of Conway's game of life. This is simply displayed in a terminal
 *with O's representing "Alive" cells and .'s representing "Dead" cells. This is
 *merely a proof of concept and is not meant for any practical purpose. It may be
 *used under the GNU Public License found in the root of this repository.
 *There is no guarentee of this code and the author is free from all liabily there of.
 *
 *Inputs: None
 *Outputs: a lovely simple ascci board
 *
 *
 *
 *
 *
 *
 * *********************************************************************************/

#define WIDTH 70
#define HEIGHT 60

//I did not want to rely on an outside package for a simple project and wanted to avoid using system();



char Board [WIDTH] [HEIGHT]; //used as a global board. In v2 of this project I will implement a class so
// a global array will not be needed

void init_Board(); //Function prototype that will fill the board with all 0 or "Dead" cells

void run_Gen();//Function protoype for calculating the next genration and replacing it with the old.

void print_Board(); //Psedo clears the screen and prints the new board.

std::atomic<bool> done (false);//used to sync the threads.i

void board_Loop(); //Used for the thread running the board
//void wait(); //used for the loop waiting for response.

int Gen = 0; //used to keep track of all the generations
bool changed= true; //used to track if it is still changing
int main()
{
	std::thread board(board_Loop);
	std::cout << "enter char to continue" << std::endl;
	getchar();
	done = true;
	board.join();
	return 0;
}




void board_Loop()
{
	init_Board(); //initializes the board to all zeroes
	while(1) //generic game loop that runs until the other thread says it should join
	{
		print_Board(); //prints the board each loop around
		if(done) return; //exits when done is flagged as true.
		if(changed == false)
		{
			std::cout << "Game ended!";
			return;
		}
		std::this_thread::sleep_for (std::chrono::seconds(1)); //used to delay since we do want to
		//see the board.
		run_Gen();

	}

}


void init_Board()
{
std::random_device rd;
int q;
	for(int i = 0; i < WIDTH; ++i)
	{
		for(int j = 0; j < HEIGHT; ++j)
		{
			q = rd() % 2;
			if(q) Board[i][j] = 'O';
			else Board[i][j] = '.';
		}
	}
}


void print_Board()
{
	std::cout << std::string( 100, '\n' ) << "Current gen is:" << Gen << std::endl <<"Press a key to exit!\n";
        for(int i = 0; i < WIDTH; ++i)
        {
                for(int j = 0; j < HEIGHT; ++j)
                {
			std::cout << Board[i][j] << "  ";
                }
		std::cout << std::endl;
        }

}

void run_Gen()
{
				changed = false;
				Gen++;
				char copy[WIDTH][HEIGHT];

        for(int i = 0; i < WIDTH; ++i)
        {
                for(int j = 0; j < HEIGHT; ++j)
                {
									copy[i][j] = Board[i][j];
                }
        }
        for(int i = 0; i < WIDTH; ++i)
        {
                for(int j = 0; j < HEIGHT; ++j)
                {

										int neighbors = 0; // keeps track of alive neighbors
										for(int l = -1; l <=1; l++)//double for loop to check neighbors
										{
											for(int k = -1; k <=1; k++)
											{
												if(l == 0 && k == 0) break;
												if(copy[(i + l + WIDTH) % WIDTH][(j + k + HEIGHT) % HEIGHT] == 'O') neighbors++;
//checks if neighbors are alive and if so increment neighbor count The math is for wrap around
											}
										}
											if(copy[i][j] == 'O')//manages life cycle for an alive cell
											{
												//1: Any live cell with fewer than two live neighbours dies, as if by underpopulation. It will be changed
												//2: Any live cell with two or three live neighbours lives on to the next generation. Nothing is needed since this is not a state change
												//3: Any live cell with more than three live neighbours dies, as if by overpopulation. Again it causes a change.
												if((neighbors < 2) ||(neighbors > 3)) {changed= true; Board[i][j] = '.';}

											}
											else //manages dead cells
											{
												if(neighbors == 3) {Board[i][j] = 'O'; changed = true;}
											}
                }
        }
}
