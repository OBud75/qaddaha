#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

int main() {
    // Début du programme
    int res, top = 0;
    

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (res != 'q') {
        res = getch();
        if (res != ERR) {
            printw("Touche pressee : %c\n", res);
        }
        if(clock()>top+10000){
            top = clock();
            putchar('0');
        }

    }

    endwin();
    return 0;
}