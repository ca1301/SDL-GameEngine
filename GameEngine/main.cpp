#include <iostream>
#include "LoadSDL.h"
#include "Player.h"
#include "TextScreen.h"
#include "Start.h"
#include "Ship.h"
#include <vector>
#include <SDL_mixer.h>
#include "Sound.h"
#include <algorithm>
using namespace std;

int main(int argc, char** argv)
{
    //Initialise objects
    LoadSDL* loadSDL = new LoadSDL();
    Start* start1 = new Start();
    int enemiesPerRound[3][2]  = {
        {5,2},
        {10,3},
        {15,4}
    };
   cout << enemiesPerRound[0, 0] << endl;
    //Scene management
    vector <Bullet*> bullets;
    vector <Ship*> ships;

    //Amount of enemies
    int columns = 15;
    int rows = 3;

    //Player
     Player* playerOne = new Player(5);
     TextScreen* scoreText = new TextScreen();
   
    int playerScore = 0;
    scoreText->Draw(20, "../assets/Roboto.ttf", 40, 20);


    int lastUpdate = 0;
    loadSDL->Load();
   
    start1->Draw("../assets/menu.png", 0, 0, 1, 1);
    Sound* sound = new Sound("../assets/button_hover.wav");

    playerOne->Draw(1, "../assets/player/Ship.png", 2, 2);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            Ship* ship = new Ship();
            ship->Draw(1, "../assets/player/Enemy_1.png", 300 + 50 * j, 40 + 50 * i, 1, 1);
            ships.push_back(ship);
        }
    }
    
    while (start1->gameStarted == false)
    {
        start1->Render();
        start1->HandleEvents();
    }


    bool playerDied = false;

    //Game Loop
    while (playerDied == false)
    {
        //Clear the screen each frame
        SDL_RenderClear(loadSDL->m_Renderer);
        //Get delta time for player/enemy movement
        unsigned int ticks = SDL_GetTicks() - lastUpdate;
        float deltaTime = ticks / 1000.0f;
        lastUpdate = SDL_GetTicks();

        //Rendering and update the score text to display the players current score
        scoreText->Render();
        scoreText->Update("Score:  " + std::to_string(playerScore));
      

        if (playerOne->playerShoot == true)
        {
            cout << "Shoot" << endl;
            playerOne->playerShoot = false;
            Bullet* bullet = new Bullet();
            bullet->Draw(1, "../assets/player/Bullet.png", playerOne->GetPosPlayer().x, playerOne->GetPosPlayer().y - 30, 2, 2);
            bullets.push_back(bullet);
            if (Mix_PlayChannel(-1, sound->wave(), 0, ) == -1)
            {
                cout << "Failed to play sound" << endl;
            }
        }
        //Code below for game over when player runs out of lives
        //scoreText->Update("Game Over!!");
        //playerDied = true;

        for (int i = 0; i < bullets.size(); i++) {
            bullets[i]->Update(deltaTime);
            bullets[i]->Render();

            //If the bullet gets to the top of the page without hitting anything we need to destroy it
            if (bullets[i]->GetBulletRect().y < 0)
            {
                bullets[i]->Destroy();
                bullets.erase(bullets.begin() + i);
            }
        }

        for (int i = 0; i < ships.size(); i++) {
            ships[i]->Update(deltaTime);
            ships[i]->Render(0, SDL_RendererFlip::SDL_FLIP_NONE);

        }

        for (size_t i = 0; i < ships.size(); i++)
        {
            for (size_t j = 0; j < bullets.size(); j++)
            {
                if (ships[i]->Collision(bullets[j]->GetBulletRect()))
                {
                    
                    if (*find(bullets.begin(), bullets.end(), bullets[j])) {
                        //Element found in array
                        bullets[j]->Destroy();
                        bullets.erase(bullets.begin() + j);
                    }
                    
                    if (*find(ships.begin(), ships.end(), ships[i])) {
                        //Element found in array
                        ships[i]->Destroy();
                        ships.erase(ships.begin() + i);
                    }


                    playerScore += 30;
                }
            }
        }
        
        playerOne->Update(deltaTime);
        playerOne->HandleEvents();

        playerOne->Render();

        //Draw in window
        SDL_RenderPresent(loadSDL->m_Renderer);
    }
    std::cout << "Game Over!" << std::endl;
    Mix_FreeChunk(sound->wave());
    loadSDL->Clean();
    return 0;
}

struct compare
{
    int key;
    compare(int const& i) : key(i) {}

    bool operator()(int const& i) {
        return (i == key);
    }
};

