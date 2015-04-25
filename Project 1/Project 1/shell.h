#ifndef SHELL_H
#define SHELL_H

#include "Subject.h"
#include "sprite.h"
#include "TankGame.h"
#include <math.h>

namespace starkey
{
	class shell :public Subject, public sprite
	{
		public:
			shell(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, int angle);
			void advance_by_time(double dt); 
			void draw(ALLEGRO_DISPLAY *display) override;
			const double PI = 3.1415926535897;
			const float EARTHGRAVITY = -9.8;
			void setInitialAngle(int angle);	
			bool isShellReadyToDispose() const;
			void SetGame(TankGame *game);
			void InverseFlight(bool flght);
			virtual ~shell();	
		
		protected:
			int currentAngle = 0;
			bool hitGround = false;
			bool tankHit = false;
			bool explosionOver = false;
			bool readyToDispose = false;
			bool inverseFlight = false;
			ALLEGRO_BITMAP *groundExplosion;
			ALLEGRO_BITMAP *tankExplosion;
			TankGame *tankGame;

	};
}

#endif

