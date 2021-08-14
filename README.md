
Problem 3
    [commit](https://github.com/RogueEffect/slide_puzzle_c/commit/37219237bb4b5fe6d9d95372b21c55a44da05fee)

Shuffling tiles and getting user input

We can shuffle the board by creating a loop that performs a few hundred valid
moves on the board. Performing actual moves is important as just shuffling
the tiles could create an unsolvable puzzle

As for input, a fancier console program would use something like conio or curses
to draw to the screen and get input. For this project I'm going to keep it
simple and print the board for every move the user makes. We can use simple
getc calls and do some action based on the character given. We will also want
to have a loop to keep asking for input until the puzzle is solved or the
player quits
