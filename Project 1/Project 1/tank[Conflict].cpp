#include "tank.h"
#include "sprite.h"
#include <math.h>

using namespace std;
using namespace starkey;

namespace starkey
{
	tank::tank(ALLEGRO_BITMAP *bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, int ID) : vehicle(bitmap, world_width, world_height, initial_x, initial_y, initial_vx, initial_vy)
	{
		tankID = ID;
		turretImage = al_load_bitmap("turret.png");
		shellImage = al_load_bitmap("missle2.png");
		enemies = new vector<tank*>();
	}

	void tank::advance_by_time(double dt)
	{
		if (isShellFired == true)
		{
			firedShell->advance_by_time(dt);
			//Tell all observers of the shell's bounding box. 
			firedShell->NotifyObservers();

			if (firedShell->isShellReadyToDispose() == true)
			{
				isShellFired = false;
				
				delete firedShell; //Dispose of Shell.
			}
		}

		
	}

	void tank::RaiseTurret()
	{
		if (turretAngle < 90)
		{
			turretAngle++;
		}
	}

	void tank::LowerTurret()
	{
		if (turretAngle > 0)
		{
			turretAngle--;
		}
	}

	void tank::IncreaseShellVelocity()
	{
		if (shellVelocity < 10000)
		{
			shellVelocity += 5;
		}
	}

	void tank::ReduceShellVelocity()
	{
		if (shellVelocity > 0)
		{
			shellVelocity -= 5;
		}
	}

	void tank::FireShell()
	{
		if (isShellFired == false)
		{
			isShellFired = true;			
			firedShell = new shell(shellImage, worldWidth, worldHeight, currentX, 1020, shellVelocity, shellVelocity, turretAngle);
			
			//Register each enemy with the shell that is fired. Using the Observable pattern.
			for (int x = 0; x < enemies->size(); x++)
			{
				firedShell->RegisterObserver(enemies->at(x));
			}
		}
		

	}

	void tank::draw(ALLEGRO_DISPLAY *display)
	{
		sprite::draw(display);
				
		if (flipImageHorizontal == true)
		{
			al_draw_rotated_bitmap(turretImage, 50, 0, currentX + 30, currentY + 10, turretAngle * PI/180, ALLEGRO_FLIP_HORIZONTAL);//Angle to Radians conversion for rotation.
		}
		else
		{
			al_draw_rotated_bitmap(turretImage, 0, 0, currentX + 80, currentY + 10, -turretAngle * PI / 180, 0);
		}

		if (isShellFired == true)
		{
			firedShell->draw(display);
		}

	}

	int tank::GetTurretAngle()
	{
		return turretAngle;
	}

	float tank::GetShellVelocity()
	{
		return shellVelocity;
	}

	void tank::addEnemies(tank *enemy)
	{
		enemies->push_back(enemy);
	}


	tank::~tank()
	{
		al_destroy_bitmap(turretImage);
		al_destroy_bitmap(shellImage);
		enemies->clear();
		delete enemies;

		if (firedShell != NULL)
		{
			delete firedShell;
		}
	}
}
