/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include "testRook.h"
#include "pieceRook.h"     
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
  * 3       p             3
  * 2     p(r)p           2
  * 1       p             1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestRook::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Rook rook(2, 1, true /*white*/);
   board.board[2][1] = &rook;
   White pawn1(PAWN);
   board.board[1][1] = &pawn1;
   White pawn2(PAWN);
   board.board[3][1] = &pawn2;
   White pawn3(PAWN);
   board.board[2][2] = &pawn3;
   White pawn4(PAWN);
   board.board[2][0] = &pawn4;
   set <Move> moves;
   // EXERCISE
   rook.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 0);		// no possible moves
   // TEARDOWN
   board.board[2][1] = nullptr;			// white rook
   board.board[1][1] = nullptr;			// white pawn 1
   board.board[3][1] = nullptr;			// white pawn 2
   board.board[2][2] = nullptr;			// white pawn 3
   board.board[2][0] = nullptr;			// white pawn 4
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   . .(r). . . . .   2
 * 1       .             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Rook rook(2, 1, true /*white*/);
   board.board[2][1] = &rook;
   set <Move> moves;
   // EXERCISE
   rook.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 14);		                                 // many possible moves
   assertUnit(moves.find(Move("c2c3")) != moves.end());				// North
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2c8")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());				// East
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2h2")) != moves.end());
   assertUnit(moves.find(Move("c2c1")) != moves.end());				// South
   assertUnit(moves.find(Move("c2b2")) != moves.end());				// West
   assertUnit(moves.find(Move("c2a2")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr;			// white rook
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   p .(r). . . . p   2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Rook rook(2, 1, true /*white*/);
   board.board[2][1] = &rook;
   White pawn1(PAWN); 
   board.board[2][0] = &pawn1;
   White pawn2(PAWN); 
   board.board[0][1] = &pawn2;
   White pawn3(PAWN); 
   board.board[7][1] = &pawn3;
   White pawn4(PAWN);
   board.board[2][7] = &pawn4;
   set <Move> moves;
   // EXERCISE
   rook.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 10);
   assertUnit(moves.find(Move("c2d2")) != moves.end()); // East
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2b2")) != moves.end()); // West
   assertUnit(moves.find(Move("c2c3")) != moves.end()); // North
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr; // white rook
   board.board[2][0] = nullptr; // white pawn 1
   board.board[0][1] = nullptr; // white pawn 2
   board.board[7][1] = nullptr; // white pawn 3
   board.board[2][7] = nullptr; // white pawn 4
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   P .(r). . . . P   2
 * 1       P             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Rook rook(2, 1, true /*white*/);
   board.board[2][1] = &rook;
   Black pawn1(PAWN); board.board[2][7] = &pawn1;
   Black pawn2(PAWN); board.board[7][1] = &pawn2;
   Black pawn3(PAWN); board.board[2][0] = &pawn3;
   Black pawn4(PAWN); board.board[0][1] = &pawn4;
   set <Move> moves;
   // EXERCISE
   rook.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 14);
   assertUnit(moves.find(Move("c2d2"))  != moves.end()); // East
   assertUnit(moves.find(Move("c2e2"))  != moves.end());
   assertUnit(moves.find(Move("c2f2"))  != moves.end());
   assertUnit(moves.find(Move("c2g2"))  != moves.end());
   assertUnit(moves.find(Move("c2h2P")) != moves.end());
   assertUnit(moves.find(Move("c2c1P")) != moves.end()); // South
   assertUnit(moves.find(Move("c2b2"))  != moves.end()); // West
   assertUnit(moves.find(Move("c2a2P")) != moves.end());
   assertUnit(moves.find(Move("c2c3"))  != moves.end()); // North
   assertUnit(moves.find(Move("c2c4"))  != moves.end());
   assertUnit(moves.find(Move("c2c5"))  != moves.end());
   assertUnit(moves.find(Move("c2c6"))  != moves.end());
   assertUnit(moves.find(Move("c2c7"))  != moves.end());
   assertUnit(moves.find(Move("c2c8P")) != moves.end());
   // TEARDOWN
   board.board[2][1] = nullptr; // white rook
   board.board[2][7] = nullptr; // black pawn 1
   board.board[7][1] = nullptr; // black pawn 2
   board.board[2][0] = nullptr; // black pawn 3
   board.board[0][1] = nullptr; // black pawn 4
}

/*************************************
 * GET TYPE : rook
 * Input:
 * Output: ROOK
 **************************************/
void TestRook::getType()
{
   // SETUP
   Rook rook(0, 0, true);
   // EXERCISE
   PieceType pt = rook.getType();
   // VERIFY
   assertUnit(pt == ROOK);
}  // TEARDOWN
