
#ifndef SS_UI_MAIN_MENU_H_
#define SS_UI_MAIN_MENU_H_

#include <iostream>
#include <functional>
//#include <GameMenu/GameMenu.h>
//#include <SFML/Graphics.hpp>

namespace game {

    /**
     * Metadata node definition
     */
    struct Metadata_node
    {
       std::string            metadata_id;
       std::string              metadata_type;

       Metadata_node(
          const std::string &metaId,
          const std::string   &MetaType):
              metadata_id(metaId),
              metadata_type(MetaType)
       {}

       Metadata_node()
       {}

    };

//    typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> compare;
//
//    compare compTwoElmnt =
//        [](std::pair<std::string, uint32_t> elem1, std::pair<std::string, uint32_t> elem2) {
//          return elem1.second > elem2.second;
//        };
    typedef std::pair<std::string,int> pair;


    class MainMenu
    {
    public:
        std::map<std::string, uint32_t> scores_list;
        bool exit_is_pressed = false;

        //void start(sf::RenderWindow *w);
    private:

        //gmenu::MenuItem menuItems[4];
        //gmenu::Action *action[4];

//        char MenuText[4][15] = {
  //          "Start",
    //        "High Score",
      //      "Options",
        //    "Exit"
        //};
    public:
        void welcoming_message();
        bool start();
        void add_score(const uint32_t &score) ;

    };



}

#endif // !SS_UI_MAIN_MENU_H_
