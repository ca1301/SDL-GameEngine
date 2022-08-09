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

bool CheckRoundOver(vector<Ship*> ships)
{
    int aliveEnemies = 0;
    for (size_t i = 0; i < ships.size(); i++)
    {
        if (!ships[i]->destroyed)
        {
            aliveEnemies++;
        }
    }

    if (aliveEnemies == 0)
    {
        cout << "Round Over" << endl;
        return true;
    }
    return false;
}

void Collide(Ship* ship, Bullet* bullet, Player* player)
{
    if ((bullet->GetBulletRect().x - ship->GetShipRect().x < ship->GetShipRect().w) &&
        (ship->GetShipRect().x - bullet->GetBulletRect().x < bullet->GetBulletRect().w) &&
        (bullet->GetBulletRect().y - ship->GetShipRect().y < ship->GetShipRect().h) &&
        (ship->GetShipRect().y - bullet->GetBulletRect().y < bullet->GetBulletRect().h))
    {
        bullet->destroyed = true;
        bullet->Destroy();
        ship->destroyed = true;
        ship->Destroy();
        player->score += 30;
    }
    return;
}




int main(int argc, char** argv)
{
    //Initialise objects
    LoadSDL* loadSDL = new LoadSDL();
    Start* start1 = new Start();

    //Scene management
    vector <Bullet*> bullets;
    vector <Ship*> ships;

    //Amount of enemies
    int columns = 15;
    int rows = 3;

    //Player
     Player* playerOne = new Player(5);
     TextScreen* scoreText = new TextScreen();\
     scoreText->Draw(20, "../assets/Roboto.ttf", 40, 20);

     //Enemies
     float movementSpeed = 3;
     float lastMove = 0;


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
            ship->Draw(1, "../assets/player/Enemy_1.png", 20 + 50 * j, 40 + 50 * i, 1, 1);
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


        SDL_SetRenderDrawColor(loadSDL->m_Renderer, 70, 70, 70, 255);

      

        if (playerOne->playerShoot == true)
        {
            playerOne->playerShoot = false;
            Bullet* bullet = new Bullet();
            bullet->Draw(1, "../assets/player/Bullet.png", playerOne->GetPosPlayer().x, playerOne->GetPosPlayer().y - 30, 2, 2);
            bullets.push_back(bullet);

            if (Mix_PlayChannel(-1, sound->wave(), 0, ) == -1)
            {
                cout << "Failed to play sound" << endl;
            }
        }

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
            ships[i]->Update();
            ships[i]->Render(0, SDL_RendererFlip::SDL_FLIP_NONE);

            //Handle enemy movement
            if (ships[0]->GetShipRect().x < 500)
            {
                float x = ships[i]->GetShipRect().x;
                ships[i]->Move(x += 1, ships[i]->GetShipRect().y);
            }

        }
        
       

        for (int i = 0; i < ships.size(); i++)
        {
            for (int j = 0; j < bullets.size(); j++)
            {
                if (ships[i]->destroyed == false && bullets[j]->destroyed == false)
                {
                    Collide(ships[i], bullets[j], playerOne);
                    if (CheckRoundOver(ships))
                    {
                        for (size_t g = 0; g < ships.size(); g++)
                        {
                            ships.erase(ships.begin() + g);
                        }
                    }
                }
            }
        }
        
        playerOne->Update(deltaTime);
        playerOne->HandleEvents();

        playerOne->Render();

        //Rendering and update the score text to display the players current score
        scoreText->Render();
        scoreText->Update("Score:  " + std::to_string(playerOne->score));

        //Draw in window
        SDL_RenderPresent(loadSDL->m_Renderer);
    }
    std::cout << "Game Over!" << std::endl;
    Mix_FreeChunk(sound->wave());
    loadSDL->Clean();
    return 0;
}





