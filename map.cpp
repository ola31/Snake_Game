#include "functions.h"

extern WINDOW* game;

void set_obstacle_on_map(vector<vector<int>>& map, int stage) {

    int y_size = map.size();
    int x_size = map[0].size();
    for (int y = 1; y < y_size-1; y++) {
        for (int x = 1; x < x_size-1; x++) {
            map[y][x] = EMPTY;
        }
    }

    if (stage == 0) {
        // Obstacles 
        map[10][10] = map[10][11] = map[9][11] = map[10][12] = map[10][13] = WALL;
        map[15][20] = map[15][21] = map[15][22] = map[15][23] = WALL;
    }
    else if (stage == 1) {
        // Obstacles 
        map[6][10] = map[6][11] = map[6][12] = map[7][12] = map[8][12] = WALL;
        map[16][20] = map[17][20] = map[18][20] = map[19][20] = WALL;
    }
    else if (stage == 2) {
        // Obstacles 
        map[21][10] = map[21][10] = map[21][11] = map[21][12] = map[21][13] = map[22][13] = map[23][13] = WALL;
        map[10][20] = map[10][21] = map[10][22] = map[11][22] = map[10][23] = map[10][24] = WALL;
    }
    else if (stage == 3) {
        // Obstacles 
        map[10][10] = map[10][11] = map[9][11] = map[10][12] = map[10][13] = WALL;
        map[15][20] = map[15][21] = map[15][22] = map[15][23] = WALL;

        map[7][3] = map[7][4] = map[7][5] = map[7][6] = map[8][6] = map[9][6] = map[10][6] = WALL;
        map[15][20] = map[16][20] = map[15][21] = map[16][21] = WALL;

    }

}


void init_map(vector<vector<int>>& map, int y_size, int x_size)
{
    // Empty space : 10
    for (int j = 0; j < y_size; j++) {
        for (int i = 0; i < x_size; i++)
            if(map[j][i] != WALL) map[j][i] = EMPTY;
    }
    // Wall : 1
    for (int i = 1; i < x_size - 1; i++) map[0][i] = WALL;
    for (int i = 1; i < x_size - 1; i++) map[y_size - 1][i] = WALL;
    for (int j = 1; j < y_size - 1; j++) map[j][0] = 1;
    for (int j = 1; j < y_size - 1; j++) map[j][x_size - 1] = WALL;

    // Immune wall - 2
    map[0][0] = IMMUNE_WALL;
    map[0][x_size - 1] = IMMUNE_WALL;
    map[y_size - 1][0] = IMMUNE_WALL;
    map[y_size - 1][x_size - 1] = IMMUNE_WALL;


}

void make_map(vector<vector<int>>& map, int y_size, int x_size) { // make map on back screen
    for (int j = 0; j < y_size; j++) {
        for (int i = 0; i < x_size; i++) { // x range coution!!
            wattron(game, COLOR_PAIR(map[j][i]));
            mvwprintw(game, j, 2 * i, "  ");
        }
    }
}