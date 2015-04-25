#ifndef SPRITE_H
#define SPRITE_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <cstdlib>

namespace starkey {
  class sprite {
  public:
    	
	 /**
     * Construct a sprite giving it a bitmap to display when it is
     * drawn and the position of its upper-left hand corner in the
     * world.  Also specify the initial velocity of the sprite.
     */
    sprite(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy);

	
    virtual ~sprite();

    /**
     * these two should cause errors, no copying!
     */
    sprite(const sprite& other);
    sprite& operator =(const sprite& other);


    /**
     * Draw this sprite. See world.draw for discussion of the display
     * variable.
     */
    void virtual draw(ALLEGRO_DISPLAY *display);


    /**
     * Move time forward by the specified amount
     */
    void virtual advance_by_time(double dt) =0;

    /**
     * Return my bitmap
     */
	ALLEGRO_BITMAP virtual *get_bitmap() const;

    // Add other methods here
	virtual void flipHorizontal(bool flip);

	float GetCurrentX();
	float GetCurrentY();
    
	protected:

    // Put your i-vars here
	  ALLEGRO_BITMAP *currentBitmap;
	  std::size_t worldWidth;
	  std::size_t worldHeight;
	  
	  float currentX = 0.0;
	  float currentY = 0.0;
	  float initialVX = 0.0;
	  float initialVY = 0.0;
	  float currentVX = 0.0;
	  float currentVY = 0.0;
	  float currentACCX = 0.0;
	  float currentACCY = 0.0;
	  bool flipImageHorizontal = false;
  };
}
#endif /* SPRITE_H */
