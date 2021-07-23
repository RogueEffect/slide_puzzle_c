
/*

Slide Puzzle

    Simple sliding puzzle to practice C.

rogueeffect

*/

#include <stdio.h>


// I like using 1d arrays, but you could used a 2d array here.
// Note that with my solution I don't need a null terminator because
//   I'm not going to print this conventionally.
char    tiles[16];

// Function declarations. Definitions at the end.
void    init();
void    draw_board();



int main(int argc, char** argv) {
    printf("Testing print function...\n");
    init();
    draw_board();
    
    // This may help us find out if theres a crash
    printf("done.\n");
}



// We will probably do more than init tiles here so lets keep the name broad
void init() {
    // Here we can loop through and populate the tiles array with letters
    for(int i = 0; i < 15; i++) { // 15 loops becase we will set the final
        char c = 'A' + i;         // tile manually (chars are just like ints
        tiles[i] = c;             // so you can do math on them)
    }
    tiles[15] = ' '; // Manually set the spacer tile at the end
}

// This function will only draw the board. For now lets forgo the fancy border
void draw_board() {
    // This loop goes row by row
    for(int y = 0; y < 4; y++) {
        // An indent so the board isnt on the edge of the window
        printf("  ");
        // This loop goes column by column
        for(int x = 0; x < 4; x++) {
            // Here you could just do tiles[y][x] or tiles[x][y]
            //   depending on how you populate a 2d array
            // With my method I'll just use some math to get the right chars
            putc(tiles[x + y * 4], stdout);
        }
        putc('\n', stdout);
    }
}


// After building and running, this solution worked. Now we can think about
//   fancier ways to print the board.
// With more printing operations however, we will have to think about
//   optimizing a bit.
