/***************************************************************
 *    Name: Tony Tam  Course Code: ICS3U  Date: Jan.18,2018    *
 *                                                             *
 *      This file contains most of the functions related to    *
 *    the display and movement.                                *
 ***************************************************************/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "Summative_Header.h"

extern ALLEGRO_DISPLAY *display; //add display object
extern ALLEGRO_BITMAP *image;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *gameTime;
extern ALLEGRO_TIMER *objectTimer;
extern ALLEGRO_TIMER *planetTimer;
extern ALLEGRO_TIMER *spriteTimer;

void DisplayIntructions(int Screen_H, int Screen_W) {

    // initialize display
    display = al_create_display(Screen_W, Screen_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }
    al_set_window_title(display, "StarFall - InstructionScreen"); //Sets title of window to "StarFall - TitleScreen"




    // Declare a BITMAP called image, setting it's initial value to nullptr
    ALLEGRO_BITMAP *image = nullptr;
    image = al_load_bitmap("Instruction_Screen640Wx580H.png");
    if (!image) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // Display picture started at top left corner
    al_draw_bitmap(image, 0, 0, 0);

    // write display to screen
    al_flip_display();

    // Closes screen when space is pressed
    bool doexit = false;
    while (!doexit) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_SPACE:
                doexit = true;
                break;
            }
        }
    }
    al_destroy_display(display);
    al_destroy_bitmap(image);
}

void DisplayTitle(int Screen_H,int Screen_W) {
    // initialize display
    display = al_create_display(Screen_W, Screen_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }
    al_set_window_title(display, "StarFall - TitleScreen"); //Sets title of window to "StarFall - TitleScreen"

    // set up event queue and puts up a message box and destroys the display if it fails
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // need to register events for our event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Declare a BITMAP called image, setting it's initial value to nullptr
    ALLEGRO_BITMAP *image = nullptr;
    image = al_load_bitmap("Title_Page640Wx580H.png");
    if (!image) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load title image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // Display picture started at top left corner
    al_draw_bitmap(image, 0, 0, 0);

    // write display to screen
    al_flip_display();

    // Closes screen when space is pressed
    bool doexit = false;
    while (!doexit) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_SPACE:
                doexit = true;
                break;
            }
        }
    }
    al_destroy_display(display);
    al_destroy_bitmap(image);
}

void DisplayGame(int Screen_H,int Screen_W) {

    // initialize display
    display = al_create_display(Screen_W, Screen_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    al_set_window_title(display, "StarFall - GameScreen");

    // set up event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // need to register events for our event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(gameTime));
    al_register_event_source(event_queue, al_get_timer_event_source(objectTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(planetTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(spriteTimer));

    // Declare a BITMAP called image, setting it's initial value to nullptr
    image = al_load_bitmap("Game_Screen640Wx580H.png");
    if (!image) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }
    // Display picture started at top left corner
    al_draw_bitmap(image, 0, 0, 0);

    // write display to screen
    al_flip_display();
}

void DisplayEnd(int Screen_H, int Screen_W, bool &playagain, bool &replay) {
    // initialize display
    display = al_create_display(Screen_W, Screen_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }
    al_set_window_title(display, "StarFall - EndScreen"); //Sets title of window to "StarFall - TitleScreen"

    // set up event queue and puts up a message box and destroys the display if it fails
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // need to register events for our event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Declare a BITMAP called image, setting it's initial value to nullptr
    ALLEGRO_BITMAP *image = nullptr;
    image = al_load_bitmap("End_Page650Wx580H.png");
    if (!image) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    // Display picture started at top left corner
    al_draw_bitmap(image, 0, 0, 0);

    // write display to screen
    al_flip_display();

    // Closes screen when space is pressed
    bool doexit = false;
    while (!doexit) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_SPACE:
                playagain = true;
                replay = true;
                doexit = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                playagain = false;
                doexit = true;
            }
        }
    }
    al_destroy_display(display);
    al_destroy_bitmap(image);
}

void InitializeAllegro() {
    //initializes allegro
    al_init();

    // Initialize keyboard routines
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    //Initialize image add on
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize al_init_image_addon!",nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // set up event queue and puts up a message box and destroys the display if it fails
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }

    gameTime = al_create_timer(1.0);
    objectTimer = al_create_timer(1.0 / 50);
    planetTimer = al_create_timer(1.0 / 40);
    spriteTimer = al_create_timer(1.0 / 50);
}

bool isCollision(Graphics &object1, Graphics &object2) {
    object1.leftBoarder = object1.XCoord;
    object1.rightBoarder = object1.XCoord + al_get_bitmap_width(object1.picture);
    object1.topBoarder = object1.YCoord;
    object1.bottomBoarder = object1.YCoord + al_get_bitmap_height(object1.picture);

    object2.leftBoarder = object2.XCoord;
    object2.rightBoarder = object2.XCoord + al_get_bitmap_width(object2.picture);
    object2.topBoarder = object2.YCoord;
    object2.bottomBoarder = object2.YCoord + al_get_bitmap_height(object1.picture);

    if (object1.bottomBoarder < object2.topBoarder) {
        return false;
    } else if (object1.topBoarder > object2.bottomBoarder) {
        return false;
    } else if (object1.rightBoarder < object2.leftBoarder) {
        return false;
    } else if (object1.leftBoarder > object2.rightBoarder) {
        return false;
    }
    return true;
}
