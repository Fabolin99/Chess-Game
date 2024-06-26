/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    Everything we need to know about the Bishop piece
 ************************************************************************/

#include "testBishop.h"
#include "pieceBishop.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3     p   p           3
  * 2      (b)            2
  * 1     p   p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestBishop::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(2, 1, true /*white*/);
   board.board[2][1] = &bishop;
   White pawn1(PAWN);
   board.board[1][2] = &pawn1;
   White pawn2(PAWN);
   board.board[3][2] = &pawn2;
   White pawn3(PAWN);
   board.board[1][0] = &pawn3;
   White pawn4(PAWN);
   board.board[3][0] = &pawn4;
   set <Move> moves;
   // EXERCISE
   bishop.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 0);
   // TEARDOWN
   board.board[2][1] = nullptr;			// white bishop
   board.board[1][2] = nullptr;			// white pawn 1
   board.board[3][2] = nullptr;			// white pawn 2
   board.board[1][0] = nullptr;			// white pawn 3
   board.board[3][0] = nullptr;			// white pawn 4
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(2, 1, true /*white*/);
   board.board[2][1] = &bishop;
   set <Move> moves;
   // EXERCISE
   bishop.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 9);                                              // many possible moves 
   assertUnit(moves.find(Move("c2d3")) != moves.end());                 // North East
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end());                 // South East
   assertUnit(moves.find(Move("c2b1")) != moves.end());                 // South West
   assertUnit(moves.find(Move("c2b3")) != moves.end());                 // North West
   assertUnit(moves.find(Move("c2a4")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr;                                               // white bishop
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(2, 1, true /*white*/);
   board.board[2][1] = &bishop;
   White pawn1(PAWN); board.board[0][3] = &pawn1;
   White pawn2(PAWN); board.board[1][0] = &pawn2;
   White pawn3(PAWN); board.board[3][0] = &pawn3;
   White pawn4(PAWN); board.board[7][6] = &pawn4;
   set <Move> moves;
   // EXERCISE
   bishop.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 5);                                 // many possible moves
   assertUnit(moves.find(Move("c2b3")) != moves.end());    // North West
   assertUnit(moves.find(Move("c2d3")) != moves.end());    // North East
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr;                                   // white bishop
   board.board[0][3] = nullptr;                                   // white pawn a4
   board.board[1][0] = nullptr;                                   // white pawn b1
   board.board[3][0] = nullptr;                                   // white pawn d1
   board.board[6][6] = nullptr;                                   // white pawn h7
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/);
   bishop.fWhite = true;
   bishop.position.set(2, 1);
   board.board[2][1] = &bishop;
   Black pawn1(PAWN);
   board.board[1][0] = &pawn1;
   Black pawn2(PAWN);
   board.board[3][0] = &pawn2;
   Black pawn3(PAWN);
   board.board[0][3] = &pawn3;
   Black pawn4(PAWN);
   board.board[6][6] = &pawn4;
   set <Move> moves;
   // EXERCISE
   bishop.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 9);                                       // many possible moves
   assertUnit(moves.find(Move("c2b1P")) != moves.end());				// South West
   assertUnit(moves.find(Move("c2b3")) != moves.end());				// North West
   assertUnit(moves.find(Move("c2a4P")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());				// North East
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7P")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr;			// white bishop
   board.board[1][0] = nullptr;			// black pawn 1
   board.board[3][0] = nullptr;			// black pawn 2
   board.board[0][3] = nullptr;			// black pawn 3
   board.board[6][6] = nullptr;			// black pawn 4
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP
   Bishop bishop(0, 0, true);
   // EXERCISE
   PieceType pt = bishop.getType();
   // VERIFY
   assertUnit(pt == BISHOP);
}  // TEARDOWN
