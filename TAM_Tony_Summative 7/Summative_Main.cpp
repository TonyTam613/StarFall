/******************************************************************************************************
 *    Name: Tony Tam  Date Due: Jan. 18, 2018  Course Code: ISC3U                                     *
 *                                                                                                    *
 *        This game is a game where the player can move a sprite around and collect and avoid         *
 *    different falling objects. The stars will give your points, the asteroids will kill you         *
 *    and end the game, and the planets will take away points from your score.                        *
 ******************************************************************************************************/

#include "Summative_Header.h"


ALLEGRO_DISPLAY *display = nullptr; //add display object
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;		// add event queue object
ALLEGRO_BITMAP *image = nullptr;
ALLEGRO_TIMER *gameTime = nullptr;
ALLEGRO_TIMER *objectTimer = nullptr;
ALLEGRO_TIMER *planetTimer = nullptr;
ALLEGRO_TIMER *mouvementTimer = nullptr;
ALLEGRO_FONT *font = nullptr;

enum KEYS{LEFT, RIGHT};

int main(int argc, char *argv[]) {

    //Declaring some of my variables
    int starNumber = 20;
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
    InitializeAllegro();

    srand(time(nullptr));

    //Initializing my structures
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

    printf(" Input your name: ");
    scanf(" %s", newUser.userName);


    DisplayTitle(Screen_H, Screen_W);

    DisplayIntructions(Screen_H, Screen_W);

    DisplayGame(Screen_H, Screen_W);

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    ALLEGRO_FONT *font = al_load_ttf_font("nasalization-rg.ttf", 20, 0);

    for (int i = 0; i < starNumber; i++) {
        al_draw_bitmap(Stars[i].picture, Stars[i].XCoord, Stars[i].YCoord, 0);
    }
    for (int i = 0; i < asteroidNumber; i++) {
        al_draw_bitmap(Asteroids[i].picture, Asteroids[i].XCoord, Asteroids[i].YCoord, 0);
    }
    for (int i = 0; i < planetNumber; i++) {
        al_draw_bitmap(Planets[i].picture, Planets[i].XCoord, Planets[i].YCoord, 0);
    }

    // remove pink part of image
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

//    prints sprite on screen
	al_draw_bitmap(sprite.picture, sprite.XCoord, sprite.YCoord, 0);
	al_flip_display();

	al_start_timer(gameTime);
	al_start_timer(objectTimer);
	al_start_timer(planetTimer);
	al_start_timer(mouvementTimer);
    while (Game) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            Game = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    Game = false;
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
            }
        }
        else if (ev.timer.source == objectTimer) {
            for (int i = 0; i < starNumber; i++) {
                if (Stars[i].YCoord >= 521) {
                    Stars[i].YCoord = rand() % 2000 - 2025;
                    Stars[i].XCoord = rand() % 615;
                }
                else {
                    Stars[i].YCoord++;
                }
            }
            for (int i = 0; i < asteroidNumber; i++) {
                if (Asteroids[i].YCoord >= 521) {
                    Asteroids[i].YCoord = rand() % 2000 - 2025;
                    Asteroids[i].XCoord = rand() % 615;
                }
                else {
                    Asteroids[i].YCoord++;
                }
            }
        }
        else if (ev.timer.source == planetTimer) {
            for (int i = 0; i < planetNumber; i++) {
                if (Planets[i].YCoord >= 511) {
                    Planets[i].YCoord = rand() % 2000 - 2037;
                    Planets[i].XCoord = rand() % 603;
                }
                else {
                    Planets[i].YCoord++;
                }
            }
        }
        else if (ev.timer.source == gameTime) {
            gameLength++;
            if (objSpeed < 320) {
                if (gameLength % 10 == 0) {
                    objSpeed += 20;
                    planetSpeed += 20;
                    al_set_timer_speed(objectTimer, 1.0 / (50 + objSpeed));
                    al_set_timer_speed(planetTimer, 1.0 / (40 + planetSpeed));
                }
            }
        }
        else if (ev.timer.source == mouvementTimer) {
            sprite.XCoord += keys[RIGHT] * 5;
            sprite.XCoord -= keys[LEFT] * 5;
        }


        sprintf(gameLengthtxt, "%d", gameLength);

        sprintf(Scoretxt, "%d", newUser.userScore);

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

        al_flip_display();

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

    al_destroy_timer(objectTimer);
    al_destroy_timer(gameTime);
    al_destroy_timer(planetTimer);
    al_destroy_display(display);

    if ((fileWrite = fopen( "UserScores.txt", "a")) != NULL) {
        fprintf(fileWrite, "%s %d ", newUser.userName, newUser.userScore);
        fprintf(fileWrite, "\n");
    }
    fclose(fileWrite);

    for (int i = 0; i < starNumber; i++) {
        al_destroy_bitmap(Stars[i].picture);
    }
    for (int i = 0; i < asteroidNumber; i++) {
        al_destroy_bitmap(Asteroids[i].picture);
    }
    for (int i = 0; i < planetNumber; i++) {
        al_destroy_bitmap(Planets[i].picture);
    }

    DisplayEnd(Screen_H, Screen_W);
    al_destroy_event_queue(event_queue);

    return 0;
}
