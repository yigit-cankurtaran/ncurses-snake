#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LEN 100
#define WIDTH 40
#define HEIGHT 20

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
    int food_x = rand() % WIDTH;
    int food_y = rand() % HEIGHT;
    int ch, direction = KEY_RIGHT; // default start dir
    bool game_over = false;

    while (!game_over)
    {
        clear(); // wipe screen before redraw

        // top-bottom walls
        for (int i = 0; i <= WIDTH + 1; i++)
        {
            mvprintw(0, i, "#");
            mvprintw(HEIGHT + 1, i, "#");
        }
        // left-right walls
        for (int i = 0; i <= HEIGHT + 1; i++)
        {
            mvprintw(0, i, "#");
            mvprintw(i, WIDTH + 1, "#");
        }

        mvprintw(food_y, food_x, "*");
        mvprintw(y, x, "@"); // snake head
        // snake tail
        for (int i = 0; i < tail_len; i++)
        {
            mvprintw(tail_y[i], tail_x[i], "o");
        }
        refresh();

        halfdelay(1); // 100ms for input then move
        // this is how we move even when we don't press anything
        // every loop switch(direction) runs and adjusts x or y

        ch = getch();
        if (ch == 'q')
            break;
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
        {
            direction = ch;
        }

        // head location before moving
        int prev_x = x, prev_y = y;

        switch (direction)
        {
        case KEY_UP:
            if (y > 0)
                y--;
            break;
        case KEY_DOWN:
            if (y < HEIGHT + 1)
                y++;
            break;
        case KEY_LEFT:
            if (x > 0)
                x--;
            break;
        case KEY_RIGHT:
            if (x < WIDTH + 1)
                x++;
            break;
        }

        // wall collision
        if (x <= 0 || x >= WIDTH + 1 || y <= 0 || y >= HEIGHT + 1)
        {
            game_over = true;
        }

        // tail collision
        for (int i = 0; i < tail_len; i++)
        {
            if (x == tail_x[i] && y == tail_y[i])
            {
                game_over = true;
            }
        }

        // eating food
        if (x == food_x && y == food_y)
        {
            tail_len++;
            // new food place
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
        }

        if (tail_len > 0)
        {
            // shift tail forward
            for (int i = 0; i < tail_len - 1; i++)
            {
                tail_x[i] = tail_x[i + 1];
                tail_y[i] = tail_y[i + 1];
            }
            // tail follows where head was
            tail_x[tail_len - 1] = prev_x;
            tail_y[tail_len - 1] = prev_y;

            printf("tail head position is (%d,%d)", tail_x[tail_len - 1], tail_y[tail_len - 1]);
        }
    }

    // Game over screen
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Game over!");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 5, "score: %d", tail_len);
    refresh();

    // RESET INPUT MODE TO NORMAL
    timeout(-1); // BLOCKING input
    cbreak();    // Disable halfdelay
    echo();      // Show what you type
    flushinp();  // Clear input buffer

    // WAIT FOR KEY
    getch();

    endwin();
    return 0;
}