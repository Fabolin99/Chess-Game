/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"     
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
  * 3     p p p           3
  * 2     p(q)p           2
  * 1     p p p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestQueen::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true /*white*/);
	board.board[2][1] = &queen;
	White pawn1(PAWN);
	board.board[1][2] = &pawn1;
	White pawn2(PAWN);
	board.board[2][2] = &pawn2;
	White pawn3(PAWN);
	board.board[3][2] = &pawn3;
	White pawn4(PAWN);
	board.board[1][1] = &pawn4;
	White pawn5(PAWN);
	board.board[3][1] = &pawn5;
	White pawn6(PAWN);
	board.board[1][0] = &pawn6;
	White pawn7(PAWN);
	board.board[2][0] = &pawn7;
	White pawn8(PAWN);
	board.board[3][0] = &pawn8;
	set <Move> moves;
	// EXERCISE
	queen.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 0);		// many possible moves
	// TEARDOWN
	board.board[2][1] = nullptr;			// white queen
	board.board[1][2] = nullptr;			// white pawn 1
	board.board[2][2] = nullptr;			// white pawn 2
	board.board[3][2] = nullptr;			// white pawn 3
	board.board[1][1] = nullptr;			// white pawn 4
	board.board[3][1] = nullptr;			// white pawn 5
	board.board[1][0] = nullptr;			// white pawn 6
	board.board[2][0] = nullptr;			// white pawn 7
	board.board[3][0] = nullptr;			// white pawn 8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, false /*white*/);
	board.board[2][1] = &queen;
	set <Move> moves;
	// EXERCISE
	queen.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 23);												   // many possible moves
	assertUnit(moves.find(Move("c2c3")) != moves.end());				// North
	assertUnit(moves.find(Move("c2c4")) != moves.end());
	assertUnit(moves.find(Move("c2c5")) != moves.end());
	assertUnit(moves.find(Move("c2c6")) != moves.end());
	assertUnit(moves.find(Move("c2c7")) != moves.end());
	assertUnit(moves.find(Move("c2c8")) != moves.end());
	assertUnit(moves.find(Move("c2d3")) != moves.end());				// North East
	assertUnit(moves.find(Move("c2e4")) != moves.end());
	assertUnit(moves.find(Move("c2f5")) != moves.end());
	assertUnit(moves.find(Move("c2g6")) != moves.end());
	assertUnit(moves.find(Move("c2h7")) != moves.end());
	assertUnit(moves.find(Move("c2d2")) != moves.end());				// East
	assertUnit(moves.find(Move("c2e2")) != moves.end());
	assertUnit(moves.find(Move("c2f2")) != moves.end());
	assertUnit(moves.find(Move("c2g2")) != moves.end());
	assertUnit(moves.find(Move("c2h2")) != moves.end());
	assertUnit(moves.find(Move("c2d1")) != moves.end());				// South East
	assertUnit(moves.find(Move("c2c1")) != moves.end());				// South
	assertUnit(moves.find(Move("c2b1")) != moves.end());				// South West
	assertUnit(moves.find(Move("c2b2")) != moves.end());				// West
	assertUnit(moves.find(Move("c2a2")) != moves.end());	
	assertUnit(moves.find(Move("c2b3")) != moves.end());				// North West
	assertUnit(moves.find(Move("c2a4")) != moves.end());
	// TEARDOWN
	board.board[2][1] = nullptr;			// white queen
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true /*white*/);
	board.board[2][1] = &queen;
	White pawn1(PAWN);
	board.board[2][7] = &pawn1;
	White pawn2(PAWN);
	board.board[7][6] = &pawn2;
	White pawn3(PAWN);
	board.board[7][1] = &pawn3;
	White pawn4(PAWN);
	board.board[3][0] = &pawn4;
	White pawn5(PAWN);
	board.board[2][0] = &pawn5;
	White pawn6(PAWN);
	board.board[1][0] = &pawn6;
	White pawn7(PAWN);
	board.board[0][1] = &pawn7;
	White pawn8(PAWN);
	board.board[0][3] = &pawn8;
	set <Move> moves;
	// EXERCISE
	queen.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 15);													// many possible moves
	assertUnit(moves.find(Move("c2c3")) != moves.end());				// North
	assertUnit(moves.find(Move("c2c4")) != moves.end());
	assertUnit(moves.find(Move("c2c5")) != moves.end());
	assertUnit(moves.find(Move("c2c6")) != moves.end());
	assertUnit(moves.find(Move("c2c7")) != moves.end());
	assertUnit(moves.find(Move("c2d3")) != moves.end());				// North East
	assertUnit(moves.find(Move("c2e4")) != moves.end());
	assertUnit(moves.find(Move("c2f5")) != moves.end());
	assertUnit(moves.find(Move("c2g6")) != moves.end());
	assertUnit(moves.find(Move("c2d2")) != moves.end());				// East
	assertUnit(moves.find(Move("c2e2")) != moves.end());
	assertUnit(moves.find(Move("c2f2")) != moves.end());
	assertUnit(moves.find(Move("c2g2")) != moves.end());
	assertUnit(moves.find(Move("c2b2")) != moves.end());				// West
	assertUnit(moves.find(Move("c2b3")) != moves.end());				// North West
	// TEARDOWN
	board.board[2][1] = nullptr;			// white queen
	board.board[2][7] = nullptr;			// white pawn 1
	board.board[7][6] = nullptr;			// white pawn 2
	board.board[7][1] = nullptr;			// white pawn 3
	board.board[3][0] = nullptr;			// white pawn 4
	board.board[2][0] = nullptr;			// white pawn 5
	board.board[1][0] = nullptr;			// white pawn 6
	board.board[0][1] = nullptr;			// white pawn 7
	board.board[0][3] = nullptr;			// white pawn 8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, false /*white*/);
	queen.fWhite = true;
	queen.position.set(2, 1);
	board.board[2][1] = &queen;
	Black pawn1(PAWN);
	board.board[2][7] = &pawn1;
	Black pawn2(PAWN);
	board.board[7][6] = &pawn2;
	Black pawn3(PAWN);
	board.board[7][1] = &pawn3;
	Black pawn4(PAWN);
	board.board[3][0] = &pawn4;
	Black pawn5(PAWN);
	board.board[2][0] = &pawn5;
	Black pawn6(PAWN);
	board.board[1][0] = &pawn6;
	Black pawn7(PAWN);
	board.board[0][1] = &pawn7;
	Black pawn8(PAWN);
	board.board[0][3] = &pawn8;
	set <Move> moves;
	// EXERCISE
	queen.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 23);		// many possible moves
	assertUnit(moves.find(Move("c2c3"))  != moves.end());				// North
	assertUnit(moves.find(Move("c2c4"))  != moves.end());
	assertUnit(moves.find(Move("c2c5"))  != moves.end());
	assertUnit(moves.find(Move("c2c6"))  != moves.end());
	assertUnit(moves.find(Move("c2c7"))  != moves.end());
	assertUnit(moves.find(Move("c2c8P")) != moves.end());
	assertUnit(moves.find(Move("c2d3"))  != moves.end());				// North East
	assertUnit(moves.find(Move("c2e4"))  != moves.end());
	assertUnit(moves.find(Move("c2f5"))  != moves.end());
	assertUnit(moves.find(Move("c2g6"))  != moves.end());
	assertUnit(moves.find(Move("c2h7P")) != moves.end());
	assertUnit(moves.find(Move("c2d2"))  != moves.end());				// East
	assertUnit(moves.find(Move("c2e2"))  != moves.end());
	assertUnit(moves.find(Move("c2f2"))  != moves.end());
	assertUnit(moves.find(Move("c2g2"))  != moves.end());
	assertUnit(moves.find(Move("c2h2P")) != moves.end());
	assertUnit(moves.find(Move("c2d1P")) != moves.end());				// South East
	assertUnit(moves.find(Move("c2c1P")) != moves.end());				// South
	assertUnit(moves.find(Move("c2b1P")) != moves.end());				// South West
	assertUnit(moves.find(Move("c2b2"))  != moves.end());				// West
	assertUnit(moves.find(Move("c2a2P")) != moves.end());
	assertUnit(moves.find(Move("c2b3"))  != moves.end());				// North West
	assertUnit(moves.find(Move("c2a4P")) != moves.end());
	// TEARDOWN
	board.board[2][1] = nullptr;			// white queen
	board.board[2][7] = nullptr;			// black pawn 1
	board.board[7][6] = nullptr;			// black pawn 2
	board.board[7][1] = nullptr;			// black pawn 3
	board.board[3][0] = nullptr;			// black pawn 4
	board.board[2][0] = nullptr;			// black pawn 5
	board.board[1][0] = nullptr;			// black pawn 6
	board.board[0][1] = nullptr;			// black pawn 7
	board.board[0][3] = nullptr;			// black pawn 8
}

/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{  // SETUP
	Queen queen(0, 0, true);
	// EXERCISE
	PieceType pt = queen.getType();
	// VERIFY
	assertUnit(pt == QUEEN);
}  // TEARDOWN
