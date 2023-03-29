#include "Ball.h"
#include <stdio.h>

void update_ball(Ball* ball, PCONT* player, PCONT* player2, char* score_str){
	// labda mozgatása SPEED-el
	ball->rect.x += ball->vel_x;
	ball->rect.y += ball->vel_y;
	// x velocity megfordítása, ha a labda a jobb oldalához ér valamint pontozás (játékos 2nek) ezért a másik játékos "szervál"
	if(ball->rect.x <= 0){
		ball->rect.x = BALL_START_X;
		ball->rect.y = BALL_START_Y;
		ball->vel_x *= -1;
		player2->score++;
		sprintf(score_str, "%d  %d", player->score, player2->score);
	}
	// x velocity megfordítása, ha a labda a jobb oldalához ér valamint pontozás (játékos 1nek) ezért a másik játékos "szervál"
	if(ball->rect.x + ball->rect.w >= WINDOW_WIDTH){
		ball->rect.x = BALL_START_X;
		ball->rect.y = BALL_START_Y;
		ball->vel_x *= -1;
		player->score++;
		sprintf(score_str, "%d  %d", player->score, player2->score);
	}
	// y velocity megfordítása, ha a labda a tetejéhez ér
	if(ball->rect.y <= 0){
				ball->rect.y = 0;
				ball->vel_y *= -1;
			}
	// y velocity megfordítása, ha a labda az aljához ér
	if(ball->rect.y + ball->rect.h >= WINDOW_HEIGHT){
				ball->rect.y = WINDOW_HEIGHT - ball->rect.h;
				ball->vel_y *= -1;
			}
	// velocity megfordítása, ha a labda az első játékos pöckéhez ér (határain belül érkezik hozzá, legalább a labda széle érinti a pöcök szélét, csak ott ahol az x nagyobb mint player x, vagyis ott van a pöcök)
	if(ball->rect.y + ball->rect.h >= player->rect.y && ball->rect.y <= player->rect.y + player->rect.h && ball->rect.x >= player->rect.x && ball->rect.x <= player->rect.x + player->rect.w){
		ball->rect.x = player->rect.x + player->rect.w; // ha esetleg belemenne a pöcökbe, akkor visszatoljuk a labdát a pöcök szélére
		ball->vel_x *= -1;
	}
	// velocity megfordítása, ha a labda a második játékos pöckéhez ér
	if(ball->rect.y + ball->rect.h >= player2->rect.y && ball->rect.y - ball->rect.h <= player2->rect.y + player2->rect.h && ball->rect.x + ball->rect.w >= player2->rect.x && ball->rect.x <= player2->rect.x + player2->rect.w){
		ball->rect.x = player2->rect.x - ball->rect.w;
		ball->vel_x *= -1;
	}
	return;
}

