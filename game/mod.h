//all modular modded code in this header file.
#ifndef MOD_H
#define MOD_H

void start_display_stats();
void display_stats_think(edict_t* self);

void add_points(int points);
void increase_kill_count();


void register_spawner(edict_t* spawner);
edict_t* get_random_spawner();
void start_enemy_spawn();
void enemy_spawn_think(edict_t* self);
void spawn_enemy_at_random_spawner();
void spawn_enemy(edict_t* spawner);
void SP_enemy_spawner(edict_t* self);




#endif // MOD_H