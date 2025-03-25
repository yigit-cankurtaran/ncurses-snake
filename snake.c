#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// BUG: after we eat the food the @ becomes an o

#define MAX_LEN 100

int main(int argc, char const *argv[])
{
    initscr();
    noecho();             // don't display keypresses
    cbreak();             // don't wait for enter
    keypad(stdscr, TRUE); // arrow keys
    curs_set(0);
    srand(time(NULL));

    int x = 10, y = 10; // starting pos
    int tail_x[MAX_LEN], tail_y[MAX_LEN];
    int tail_len = 0;
    int food_x = rand() % 80;
    int food_y = rand() % 24;
    int ch, direction = KEY_RIGHT; // default start dir

    while (1)
    {
        clear();
        mvprintw(food_y, food_x, "*");
        mvprintw(y, x, "@"); // snake head
        // snake tail
        for (int i = 0; i < tail_len; i++)
        {
            mvprintw(tail_y[i], tail_x[i], "o");
        }
        refresh();

        halfdelay(1); // 100ms for input then move
        ch = getch();
        if (ch == 'q')
            break;

        if (tail_len < MAX_LEN)
        {
            tail_x[tail_len] = x;
            tail_x[tail_len] = y;
        }

        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
        {
            direction = ch;
        }

        switch (direction)
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

        // eating food
        if (x == food_x && y == food_y)
        {
            tail_len++;
            // new food place
            food_x = rand() % 80;
            food_y = rand() % 24;
        }
        else if (tail_len > 0)
        {
            // shift tail forward
            for (int i = 0; i < tail_len - 1; i++)
            {
                tail_x[i] = tail_x[i + 1];
                tail_y[i] = tail_y[i + 1];
            }
            tail_x[tail_len - 1] = x;
            tail_y[tail_len - 1] = y;
        }
    }

    endwin();
    return 0;
}
