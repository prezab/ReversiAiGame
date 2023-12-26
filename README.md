# Reversi AI Game

This is a simple console-based implementation of the Reversi game (also known as Othello) in C. The game includes an AI opponent that uses the minimax algorithm with alpha-beta pruning to make intelligent moves.

## About the Project

This project was apart of my APS105 Course at the University of Toronto. It implements the Reversi game with a command-line interface. Players can play against each other or against an AI opponent. The AI opponent employs the minimax algorithm with alpha-beta pruning to make strategic moves.

## How to Play

- The game board is represented as a grid of size NxN.
- Players take turns to place their pieces on the board.
- A player can place a piece in a position where it will "sandwich" the opponent's pieces between two of their own.
- The game ends when no legal moves are possible, and the player with the most pieces on the board wins.

## AI Strategy

The AI opponent uses the minimax algorithm with alpha-beta pruning to determine the best move. Alpha-beta pruning is a search algorithm that reduces the number of nodes evaluated in the search tree. This improves the efficiency of the AI, allowing it to explore deeper into the game tree and make better-informed decisions.

## Implementation Details

- The game logic is implemented in C, and the AI strategy is based on the minimax algorithm with alpha-beta pruning.
- The `boardscore` function evaluates the current state of the board to assign scores to different positions.
- The `getcomputerscore` function implements the minimax algorithm with alpha-beta pruning to calculate the score of a potential move.
- The AI uses the calculated scores to make strategic moves during the game.

Hope you enjoy!
