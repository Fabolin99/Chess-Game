/***********************************************************************
 * Source File:
 *    TEST PIECE
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The unit tests for a piece base class
 ************************************************************************/

#include "testPiece.h"
#include "piece.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

 /*************************************
  * ASSIGNMENT
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 
  *        rhs.fWhite=true  .lastMove=3 .nMoves=1
  * output:lhs.fWhite=true  .lastMove=3 .nMoves=1
  **************************************/
void TestPiece::assignment()
{  // SETUP
   PieceDerived lhs(0,0,true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   PieceDerived rhs(3, 3, true);
   rhs.fWhite = true;
   rhs.lastMove = 3;
   rhs.nMoves = 1;
   // EXERCISE
   lhs = rhs;
   // VERIFY
   assertUnit(lhs.fWhite == true);
   assertUnit(lhs.lastMove == 3);
   assertUnit(lhs.nMoves == 1);
   assertUnit(rhs.fWhite == true);
   assertUnit(rhs.lastMove == 3);
   assertUnit(rhs.nMoves == 1);
}  // TEARDOWN

 /*************************************
  * EQUALS : space equals space
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=space
  * output:true
  **************************************/
void TestPiece::equals_same()
{  // SETUP
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = false;
   PieceType rhs = SPACE;
   // EXERCISE
   isSame = lhs == rhs;
   // VERIFY
   assertUnit(isSame == true);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * EQUALS : space not equals rook
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=rook
  * output:true
  **************************************/
void TestPiece::equals_different()
{  // SETUP
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = true;
   PieceType rhs = ROOK;
   // EXERCISE
   isSame = lhs == rhs;
   // VERIFY
   assertUnit(isSame == false);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * NOT EQUALS : space equals space
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=space
  * output:false
  **************************************/
void TestPiece::notEquals_same()
{  // SETUP
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = true;
   PieceType rhs = SPACE;
   // EXERCISE
   isSame = lhs != rhs;
   // VERIFY
   assertUnit(isSame == false);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * NOT EQUALS : space not equals rook
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=rook
  * output:true
  **************************************/
void TestPiece::notEquals_different()
{  // SETUP
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = false;
   PieceType rhs = ROOK;
   // EXERCISE
   isSame = lhs != rhs;
   // VERIFY
   assertUnit(isSame == true);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * IS WHITE : white
  * input: piece.fWhite=true .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  * output:true
  **************************************/
void TestPiece::isWhite_white()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = true;
   piece.lastMove = 6;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isWhite = false;
   // EXERCISE
   isWhite = piece.isWhite();
   // VERIFY
   assertUnit(isWhite == true);
   assertUnit(piece.fWhite == true);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * IS WHITE : black
  * input: piece.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  * output:false
  **************************************/
void TestPiece::isWhite_black()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 6;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isWhite = true;
   // EXERCISE
   isWhite = piece.isWhite();
   // VERIFY
   assertUnit(isWhite == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * IS MOVED : inital when not moved
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  * output:false
  **************************************/
void TestPiece::isMoved_initial()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   bool isMoved = true;
   // EXERCISE
   isMoved = piece.isMoved();
   // VERIFY
   assertUnit(isMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // TEARDOWN

 /*************************************
  * IS MOVED : has moved twice
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:true
  **************************************/
void TestPiece::isMoved_hasMoved()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isMoved = false;
   // EXERCISE
   isMoved = piece.isMoved();
   // VERIFY
   assertUnit(isMoved == true);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * GET NUMBER MOVES : inital when not moved
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  * output:0
  **************************************/
void TestPiece::getNMoves_initial()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   int nMoves = 9;
   // EXERCISE
   nMoves = piece.getNMoves();
   // VERIFY
   assertUnit(nMoves == 0);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // TEARDOWN

 /*************************************
  * GET NUMBER MOVES : has moved twice
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:2
  **************************************/
void TestPiece::getNMoves_hasMoved()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int nMoves = 9;
   // EXERCISE
   nMoves = piece.getNMoves();
   // VERIFY
   assertUnit(nMoves == 2);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * GET POSITION
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:pos(2,3)
  **************************************/
void TestPiece::getPosition()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2,3);
   Position pos;
   // EXERCISE
   pos = piece.getPosition();
   // VERIFY
   assertUnit(pos == Position(2,3));
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * JUST MOVED : initial position of the piece
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  *        currentMove=7
  * output:false
  **************************************/
void TestPiece::justMoved_initial()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   int currentMove = 7;
   bool justMoved = true;
   // EXERCISE
   justMoved = piece.justMoved(currentMove);
   // VERIFY
   assertUnit(justMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // TEARDOWN

 /*************************************
  * JUST MOVED : moved a few times
  * input: piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *        currentMove=7
  * output:false
  **************************************/
void TestPiece::justMoved_hasMoved()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 7;
   bool justMoved = true;
   // EXERCISE
   justMoved = piece.justMoved(currentMove);
   // VERIFY
   assertUnit(justMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 4);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * JUST MOVED : just moved
  * input: piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *        currentMove=5
  * output:true
  **************************************/
void TestPiece::justMoved_justMoved()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 5;
   bool justMoved = false;
   // EXERCISE
   justMoved = piece.justMoved(currentMove);
   // VERIFY
   assertUnit(justMoved == true);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 4);
   assertUnit(piece.nMoves == 2);
}  // TEARDOWN

 /*************************************
  * SET LAST MOVE
  * input:  piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *         currentMove=6
  * output: piece.fWhite=false .lastMove=6 .nMoves=3 .pos(2,3) .type=space
  **************************************/
void TestPiece::setLastMove()
{  // SETUP
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 6;
   // EXERCISE
   piece.setLastMove(currentMove);
   // VERIFY
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 3);
}  // TEARDOWN

