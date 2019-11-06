#include <ncursesw/ncurses.h>
#include <locale.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define SNAKE 1
#define BLOCK 2
#define FOOD 3
#define TIMEOUT 100             /* in ms */
#define SCORETEXT "Score:"
#define XUP 0
#define XDOWN 1
#define YUP 2
#define YDOWN 3
const int COLOR[] = { COLOR_BLACK, COLOR_BLUE, COLOR_WHITE, COLOR_GREEN };

unsigned int emptynum;
#define COLORNUM (sizeof(COLOR)/sizeof(COLOR[0]))
#define DRAWSTR ("▀")
unsigned int score;
char *block;
char *dir;
unsigned int xnum;
unsigned int ynum;
#define blockxy(x,y) (block[(x)+(y)*xnum])
char
unit (const unsigned int x, const unsigned int y)
{
    return x >= xnum || y >= ynum ? BLOCK : blockxy (x, y);
}

void
drawPoint (unsigned int x, unsigned int y)
{
    unsigned int y1 = (y / 2) * 2;
    int tmp;
    attron (tmp =
            COLOR_PAIR (blockxy (x, y1) + COLORNUM * blockxy (x, y1 + 1) +
                        1));
    mvaddstr (1 + y1 / 2, x + 2, DRAWSTR);
    attroff (tmp);

}

void
drawAllPoint (void)
{
    for (unsigned int x = 0; x < xnum; x++)
        for (unsigned int y = 0; y < ynum; y += 2)
          {
              unsigned int tmp;
              attron (tmp =
                      COLOR_PAIR (blockxy (x, y) +
                                  COLORNUM * blockxy (x, y + 1) + 1));
              mvaddstr (1 + y / 2, x + 2, DRAWSTR);
              attroff (tmp);
          }
}

void
drawFrame (void)
{
    for (unsigned int x = 0; x < COLS; x++)
      {
          mvaddstr (0, x, "█");
          mvaddstr (LINES - 3, x, "█");
      }
    for (unsigned int y = 1; y < LINES - 3; y++)
      {
          mvaddstr (y, 0, "██");
          mvaddstr (y, COLS - 2, "██");
      }
}

void
drawInfo (void)
{
    char scorestr[sizeof (unsigned int) + 1];
    mvaddstr (LINES - 2, 0, SCORETEXT);
    sprintf (scorestr, "%u", score);
    mvaddstr (LINES - 2, sizeof (SCORETEXT) - 1, scorestr);
}

void
sigint (int param)
{
    while (getch () != ERR);
    clear ();
    refresh ();
    endwin ();
    free (block);
    free (dir);
    printf ("Score: %u\nGoodbey!\n", score);
    exit (0);
}

void
gameover (void)
{
    init_pair (1, COLOR_RED, COLOR_WHITE);
    attron (COLOR_PAIR (1));
    mvaddstr (LINES - 1, 0, "Game Over!!!!!");
    attroff (COLOR_PAIR (1));
    refresh ();
    sleep (1);
    sigint (0);
}

void
addFood (void)
{
    unsigned int tmp = rand () % emptynum;
    unsigned int pointer = 0 - 1;
    while (block[++pointer] != 0 || tmp--);
    block[pointer] = FOOD;
    emptynum--;
    drawPoint (pointer % xnum, pointer / xnum);
}

int
main (void)
{
    srand ((unsigned) time (NULL));
    setlocale (LC_ALL, "");
    WINDOW *window = initscr ();
    start_color ();
    for (unsigned short bnum = 0; bnum < COLORNUM; bnum++)
        for (unsigned short anum = 0; anum < COLORNUM; anum++)
            init_pair (1 + anum + COLORNUM * bnum, COLOR[anum], COLOR[bnum]);
    cbreak ();
    noecho ();
    signal (SIGINT, sigint);
    timeout (TIMEOUT);
    keypad (window, 1);

    xnum = COLS - 4;
    ynum = (LINES - 4) * 2;
    unsigned int num = xnum * ynum;
    block = (char *) calloc (num, 1);
    dir = (char *) calloc (num, 1);
    for (unsigned int pointer = 0; pointer <= num; pointer++)
        block[pointer] = 0;
    score = 0;
    emptynum = num - 1;
    unsigned int head[2] = { 0, 0 };
    unsigned int tail[2] = { 0, 0 };
    dir[0] = XUP;
    blockxy (0, 0) = SNAKE;
    unsigned int snakepointer = 0;
    addFood ();
    drawInfo ();
    drawFrame ();
    drawAllPoint ();

    while (1)
      {
          const unsigned int pointer1 = (snakepointer + score) % num;
          switch (getch ())
            {
            case KEY_LEFT:     //x+
                if (!score || XUP != dir[pointer1])
                    dir[pointer1] = XDOWN;
                break;
            case KEY_RIGHT:    //x-
                if (!score || XDOWN != dir[pointer1])
                    dir[pointer1] = XUP;
                break;
            case KEY_UP:       //y-
                if (!score || YUP != dir[pointer1])
                    dir[pointer1] = YDOWN;
                break;
            case KEY_DOWN:     //y+
                if (!score || YDOWN != dir[pointer1])
                    dir[pointer1] = YUP;
                break;
            case 'q':
                sigint (0);
            }
          dir[(pointer1 + 1) % num] = dir[pointer1];
          head[0] += (dir[pointer1] == XUP) - (dir[pointer1] == XDOWN);
          head[1] += (dir[pointer1] == YUP) - (dir[pointer1] == YDOWN);
          switch (unit (head[0], head[1]))
            {
            case BLOCK:
                gameover ();
            case SNAKE:
                gameover ();
            case FOOD:
                score++;
                addFood ();
                break;
            case 0:
                blockxy (tail[0], tail[1]) = 0;
                drawPoint (tail[0], tail[1]);
                tail[0] +=
                    (dir[snakepointer] == XUP) - (dir[snakepointer] == XDOWN);
                tail[1] +=
                    (dir[snakepointer] == YUP) - (dir[snakepointer] == YDOWN);
                snakepointer = (snakepointer + 1) % num;
            }
          blockxy (head[0], head[1]) = SNAKE;
          drawPoint (head[0], head[1]);
          drawInfo ();
          refresh ();
      }


    sigint (0);
}
