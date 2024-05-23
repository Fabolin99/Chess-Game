/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The PAWN class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(this->position, !this->fWhite);
}


/**********************************************
 * PAWN : GET POSITIONS
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   CR possibleMoves[3] =
   {
      {0,  1}, {-1,  1}, {1,  1}
   };
   // Going through every single possible adjust-move
   for (int i = 0; i < 3; i++)
   {
      int newRow = this->position.getRow() + possibleMoves[i].row;
      int newCol = this->position.getCol() + possibleMoves[i].col;

      Position newPos(newCol, newRow);

      if (newPos.isValid())
      {
         if (i == 0 && board[newPos].getType() == SPACE)
         {
            Move move(this->position, newPos, Move::MOVE, SPACE/*capture*/, this->fWhite);
            moves.insert(move);
         }
         else if (i != 0 && board[newPos].isWhite() != this->fWhite)
         {
            Move move(this->position, newPos, Move::MOVE, board[newPos].getType()/*capture*/, this->fWhite);
            moves.insert(move);
         }
      }
   }
}