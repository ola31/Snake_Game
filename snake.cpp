#include "functions.h"

extern WINDOW* game;
extern score score_;

bool d_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate);
bool cw_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate);
bool ccw_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate);
bool inv_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate);

void initialize_snake(vector<vector<int>>& snake) {

    snake.resize(3);
    snake[0] = { 3, 5, 5 }; // Snake head, initial posision: (y,x), direction 0, 1, 2, 3
    snake[1] = { 4, 5, 6 }; // Snake tail                                  up down left right
    snake[2] = { 4, 5, 7 }; // Snake tail
}

void make_snake(vector<vector<int>>& snake) // make snake on back screen
{
    for (int i = 0; i < snake.size(); i++) {
        wattron(game, COLOR_PAIR(snake[i][0]));
        mvwprintw(game, snake[i][Y], 2 * snake[i][X], "  "); // y, x
    }
}

void snake_moving(vector<vector<int>>& snake, int& direction, vector<vector<int>>& map, vector<vector<int>>& item_map, vector<vector<int>>& gate) // update position of snake
{
    if (item_map[snake[0][Y]][snake[0][X]] == POISON_ITEM) { // poison
        snake.pop_back();
        map[snake[0][Y]][snake[0][X]] = item_map[snake[0][Y]][snake[0][X]] = EMPTY;
        score_.Poison_item ++;
    }
    vector<int> tmp = snake[snake.size() - 1];

    // update tails
    for (int i = snake.size() - 1; i > 0; i--) { 
        snake[i][Y] = snake[i - 1][Y];
        snake[i][X] = snake[i - 1][X];
    }

    

    // update head
    if (direction == KEY_UP) snake[0][1] -= 1;
    else if (direction == KEY_DOWN) snake[0][1] += 1;
    else if (direction == KEY_LEFT) snake[0][2] -= 1;
    else if (direction == KEY_RIGHT) snake[0][2] += 1;
    int out_gate;
    if (snake[0][Y] == gate[0][0] and snake[0][X] == gate[0][1]) { // gate 0
        out_gate = 1;
        snake_gate_moving(map, snake, gate, direction, out_gate);
    }
    else if (snake[0][Y] == gate[1][0] and snake[0][X] == gate[1][1]) { // gate 1
        out_gate = 0;
        snake_gate_moving(map, snake, gate, direction, out_gate);
    }

    if (item_map[snake[0][Y]][snake[0][X]] == GROWTH_ITEM) { // growth
        snake.push_back(tmp);
        map[snake[0][Y]][snake[0][X]] = item_map[snake[0][Y]][snake[0][X]] = EMPTY;
        score_.Growth_item ++;
    }

    score_.Current_length = snake.size();

}

// snake가 gate를 통과하는 중인지 체크
bool snake_on_gate(vector<vector<int>>& snake, vector<vector<int>>& gate) {
    for (int i = 0; i < snake.size(); i++) {
        if (snake[i][1] == gate[0][0] and snake[i][2] == gate[0][1] or snake[i][1] == gate[1][0] and snake[i][2] == gate[1][1])
            return true;
    }

    return false;
}

