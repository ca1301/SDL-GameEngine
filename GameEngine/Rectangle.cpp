#include "Rectangle.h"

Rectangle::Rectangle(Uint8 r, Uint8 g, Uint8 b)
{
	rectColour = { r, g, b, 255 };
}

Rectangle::~Rectangle()
{
}

void Rectangle::Drawing(SDL_Rect rect)
{
	SDL_SetRenderDrawColor(m_Renderer, rectColour.r, rectColour.g, rectColour.b, 255);
	SDL_RenderFillRect(m_Renderer, &rect);
}
