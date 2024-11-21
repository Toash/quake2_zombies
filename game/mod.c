#include "g_local.h"
#include "mod.h"

qboolean debug = true;
/*
* -------------------------------------------
                    PLAYER
 -------------------------------------------
*/
void start_display_stats() {

    gi.dprintf("Starting to display stats.");
    edict_t* stats_timer = G_Spawn();
    stats_timer->nextthink = level.time + 1;
    stats_timer->think = display_stats_think;

}

void display_stats_think(edict_t* self) {
    edict_t* player = &g_edicts[1];

    //display the player stats.
    gi.centerprintf(player, "%d kills | Round 1 | %d points", player->kills,player->points);

    self->nextthink = level.time + 1; // reset the timer.
}

void add_points(int points) {
	
    edict_t* player = &g_edicts[1];
	gi.dprintf("gained %d points.", points);
	player->points += points;
	
}

void increase_kill_count() {

    edict_t* player = &g_edicts[1];
    player->kills += 1;
}


/*
* -------------------------------------------
                    ENEMIES
 -------------------------------------------
*/

#define MAX_SPAWNERS 20
edict_t* spawners[MAX_SPAWNERS];
int spawner_count = 0;

void register_spawner(edict_t* spawner) {
    if (spawner_count < MAX_SPAWNERS) {
        spawners[spawner_count++] = spawner;
        gi.dprintf("Spawner registered. Total spawners: %d\n", spawner_count);
    }
    else {
        gi.dprintf("Maximum spawner limit reached!\n");
    }
}

edict_t* get_random_spawner() {
    if (spawner_count == 0) {
        gi.dprintf("No spawners available!\n");
        return NULL;
    }
    int random_index = rand() % spawner_count;
    return spawners[random_index];
    
}

// unleash the wave
void start_enemy_spawn() {
    edict_t * spawner_entity = G_Spawn();
    if (!spawner_entity) {
        gi.dprintf("Could not create spawner entity");
    } 
    spawner_entity->think = enemy_spawn_think;
    spawner_entity->nextthink = 1; // initial spawn grace.

    gi.linkentity(spawner_entity);
    gi.dprintf("The zombiezz are coming");
}

void enemy_spawn_think(edict_t *self) {

    spawn_enemy_at_random_spawner();
    self->nextthink = level.time + 5; // reset the timer.
}
// Function to spawn an enemy at a random spawner
void spawn_enemy_at_random_spawner() {
    edict_t* spawner = get_random_spawner();
    if (spawner) {
        spawn_enemy(spawner);
    }
    else {
        gi.dprintf("Could not get a random spawner.");
    }
}


// will be linked from g_spawn.c
void ED_CallSpawn(edict_t* ent);

// Function to spawn an enemy
void spawn_enemy(edict_t* spawner) {
    edict_t* enemy;

    enemy = G_Spawn();
    if (!enemy)
    {
        gi.dprintf("Could not spawn an enemy.");
        return;
    }

    // determine what entity to spawn.
    enemy->classname = "monster_soldier_light";

    // set position
    // spawn a little higher to prevent clipping with the floor.
    vec3_t spawnpoint; 
    vec3_t offset = { 0,0,20 };
    VectorAdd(spawner->s.origin, offset, spawnpoint);

    VectorCopy(spawnpoint, enemy->s.origin );

    ED_CallSpawn(enemy);

    if (debug) {
        gi.dprintf("Soldier spawned at %f %f %f\n",
            enemy->s.origin[0], enemy->s.origin[1], enemy->s.origin[2]);
    }

}

// Spawner entity setup
void SP_enemy_spawner(edict_t* self) {

    gi.dprintf("ENEMY SPAWNWER CREATEWD");
    register_spawner(self);

    self->movetype = MOVETYPE_NONE; 
    self->solid = SOLID_NOT;       

    gi.linkentity(self);
}