#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "element.h"
#include "SDL.h"

#include "game.h"

const uint32_t NUMBER_OF_FOODS = 1;

std::mutex mutex_protection;

Game::Game(std::size_t grid_width, std::size_t grid_height)
: snake(grid_width, grid_height),
  engine(dev()),
  random_w(0, static_cast<int>(grid_width)),
  random_h(0, static_cast<int>(grid_height))
{

    // initialization
    special_food_created = false;
    previous_special_food_created = false;

    _traps_numer = random_w(engine);;
    _specials_food_number = NUMBER_OF_FOODS;

    _trap = std::shared_ptr<Trap>(new Trap());
    _special_food = std::shared_ptr<Special_food>(new Special_food());

    PlaceFood();
    PlaceTraps();
}

void Game::Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, snake);
        if (not Update() )
        {
            return;
        }

        renderer.Render(snake, food, _trap, _special_food);

        frame_end = SDL_GetTicks();


        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::PlaceFood()
{
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

/* a helper to place traps*/
void Game::PlaceTraps()
{
    std::lock_guard<std::mutex> lock( mutex_protection );
    int x, y;
    while (true)
    {
        /// Return if we meet the size requiremens.
        if (_traps_numer == _trap->get_element_ocurrence())
        {
            return;
        }

        // Generate x and y coordinate with random values
        x = random_w(engine);
        y = random_h(engine);

        // Check that the location is empty
        auto foodExistInThisLocation = food.x == x && food.y == y;

        if ( !snake.SnakeCell(x, y) && !foodExistInThisLocation )
        {
            _trap->create_element(Coordinate(x, y));
        }
    }
}

/* a helper to place special food*/
std::map<int, int> Game::PlaceSpecialFood()
{
    std::lock_guard<std::mutex> lock( mutex_protection );
    int x, y;
    std::map<int, int> response;
    while (true)
    {
        // Generate x and y coordinate with random values
        x = random_w(engine);
        y = random_h(engine);

        // Check that the location is empty
        auto foodExistInThisLocation = food.x == x && food.y == y;
        auto trapExistInThisLocation = _trap->element_is_of_type(Coordinate(x,y));

        if (!snake.SnakeCell(x, y) && !foodExistInThisLocation && !trapExistInThisLocation )
        {
            _special_food->create_element(Coordinate(x,y));
            response[x]=y;
            return response;
        }
    }

//    std::cout << "Quitting the the loop \n";
}


bool Game::Update()
{
    if (!snake.alive)
    {
        return true;
    }

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    /// Is a trap
    if (_trap->element_is_of_type(Coordinate(new_x, new_y)))
    {
        snake.alive = false;
        return false;
    }

    /// if a special food
    if (_special_food->element_is_of_type(Coordinate(new_x, new_y)))
    {
        snake.speed += 0.01;
        score = score + 6;
        _special_food->delete_element(Coordinate(new_x, new_y));
        PlaceTraps();
        return true;
    }

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y)
    {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();
        previous_special_food_created = false;

        snake.speed += 0.02;
    }

    if ( score % 5 == 0 && score > 1 && special_food_created == false && previous_special_food_created == false)
    {
        startTime = std::chrono::system_clock::now();
        std::string message;

        /// Place the special food;
        spFoodPosition = PlaceSpecialFood();
        special_food_created = true;
        previous_special_food_created = true;

        //      std::thread t([message]{
        //              //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //              std::cout<<"hello";
        //

        //
        //      });
        //      t.join();

        //timer_start(do_something, 1000);
    }
    endTime = std::chrono::system_clock::now();
    // DEbug    std::cout<<"duration : "<<std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime ).count();
    if ( std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime ).count() > 10000 && special_food_created == true)
    {


        std::cout<<"you have to delete";
        _special_food->delete_element(Coordinate(spFoodPosition.begin()->first,spFoodPosition.begin()->second));
        special_food_created = false;
    }

    return true;
}
// Function to find that number divisible
// by 5 or not. The function assumes that
// string length is at least one.
//bool Game::isDivisibleBy5(std::string str)
//{
//    int n = str.length();
//
//    return ( ((str[n-1]-'0') == 0) ||
//             ((str[n-1]-'0') == 5));
//}
int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

