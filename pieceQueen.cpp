/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The QUEEN class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Queen::display(ogstream* pgout) const
{
   pgout->drawQueen(this->position, !this->fWhite);
}


/**********************************************
 * QUEEN : GET POSITIONS
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
   CR possibleMoves[8] =
   {
      {-1,  1}, {0,  1}, {1,  1},
      {-1,  0},          {1,  0},
      {-1, -1}, {0, -1}, {1, -1}
   };
   // Going through every single possible adjust-move
   for (int i = 0; i < 8; i++)
   {
      int newRow = this->position.getRow() + possibleMoves[i].row;
      int newCol = this->position.getCol() + possibleMoves[i].col;

      Position newPos(newCol, newRow);

      while (newPos.isValid() && board[newPos].getType() == SPACE)
      {
         Move move(this->position, newPos, Move::MOVE, SPACE/*capture*/, this->fWhite);
         moves.insert(move);

         newCol += possibleMoves[i].col;
         newRow += possibleMoves[i].row;

         if (newCol >= 0 && newCol < 8 && newRow >= 0 && newCol < 8)
         {
            newPos.set(newCol, newRow);
         }
         else
         {
            break;
         }
      }

      if (newPos.isValid())
      {
         if (board[newPos].isWhite() != this->fWhite)
         {
            Move move(this->position, newPos, Move::MOVE, board[newPos].getType()/*capture*/, this->fWhite);
            moves.insert(move);
         }
      }
   }
}