void snake_gate_moving(vector<vector<int>>& map, vector<vector<int>>& snake, vector<vector<int>>& gate, int& direction, int out_gate) {
    
    score_.Gate_count ++;
    
    if (gate[out_gate][0] == 0) { // 출구가 위 가장자리
        snake[0][Y] = gate[out_gate][0] + 1;
        snake[0][X] = gate[out_gate][1];
        direction = KEY_DOWN;
    }
    else if (gate[out_gate][0] == YG_SIZE - 1) { // 출구가 아래 가장자리
        snake[0][Y] = gate[out_gate][0] - 1;
        snake[0][X] = gate[out_gate][1];
        direction = KEY_UP;
    }
    else if (gate[out_gate][1] == 0) { // 출구가 왼쪽 가장자리
        snake[0][Y] = gate[out_gate][0];
        snake[0][X] = gate[out_gate][1] + 1;
        direction = KEY_RIGHT;
    }
    else if (gate[out_gate][1] == XG_SIZE - 1) { // 출구가 오른쪽 가장자리
        snake[0][Y] = gate[out_gate][0];
        snake[0][X] = gate[out_gate][1] - 1;
        direction = KEY_LEFT;
    }
    else {
        if (d_check(map, gate, direction, out_gate));
        else if (cw_check(map, gate, direction, out_gate));
        else if (cw_check(map, gate, direction, out_gate));
        else if (inv_check(map, gate, direction, out_gate));

        if (direction == KEY_UP) snake[0][Y] = gate[out_gate][0] - 1, snake[0][X] = gate[out_gate][1];
        else if (direction == KEY_DOWN) snake[0][Y] = gate[out_gate][0] + 1, snake[0][X] = gate[out_gate][1];
        else if (direction == KEY_LEFT) snake[0][Y] = gate[out_gate][0], snake[0][X] = gate[out_gate][1] - 1;
        else if (direction == KEY_RIGHT) snake[0][Y] = gate[out_gate][0], snake[0][X] = gate[out_gate][1] + 1;
    }
}

// 진입 방향으로 진출 할 수 있는지
bool d_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate) {
    if (direction == KEY_UP and map[gate[out_gate][0] - 1][gate[out_gate][1]] != WALL) return true;
    else if (direction == KEY_DOWN and map[gate[out_gate][0] + 1][gate[out_gate][1]] != WALL) return true;
    else if (direction == KEY_LEFT and map[gate[out_gate][0]][gate[out_gate][1] - 1] != WALL) return true;
    else if (direction == KEY_RIGHT and map[gate[out_gate][0]][gate[out_gate][1] + 1] != WALL) return true;
    else return false;
}
// 진입 방향의 시계방향으로 진출 할 수 있는지
bool cw_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate) {
    if (direction == KEY_UP and map[gate[out_gate][0]][gate[out_gate][1] + 1] != WALL) {
        direction = KEY_RIGHT;
        return true;
    }
    else if (direction == KEY_DOWN and map[gate[out_gate][0]][gate[out_gate][1] - 1] != WALL) {
        direction = KEY_LEFT;
        return true;
    }
    else if (direction == KEY_LEFT and map[gate[out_gate][0] - 1][gate[out_gate][1]] != WALL) {
        direction = KEY_UP;
        return true;
    }
    else if (direction == KEY_RIGHT and map[gate[out_gate][0] + 1][gate[out_gate][1]] != WALL) {
        direction = KEY_DOWN;
        return true;
    }
    else return false;
}

// 진입 방향의 반시계방향으로 진출
bool cww_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate) {
    if (direction == KEY_UP and map[gate[out_gate][0]][gate[out_gate][1] - 1] != WALL) {
        direction = KEY_LEFT;
        return true;
    }
    else if (direction == KEY_DOWN and map[gate[out_gate][0]][gate[out_gate][1] + 1] != WALL) {
        direction = KEY_RIGHT;
        return true;
    }
    else if (direction == KEY_LEFT and map[gate[out_gate][0] + 1][gate[out_gate][1]] != WALL) {
        direction = KEY_DOWN;
        return true;
    }
    else if (direction == KEY_RIGHT and map[gate[out_gate][0] - 1][gate[out_gate][1]] != WALL) {
        direction = KEY_UP;
        return true;
    }
    else return false;
}
// 진입 방향의 반대방향으로 진출 할 수 있는지
bool inv_check(vector<vector<int>>& map, vector<vector<int>>& gate, int& direction, int out_gate) {
    if (direction == KEY_UP) direction = KEY_DOWN;
    else if (direction == KEY_DOWN) direction = KEY_UP;
    else if (direction == KEY_LEFT) direction = KEY_RIGHT;
    else if (direction == KEY_RIGHT) direction = KEY_LEFT;
    return true;
}