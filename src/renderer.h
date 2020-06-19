#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

#include "element.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake,
              SDL_Point const &food,
              const std::shared_ptr<Trap> trap,
              const std::shared_ptr<Special_food> specialFood);

  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // trap texture
  SDL_Texture *trapTexture;

  // special food texture
  SDL_Texture *specialFoodTexture;

  void place_traps(const std::shared_ptr<Trap> trap) const;
  void place_special_food(const std::shared_ptr<Special_food> specialFood) const;

//  void placeSpecialFood(const std::shared_ptr<Special_food> specialFood) const;

};

#endif
