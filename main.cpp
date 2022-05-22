#include "functions.h"  
 
 
WINDOW* game; // game screen 
WINDOW* mission_board; 
WINDOW* score_board;

int tick_count;
int stage = 0;

score score_;
mission mission_;

int main() {

    Initialize_settings();

    int x_size = XG_SIZE; // 원도우 가로 사이즈 -> 주의!! Space 2개당 1칸
    int y_size = YG_SIZE; // 원도우 세로 사이즈 -> 주의!! Space 1개당 1칸
   

    game = newwin(YG_SIZE, 2* XG_SIZE, 1, 3);
    score_board = newwin(SCORE_WIN_SIZE_Y, SCORE_WIN_SIZE_X, Score_win_y, Score_win_x);
    mission_board = newwin(MISSION_WIN_SIZE_Y, MISSION_WIN_SIZE_X, Mission_win_y, Mission_win_x);

    vector<vector<int>> map(YG_SIZE, vector<int>(XG_SIZE, 0)); // Map, 원도우 가로 사이즈 -> 주의!! Space 2개당 1칸  
    vector<vector<int>> item_map(YG_SIZE, vector<int>(XG_SIZE, 0));
    vector<vector<int>> gate(2, vector<int>(2));

    gate[0] = { 0, 1 };
    gate[1] = { 0, 1 };

    vector<vector<int>> snake(3, vector<int>(3)); // Snake
    initialize_snake(snake);
    init_mission();

    set_obstacle_on_map(map, stage);
    init_map(map, y_size, x_size); // Map initialize

    int direction = KEY_LEFT;

    while (rule_check(snake, map)) {
        
        nodelay(stdscr, TRUE);

        int c = getch();
        if (c != -1) direction = c; // if input value exist
        
        make_gate(map, snake, gate);
        snake_moving(snake, direction, map, item_map, gate);
        spawn_item_on_map(item_map, map);

        make_map(map, y_size, x_size);
        make_snake(snake);
        wrefresh(game);
        update_boards();

        if (stage_clear_check()) {
            if (++stage > 3) break;
            direction = KEY_LEFT;
            move_to_next_stage(map, snake, stage);
        }
        Sleep(dt); //0.5 sec

        tick_count++;
    }


    getch();
    delwin(game);
    delwin(mission_board);
    delwin(score_board);
    endwin();

    return 0;
}