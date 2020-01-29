//g++ gameOfLife2.cpp -pthread -std=c++14 -lGLU -lGL -lglut -lX11 -lpng -g -o test

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random> //used to create a random starting board
#include <chrono>
#define WIDTH 100 //multiply by scalar to get full size this is scaled size
#define HEIGHT 70 //multiply by scalar to get full size this is scaled size
#define SCALAR 10
int array[WIDTH][HEIGHT];
void run_Gen();
class gameOfLife : public olc::PixelGameEngine
{
public:
  	gameOfLife()
    {
		sAppName = "Game_Of_Life";
	  }
  public:
    	bool OnUserCreate() override
	{
    std::random_device rd;
		// Called once at the start, so create things here
    		for (int x = 0; x < ScreenWidth(); x++)
    			for (int y = 0; y < ScreenHeight(); y++)
    				array[x][y] = rd() % 2;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

    		std::this_thread::sleep_for (std::chrono::seconds(1));
		// called once per frame
    run_Gen();
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				if(array[x][y]) Draw(x, y, olc::DARK_RED);
        else Draw(x, y, olc::DARK_CYAN);
		return true;
	}
};


void run_Gen()
{


				char copy[WIDTH][HEIGHT];

        for(int i = 0; i < WIDTH; ++i)
        {
                for(int j = 0; j < HEIGHT; ++j)
                {
									copy[i][j] = array[i][j];
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
												if(copy[(i + l + WIDTH) % WIDTH][(j + k + HEIGHT) % HEIGHT] == 1) neighbors++;
//checks if neighbors are alive and if so increment neighbor count The math is for wrap around
											}
										}
											if(copy[i][j] == 1)//manages life cycle for an alive cell
											{
												//1: Any live cell with fewer than two live neighbours dies, as if by underpopulation. It will be changed
												//2: Any live cell with two or three live neighbours lives on to the next generation. Nothing is needed since this is not a state change
												//3: Any live cell with more than three live neighbours dies, as if by overpopulation. Again it causes a change.
												if((neighbors < 2) ||(neighbors > 3)) { array[i][j] = 0;}

											}
											else //manages dead cells
											{
												if(neighbors == 3) {array[i][j] = 1; }
											}
                }
        }
}

int main()
{
	gameOfLife demo;
	if (demo.Construct(WIDTH, HEIGHT, SCALAR, SCALAR))
		demo.Start();

	return 0;
}
