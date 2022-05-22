#include "functions.h"

extern WINDOW* mission_board;
extern WINDOW* score_board;

extern score score_;
extern mission mission_;

void init_mission(void) {  // ���������� ��ǥ �̼ǰ��� ���� �Ҵ�
    mission_.Goal_length = (rand() % (MAX_LENGTH - MIN_LENGTH)) + MIN_LENGTH +1;
    mission_.Growth_item =  rand() % MAX_GOAL_GROWTH_ITEM + 1;
    mission_.Poison_item =  rand() % MAX_GOAL_POISON_ITEM + 1;
    mission_.Gate_count  =  rand() % MAX_GOAL_GATE_COUNT + 1;
}



void update_mission_board(void) {  //�̼� board ������Ʈ
    wbkgd(mission_board, COLOR_PAIR(MISSION_BOARD)); //white
    wattron(mission_board, COLOR_PAIR(MISSION_BOARD));
    mvwprintw(mission_board, 1, 1  , "Mission");
    mvwprintw(mission_board, 3, 1, "B: %2d  (%c)", mission_.Goal_length,mission_.Goal_length_done);
    mvwprintw(mission_board, 4, 1, "+: %2d  (%c)", mission_.Growth_item,mission_.Growth_item_done);
    mvwprintw(mission_board, 5, 1, "-: %2d  (%c)", mission_.Poison_item,mission_.Poison_item_done);
    mvwprintw(mission_board, 6, 1, "G: %2d  (%c)", mission_.Gate_count, mission_.Gate_count_done);
  
    wrefresh(mission_board);
    
}


void check_completed_mission(void) { //�� �̼� �׸��� �޼��� ��� v(üũǥ��) 
    if (score_.Current_length >= mission_.Goal_length) mission_.Goal_length_done = 'v';
    else mission_.Goal_length_done = ' ';

    if (score_.Growth_item    >= mission_.Growth_item) mission_.Growth_item_done = 'v';
    else mission_.Growth_item_done = ' ';

    if (score_.Poison_item    >= mission_.Poison_item) mission_.Poison_item_done = 'v';
    else mission_.Poison_item_done = ' ';

    if (score_.Gate_count     >= mission_.Gate_count)  mission_.Gate_count_done  = 'v';
    else mission_.Gate_count_done = ' ';
}


void update_score_board(void) {  // ���ھ� ���� ������Ʈ
    wbkgd(score_board, COLOR_PAIR(SCORE_BOARD)); //white
    wattron(score_board, COLOR_PAIR(SCORE_BOARD));
    mvwprintw(score_board, 1, 1, "Score Board");
    mvwprintw(score_board, 3, 1, "B: %2d / %2d", score_.Current_length, mission_.Goal_length);
    mvwprintw(score_board, 4, 1, "+: %2d ", score_.Growth_item);
    mvwprintw(score_board, 5, 1, "-: %2d ", score_.Poison_item);
    mvwprintw(score_board, 6, 1, "G: %2d ", score_.Gate_count);

    check_completed_mission();  // �� �̼��� ���� �� ��� v(üũ ǥ��)

    wrefresh(score_board);

}

void clear_score_and_mission(void) {  //���� ���������� �Ѿư��� ���� �̼� �޼� ����� �ʱ�ȭ
    score_.Current_length = 3;
    score_.Growth_item = 0;
    score_.Poison_item = 0;
    score_.Gate_count = 0;
}



void update_boards(void) {  //�̼�, ���ھ� ������Ʈ(main �Լ����� ȣ���)
    update_mission_board();
    update_score_board();
}

bool stage_clear_check(void) {  //���� �������� Ŭ���� ���� üũ
    if (
        (score_.Current_length >= mission_.Goal_length) &&
        (score_.Growth_item >= mission_.Growth_item) &&
        (score_.Poison_item >= mission_.Poison_item) &&
        (score_.Gate_count >= mission_.Gate_count)
        )
    {
        return true;
    }
    else return false;
}

void move_to_next_stage(vector<vector<int>>& map, vector<vector<int>>& snake, int& stage) { 
    //���� ���������� �Ѿ�� �۾� ����(���� �ʱ�ȭ, ��ֹ� ���ġ)

    int y_size = map.size();
    int x_size = map[0].size();
    initialize_snake(snake);
    clear_score_and_mission();

    init_mission();
    set_obstacle_on_map(map, stage);  //��ֹ� ���ġ
    init_map(map, y_size, x_size); // Map initialize
}