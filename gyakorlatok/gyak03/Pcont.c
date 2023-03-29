#include "Ball.h"
#include "Pcont.h"

void playerControls(PCONT* player){
	// adott player mozgatása
	if(player->controls[0] && !player->controls[1]) player->rect.y -= 5;
	if(player->controls[1] && !player->controls[0]) player->rect.y += 5;
	// limitálás 0, ha a játékos a felső szélére ér, window_height ha a játékos a alsó szélére ér (fejjel lefele van ugye a koordináta rendszer)
	if(player->rect.y <= 0) player->rect.y = 0;
	if(player->rect.y + player->rect.h >= WINDOW_HEIGHT) player->rect.y = WINDOW_HEIGHT - player->rect.h;
	return;
}
