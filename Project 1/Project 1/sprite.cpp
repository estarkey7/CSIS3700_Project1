#include "sprite.h"

using namespace std;

namespace starkey
{		
	sprite::sprite(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy)
	{
		currentBitmap = initial_bitmap;
		worldWidth = world_width;
		worldHeight = world_height;
		currentX = initial_x;
		currentY = initial_y;
		initialVX = initial_vx;
		initialVY = initial_vy;
		currentVX = initial_vx;
		currentVY = initial_vy;		

	}
		

	void sprite::draw(ALLEGRO_DISPLAY *display)
	{
		if (flipImageHorizontal == true)
		{
			al_draw_bitmap(currentBitmap, currentX, currentY, ALLEGRO_FLIP_HORIZONTAL);
		}
		else
		{
			al_draw_bitmap(currentBitmap, currentX, currentY, 0);
		}
		
	}

	

	ALLEGRO_BITMAP* sprite::get_bitmap() const
	{
		return sprite::currentBitmap;
	}

	void sprite::flipHorizontal(bool flip)
	{
		flipImageHorizontal = flip;
	}

	float sprite::GetCurrentX()
	{
		return currentX;
	}

	float sprite::GetCurrentY()
	{
		return currentY;
	}

	sprite::~sprite()
	{

	}

}