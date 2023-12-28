#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Interactive/Interactive.h"
#include "../../include/Output.h"
#include "../../include/Interpreter.h"
///////////////////////////////////////////////////////////////

void interactive_mode() {
    // Initialize ncurses
    WINDOW * window = initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Check if terminal supports colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }

    // Create a window
    WINDOW *win = newwin(10, 30, 5, 5);

    // Enable scrolling for the window
    scrollok(win, TRUE);

    // Print messages with different colors
    wattron(win, COLOR_PAIR(1));
    wprintw(win, "Error: Something went wrong!\n");
    wattroff(win, COLOR_PAIR(1));

    wattron(win, COLOR_PAIR(2));
    wprintw(win, "Success: Operation completed.\n");
    wattroff(win, COLOR_PAIR(2));

    // Refresh and wait for a key press
    wrefresh(win);

    int ch;
    while ((ch = wgetch(win)) != 'x') {
        // You can handle other key presses here if needed
    }

    // Clean up
    delwin(win);
    delwin(window);

    // End ncurses mode
    endwin();
exit_curses(0);
_nc_freeall();
    printf("done\n");
}



///////////////////////////////////////////////////////////////