/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The ROOK class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Rook::display(ogstream* pgout) const
{
   pgout->drawRook(this->position, !this->fWhite);
}

/**********************************************
 * ROOK : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
   CR possibleMoves[4] =
   {
      {0,  1},  // Up
      {-1,  0}, // Left
      {1,  0},  // Right
      {0, -1}   // Down
   };

   // Going through every single possible adjust-move
   for (int i = 0; i < 4; i++)
   {
      int newRow = this->position.getRow() + possibleMoves[i].row;
      int newCol = this->position.getCol() + possibleMoves[i].col;

      Position newPos(newCol, newRow);

      // Continue moving in the direction until hitting the edge of the board or another piece
      while (newPos.isValid() && board[newPos].getType() == SPACE)
      {
         Move move(this->position, newPos, Move::MOVE, SPACE/*capture*/, this->fWhite);
         moves.insert(move);

         newCol += possibleMoves[i].col;
         newRow += possibleMoves[i].row;
         newPos.set(newCol, newRow);
      }

      // If the new position is valid and contains an opponent's piece, add it as a valid move
      if (newPos.isValid() && board[newPos].isWhite() != this->fWhite)
      {
         Move move(this->position, newPos, Move::MOVE, board[newPos].getType()/*capture*/, this->fWhite);
         moves.insert(move);
      }
   }
}