#include <cmath>
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Observer.h"
#include "Subject.h"
#include "vehicle.h"
#include "TankGame.h"

#include "world.h"

using namespace std;
using namespace starkey;

const float FPS = 60;

const size_t WIDTH=1920;
const size_t HEIGHT=1080;

int main(int argc, char **argv)
{
 
   if(!al_init()) {
     cerr << "Failed to initialize allegro!" << endl;
     exit(1);
   }
 
   if(!al_init_image_addon()) {
     cerr << "Failed to initialize al_init_image_addon!" << endl;
     exit(1);
   }
   
   if(!al_install_mouse()) {
     cerr << "Failed to install mouse." << endl;
     exit(1);
   }

   if(!al_install_keyboard()) {
     cerr << "Failed to install keyboard." << endl;
     exit(1);
   }

   //Initialize Font engine add-ons.
   al_init_font_addon();   

   if (!al_init_ttf_addon())
   {
	   cerr << "Failed to install true type font addon." << endl;
	   exit(1);
   }

   // This option causes the display to wait for VSYNC before flipping
   // pages. This can help to avoid tearing. Comment this out if you
   // are having refresh problems.
   al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);

   ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
 
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }


   ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
   if(!timer) {
     al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", 
                                NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
     return -1;
   }

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   if(!event_queue) {
     al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!", 
                                NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   ALLEGRO_FONT *fontx = al_load_ttf_font("arial.ttf", 36, 0);

   if (!fontx){
	   fprintf(stderr, "Could not load 'arial.ttf'.\n");
	   return -1;
   }

  
 
   al_register_event_source(event_queue, al_get_display_event_source(display)); 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_start_timer(timer);

   starkey::world theWorld(display, WIDTH, HEIGHT);
   
   double time = 0;
   bool redraw = true; // paint the first time through
   ALLEGRO_EVENT ev;
   do
   {
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) 
	  {
         redraw = true;
      }
	  else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	  {
		  

		  switch (ev.keyboard.keycode)
		  {			  			 
			  case ALLEGRO_KEY_DOWN:
				  theWorld.ReduceAngle();
				  break;
				 

			  case ALLEGRO_KEY_UP:
				  theWorld.IncreaseAngle();
				  break;

			  case ALLEGRO_KEY_LEFT:
				  theWorld.ReduceVelocity();
				  break;

			  case ALLEGRO_KEY_RIGHT:
				  theWorld.IncreaseVelocity();
				  break;

			  case ALLEGRO_KEY_SPACE:
				  theWorld.Fire();
				  break;            

			  case ALLEGRO_KEY_ESCAPE:
				 //Leave game early.
				  return 0;
				  break;

		  }
	  }

       
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         time += 1/FPS;

         theWorld.advance_by_time(1/FPS);	

         theWorld.draw(display);

         al_flip_display();
      }
   } while(ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);
 

 
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

