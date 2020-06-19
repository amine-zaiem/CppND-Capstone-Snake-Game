#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <exception>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>

#include "MainMenu.h"

using namespace std;

/** Game repository */
const char * const GAME_REPOSITORY = "../";

/** RECORDS HISTORY FILE PATH */
const char * const HISTORY_RECORDS = "records_history.txt";


bool sortedVect(
        const std::pair<std::string, uint32_t> &a,
        const std::pair<std::string, uint32_t> &b
        )
{
  return ( a.second > b.second );
}

void game::MainMenu::welcoming_message()
{
    cout << " ######################################################################################################\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****  **********  ****      ****   ********      ******      *****   ******   ***       ************#\n";
    cout << " #****  **********  ****  ********   *******   ********   ****   ***  *  **  *  ***  *****************#\n";
    cout << " #****  ****  ****  ****      ****   ******   ********   ******   **  **   ***  ***       ************#\n";
    cout << " #*****  **  *  *  *****  ********   *******   ********   ****   ***  ********  ***  *****************#\n";
    cout << " #******  *****  *******      ****       ****      *****       *****  ********  ***       ************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #*************************           ********      **************************************************#\n";
    cout << " #****************************    **********   ****   ************************************************#\n";
    cout << " #****************************    *********   ******   ***********************************************#\n";
    cout << " #****************************    **********   ****   ************************************************#\n";
    cout << " #****************************    ************      **************************************************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****     **   *****  *****   *****  ***  **     *******     *******   *****  *******  ****      ****#\n";
    cout << " #****  ** **    ****  ***  ***  ***  *  ****  *********  **********  *  ***  *  **  **  ***  ********#\n";
    cout << " #*****   ***  **  **  **  *****  **    *****     ******  *********  ***  **  ***   ***  ***      ****#\n";
    cout << " #**** **  **  ***  *  **         **  **  ***  *********  ****   **       **  *********  ***  ********#\n";
    cout << " #*****    **  ****    **  *****  **  ***  **     *******      ****  ***  **  *********  ***      ****#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " #****************************************************************************************************#\n";
    cout << " ######################################################################################################\n\n";
}
bool game::MainMenu::start()
{

    cout << " \n\nPLEASE PRESS ...\n" << "\n";
    cout << " 1. START NEW GAME" << "\n";
    cout << " 2. TOP SCORES" << "\n";
    cout << " 3. EXIT\n" << "\n";
    cout << "CHOSEN : ";

    uint16_t pressedKey;
    //std::cin >> pressedKey;

    while ( not ( cin >> pressedKey ) )
    {
        cin.clear();

        while ( cin.get() != '\n' )
        {
            continue;
        }

        // if not a number try again:
        cout << "\n Only number is allowed. Please enter correct number -->  ";

    }
    if ( not ( pressedKey == 1 || pressedKey == 2 || pressedKey == 3 ) )
    {
        cout << "\nPlease enter 1 or 2 or 3, try again..."
                  << "\n\n";
        return false;
    }

    switch (pressedKey)
    {

    case 1:
    {
        std::cout<<"\n Game will start is few seconds ...  \n";
        return true;
    };
    break;

    case 2:
    {
        std::map<string, uint32_t> playerHistory;
        std::string line, playerName;
        uint32_t playerScore;

        try
        {
            std::string gameRepos(GAME_REPOSITORY);
            std::string historyRecords(HISTORY_RECORDS);

            std::ifstream filestream(gameRepos + historyRecords);
            if (filestream.is_open())
            {
              while ( std::getline(filestream, line) )
              {

                std::istringstream linestream(line);
                while (linestream >> playerName >> playerScore)
                {

                    playerHistory[playerName] = playerScore;
                }

              }
              filestream.close();
            }
        }
        catch (std::exception &e)
        {

           std::cout<<"Error :  unknown exception, "<<e.what()<<std::endl;

        }
        //cout<< "size of player history" << playerHistory.size(); // debug
        if (playerHistory.size() > 0)
        {

            // create an empty vector of pairs
            vector<pair> vec;

            // copy key-value pairs from the map to the vector
            std::copy(playerHistory.begin(),
                    playerHistory.end(),
                    std::back_inserter<std::vector<pair>>(vec));

            // sort the vector by increasing order of its pair's second value
            // if second value are equal, order by the pair's first value
            std::sort(vec.begin(), vec.end(),
                    [](const pair& l, const pair& r) {
                        if (l.second != r.second)
                            return l.second < r.second;

                        return l.first < r.first;
                    });

            //cout<< "size of sorted list" << sorted_records.size();
            cout<<"\nTOP SCORES :\n\n";
            for ( auto recordItem : vec )
            {
               cout << "" << ". player : " << recordItem.first << ", score : " << recordItem.second << std::endl;
            }
        }
        else
        {
            cout << "No records yet, press 1 and be the first player ...!\n";
        }
        return false;
    };
    break;
    case 3:
    {
        exit_is_pressed = true;
        cout << "Exiting the game ... we hope you enjoyed" << std::endl;
        cout << " ######################################################################################################\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #******           ******   ****  ***        ***       **      ***      **  *****  *****        ******#\n";
        cout << " #****  **********  *****   ****  ******  ********  *******  *******  ****    ***  ****  *****  ******#\n";
        cout << " #****  **********  *****   ****  ******  ********  *******  *******  ****  *  **  ***  **************#\n";
        cout << " #****  **********  *****   ****  ******  ********  *******  *******  ****  **  *  ***  **************#\n";
        cout << " #*****  ******    ******   ****  ******  ********  *******  *******  ****  ***    ****  *****     ** #\n";
        cout << " #******          *   ***         ****       *****  *******  *****      **  ****   *****         *****#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****     **   *****  *****   *****  ***  **     *******     *******   *****  *******  ****      ****#\n";
        cout << " #****  ** **    ****  ***  ***  ***  *  ****  *********  **********  *  ***  *  **  **  ***  ********#\n";
        cout << " #*****   ***  **  **  **  *****  **    *****     ******  *********  ***  **  ***   ***  ***      ****#\n";
        cout << " #**** **  **  ***  *  **         **  **  ***  *********  ****   **       **  *********  ***  ********#\n";
        cout << " #*****    **  ****    **  *****  **  ***  **     *******      ****  ***  **  *********  ***      ****#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " #****************************************************************************************************#\n";
        cout << " ######################################################################################################\n\n";

        //return false;
    };
    break;
    default:
    {
       std::cout<<"Invalid choice, please press one of the above numbers\n";
       return false;
    }
    return false;
    }
}


void game::MainMenu::add_score( const uint32_t &score)
{
    std::string Name;
    char flag;
    std::string gameRepos(GAME_REPOSITORY);
    std::string historyRecords(HISTORY_RECORDS);

    //std::ifstream filestream(gameRepos + historyRecords);

    try
    {
        std::map<string, uint32_t>::iterator it;
        std::cout << "Please enter your name..." << std::endl;

        std::cin >> Name;
        scores_list[Name] = score;

        // For debugging
        for ( auto item : scores_list)
        {
            std::cout<<"name :"<<item.first<<" score : "<<item.second<<"\n";
        }

        std::cout<< "Score added successefully\n";

        std::ofstream scoreFile;
        scoreFile.open( gameRepos + historyRecords, ios_base::app);

        for ( auto item : scores_list)
        {
            scoreFile << item.first << " " << item.second << "\n";
        }
        scoreFile.close();
    }
    catch (std::exception &e)
    {

       std::cout<<"Error :  unknown exception, "<<e.what()<<std::endl;

    }
}


