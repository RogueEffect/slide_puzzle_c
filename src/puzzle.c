
/*

Slide Puzzle

    Simple sliding puzzle to practice C.

rogueeffect

*/

#include <stdio.h>
#include <string.h> // We need this for memset and later memcpy


// Let's define some constants
#define WIDTH   4 // These two for the board width and height
#define HEIGHT  4 // We may want to have larger boards later
#define SQUARE_SIZE     2 // This will be how wide and tall we draw the tiles
// These constants will be the actual size of the board when drawn
#define BOARD_WIDTH     (SQUARE_SIZE * WIDTH + 1)
#define BOARD_HEIGHT    (SQUARE_SIZE * HEIGHT + 1)
#define INDENT  4 // Indent when drawing the board

// We can use the constants here now
char    tiles[WIDTH * HEIGHT];

void    init();
void    draw_board();



int main(int argc, char** argv) {
    printf("Testing print function... again\n");
    init();
    draw_board();
    
    printf("done.\n");
}



void init() {
    // Use the constants here as well
    for(int i = 0; i < WIDTH * HEIGHT - 1; i++) {
        char c = 'A' + i;
        tiles[i] = c;
    }
    tiles[WIDTH * HEIGHT - 1] = ' ';
}

void draw_board() {
    // With larger boards many calls to printf or putc will slow down our draw
    //   function too much. Let's use a char buffer per line to reduce prints
    printf("\n");
    for(int y = 0; y < BOARD_HEIGHT; y++) {
        // The buffer will need to be the board width + 1 for the null
        char buffer[BOARD_WIDTH + 1];
        for(int x = 0; x < BOARD_WIDTH; x++) {
            char c = ' '; // Empty space if square size is more than 2
            // Time for more math
            if(y % SQUARE_SIZE == 0) c = '-'; // Horizontal tile separators
            else if(x % SQUARE_SIZE == 0) c = '|'; // Vertical separators
            // This will place the tile letter on the top left of its tile
            //   Later we can do some math to center it in it's tile
            if(x % SQUARE_SIZE == 1 && y % SQUARE_SIZE == 1) {
                // To get the proper x and y for tiles array we can just divide
                //   by square size
                int tx = x / SQUARE_SIZE;
                int ty = y / SQUARE_SIZE;
                // Take care not to use board width or you'll go out of bounds
                c = tiles[tx + ty * WIDTH];
            }
            // Write the char to the buffer
            buffer[x] = c;
        }
        // Add a null terminator
        buffer[BOARD_WIDTH] = '\0';
        // A small buffer for the indent
        char indent[INDENT + 1];
        // Set all chars to spaces
        memset(indent, ' ', INDENT);
        // Null
        indent[INDENT] = '\0';
        // Print the indent immediately followed by the board buffer
        printf("%s%s\n", indent, buffer);
    }
    printf("\n");
}


// Now our board looks a bit better, you can even change the board size and 
//   square size to see what larger boards would look like
// Because larger boards would mean more print statements, this is still not the
//   the most optimal way to print the board
// We could make one large buffer to contain the whole board and indents then
//   print it all at once to speed it up a bit
//
// If you're having trouble understanding the math involved with drawing the
// board, maybe this figure will help you (Assume board is 4x4 and square is 2)
//
//  0123456789 X Each row is a buffer 10 long (remember we need nulls)
// 0---------\0  Meanwhile our outer loop goes for 9 iterations
// 1| | | | |\0  Inside the two loops our first if statement deals with
// 2---------\0    whether or not y is on a row where we want horizontal
// 3| | | | |\0    seperators (y % SQUARE_SIZE == 0) so every other row
// 4---------\0    is filled with - chars
// 5| | | | |\0  The if-else statement only happens when the previous if is
// 6---------\0    not true. Here every other char is | and if it was not
// 7| | | | |\0    changed, we add a space instead
// 8---------\0  Then if x and y is the first space inside a tile, we grab
// Y               the appropriate char from the tiles array