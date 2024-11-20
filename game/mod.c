#include "g_local.h"
void add_points(int points) {
	edict_t* player = &g_edicts[1]; 
	gi.dprintf("gained %d points.", points);
	player->points += points;
	gi.centerprintf(player, "%d points", player->points);
}