#include "functions.h"

extern int tick_count;

void make_gate(vector<vector<int>>& map, vector<vector<int>>& snake, vector<vector<int>>& gate) {
    
    if (tick_count % 50 == 1 and !snake_on_gate(snake, gate)) {
        int a = rand() % (2 * XG_SIZE + 2 * YG_SIZE - 4);
        int b = rand() % (2 * XG_SIZE + 2 * YG_SIZE - 4);
        while (a == b) b = rand() % (2 * XG_SIZE + 2 * YG_SIZE - 4);

        int c = 0;
        map[gate[0][0]][gate[0][1]] = map[gate[1][0]][gate[1][1]] = WALL; // init

        for (int i = 0; i < YG_SIZE; i++) {
            for (int j = 0; j < XG_SIZE; j++) {
                if (map[i][j] == WALL) {
                    if (c == a) { // gate 0
                        map[i][j] = GATE;
                        gate[0][0] = i;
                        gate[0][1] = j;
                    }
                    if (c == b) { // gate 1
                        map[i][j] = GATE;
                        gate[1][0] = i;
                        gate[1][1] = j;
                    }
                    c++;
                }
            }
        }
    }

}