
Problem 2
    [commit](https://github.com/RogueEffect/slide_puzzle_c/commit/55a1ea7a6132a1289493e938151bd86ca18cbdf3)

How can we handle moves?

On a physical slide puzzle we can slide a tile into the space. In a digital
  version we can accomplish the same by swapping the space with an adjacent tile

Consider the move below where we start with the solved board and swap L and space

```
  ABCD    ABCD
  EFGH -> EFGH
  IJKL    IJK 
  MNO     MNOL
```

Actually swapping tiles should be trivial, however we have to consider if a move
  is valid or not beforehand. Another thing to consider is how can we find out
  which tiles are able to move?

A simple way to handle a move would be to keep track of the spacer tile and do
  moves based around its location. Getting surrounding tiles will require more
  math, but it should be fairly simple

If you have the x and y location of the spacer tile you can find the following
  adjacent tiles with some simple arithmatic
  
  The tile above the space will be at (x, y - 1)
  The tile below will be at (x, y + 1)
  Left is (x - 1, y)
  and right is (x + 1, y)
  
These four moves should be the only valid moves in the game (assuming we dont try
  moving the space out of the board). An easy way to avoid going out of bounds
  would be to check that the position of the adjacent tile is 0 <= x < width
  and 0 <= y < height

Now we can work on two functions, one to handle moves and one to actually swap
  the tiles
