//all modular modded code in this header file.
#ifndef MOD_H
#define MOD_H

void start_display_stats();
void display_stats(edict_t* self);

void add_points(int points);

// Function to spawn an enemy
void spawn_enemy(edict_t* spawner);

// Spawner logic
void enemy_spawner_think(edict_t* self);

// Spawner entity setu
void SP_enemy_spawner(edict_t* self);



#endif // MOD_H