#include <ncurses.h>

int main(int argc, char const *argv[])
{
    initscr();
    printw("snake is coming...");
    refresh();
    getch(); // wait for keypress
    endwin();
    return 0;
}
