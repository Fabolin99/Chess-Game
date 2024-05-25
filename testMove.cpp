/***********************************************************************
 * Header File:
 *    TEST MOVE 
 * Author:
 *     Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>
#include <iostream>

using namespace std;

 /*************************************
  * Constructor : default
  * Input: 
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{
	// SETUP
	// EXERCISE
	Move move;
	// Verify
	assertUnit(move.source == INVALID);
	assertUnit(move.dest == INVALID);
}  // TEARDOWN

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =2,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{
	// SETUP
	// EXERCISE
	Move move("e5e6");
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x45); 
	assertUnit(move.moveType == Move::MOVE);
}	// TEARDOWN

 /*************************************
  * READ simple move 
  * Input:  e5d6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::read_simple()
{
	// SETUP
	// EXERCISE
	Move move("e5d6");
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 3
	assertUnit(move.moveType == Move::MOVE);
}  // TEARDOWN

 /*************************************
  * READ capture move 
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::read_capture()
{
	// SETUP
	// EXERCISE
	Move move("e5d6r");
	// VERIFY 
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}  // TEARDOWN

 /*************************************
  * READ enpassant move 
  * Input:  e5d6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::read_enpassant()
{
	// SETUP
	Move move;
	// EXERCISE
	bool success = move.assign("e5d6E");
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 3
	assertUnit(move.moveType == Move::ENPASSANT);
}  // TEARDOWN

 /*************************************
  * READ king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::read_castleKing()
{
	// SETUP
	Move move;
	// EXERCISE
	bool success = move.assign("e1g1c");
	// VERIFY
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x60);
	assertUnit(move.moveType == Move::CASTLE_KING);
}  // TEARDOWN

 /*************************************
  * READ queen side castle
  * Input:  e1g1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::read_castleQueen()
{
	// SETUP
	Move move;
	// EXERCISE
	bool success = move.assign("e1c1C");
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x20);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}  // TEARDOWN

 /*************************************
  * ASSIGN simple move
  * Input:  e5e6
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN // The type should be move
  **************************************/
void TestMove::assign_simple()
{
	// SETUP
	Move move;
	// EXERCISE
	bool success = move.assign("e5e6");
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x44);// 'e' corresponds to column 4
	assertUnit(move.dest.colRow == 0x45);
	assertUnit(move.moveType == Move::MOVE); 
}  // TEARDOWN

 /*************************************
  * ASSIGN capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::assign_capture()
{
	// SETUP 
	Move move;
	// EXERCISE
	bool success = move.assign("e5d6r");
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}  // TEARDOWN

 /*************************************
  * ASSIGN enpassant move
  * Input:  e5d6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::assign_enpassant()
{
	// SETUP
	Move move;
	// EXERCISE
	bool success = move.assign("e5d6E");
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);
	assertUnit(move.moveType == Move::ENPASSANT);
} // TEARDOWN

 /*************************************
  * ASSIGN king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::assign_castleKing()
{
	// SETUP 
	Move move;
	// EXERCISE
	bool success = move.assign("e1g1c");
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x60);
	assertUnit(move.moveType == Move::CASTLE_KING);
}  // TEARDOWN

 /*************************************
  * ASSIGN queen side castle
  * Input:  e1g1C <- possible typo 
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::assign_castleQueen()
{
	// SETUP 
	Move move;
	// EXERCISE
	bool success = move.assign("e1c1C"); 
	// VERIFY 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x20);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}  // TEARDOWN

 /*************************************
  * GET TEXT simple move
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  * Output: e5e6
  **************************************/
void TestMove::getText_simple()
{  // SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x45;
	move.moveType = Move::MOVE;
	move.capture = INVALID;
	// EXERCISE
	string output = move.getText();
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x45);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == INVALID);
	assertUnit(output == "e5e6");
}  // TEARDOWN

/*************************************
  * GET TEXT capture
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  * Output: e5e6r
  **************************************/
void TestMove::getText_capture()
{  // SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x45;
	move.moveType = Move::MOVE;
	move.capture = ROOK;
	// EXERCISE
	string output = move.getText();
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x45);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
	assertUnit(output == "e5e6r");
}  // TEARDOWN

/*************************************
  * GET TEXT en passant
  * Input : source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  *         capture=PAWN
  * Output: e5f6E
  **************************************/
void TestMove::getText_enpassant()
{  // SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x55;
	move.moveType = Move::ENPASSANT;
	move.capture = PAWN;
	// EXERCISE
	string output = move.getText();
	// VERIFY
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x55);
	assertUnit(move.moveType == Move::ENPASSANT);
	assertUnit(move.capture == PAWN);
	assertUnit(output == "e5f6E");
}  // TEARDOWN

/*************************************
  * GET TEXT king side castle
  * Input : source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  * Output: e1g1c
  **************************************/
void TestMove::getText_castleKing()
{  // SETUP
	Move move;
	move.source.colRow = 0x40;
	move.dest.colRow = 0x60;
	move.moveType = Move::CASTLE_KING;
	move.capture = INVALID;
	// EXERCISE
	string output = move.getText();
	// VERIFY
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x60);
	assertUnit(move.moveType == Move::CASTLE_KING);
	assertUnit(move.capture == INVALID);
	assertUnit(output == "e1g1c");
}	// TEARDOWN

