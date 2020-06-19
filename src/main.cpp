#include <iostream>

#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "MainMenu.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  bool startStatus = false;

  game::MainMenu main;
  main.welcoming_message();

  while( true )
  {
      while ( not startStatus )
      {

          startStatus = main.start();
          //std::cout << "exit status"<< main.exit_is_pressed ? "yes" : "no";
          if (main.exit_is_pressed == true)
          {
             std::cout<<"exit is pressed ... Quitting \n";
             return 0;
             break;
          }


      }



      startStatus = false;
      Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      Controller controller;
      Game game(kGridWidth, kGridHeight);
      game.Run(controller, renderer, kMsPerFrame);
      std::cout << "\n\nGame has terminated successfully!\n";
      std::cout << "Your Score: " << game.GetScore() << "\n";
      std::cout << "Size of the snake: " << game.GetSize() << "\n";

      game::MainMenu menu;
      menu.add_score( game.GetScore() );

  }
  return 0;
}
