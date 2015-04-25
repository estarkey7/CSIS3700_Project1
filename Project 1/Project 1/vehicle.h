#ifndef VEHICLE_H
#define VEHICLE_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "Observer.h"
#include "Subject.h"
#include "sprite.h"
#include <cstdlib>

//Abstract vehicle class
namespace starkey
{
	class vehicle : public Observer, public Subject, public sprite
	{

	public:
		vehicle(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy);

		virtual ~vehicle();
	
	protected:
		
	};
}

#endif //VEHICLE_H