/*************************************
  * GET TEXT queen side castle
  * Input : source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  * Output: e1c1C
  **************************************/
void TestMove::getText_castleQueen()
{  // SETUP
	Move move;
	move.source.colRow = 0x40;
	move.dest.colRow = 0x20;
	move.moveType = Move::CASTLE_QUEEN;
	move.capture = INVALID;
	// EXERCISE
	string output = move.getText();
	// VERIFY
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x20);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
	assertUnit(move.capture == INVALID);
	assertUnit(output == "e1c1C");
}	// TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE space
  * Input :  SPACE
  * Output:  ' '
  **************************************/
void TestMove::letterFromPieceType_space()
{  // SETUP
	Move move;
	char expected = ' ';
	// EXERCISE
	char actual = move.letterFromPieceType(SPACE);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{  // SETUP
	Move move;
	char expected = 'p';
	// EXERCISE
	char actual = move.letterFromPieceType(PAWN);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE bishop
  * Input : BISHOP
  * Output:  'b'
  **************************************/
void TestMove::letterFromPieceType_bishop()
{  // SETUP
	Move move;
	char expected = 'b';
	// EXERCISE
	char actual = move.letterFromPieceType(BISHOP);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE knight
  * Input : KNIGHT
  * Output:  'n'
  **************************************/
void TestMove::letterFromPieceType_knight()
{  // SETUP
	Move move;
	char expected = 'n';
	// EXERCISE
	char actual = move.letterFromPieceType(KNIGHT);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE rook
  * Input : ROOK
  * Output:  'r'
  **************************************/
void TestMove::letterFromPieceType_rook()
{  // SETUP
	Move move;
	char expected = 'r';
	// EXERCISE
	char actual = move.letterFromPieceType(ROOK);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE queen
  * Input : QUEEN
  * Output:  'q'
  **************************************/
void TestMove::letterFromPieceType_queen()
{  // SETUP
	Move move;
	char expected = 'q';
	// EXERCISE
	char actual = move.letterFromPieceType(QUEEN);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * LETTER FROM PIECE TYPE king
  * Input : KING
  * Output:  'k'
  **************************************/
void TestMove::letterFromPieceType_king()
{  // SETUP
	Move move;
	char expected = 'k';
	// EXERCISE
	char actual = move.letterFromPieceType(KING);
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER pawn
  * Input : 'p'
  * Output:  PAWN
  **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{  // SETUP
	Move move;
	PieceType expected = PAWN;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('p');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER bishop
  * Input : 'b'
  * Output:  BISHOP
  **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{  // SETUP
	Move move;
	PieceType expected = BISHOP;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('b');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER knight
  * Input : 'n'
  * Output: KNIGHT
  **************************************/
void TestMove::pieceTypeFromLetter_knight()
{  // SETUP
	Move move;
	PieceType expected = KNIGHT;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('n');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER rook
  * Input : 'r'
  * Output: ROOK
  **************************************/
void TestMove::pieceTypeFromLetter_rook()
{  // SETUP
	Move move;
	PieceType expected = ROOK;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('r');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER queen
  * Input : 'q'
  * Output: QUEEN
  **************************************/
void TestMove::pieceTypeFromLetter_queen()
{  // SETUP
	Move move;
	PieceType expected = QUEEN;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('q');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

 /*************************************
  * PIECE TYPE FROM LETTER king
  * Input : 'k'
  * Output: KING
  **************************************/
void TestMove::pieceTypeFromLetter_king() 
{  // SETUP
	Move move;
	PieceType expected = KING;
	// EXERCISE
	char actual = move.pieceTypeFromLetter('k');
	// VERIFY
	assertUnit(expected == actual);
}  // TEARDOWN

/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{  // SETUP
	Move move1("b2b4");
	Move move2("b2b5");
	// EXERCISE
	// VERIFY
	assertUnit(!(move1 == move2));
}  // TEARDOWN

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: false
  **************************************/
void TestMove::equal_equals()
{  // SETUP
	Move move1("b2b4");
	Move move2("b2b4");
	// EXERCISE
	// VERIFY
	assertUnit(move1 == move2);
}  // TEARDOWN

 /*************************************
  * LESS THAN - LESS THAN
  * Input : b2b2 < b2b4
  * Output: true
  **************************************/
void TestMove::lessthan_lessthan()
{  // SETUP
	Move move1("b2b2");
	Move move2("b2b4");
	// EXERCISE
	// VERIFY
	assertUnit(move1 < move2);
}  // TEARDOWN

 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{  // SETUP
	Move move1("b2b4");
	Move move2("b2b4");
	// EXERCISE
	// VERIFY
	assertUnit(!(move1 < move2));
}  // TEARDOWN

 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{  // SETUP
	Move move1("b2b4");
	Move move2("b2b2");
	// EXERCISE
	// VERIFY
	assertUnit(!(move1 < move2));
}  // TEARDOWN