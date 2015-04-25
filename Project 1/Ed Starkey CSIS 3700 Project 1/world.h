#ifndef WORLD_H
#define WORLD_H

#include "allegro5/allegro.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "sprite.h"
#include "tank.h"
#include "TankGame.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace starkey 
{
  class world 
  {
  public:
    /**
     * Construct the world. The display is passed in simply to make it
     * possible to modify options or access the backbuffer. DO NOT
     * store the display in an instance variable. DO NOT start drawing
     * on the screen. Just load bitmaps etc.
     */
    world(ALLEGRO_DISPLAY *display, std::size_t window_width, std::size_t window_height);

    /**
     * Free any resources being used by the world.
     */
    ~world();

    /**
     * Block the copy constructor.  Worlds should not be copied to
     * just assert(false)
     */
    world(const world& other);

    /**
     * Block operator =.  Worlds should not be assigned.
     */
    world& operator =(const world& other);
 
    
    /**
     * Advance the state of the world forward by the specified time.
     */
    void advance_by_time(double dt);

	tank* getPlayer(int x);

    /**
     * Draw the world. Note that the display variable is passed only
     * because it might be needed to switch the target bitmap back to
     * the backbuffer.
     */
    void draw(ALLEGRO_DISPLAY *display);

	void IncreaseVelocity();
	void ReduceVelocity();
	void IncreaseAngle();
	void ReduceAngle();
	void Fire();


  protected:
	  std::size_t windowWidth;
	  std::size_t windowHeight;
	  std::vector<sprite*> worldsSprites;
	  void createPlayers();
	  void createWorldBackground();
	  void createScoreStats();
	  
	  float randomGenerator(float min, float max);
	  ALLEGRO_BITMAP *backgroundImage;
	  ALLEGRO_BITMAP *playerImage;
	  ALLEGRO_BITMAP *missleImage;	  
	  ALLEGRO_FONT *scoreBoardFont;
	  ALLEGRO_FONT *statsFont;
	  int currentPlayer = 1;

	  TankGame* game;
	  tank* Player1;
	  tank* Player2;

	  std::string player, angle, velocity;
	  std::stringstream playerStream;
	  std::stringstream turretAngleStream;
	  std::stringstream shellVelocityStream;
  };
}

#endif /* WORLD_H */
