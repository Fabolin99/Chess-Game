/***********************************************************************
 * Header File:
 *    KNIGHT
 * Author:
*    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The KNIGHT class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KNIGHT
  * The knight, aka the "Horse"
  ***************************************************/
class Knight : public Piece
{
public:
   Knight(const Position& pos, bool isWhite) : Piece(10, 10, true) { }
   Knight(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~Knight() {                }
   PieceType getType()            const { return KNIGHT; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};