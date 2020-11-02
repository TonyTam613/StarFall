/******************************************************************************************************
 *    Name: Tony Tam  Date Due: Jan. 18, 2018  Course Code: ISC3U                                     *
 *                                                                                                    *
 *        This game is a game where the player can move a sprite around and collect and avoid         *
 *    different falling objects. The stars will give your points, the asteroids will kill you         *
 *    and end the game, and the planets will take away points from your score.                        *
 ******************************************************************************************************/

#include "Summative_Header.h"

//declare and initialize global variables
ALLEGRO_DISPLAY *display = nullptr; //add display object
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;		// add event queue object
ALLEGRO_BITMAP *image = nullptr;
ALLEGRO_TIMER *gameTime = nullptr;
ALLEGRO_TIMER *objectTimer = nullptr;
ALLEGRO_TIMER *planetTimer = nullptr;
ALLEGRO_TIMER *spriteTimer = nullptr;
ALLEGRO_FONT *font = nullptr;

enum KEYS {LEFT, RIGHT}; // make the words LEFT and RIGHT represent the number 0 and 1

int main(int argc, char *argv[]) {

    //Declaring and Initializing my variables
    int starNumber = 14;
    int asteroidNumber = 10;
    int planetNumber = 7;
    int gameLength = 0;
    int objSpeed = 0;
    int planetSpeed = 0;
    char gameLengthtxt[5];
    char Scoretxt[50];
    FILE *fileWrite = nullptr;
    bool Game = true;
    bool keys[2] = {false, false};
    bool playAgain = true;
    bool rePlay = false;
    InitializeAllegro();

    srand(time(nullptr)); //seeds the random numbers to time

    //Initializing my structures, loads bitmaps, assigns locations to the bitmaps
    Users newUser;
    newUser.userScore = 0;

    Graphics sprite;
    sprite.picture = al_load_bitmap("Sprite27Wx63H.png");
    if (!sprite.picture) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }
    sprite.XCoord = rand() % 320 - 13;
    sprite.YCoord = 483;
    sprite.leftBoarder = sprite.XCoord;
    sprite.rightBoarder = sprite.XCoord + al_get_bitmap_width(sprite.picture);
    sprite.topBoarder = sprite.YCoord;
    sprite.bottomBoarder = sprite.YCoord + al_get_bitmap_height(sprite.picture);

    Graphics Stars[starNumber];
    for (int i = 0; i < starNumber; i++) {
        Stars[i].picture = al_load_bitmap("Shooting_Star25Wx25H.png");
        Stars[i].YCoord = rand() % 2000 - 2025;
        Stars[i].XCoord = rand() % 615;
        Stars[i].leftBoarder = Stars[i].XCoord;
        Stars[i].rightBoarder = Stars[i].XCoord + al_get_bitmap_width(Stars[i].picture);
        Stars[i].topBoarder = Stars[i].YCoord;
        Stars[i].bottomBoarder = Stars[i].YCoord + al_get_bitmap_height(Stars[i].picture);
    }

    Graphics Asteroids[asteroidNumber];
    for (int i = 0; i < asteroidNumber; i++) {
        Asteroids[i].picture = al_load_bitmap("Asteroid25Wx21H.png");
        Asteroids[i].YCoord = rand() % 2000 - 2021;
        Asteroids[i].XCoord = rand() % 615;
        Asteroids[i].leftBoarder = Asteroids[i].XCoord;
        Asteroids[i].rightBoarder = Asteroids[i].XCoord + al_get_bitmap_width(Asteroids[i].picture);
        Asteroids[i].topBoarder = Asteroids[i].YCoord;
        Asteroids[i].bottomBoarder = Asteroids[i].YCoord + al_get_bitmap_height(Asteroids[i].picture);
    }

    Graphics Planets[planetNumber];
    for (int i = 0; i < planetNumber; i++) {
        switch (i) {
        case 0:
            Planets[i].picture = al_load_bitmap("Mercury35Wx35H.png");
            break;
        case 1:
            Planets[i].picture = al_load_bitmap("Venus35Wx35H.png");
            break;
        case 2:
            Planets[i].picture = al_load_bitmap("Earth35Wx35H.png");
            break;
        case 3:
            Planets[i].picture = al_load_bitmap("Mars35Wx35H.png");
            break;
        case 4:
            Planets[i].picture = al_load_bitmap("Jupiter35Wx35H.png");
            break;
        case 5:
            Planets[i].picture = al_load_bitmap("Saturn35Wx35H.png");
            break;
        case 6:
            Planets[i].picture = al_load_bitmap("Uranus35Wx37H.png");
            break;
        case 7:
            Planets[i].picture = al_load_bitmap("Neptune37Wx35H.png");
            break;
        }
    }
    for (int i = 0; i < planetNumber; i++) {
        Planets[i].YCoord = rand() % 2000 - 2037;
        Planets[i].XCoord = rand() % 603;
        Planets[i].leftBoarder = Planets[i].XCoord;
        Planets[i].rightBoarder = Planets[i].XCoord + al_get_bitmap_width(Planets[i].picture);
        Planets[i].topBoarder = Planets[i].YCoord;
        Planets[i].bottomBoarder = Planets[i].YCoord + al_get_bitmap_height(Planets[i].picture);
    }

    //the while loop that replays the game when space is hit at the end of the game
    while (playAgain) {

        //when the game is replayed it clears the console and recreates all of the timers
        //if I don't destroy and recreate the timers the game will lag a lot when it is replayed
        if (rePlay) {
            gameTime = al_create_timer(1.0);
            objectTimer = al_create_timer(1.0 / 50);
            planetTimer = al_create_timer(1.0 / 40);
            spriteTimer = al_create_timer(1.0 / 50);
            system("CLS");
        }

        //asks user for their name and assigns the string o newUser.userName
        printf(" Input your name: ");
        scanf(" %s", newUser.userName);

        //displays the title window and closes it when space is pressed
        DisplayTitle(Screen_H, Screen_W);

        //displays the title window and closes it when space is pressed
        DisplayIntructions(Screen_H, Screen_W);

        //resets the score, game length, object and planet speed, and the game bool when the game is replayed, also sets the keys to false
        //so you don't start the game moving uncontrollably
        newUser.userScore = 0;
        gameLength = 0;
        objSpeed = 0;
        planetSpeed = 0;
        Game = true;
        for (int i = 0; i < 2; i++) {
            keys[i] = false;
        }

        //resets the timer speeds to the starting speed
        al_set_timer_speed(objectTimer, 1.0 / 40);
        al_set_timer_speed(planetTimer, 1.0 / 50);

        //resets the positions of all of the falling object bitmaps
        for (int i = 0; i < starNumber; i++) {
            Stars[i].YCoord = rand() % 2000 - 2025;
            Stars[i].XCoord = rand() % 615;
        }
        for (int i = 0; i < asteroidNumber; i++) {
            Asteroids[i].YCoord = rand() % 2000 - 2025;
            Asteroids[i].XCoord = rand() % 615;
        }
        for (int i = 0; i < planetNumber; i++) {
            Planets[i].YCoord = rand() % 2000 - 2037;
            Planets[i].XCoord = rand() % 603;
        }

        //displays game screen
        DisplayGame(Screen_H, Screen_W);

        //initializes font and ttf add on
        al_init_font_addon(); // initialize the font addon
        al_init_ttf_addon();// initialize the ttf (True Type Font) addon

        //initializes font as the nasalization font, at a font size of 20
        ALLEGRO_FONT *font = al_load_ttf_font("nasalization-rg.ttf", 20, 0);

        //draws all of the falling object bitmaps
        for (int i = 0; i < starNumber; i++) {
            al_draw_bitmap(Stars[i].picture, Stars[i].XCoord, Stars[i].YCoord, 0);
        }
        for (int i = 0; i < asteroidNumber; i++) {
            al_draw_bitmap(Asteroids[i].picture, Asteroids[i].XCoord, Asteroids[i].YCoord, 0);
        }
        for (int i = 0; i < planetNumber; i++) {
            al_draw_bitmap(Planets[i].picture, Planets[i].XCoord, Planets[i].YCoord, 0);
        }

        // remove pink part of all of the images
        al_convert_mask_to_alpha(sprite.picture, PINK);	// pink mask, but we can pick any colour
        for (int i = 0; i < starNumber; i++) {
            al_convert_mask_to_alpha(Stars[i].picture, PINK);
        }
        for (int i = 0; i < asteroidNumber; i++) {
            al_convert_mask_to_alpha(Asteroids[i].picture, PINK);
        }
        for (int i = 0; i < planetNumber; i++) {
            al_convert_mask_to_alpha(Planets[i].picture, PINK);
        }

        //flips display and prints all of the bit maps onto the screen
        al_draw_bitmap(sprite.picture, sprite.XCoord, sprite.YCoord, 0);
        al_flip_display();

        //starts all of the timers
        al_start_timer(gameTime);
        al_start_timer(objectTimer);
        al_start_timer(planetTimer);
        al_start_timer(spriteTimer);

        //this while loop loops the code for the actual game
        while (Game) {

            //creates an event variable and waits for an event to happen
            //if the event is an arrow key that was pressed down it will move the sprite
            //if it is the object timer, then it will check if the object is at the bottom or not and reset its position if it is
            //and it makes the objects fall if not
            //if it is the planet timer, it will do the same thing as the object timer
            //if it is the game timer it will add 1 to game length each second, and increase the speeds of the object timer and planet timer every 10 seconds
            //if it is the movement timer it allows the sprite to move if the arrow key is being held down
            //the movement timer is to keep the sprite moving at a constant speed so that when the objects speed up the sprite doesn't speed up too
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                Game = false;
            } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) { // the if statement for the left and right and escape keyboard key events, which will move the sprite or exit the game
                switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:                 //the first two cases makes the keys[LEFT] and keys[RIGHT] bool true if the respective arrow key is pressed
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    Game = false;
                    break;
                }
            } else if (ev.type == ALLEGRO_EVENT_KEY_UP) { //makes the bools keys[LEFT] and keys[RIGHT] false again when the key is let go of
                switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                }
            } else if (ev.timer.source == gameTime) {   //increments the game length every second and object and planet speed every 10 seconds
                gameLength++;
                if (objSpeed < 70) {
                    if (gameLength % 10 == 0) {
                        objSpeed += 10;
                        planetSpeed += 10;
                        al_set_timer_speed(objectTimer, 1.0 / (40 + objSpeed));
                        al_set_timer_speed(planetTimer, 1.0 / (50 + planetSpeed));
                    }
                }
            } else if (ev.timer.source == objectTimer) {
                for (int i = 0; i < starNumber; i++) {      //resets the position of the star if the star hits the bottom
                    if (Stars[i].YCoord >= 521) {
                        Stars[i].YCoord = rand() % 2000 - 2025;
                        Stars[i].XCoord = rand() % 615;
                    } else {
                        Stars[i].YCoord++;                  //increases the Y coordinate of the star which makes it fall
                    }
                }
                for (int i = 0; i < asteroidNumber; i++) {  //does the same thing as the stars except with the asteroids
                    if (Asteroids[i].YCoord >= 521) {
                        Asteroids[i].YCoord = rand() % 2000 - 2025;
                        Asteroids[i].XCoord = rand() % 615;
                    } else {
                        Asteroids[i].YCoord++;
                    }
                }
            } else if (ev.timer.source == planetTimer) {    //does the same thing as the stars except with the planets
                for (int i = 0; i < planetNumber; i++) {
                    if (Planets[i].YCoord >= 511) {
                        Planets[i].YCoord = rand() % 2000 - 2037;
                        Planets[i].XCoord = rand() % 603;
                    } else {
                        Planets[i].YCoord++;
                    }
                }
            } else if (ev.timer.source == spriteTimer) {    //keeps the speed of the sprite's movement consistent throughout the entire game
                sprite.XCoord -= keys[LEFT] * 5;
                sprite.XCoord += keys[RIGHT] * 5;
            }

            //makes the user score and game length int into a string so it can be printed by the code below
            sprintf(gameLengthtxt, "%d", gameLength);

            sprintf(Scoretxt, "%d", newUser.userScore);

            //draws all of the bitmaps and draws the text
            al_draw_bitmap(image, 0, 0, 0);

            for (int i = 0; i < starNumber; i++) {
                al_draw_bitmap(Stars[i].picture, Stars[i].XCoord, Stars[i].YCoord, 0);
            }
            for (int i = 0; i < asteroidNumber; i++) {
                al_draw_bitmap(Asteroids[i].picture, Asteroids[i].XCoord, Asteroids[i].YCoord, 0);
            }
            for (int i = 0; i < planetNumber; i++) {
                al_draw_bitmap(Planets[i].picture, Planets[i].XCoord, Planets[i].YCoord, 0);
            }

            al_draw_bitmap(sprite.picture, sprite.XCoord, sprite.YCoord, 0);

            al_draw_text(font, WHITE, 50, 550, ALLEGRO_ALIGN_CENTER, "Score: ");

            al_draw_text(font, WHITE, 140, 550, ALLEGRO_ALIGN_CENTER, Scoretxt);

            al_draw_text(font, WHITE, 500, 550, ALLEGRO_ALIGN_CENTER, "Seconds: ");

            al_draw_text(font, WHITE, 600, 550, ALLEGRO_ALIGN_CENTER, gameLengthtxt);

            al_flip_display(); // flips the display (displays all of the drawn bitmaps and text

            if (sprite.XCoord < 0) {
                sprite.XCoord = 615;
            }
            if (sprite.XCoord > 616) {
                sprite.XCoord = 1;
            }

            for (int i = 0; i < starNumber; i++) {
                if (isCollision(Stars[i], sprite)) {
                    Stars[i].YCoord = rand() % 2000 - 2025;
                    Stars[i].XCoord = rand() % 615;
                    newUser.userScore++;
                }
            }
            for (int i = 0; i < asteroidNumber; i++) {
                if (isCollision(Asteroids[i], sprite)) {
                    Asteroids[i].YCoord = rand() % 2000 - 2025;
                    Asteroids[i].XCoord = rand() % 615;
                    newUser.userScore -= 2;
                }
            }
            for (int i = 0; i < planetNumber; i++) {
                if (isCollision(Planets[i], sprite)) {
                    Game = false;
                }
            }
        }

        al_destroy_display(display);

        if ((fileWrite = fopen( "UserScores.txt", "a")) != NULL) {
            fprintf(fileWrite, "%s %d ", newUser.userName, newUser.userScore);
            fprintf(fileWrite, "\n");
        }
        fclose(fileWrite);

        DisplayEnd(Screen_H, Screen_W, playAgain, rePlay);

        al_destroy_timer(objectTimer);
        al_destroy_timer(gameTime);
        al_destroy_timer(planetTimer);
        al_destroy_timer(spriteTimer);
    }

    for (int i = 0; i < starNumber; i++) {
        al_destroy_bitmap(Stars[i].picture);
    }
    for (int i = 0; i < asteroidNumber; i++) {
        al_destroy_bitmap(Asteroids[i].picture);
    }
    for (int i = 0; i < planetNumber; i++) {
        al_destroy_bitmap(Planets[i].picture);
    }

    al_destroy_bitmap(sprite.picture);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_bitmap(image);

    return 0;
}
