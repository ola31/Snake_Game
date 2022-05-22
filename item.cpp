#include "functions.h"

extern int tick_count;

void spawn_item_on_map(vector<vector<int>>& item_map, vector<vector<int>>& main_map) {
    int X_length = item_map[0].size();
    int Y_length = item_map.size();

    int y, x;
    int item;
    int number_or_item;

    if (tick_count % 20 == 19) {
        for (int x = 0; x < X_length; x++) {
            for (int y = 0; y < Y_length; y++) {
                if (item_map[y][x] == POISON_ITEM or item_map[y][x] == GROWTH_ITEM) {
                    main_map[y][x] = item_map[y][x] = EMPTY; // back ground
                }
            }
        }
        number_or_item = rand() % 3 + 1;  //1~3°³

        for (int i = 0; i < number_or_item; i++) {
            do {
                x = rand() % (X_length - 3) + 1;
                y = rand() % (Y_length - 3) + 1;
            } while (main_map[y][x] != 10);
            item = (rand() % 2 == 0) ? POISON_ITEM : GROWTH_ITEM; // poison: 6, growth: 5
            item_map[y][x] = item;
        }

    }
    for (int x = 0; x < X_length; x++) {
        for (int y = 0; y < Y_length; y++) {
            if (item_map[y][x] == POISON_ITEM or item_map[y][x] == GROWTH_ITEM) {
                main_map[y][x] = item_map[y][x];
            }
        }
    }

}
