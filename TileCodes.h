#ifndef TILECODES_H
#define TILECODES_H

// Colours
#define RED    'R'
#define ORANGE 'O'
#define YELLOW 'Y'
#define GREEN  'G'
#define BLUE   'B'
#define PURPLE 'P'

// Shapes
#define CIRCLE    1
#define STAR_4    2
#define DIAMOND   3
#define SQUARE    4
#define STAR_6    5
#define CLOVER    6

// M3 colour defines 
/*    Source: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
Source: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors      */

#define COLOUR_RESET  "\033[0m"
#define RED_COLOR     "\033[31m"
#define ORANGE_COLOR  "\033[1m\033[33m"
#define YELLOW_COLOR  "\033[33m"      
#define GREEN_COLOR   "\033[32m"      
#define BLUE_COLOUR   "\033[34m"
#define PURPLE_COLOR  "\e[0;35m"


#define MAX_TILES_IN_HAND 6
#define BOARD_DIM 26
#define NUM_OF_TILES 72 
#define NUM_OF_TILES_M3 108 

#endif // TILECODES_H
