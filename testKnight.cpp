/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>  
#include <iostream>

using namespace std;

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3             p   .   3
 * 2           P         2
 * 1              (n)    1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_end()
{
	// SETUP
	BoardEmpty board;
	Knight knight(7, 7, false /*white*/);
	knight.fWhite = true;
	knight.position.set(6, 0);
	board.board[6][0] = &knight;
	Black black(PAWN);
	board.board[4][1] = &black;
	White white(PAWN);
	board.board[5][2] = &white;
	set <Move> moves;

	// EXERCISEd
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);		// many possible moves
	assertUnit(moves.find(Move("g1e2p")) != moves.end());
	assertUnit(moves.find(Move("g1h3")) != moves.end());

	// TEARDOWN
	board.board[6][0] = nullptr;			// white knight
	board.board[4][1] = nullptr;			// black pawn
	board.board[5][2] = nullptr;			// white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Knight knight(7, 7, false /*white*/);
	knight.fWhite = true;
	knight.position.set(3, 4);
	board.board[3][4] = &knight;
	White pawn1(PAWN);
	board.board[4][6] = &pawn1;
	White pawn2(PAWN);
	board.board[5][5] = &pawn2;
	White pawn3(PAWN);
	board.board[5][3] = &pawn3;
	White pawn4(PAWN);
	board.board[4][2] = &pawn4;
	White pawn5(PAWN);
	board.board[2][2] = &pawn5;
	White pawn6(PAWN);
	board.board[1][3] = &pawn6;
	White pawn7(PAWN);
	board.board[1][5] = &pawn7;
	White pawn8(PAWN);
	board.board[2][6] = &pawn8;
	set <Move> moves;

	// EXERCISEd
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);		// many possible moves

	// TEARDOWN
	board.board[6][0] = nullptr;		// white knight
	board.board[4][6] = nullptr;		// white pawn 1
	board.board[5][5] = nullptr;		// white pawn 2
	board.board[5][3] = nullptr;		// white pawn 3
	board.board[4][2] = nullptr;		// white pawn 4
	board.board[2][2] = nullptr;		// white pawn 5
	board.board[1][3] = nullptr;		// white pawn 6
	board.board[1][5] = nullptr;		// white pawn 7
	board.board[2][6] = nullptr;		// white pawn 8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
	// SETUP
	BoardEmpty board;
	Knight knight(7, 7, false /*white*/);
	knight.fWhite = true;
	knight.position.set(3, 4);
	board.board[3][4] = &knight;
	Black pawn1(PAWN);
	board.board[4][6] = &pawn1;
	Black pawn2(PAWN);
	board.board[5][5] = &pawn2;
	Black pawn3(PAWN);
	board.board[5][3] = &pawn3;
	Black pawn4(PAWN);
	board.board[4][2] = &pawn4;
	Black pawn5(PAWN);
	board.board[2][2] = &pawn5;
	Black pawn6(PAWN);
	board.board[1][3] = &pawn6;
	Black pawn7(PAWN);
	board.board[1][5] = &pawn7;
	Black pawn8(PAWN);
	board.board[2][6] = &pawn8;
	set <Move> moves;

	// EXERCISEd
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);		// many possible moves
	assertUnit(moves.find(Move("d5e7P")) != moves.end());
	assertUnit(moves.find(Move("d5f6P")) != moves.end());
	assertUnit(moves.find(Move("d5e3P")) != moves.end());
	assertUnit(moves.find(Move("d5f4P")) != moves.end());
	assertUnit(moves.find(Move("d5c3P")) != moves.end());
	assertUnit(moves.find(Move("d5b4P")) != moves.end());
	assertUnit(moves.find(Move("d5b6P")) != moves.end());
	assertUnit(moves.find(Move("d5c7P")) != moves.end());

	// TEARDOWN
	board.board[6][0] = nullptr;		// white knight
	board.board[4][6] = nullptr;		// black pawn 1
	board.board[5][5] = nullptr;		// black pawn 2
	board.board[5][3] = nullptr;		// black pawn 3
	board.board[4][2] = nullptr;		// black pawn 4
	board.board[2][2] = nullptr;		// black pawn 5
	board.board[1][3] = nullptr;		// black pawn 6
	board.board[1][5] = nullptr;		// black pawn 7
	board.board[2][6] = nullptr;		// black pawn 8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{
	// SETUP
	BoardEmpty board;
	Knight knight(7, 7, false /*white*/);
	knight.fWhite = true;
	knight.position.set(3, 4);
	board.board[3][4] = &knight;
	set <Move> moves;

	// EXERCISEd
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);		// many possible moves
	assertUnit(moves.find(Move("d5e7")) != moves.end());
	assertUnit(moves.find(Move("d5f6")) != moves.end());
	assertUnit(moves.find(Move("d5e3")) != moves.end());
	assertUnit(moves.find(Move("d5f4")) != moves.end());
	assertUnit(moves.find(Move("d5c3")) != moves.end());
	assertUnit(moves.find(Move("d5b4")) != moves.end());
	assertUnit(moves.find(Move("d5b6")) != moves.end());
	assertUnit(moves.find(Move("d5c7")) != moves.end());

	// TEARDOWN
	board.board[6][0] = nullptr;		// white knight
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{   // SETUP
	Knight knight(0, 0, true);
	// EXERCISE
	PieceType pt = knight.getType();
	// VERIFY
	assertUnit(pt == KNIGHT);
}   // TEARDOWN
