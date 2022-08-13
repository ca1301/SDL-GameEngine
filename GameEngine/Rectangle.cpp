#include "Rectangle.h"

Rectangle::Rectangle(Uint8 r, Uint8 g, Uint8 b, SDL_Rect rect)
{
	rectColour = { r, g, b, 255 };
	this->rect = rect;
}

Rectangle::~Rectangle()
{
}

void Rectangle::Drawing()
{
	SDL_SetRenderDrawColor(m_Renderer, rectColour.r, rectColour.g, rectColour.b, 255);
	SDL_RenderFillRect(m_Renderer, &rect);
}
