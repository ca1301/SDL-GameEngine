#include "Menu.h"
#include "resource.h"
#include <SDL_syswm.h>
#include <iostream>

using namespace std;

Menu::Menu()
{
	window = FindWindow(NULL, L"My Game");
	if (window == NULL)
	{
		cout << "Failed to find window" << endl;
		exit(1);
	}

	menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

	if (menu == NULL)
	{
		cout << "Failed to create menu" << endl;
		exit(1);
	}

	if (SetMenu(window, menu) == 0)
	{
		cout << "Failed to set menu" << endl;
		exit(1);
	}
	Uint8 eventStateResult = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	if (eventStateResult == SDL_ENABLE)
	{
		cout << "Failed to enable windows event state" << endl;
		exit(1);
	}
}
Menu::~Menu()
{

}
void Menu::GetMenu()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_SYSWMEVENT:
			if (event.syswm.msg->msg.win.wParam == ID_FILE_NEWWINDOW)
			{
				cout << "ID_FILE_NEWWINDOW= " << ID_FILE_NEWWINDOW << "\n";
				//Create new SDL window
				if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
				{
					//A Window for rendering
					sdlWindow2 = SDL_CreateWindow("Sub Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
				}
				//Render for the created window
				sdlRenderer2 = SDL_CreateRenderer(sdlWindow2, 0, -1);


			}
			else if (event.syswm.msg->msg.win.wParam == ID_FILE_EXIT)
			{
				cout << "ID_FILE_EXIT= " << ID_FILE_EXIT << "\n";
				SDL_DestroyWindow(sdlWindow2);
				SDL_DestroyRenderer(sdlRenderer2);
			}
			else if (event.syswm.msg->msg.win.wParam == ID_HELP_ABOUTGAME)
			{
				cout << "ID_HELP_ABOUTGAME= " << ID_HELP_ABOUTGAME << "\n";
				DisplayDialogBox();
			}
		}
	}
}

int Menu::DisplayDialogBox()
{
	int msgBoxID = MessageBox(NULL, L"This is my game.\nPlease press SPACE BAR to run it", L"My Game Message", MB_ICONEXCLAMATION | MB_OK);
	return msgBoxID;
}
