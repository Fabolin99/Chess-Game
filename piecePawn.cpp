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

void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(this->position, !this->fWhite);
}

void Pawn::getMoves(set<Move>& moves, const Board& board) const
{
   // will it get promoted?
   bool fPromotion = false;
   // moving direction
   int rowAdjust;
   if (this->fWhite)
   {
      rowAdjust = 1;    // moving up   (for white)
   }
   else
   {
      rowAdjust = -1;   // moving down (for black)
   }

   // normal move
   Position spaceInFront(this->position.getCol(), this->position.getRow() + rowAdjust);
   if (spaceInFront.isValid())
   {
      if (board[spaceInFront].getType() == SPACE)
      {
         if (spaceInFront.getRow() == 7 || spaceInFront.getRow() == 0)
         {
            fPromotion = true;
         }
         moves.insert(Move(this->position, spaceInFront, Move::MOVE, SPACE, this->fWhite, fPromotion));
         fPromotion = false;
         // advance move
         Position spaceTwoInFront(this->position.getCol(), this->position.getRow() + 2 * rowAdjust);
         if (spaceTwoInFront.isValid())
         {
            if (board[spaceTwoInFront].getType() == SPACE && !board[this->position].isMoved())
            {
               moves.insert(Move(this->position, spaceTwoInFront, Move::MOVE, SPACE, this->fWhite));
            }
         }
      }
   }

   // capturing
   Position spaceLeftDiagonal(this->position.getCol() - 1, this->position.getRow() + rowAdjust);
   if (spaceLeftDiagonal.isValid())
   {
      if (board[spaceLeftDiagonal].getType() != SPACE && board[spaceLeftDiagonal].isWhite() != this->fWhite)
      {
         if (spaceInFront.getRow() == 7 || spaceInFront.getRow() == 0)
         {
            fPromotion = true;
         }
         moves.insert(Move(this->position, spaceLeftDiagonal, Move::MOVE, board[spaceLeftDiagonal].getType(), this->fWhite, fPromotion));
         fPromotion = false;
      }
   }
   Position spaceRightDiagonal(this->position.getCol() + 1, this->position.getRow() + rowAdjust);
   if (spaceRightDiagonal.isValid())
   {
      if (board[spaceRightDiagonal].getType() != SPACE && board[spaceRightDiagonal].isWhite() != this->fWhite)
      {
         if (spaceInFront.getRow() == 7 || spaceInFront.getRow() == 0)
         {
            fPromotion = true;
         }
         moves.insert(Move(this->position, spaceRightDiagonal, Move::MOVE, board[spaceRightDiagonal].getType(), this->fWhite, fPromotion));
      }
   }

   // enpassant
   if (this->position.getRow() == 3 || this->position.getRow() == 4)
   {
      Position spaceOnLeft(this->position.getCol() - 1, this->position.getRow());
      if (board[spaceOnLeft].getType() == PAWN && board[spaceOnLeft].isWhite() != this->fWhite && board[spaceOnLeft].justMoved(board.getCurrentMove()))
      {
         Position newPos(this->position.getCol() - 1, this->position.getRow() + rowAdjust);
         moves.insert(Move(this->position, newPos, Move::ENPASSANT, PAWN, this->fWhite));
      }
      Position spaceOnRight(this->position.getCol() + 1, this->position.getRow());
      if (board[spaceOnRight].getType() == PAWN && board[spaceOnRight].isWhite() != this->fWhite && board[spaceOnRight].justMoved(board.getCurrentMove()))
      {
         Position newPos(this->position.getCol() + 1, this->position.getRow() + rowAdjust);
         moves.insert(Move(this->position, newPos, Move::ENPASSANT, PAWN, this->fWhite));
      }
   }
}