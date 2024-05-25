/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The BISHOP class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Bishop::display(ogstream* pgout) const
{
   pgout->drawBishop(this->position, !this->fWhite);
}

/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Bishop::getMoves(set<Move>& moves, const Board& board) const
{
   CR possibleMoves[4] =
   {
      {-1,  1}, {1,  1},
      {-1, -1}, {1, -1}
   };

   // Iterate through each direction
   for (int i = 0; i < 4; i++)
   {
      int newRow = this->position.getRow() + possibleMoves[i].row;
      int newCol = this->position.getCol() + possibleMoves[i].col;

      // Continue moving in the same direction until we hit a piece or the board edge
      while (true)
      {
         Position newPos(newCol, newRow);

         // If the new position is not valid, break the loop
         if (!newPos.isValid())
            break;

         // If the new position has a piece
         if (board[newPos].getType() != SPACE)
         {
            // If the piece is of the opposite color, add the capture move
            if (board[newPos].isWhite() != this->fWhite)
            {
               Move move(this->position, newPos, Move::MOVE, board[newPos].getType() /* capture */, this->fWhite);
               moves.insert(move);
            }

            // Break the loop after dealing with a non-SPACE piece
            break;
         }

         Move move(this->position, newPos, Move::MOVE, SPACE /* capture */, this->fWhite);
         moves.insert(move);

         newCol += possibleMoves[i].col;
         newRow += possibleMoves[i].row;
      }
   }
}