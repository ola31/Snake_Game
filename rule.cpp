#include "functions.h"

bool rule_check(vector<vector<int>>& snake, vector<vector<int>>& map)
{
    // lenght is less than 3
    if (snake.size() < 3) return false;

    // touch the wall
    if (map[snake[0][Y]][snake[0][X]] == WALL) return false;

    // touch itself
    for (int i = 1; i < snake.size(); i++) {
        if (snake[0][Y] == snake[i][Y] and snake[0][X] == snake[i][X]) return false;
    }

    return true;
}