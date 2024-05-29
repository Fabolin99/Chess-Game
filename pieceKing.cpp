/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The KING class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "pieceSpace.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

using namespace std;

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void King::display(ogstream* pgout) const
{
   pgout->drawKing(this->position, !this->fWhite);
}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   // Adjust-moves for a King
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
   // white king castling
   if (this->fWhite)
   {
      // queen side
      if (board[Position(1, 0)].getType() == SPACE &&       // check if it's empty between
         board[Position(2, 0)].getType() == SPACE &&       // the king and the left rook
          board[Position(3, 0)].getType() == SPACE   )      
      {
         if (board[Position(0, 0)].getType() == ROOK &&     // check if the king and 
         {
            moves.insert(Move("e1c1C"));
         }
      }
      // king side
      if (board[Position(5, 0)].getType() == SPACE &&       // check if it's empty between
      {
         if (board[Position(7, 0)].getType() == ROOK &&     // check if the king and 
         {
            moves.insert(Move("e1g1c"));
         }
      }
   }
   // black king castling
   else
   {
      // queen side
      if (board[Position(1, 7)].getType() == SPACE &&       // check if it's empty between
         board[Position(2, 7)].getType() == SPACE &&       // the king and the left rook
      {
         if (board[Position(0, 7)].getType() == ROOK &&     // check if the king and 
         {
            moves.insert(Move("e8c8C"));
         }
      }
      // king side
      if (board[Position(5, 7)].getType() == SPACE &&       // check if it's empty between
      {
         if (board[Position(7, 7)].getType() == ROOK &&     // check if the king and
         {
            moves.insert(Move("e8g8c"));
         }
      }
   }
}