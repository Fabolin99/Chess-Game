/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;

/************************************************
 * PIECE : CONSTRUCTOR
 ***********************************************/
Piece::Piece(int c, int r, bool isWhite)
{
   this->nMoves = 0;
   this->position = Position(c, r);
   this->fWhite = isWhite;
   this->lastMove = 0;
}

/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{

   if (this != &rhs) // protect against invalid self-assignment
   {
      // copy member variables from rhs
      this->fWhite = rhs.fWhite;
      this->lastMove = rhs.lastMove;
      this->nMoves = rhs.nMoves;
      this->position = rhs.position; // assuming Position has a working copy assignment operator
   }
   return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move> & movesSet, const Board & board) const
{
}

