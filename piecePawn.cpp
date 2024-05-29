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
   {
   {

      {
         {
         }
         {
         }
      Position spaceOnRight(this->position.getCol() + 1, this->position.getRow());
      if (board[spaceOnRight].getType() == PAWN && board[spaceOnRight].isWhite() != this->fWhite && board[spaceOnRight].justMoved(board.getCurrentMove()))
      {
         Position newPos(this->position.getCol() + 1, this->position.getRow() + rowAdjust);
         moves.insert(Move(this->position, newPos, Move::ENPASSANT, PAWN, this->fWhite));
      }
   }
}