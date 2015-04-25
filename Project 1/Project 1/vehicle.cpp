#include "vehicle.h"

using namespace starkey;

namespace starkey
{
	vehicle::vehicle(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy) : sprite(initial_bitmap, world_width, world_height, initial_x, initial_y, initial_vx, initial_vy)
	{
		
	}
		

	vehicle::~vehicle()
	{

	}

}

