# Terminal based TicTacToe AI
This unbeatable TicTacToe AI was implemented in as few lines of code as possible without sacrifing readability and performance. AI uses minimax algorithm with alpha-beta pruning.
# How to play #
Run the code from main.cpp using a compiler of your choice. Or alternatively, run the code on an [online compiler](https://www.onlinegdb.com/online_c++_compiler)

AI is `X` and you are `O`

Input format of coordinates : `<row><space><column>`

`<row>`, `<column>` must be an integer between 1 and 3 inclusive. An invalid input will end your turn or will crash program.
# Gameplay #

## AI starts first ##
```cpp
AI starts first? 1/0 1
X..
...
...

1 2
XO.
...
...

XO.
X..
...

3 1
XO.
X..
O..

XO.
XX.
O..

2 3
XO.
XXO
O..

XO.
XXO
O.X

AI won!

```

## You start first ##
```cpp
AI starts first? 1/0 0
2 2
...
.O.
...

X..
.O.
...

1 2
XO.
.O.
...

XO.
.O.
.X.

2 3
XO.
.OO
.X.

XO.
XOO
.X.

3 1
XO.
XOO
OX.

XOX
XOO
OX.

3 3
XOX
XOO
OXO

Draw


```
