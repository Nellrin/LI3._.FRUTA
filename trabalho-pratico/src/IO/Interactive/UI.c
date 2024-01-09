#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Interactive/UI.h"

static void terminal_write_line(int line){
    printf("\033[%d;0H", line + 1);
}
int terminal_width(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
int terminal_height(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}
void bottom_of_terminal(){
    printf("\033[999;1H");
}
///////////////////////////////////////////////////////////////
void clear_terminal(){
    printf("\033[2J");
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void better_UI(char ** list_strings, int amount){

    for(int i = 0; i < amount; i++){
        terminal_write_line(atoi(list_strings[i]));

        if((list_strings[i][3]) == '@'){
            for(int j = 0; j<terminal_width(atoi(&list_strings[i][5]));j++)
            printf("%c",list_strings[i][4]);
        }

        else
        printf("%s",(list_strings[i]+3));
    }
    
}
///////////////////////////////////////////////////////////////
