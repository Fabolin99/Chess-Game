/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The KNIGHT class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Knight::display(ogstream* pgout) const
{
   pgout->drawKnight(this->position, !this->fWhite);
}

/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   // Adjust-moves for a Knight
   CR possibleMoves[8] =
   {
            {-1,  2}, {1,  2},
   {-2,  1},                    {2,  1},
   {-2, -1},                    {2, -1},
            {-1, -2}, {1, -2}
   };

   // Going through every single possible adjust-move
   for (int i = 0; i < 8; i++)
   {
      int newRow = this->position.getRow() + possibleMoves[i].row;
      int newCol = this->position.getCol() + possibleMoves[i].col;

      Position newPos(newCol, newRow);

      if (newPos.isValid())
      {
         if (board[newPos].getType() == SPACE)
         {
            Move move(this->position, newPos, Move::MOVE, INVALID, this->fWhite);
            moves.insert(move);
         }
         else
         {
            if (board[newPos].isWhite() != this->fWhite)
            {
               Move move(this->position, newPos, Move::MOVE, board[newPos].getType(), this->fWhite);
               moves.insert(move);
            }
         }
      }
   }
}