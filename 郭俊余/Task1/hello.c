/*    
      一个 c语言+ncursesw 的花式 Hello World
      Copyright (C) 2019 郭俊余(Hagb)

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <https://www.gnu.org/licenses/>.
      */
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include "img.h"
#define ONCETIME 2000*1000      //in us
void
sigint (int param)
{
    clear ();
    refresh ();
    endwin ();
    printf ("Goodbye!\n");
    exit (0);
}

int
main (void)
{
    const int color[] = {
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_CYAN,
        COLOR_WHITE
    };
    const unsigned int colorn = sizeof (color) / sizeof (color[0]);
    srand ((unsigned) time (NULL));
    setlocale (LC_ALL, "");
    printf ("Hello,world!\n(And try to press Enter please)");
    getchar ();
    initscr ();
    start_color ();
    for (unsigned short num = 0; num < colorn; num++)
        init_pair (num, color[num], COLOR_BLACK);
    cbreak ();
    noecho ();
    signal (SIGINT, sigint);
    const long double s = ((long double) LINES) / height;
    const long double s2 = ((long double) height) / (LINES * 2);
    const unsigned int DELAY = ONCETIME / COLS;
    int colorpair;
    char mode = 0;
    char isColor = has_colors () && can_change_color ();
    for (unsigned int offest = 0; offest + 1 != 0;
         refresh (), usleep (DELAY), clear (), offest++)
        for (unsigned int w = 0; w <= COLS; w++)
            for (unsigned int h = 0; h <= LINES - 1; h++)
              {
                  char b1 =
                      header_data[((unsigned int) ((offest + w) * s2)) %
                                  width +
                                  (unsigned int) (2 * h * s2) * width];
                  char b2 =
                      header_data[((unsigned int) ((offest + w) * s2)) %
                                  width +
                                  (unsigned int) ((2 * h + 1) * s2) * width];
                  if (b1 || b2)
                    {
                        if (((unsigned int) (((offest + w) * s2)) / width) %
                            2)
                            attron (colorpair =
                                    COLOR_PAIR (rand () % colorn));
                        mvaddstr (h, w, b1
                                  && b2 ? "█" : b1 ? "▀" : "▄");
                        if (((unsigned int) (((offest + w) * s2)) / width) %
                            2)
                            attroff (colorpair);
                    }
              }
    sigint (0);
}
