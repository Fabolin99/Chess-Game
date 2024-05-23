/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6       p p p         6
  * 5       p(k)p         5
  * 4       p p p         4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKing::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(3, 4);
	board.board[3][4] = &king;
	White pawn1(PAWN);
	board.board[2][5] = &pawn1;
	White pawn2(PAWN);
	board.board[3][5] = &pawn2;
	White pawn3(PAWN);
	board.board[4][5] = &pawn3;
	White pawn4(PAWN);
	board.board[2][4] = &pawn4;
	White pawn5(PAWN);
	board.board[4][4] = &pawn5;
	White pawn6(PAWN);
	board.board[2][3] = &pawn6;
	White pawn7(PAWN);
	board.board[3][3] = &pawn7;
	White pawn8(PAWN);
	board.board[4][3] = &pawn8;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 0);		// many possible moves
	// TEARDOWN
	board.board[3][4] = nullptr;			// whtie king
	board.board[2][5] = nullptr;			// white pawn 1
	board.board[3][5] = nullptr;			// white pawn 2
	board.board[4][5] = nullptr;			// white pawn 3
	board.board[2][4] = nullptr;			// white pawn 4
	board.board[4][4] = nullptr;			// white pawn 5
	board.board[2][3] = nullptr;			// white pawn 6
	board.board[3][3] = nullptr;			// white pawn 7
	board.board[4][3] = nullptr;			// white pawn 8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(3, 4);
	board.board[3][4] = &king;
	Black pawn1(PAWN);
	board.board[2][5] = &pawn1;
	Black pawn2(PAWN);
	board.board[3][5] = &pawn2;
	Black pawn3(PAWN);
	board.board[4][5] = &pawn3;
	Black pawn4(PAWN);
	board.board[2][4] = &pawn4;
	Black pawn5(PAWN);
	board.board[4][4] = &pawn5;
	Black pawn6(PAWN);
	board.board[2][3] = &pawn6;
	Black pawn7(PAWN);
	board.board[3][3] = &pawn7;
	Black pawn8(PAWN);
	board.board[4][3] = &pawn8;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 8);		// many possible moves
	assertUnit(moves.find(Move("d5c6P")) != moves.end());
	assertUnit(moves.find(Move("d5d6P")) != moves.end());
	assertUnit(moves.find(Move("d5e6P")) != moves.end());
	assertUnit(moves.find(Move("d5c5P")) != moves.end());
	assertUnit(moves.find(Move("d5e5P")) != moves.end());
	assertUnit(moves.find(Move("d5c4P")) != moves.end());
	assertUnit(moves.find(Move("d5d4P")) != moves.end());
	assertUnit(moves.find(Move("d5e4P")) != moves.end());
	// TEARDOWN
	board.board[3][4] = nullptr;			// whtie king
	board.board[2][5] = nullptr;			// black pawn 1
	board.board[3][5] = nullptr;			// black pawn 2
	board.board[4][5] = nullptr;			// black pawn 3
	board.board[2][4] = nullptr;			// black pawn 4
	board.board[4][4] = nullptr;			// black pawn 5
	board.board[2][3] = nullptr;			// black pawn 6
	board.board[3][3] = nullptr;			// black pawn 7
	board.board[4][3] = nullptr;			// black pawn 8
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(3, 4);
	board.board[3][4] = &king;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 8);		// many possible moves
	assertUnit(moves.find(Move("d5c6")) != moves.end());
	assertUnit(moves.find(Move("d5d6")) != moves.end());
	assertUnit(moves.find(Move("d5e6")) != moves.end());
	assertUnit(moves.find(Move("d5c5")) != moves.end());
	assertUnit(moves.find(Move("d5e5")) != moves.end());
	assertUnit(moves.find(Move("d5c4")) != moves.end());
	assertUnit(moves.find(Move("d5d4")) != moves.end());
	assertUnit(moves.find(Move("d5e4")) != moves.end());
	// TEARDOWN
	board.board[3][4] = nullptr;			// whtie king
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(0, 0);
	board.board[0][0] = &king;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 3);		// many possible moves
	assertUnit(moves.find(Move("a1a2")) != moves.end());
	assertUnit(moves.find(Move("a1b1")) != moves.end());
	assertUnit(moves.find(Move("a1b2")) != moves.end());
	// TEARDOWN
	board.board[0][0] = nullptr;			// whtie king
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(4, 0);
	board.board[4][0] = &king;
	White pawn1(PAWN);
	board.board[3][1] = &pawn1;
	White pawn2(PAWN);
	board.board[4][1] = &pawn2;
	White pawn3(PAWN);
	board.board[5][1] = &pawn3;
	Rook leftRook(0, 0);
	board.board[0][0] = &leftRook;
	Rook rightRook(7, 0);
	board.board[7][0] = &rightRook;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 4);		// many possible moves
	assertUnit(moves.find(Move("e1c1C")) != moves.end());
	assertUnit(moves.find(Move("e1d1")) != moves.end());
	assertUnit(moves.find(Move("e1f1")) != moves.end());
	assertUnit(moves.find(Move("e1g1c")) != moves.end());
	// TEARDOWN
	board.board[4][0] = nullptr;			// whtie king
	board.board[3][1] = nullptr;			// white pawn 1
	board.board[4][1] = nullptr;			// white pawn 2
	board.board[5][1] = nullptr;			// white pawn 3
	board.board[0][0] = nullptr;			// white left rook
	board.board[7][0] = nullptr;			// white right rook
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.position.set(4, 7);
	board.board[4][7] = &king;
	Black pawn1(PAWN);
	board.board[3][6] = &pawn1;
	Black pawn2(PAWN);
	board.board[4][6] = &pawn2;
	Black pawn3(PAWN);
	board.board[5][6] = &pawn3;
	Rook leftRook(0, 7);
	board.board[0][7] = &leftRook;
	Rook rightRook(7, 7);
	board.board[7][7] = &rightRook;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 4);		// many possible moves
	assertUnit(moves.find(Move("e8c8C")) != moves.end());
	assertUnit(moves.find(Move("e8d8")) != moves.end());
	assertUnit(moves.find(Move("e8f8")) != moves.end());
	assertUnit(moves.find(Move("e8g8c")) != moves.end());
	// TEARDOWN
	board.board[4][7] = nullptr;			// black king
	board.board[3][6] = nullptr;			// black pawn 1
	board.board[4][6] = nullptr;			// black pawn 2
	board.board[5][6] = nullptr;			// black pawn 3
	board.board[0][7] = nullptr;			// black left rook
	board.board[7][7] = nullptr;			// black right rook
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.nMoves = 1;
	king.position.set(4, 0);
	board.board[4][0] = &king;
	White pawn1(PAWN);
	board.board[3][1] = &pawn1;
	White pawn2(PAWN);
	board.board[4][1] = &pawn2;
	White pawn3(PAWN);
	board.board[5][1] = &pawn3;
	Rook leftRook(0, 0);
	board.board[0][0] = &leftRook;
	Rook rightRook(7, 0);
	board.board[7][0] = &rightRook;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 2);		// many possible moves
	assertUnit(moves.find(Move("e1d1")) != moves.end());
	assertUnit(moves.find(Move("e1f1")) != moves.end());
	// TEARDOWN
	board.board[4][0] = nullptr;			// whtie king
	board.board[3][1] = nullptr;			// white pawn 1
	board.board[4][1] = nullptr;			// white pawn 2
	board.board[5][1] = nullptr;			// white pawn 3
	board.board[0][0] = nullptr;			// white left rook
	board.board[7][0] = nullptr;			// white right rook
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
	// SETUP
	BoardEmpty board;
	King king(7, 7, false /*white*/);
	king.fWhite = true;
	king.position.set(4, 0);
	board.board[4][0] = &king;
	White pawn1(PAWN);
	board.board[3][1] = &pawn1;
	White pawn2(PAWN);
	board.board[4][1] = &pawn2;
	White pawn3(PAWN);
	board.board[5][1] = &pawn3;
	Rook leftRook(0, 0);
	leftRook.nMoves = 1;
	board.board[0][0] = &leftRook;
	Rook rightRook(7, 0);
	rightRook.nMoves = 1;
	board.board[7][0] = &rightRook;
	set <Move> moves;
	// EXERCISE
	king.getMoves(moves, board);
	// VERIFY
	assertUnit(moves.size() == 2);		// many possible moves
	assertUnit(moves.find(Move("e1d1")) != moves.end());
	assertUnit(moves.find(Move("e1f1")) != moves.end());
	// TEARDOWN
	board.board[4][0] = nullptr;			// whtie king
	board.board[3][1] = nullptr;			// white pawn 1
	board.board[4][1] = nullptr;			// white pawn 2
	board.board[5][1] = nullptr;			// white pawn 3
	board.board[0][0] = nullptr;			// white left rook
	board.board[7][0] = nullptr;			// white right rook
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{  // SETUP
	King king(0, 0, true);
	// EXERCISE
	PieceType pt = king.getType();
	// VERIFY
	assertUnit(pt == KING);
}  // TEARDOWN


