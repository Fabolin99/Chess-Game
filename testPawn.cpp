/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>  
#include "pieceRook.h" // added for getMoves_promotionBlack()
#include <iostream>

using namespace std;

 /*************************************
  * GET MOVES TEST Simple
  * White pawn in the middle of the board: b4
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 3, true /*white*/);
   pawn.nMoves = 3;
   board.board[1][3] = &pawn;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 1);                                 // only one possible move
   assertUnit(moves.find(Move("b4b5")) != moves.end());    // move to b5
   // TEARDOWN
   board.board[1][3] = nullptr;                                  // white pawn
}

/*************************************
 * GET MOVES TEST Simple
 * Black pawn in the middle of the board: b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 3, false /*black*/);
   pawn.nMoves = 7;
   board.board[1][3] = &pawn;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 1);                                 // only one possible move
   assertUnit(moves.find(Move("b4b3")) != moves.end());    // move to b3
   // TEARDOWN
   board.board[1][3] = nullptr;                                  // black pawn
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * White pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 1, true /*white*/);
   board.board[1][1] = &pawn;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2); // two possible moves
   assertUnit(moves.find(Move("b2b3")) != moves.end());
   assertUnit(moves.find(Move("b2b4")) != moves.end());
   // TEARDOWN
   board.board[1][1] = nullptr; // white pawn
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * Black pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(2, 6, false /*black*/);
   board.board[2][6] = &pawn;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2); // two possible moves
   assertUnit(moves.find(Move("c7c6")) != moves.end()); // move to c6
   assertUnit(moves.find(Move("c7c5")) != moves.end()); // move to c5
   // TEARDOWN
   board.board[2][6] = nullptr;  // black pawn
}

/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 5, true /*white*/);
   pawn.nMoves = 5;
   board.board[1][5] = &pawn;
   Pawn pawn1(0, 6, false /*black*/);
   board.board[0][6] = &pawn1;
   Pawn pawn2(1, 6, false /*black*/);
   board.board[1][6] = &pawn2;
   Pawn pawn3(2, 6, false /*black*/);
   board.board[2][6] = &pawn3;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2); // two possible moves
   assertUnit(moves.find(Move("b6a7p")) != moves.end()); // capture to a7
   assertUnit(moves.find(Move("b6c7p")) != moves.end()); // capture to c7
   // TEARDOWN
   board.board[1][5] = nullptr; // white pawn
   board.board[0][6] = nullptr; // black pawn
   board.board[1][6] = nullptr; // black pawn
   board.board[2][6] = nullptr; // black pawn
}

/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 5, false /*black*/);
   pawn.nMoves = 10;
   board.board[1][5] = &pawn;
   Pawn pawn1(0, 4, true /*white*/);
   board.board[0][4] = &pawn1;
   Pawn pawn2(1, 4, true /*white*/);
   board.board[1][4] = &pawn2;
   Pawn pawn3(2, 4, true /*white*/);
   board.board[2][4] = &pawn3;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2); // two possible moves
   assertUnit(moves.find(Move("b6a5p")) != moves.end()); // capture to a5
   assertUnit(moves.find(Move("b6c5p")) != moves.end()); // capture to c5
   // TEARDOWN
   board.board[1][5] = nullptr; // black pawn
   board.board[0][4] = nullptr; // white pawn
   board.board[1][4] = nullptr; // white pawn
   board.board[2][4] = nullptr; // white pawn
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant b5a6E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   // SETUP
   BoardEmpty board;
   board.moveNumber = 7;
   Pawn pawn(1, 4, true /*white*/);
   board.board[1][4] = &pawn;
   Pawn pawn1(0, 4, false /*black*/);
   board.board[0][4] = &pawn1;
   pawn1.lastMove = 7;
   Pawn pawn2(2, 4, false /*black*/);
   board.board[2][4] = &pawn2;
   pawn2.lastMove = 7;
   Pawn pawn3(1, 5, false /*black*/);
   board.board[1][5] = &pawn3;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2);                                  // two possible moves
   assertUnit(moves.find(Move("b5a6E")) != moves.end());    // enpassant to a6
   assertUnit(moves.find(Move("b5c6E")) != moves.end());    // enpassant to c6
   // TEARDOWN
   board.board[1][4] = nullptr;                                    // white pawn
   board.board[0][4] = nullptr;                                    // black pawn 1
   board.board[2][4] = nullptr;                                    // black pawn 2
   board.board[1][5] = nullptr;                                    // black pawn 3
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant f4g3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   // SETUP
   BoardEmpty board;
   board.moveNumber = 99;
   Pawn pawn(5, 3, false /*black*/);
   board.board[5][3] = &pawn;
   Pawn pawn1(4, 3, true /*white*/);
   board.board[4][3] = &pawn1;
   pawn1.lastMove = 99;
   Pawn pawn2(6, 3, true /*white*/);
   board.board[6][3] = &pawn1;
   pawn2.lastMove = 99;
   Pawn pawn3(5, 2, true /*white*/);
   board.board[5][2] = &pawn3;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 2);                                  // two possible moves
   assertUnit(moves.find(Move("f4e3E")) != moves.end());    // enpassant to e3
   assertUnit(moves.find(Move("f4g3E")) != moves.end());    // enpassant to g3
   // TEARDOWN
   board.board[5][3] = nullptr;                                    // black pawn
   board.board[4][4] = nullptr;                                    // white pawn 1
   board.board[6][4] = nullptr;                                    // white pawn 2
   board.board[5][2] = nullptr;                                    // white pawn 3
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: b6a7rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 6, true /*white*/);
   board.board[1][6] = &pawn;
   Pawn pawn1(0, 7, false /*black*/);
   board.board[0][7] = &pawn1;
   Pawn pawn2(2, 7, false /*black*/);
   board.board[2][7] = &pawn2;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 3);                                  // three possible moves
   assertUnit(moves.find(Move("b7a8pQ")) != moves.end());   // promote to a8
   assertUnit(moves.find(Move("b7c8pQ")) != moves.end());   // promote to c8
   assertUnit(moves.find(Move("b7b8Q"))  != moves.end());   // promote to b8
   // TEARDOWN
   board.board[1][6] = nullptr; // white pawn
   board.board[0][7] = nullptr; // black pawn
   board.board[2][7] = nullptr; // black pawn
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: e2d1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r   r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(4, 1, false /*black*/);
   board.board[4][1] = &pawn;
   Rook rook1(3, 0, true /*white*/);
   board.board[3][0] = &rook1;
   Rook rook2(5, 0, true /*white*/);
   board.board[5][0] = &rook2;
   set <Move> moves;
   // EXERCISE
   pawn.getMoves(moves, board);
   // VERIFY
   assertUnit(moves.size() == 3);                                // three possible moves
   assertUnit(moves.find(Move("e2d1rQ")) != moves.end()); // promote to d1
   assertUnit(moves.find(Move("e2f1rQ")) != moves.end()); // promote to f1
   assertUnit(moves.find(Move("e2e1Q"))  != moves.end()); // promote to e1
   // TEARDOWN
   board.board[4][1] = nullptr;                                 // black pawn
   board.board[3][0] = nullptr;                                 // white rook
   board.board[5][0] = nullptr;                                 // white rook
}

/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   Pawn pawn(0, 0, true);
   // EXERCISE
   PieceType pt = pawn.getType();
   // VERIFY
   assertUnit(pt == PAWN);
}  // TEARDOWN

