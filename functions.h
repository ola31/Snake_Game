#pragma once
#include "curses.h"
#include <vector>
#include <cstdlib> 

#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;


#define XW_SIZE      120 // default window size
#define YW_SIZE      32  //
                     
#define XG_SIZE      30  // game window size
#define YG_SIZE      30  // 

#define SCORE_WIN_SIZE_X 40
#define SCORE_WIN_SIZE_Y 10
#define MISSION_WIN_SIZE_X 40
#define MISSION_WIN_SIZE_Y 10

#define Score_win_x    (3 + (2 * XG_SIZE) + (1*2))
#define Score_win_y    1
#define Mission_win_x  (3 + (2 * XG_SIZE) + (1*2))
#define Mission_win_y  (1 + SCORE_WIN_SIZE_Y + (1))


#define WALL            1
#define IMMUNE_WALL     2
#define HEAD            3
#define TAIL            4
#define GROWTH_ITEM     5
#define POISON_ITEM     6
#define GATE            7
#define EMPTY          10
#define SCORE_BOARD    11
#define MISSION_BOARD  12

#define MAX_LENGTH 5//10
#define MIN_LENGTH 3

#define MAX_GOAL_GROWTH_ITEM 2 //10
#define MAX_GOAL_POISON_ITEM 2 //10
#define MAX_GOAL_GATE_COUNT  2 //10

#define dt 500 //0.5ms

#define Y 1
#define X 2

struct Score {
    int Current_length = 3;
    int Growth_item = 0;
    int Poison_item = 0;
    int Gate_count = 0;
};
struct Mission {
    int Goal_length;
    int Growth_item;
    int Poison_item;
    int Gate_count;

    char Goal_length_done = ' ';
    char Growth_item_done = ' ';
    char Poison_item_done = ' ';
    char Gate_count_done  = ' ';
};
typedef Score score;
typedef Mission mission;

void init_map(vector<vector<int>>& map, int y_size, int x_size);
void make_map(vector<vector<int>>& map, int y_size, int x_size);
void initialize_snake(vector<vector<int>>& snake);
void make_snake(vector<vector<int>>& snake);
void snake_moving(vector<vector<int>>& snake, int& direction, vector<vector<int>>& map, vector<vector<int>>& item_map, vector<vector<int>>& gate);
bool rule_check(vector<vector<int>>& snake, vector<vector<int>>& map);
void spawn_item_on_map(vector<vector<int>>& item_map, vector<vector<int>>& main_map);
void Initialize_settings(void);
void make_gate(vector<vector<int>>& map, vector<vector<int>>& snake, vector<vector<int>>& gate);
bool snake_on_gate(vector<vector<int>>& snake, vector<vector<int>>& gate);
void snake_gate_moving(vector<vector<int>>& map, vector<vector<int>>& snake, vector<vector<int>>& gate, int& direction, int out_gate);

void init_mission(void);
void update_boards(void);
void clear_score_and_mission(void);

void set_obstacle_on_map(vector<vector<int>>& map, int stage);
bool stage_clear_check(void);
void move_to_next_stage(vector<vector<int>>& map, vector<vector<int>>& snake, int& stage);