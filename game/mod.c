#include "g_local.h"
#include "mod.h"

/*
* -------------------------------------------
                    PLAYER
 -------------------------------------------
*/
void start_display_stats() {

    gi.dprintf("Starting to display stats.");
    edict_t* stats_timer = G_Spawn();
    stats_timer->think = display_stats;
    stats_timer->nextthink = level.time + 1;
}

void display_stats(edict_t* self) {
    edict_t* player = &g_edicts[1];

    //display the player stats.
    gi.centerprintf(player, "%d points, Round 1", player->points);

    self->nextthink = level.time + 1; // display stats every one second.
    self->think = display_stats; // callback for think function
}

void add_points(int points) {
	
    edict_t* player = &g_edicts[1];
	gi.dprintf("gained %d points.", points);
	player->points += points;
	
}

// will be linked from g_spawn.c
void ED_CallSpawn(edict_t* ent);


/*
* -------------------------------------------
                    ENEMIES
 -------------------------------------------
*/

// Function to spawn an enemy
void spawn_enemy(edict_t* spawner) {
    edict_t* enemy;

    // Create a new entity
    enemy = G_Spawn();
    if (!enemy)
        return;

    
    enemy->classname = "monster_soldier";

    // set position
    VectorCopy(spawner->s.origin, enemy->s.origin);

    ED_CallSpawn(enemy);

    //gi.dprintf("Soldier spawned at %f %f %f\n",
    //    enemy->s.origin[0], enemy->s.origin[1], enemy->s.origin[2]);
}

// Spawner logic
void enemy_spawner_think(edict_t* self) {
    if (level.time > self->nextthink) {
        spawn_enemy(self);
        self->nextthink = level.time + 3.0; // Schedule next spawn
    }

    //self->nextthink = level.time + 0.1; // Keep the think function running
}

// Spawner entity setup
void SP_enemy_spawner(edict_t* self) {
    self->movetype = MOVETYPE_NONE; // Spawner doesn't move
    self->solid = SOLID_NOT;       // No collision
    VectorSet(self->mins, -16, -16, -16);
    VectorSet(self->maxs, 16, 16, 16);
    self->think = enemy_spawner_think; // Set think function
    self->nextthink = level.time + 1.0; // Start thinking in 1 second

    gi.linkentity(self);
}