#ifndef TANK_H
#define TANK_H

#include "vehicle.h"
#include "shell.h"
#include "sprite.h"
#include <math.h>
#include "TankGame.h"
#include <vector>

using namespace starkey;

namespace starkey
{
	class tank : public vehicle		
	{
		public:
			tank(ALLEGRO_BITMAP *bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, int ID);
			
			void RaiseTurret();
			void LowerTurret();
			void IncreaseShellVelocity();
			void ReduceShellVelocity();
			void FireShell();
			void advance_by_time(double dt);
			void draw(ALLEGRO_DISPLAY *display) override;
			const double PI = 3.1415926535897;
			int GetTurretAngle();
			float GetShellVelocity();			
			virtual ~tank();
			int GetTankID();
			void addEnemies(tank *enemy);
			virtual void Update(int x, int y, int height, int width) override;
			void SetGame(TankGame *game);

		protected:
			int turretAngle = 0;
			float shellVelocity = 0.0;
			int tankID = 0;
			shell * firedShell;
			ALLEGRO_BITMAP *turretImage;
			ALLEGRO_BITMAP *shellImage;
			ALLEGRO_BITMAP *destroyedTankImage;
			ALLEGRO_BITMAP *destroyedTurretImage;
			std::vector<tank*> *enemies;
			TankGame *tankGame;
			

	};
}

#endif