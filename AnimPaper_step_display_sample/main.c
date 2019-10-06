#include <stdio.h>
#include <stdlib.h>
#include "paper.h"

int main()
{
    init_paper(5,5,25,0.25,1);
    repeat(9) {
        if (get_color()==white) {
            change_color(black);
        } else {
            change_color(white);
        }
        colorize();
        move_right();
        colorize();
        move_down();
        colorize();
        move_left();
        colorize();
        move_up();
        step_display();
    } loop;
    display_paper();    
    return 0;
}
