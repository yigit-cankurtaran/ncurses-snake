#include <ncurses.h>

int main(int argc, char const *argv[])
{
    initscr();
    noecho();             // don't display keypresses
    cbreak();             // don't wait for enter
    keypad(stdscr, TRUE); // arrow keys
    curs_set(0);

    int x = 10, y = 10; // starting pos
    int ch;

    while (1)
    {
        clear();
        mvprintw(y, x, "@");
        refresh();

        ch = getch();
        if (ch == 'q')
            break;

        switch (ch)
        {
        case KEY_UP:
            if (y > 0)
                y--;
            break;
        case KEY_DOWN:
            if (y < 23)
                y++;
            break;
        case KEY_LEFT:
            if (x > 0)
                x--;
            break;
        case KEY_RIGHT:
            if (x < 79)
                x++;
            break;
        }
    }

    endwin();
    return 0;
}
