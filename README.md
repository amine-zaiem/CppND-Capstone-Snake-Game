# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

This a capstone project submitted for the nanodegree (Udacity C++ Nanodegree). This project is not built from scratch. It was built based on the starter repo for the Capstone project in the Udacity C++ Nanodegree Program. 

When the game is started the user has 3 options :
1/ start new game consists on Starting the new game which can be abandoned by pressing the END key. 
2/ See the records. the user can see the olds records that are sored in a file.
3/ exit the game.
When the game is finished the player withh be asked to type his the name and the score is saved on a file that contains all records. 
The concept of the game is as follow:
The snake search for foods in a loop and  when eating food score increases.
The are many traps in the map that are generated randomly, if the snake position is on the trap the game will finish.
For every 5 foods eaten, a special food item appears for 10 seconds and if it is eaten it increases the speed, the score and also the number of traps in the map.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.