#include "renderer.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

std::mutex mutex;

const char * const trapBmpPath = "../BLU.bmp";
const char * const spFoodBmpPath = "../specialFood.BMP";

Renderer::Renderer(const std::size_t screen_width,
        const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height)
: screen_width(screen_width),
  screen_height(screen_height),
  grid_width(grid_width),
  grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, screen_width,
            screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    trapTexture = SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP(trapBmpPath));

    specialFoodTexture = SDL_CreateTextureFromSurface(sdl_renderer, SDL_LoadBMP(spFoodBmpPath));
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake,
        SDL_Point const &food,
        const std::shared_ptr<Trap> trap,
        const std::shared_ptr<Special_food> specialFood)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // Placing traps
    place_traps(trap);

    // Placing special food
    place_special_food(specialFood);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
    std::lock_guard<std::mutex> lock( mutex );
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::place_traps(const std::shared_ptr<Trap> trap) const
{
    std::lock_guard<std::mutex> lock( mutex );
    for ( auto cordinateItem : trap->getCoordinates() )
    {
        SDL_Rect trapElt;

        trapElt.w = screen_width / grid_width;
        trapElt.h = screen_height / grid_height;
        trapElt.x = cordinateItem.get_x_coord() * trapElt.w;
        trapElt.y = cordinateItem.get_y_coord() * trapElt.h;

        SDL_RenderCopy(sdl_renderer, trapTexture, NULL, &trapElt);
    }
}

void Renderer::place_special_food(const std::shared_ptr<Special_food> specialFood) const
{
    std::lock_guard<std::mutex> lock( mutex );
    for ( auto cordinateItem : specialFood->getCoordinates() )
    {
        SDL_Rect spFoodElt;

        spFoodElt.w = screen_width / grid_width;
        spFoodElt.h = screen_height / grid_height;
        spFoodElt.x = cordinateItem.get_x_coord() * spFoodElt.w;
        spFoodElt.y = cordinateItem.get_y_coord() * spFoodElt.h;

        SDL_RenderCopy(sdl_renderer, specialFoodTexture, NULL, &spFoodElt);
    }
}

