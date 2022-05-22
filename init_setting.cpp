#include "functions.h"

void Initialize_settings(void) {

    initscr();

    // Color Setting
    start_color();
    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);        // Wall color         : White
    init_pair(IMMUNE_WALL, COLOR_CYAN, COLOR_CYAN);   // Immune wall color  : Cyans
    init_pair(HEAD, COLOR_YELLOW, COLOR_YELLOW);      // Snake head         : Yellow
    init_pair(TAIL, 14, 14);                          // Snake tail         : Bright Yellow
    init_pair(GROWTH_ITEM, COLOR_GREEN, 10);          // Growth item        : Green
    init_pair(POISON_ITEM, COLOR_RED, 12);            // Poison item        : Red
    init_pair(GATE, COLOR_MAGENTA, 13);               // Gate               : Magenta

    init_pair(EMPTY, COLOR_CYAN, COLOR_CYAN);         // Empty color - Cyans

    init_pair(SCORE_BOARD, COLOR_BLACK, COLOR_WHITE);   // Score Board  word : black, background : white
    init_pair(MISSION_BOARD, COLOR_BLACK, COLOR_WHITE); // Mission Board  word : black, background : white

    // Keyboard Setting 
    keypad(stdscr, TRUE); // 특수문자 입력 가능
    curs_set(0); // 커서 사라짐
    noecho(); // 입력문자 안보이게

    srand(time(NULL));

    resize_term(YW_SIZE, XW_SIZE);
    refresh();

}



