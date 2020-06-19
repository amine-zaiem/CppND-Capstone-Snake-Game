#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <chrono>
#include <ctime>
#include <map>
#include "SDL.h"
#include "controller.h"
#include "element.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point specialFood;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;


  // Trap
  std::shared_ptr<Trap> _trap;
  void PlaceTraps();


// special food
  std::shared_ptr<Special_food> _special_food;
  std::map<int, int> PlaceSpecialFood();

  int score{0};

  void PlaceFood();
  //void PlaceSpecialFood();
  bool Update();
  bool isDivisibleBy5(std::string str);


  int _traps_numer, _specials_food_number;

 public:

   bool special_food_created;

   bool previous_special_food_created;

   std::map <int,int> spFoodPosition;

   std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
};

#endif
