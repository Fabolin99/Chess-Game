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

 /*************************************
  * Constructor : default
  * Input: 
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{
	// Setup
	Move move;

	// Exercise is not necessary on this test.

	// Verify
	assertUnit(move.source == INVALID);
	assertUnit(move.dest == INVALID);
}

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =2,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{
	// Set up a Move object using the string constructor
	Move move("e5e6");

	// Verify that the source and destination positions are correct
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x45); 

	// Verify that the move type is MOVE
	assertUnit(move.moveType == Move::MOVE);
}// teardown


 /*************************************
  * READ simple move 
  * Input:  e5d6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::read_simple()
{
	// Set up a Move object using the string constructor
	Move move("e5d6");

	// Verify that the source and destination positions are correct
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 3

	// Verify that the move type is MOVE
	assertUnit(move.moveType == Move::MOVE);
}// teardown

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
	// Setup 
	Move move("e5d6r");

	// Verify 
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 

	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);

}// Teardowm

 /*************************************
  * READ enpassant move 
  * Input:  e5d6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::read_enpassant()
{
	// Setup
	Move move;
	bool success = move.assign("e5d6E");

	// Verify that the assign method returned true
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);// 'd' corresponds to column 3

	assertUnit(move.moveType == Move::ENPASSANT);
}// Teardowm

 /*************************************
  * READ king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::read_castleKing()
{
	// Set up a Move object using the default constructor
	Move move;

	// exercise
	bool success = move.assign("e1g1c");

	// verify
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x60);

	assertUnit(move.moveType == Move::CASTLE_KING);

}// Teardowm


 /*************************************
  * READ queen side castle
  * Input:  e1g1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::read_castleQueen()
{
	// Set up a Move object using the default constructor
	Move move;

	// exercise
	bool success = move.assign("e1c1C");

	// Verify 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x20);

	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}// teardown

 /*************************************
  * ASSIGN simple move
  * Input:  e5e6
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN // The type should be move
  **************************************/
void TestMove::assign_simple()
{
	// Set up 
	Move move;

	// exercise
	bool success = move.assign("e5e6");

	// Verify 
	assertUnit(success == true);

	assertUnit(move.source.colRow == 0x44);// 'e' corresponds to column 4
	assertUnit(move.dest.colRow == 0x45);

	assertUnit(move.moveType == Move::MOVE); 
} //teardown

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
	// Set up 
	Move move;

	// exercise
	bool success = move.assign("e5d6r");

	// Verify 
	assertUnit(success == true);
	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);

	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}// teardown

 /*************************************
  * ASSIGN enpassant move
  * Input:  e5d6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::assign_enpassant()
{
	// Set up 
	Move move;

	// exercise
	bool success = move.assign("e5d6E");

	// Verify 
	assertUnit(success == true);

	assertUnit(move.source.colRow == 0x44);
	assertUnit(move.dest.colRow == 0x35);

	assertUnit(move.moveType == Move::ENPASSANT);
}// teardown


 /*************************************
  * ASSIGN king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::assign_castleKing()
{
	// Set up 
	Move move;

	// exercise
	bool success = move.assign("e1g1c");

	// Verify 
	assertUnit(success == true);

	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x60);

	assertUnit(move.moveType == Move::CASTLE_KING);
}// teardown

 /*************************************
  * ASSIGN queen side castle
  * Input:  e1g1C <- possible typo 
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::assign_castleQueen()
{
	// Set up 
	Move move;

	// exercise
	bool success = move.assign("e1c1C"); 

	// Verify 
	assertUnit(success == true);

	assertUnit(move.source.colRow == 0x40);
	assertUnit(move.dest.colRow == 0x20);

	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}// teardown

 /*************************************
  * GET TEXT simple move
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  * Output: e5e6
  **************************************/
void TestMove::getText_simple()
{   // SETUP
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
}   // TEARDOWN

/*************************************
  * GET TEXT capture
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  * Output: e5e6r
  **************************************/
void TestMove::getText_capture()
{   // SETUP
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
}   // TEARDOWN

/*************************************
  * GET TEXT en passant
  * Input : source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  *         capture=PAWN
  * Output: e5f6E
  **************************************/
void TestMove::getText_enpassant()
{   // SETUP
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
}   // TEARDOWN
/*************************************
  * GET TEXT king side castle
  * Input : source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  * Output: e1g1c
  **************************************/
void TestMove::getText_castleKing()
{   // SETUP
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
{   // SETUP
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
{
	// setup
	Move move;
	char expected = ' ';
	
	//exercise
	char actual = move.letterFromPieceType(SPACE);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{
	// setup
	Move move;
	char expected = 'p';

	//exercise
	char actual = move.letterFromPieceType(PAWN);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE bishop
  * Input : BISHOP
  * Output:  'b'
  **************************************/
void TestMove::letterFromPieceType_bishop()
{
	// setup
	Move move;
	char expected = 'b';

	//exercise
	char actual = move.letterFromPieceType(BISHOP);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE knight
  * Input : KNIGHT
  * Output:  'n'
  **************************************/
void TestMove::letterFromPieceType_knight()
{
	// setup
	Move move;
	char expected = 'n';

	//exercise
	char actual = move.letterFromPieceType(KNIGHT);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE rook
  * Input : ROOK
  * Output:  'r'
  **************************************/
void TestMove::letterFromPieceType_rook()
{
	// setup
	Move move;
	char expected = 'r';

	//exercise
	char actual = move.letterFromPieceType(ROOK);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE queen
  * Input : QUEEN
  * Output:  'q'
  **************************************/
void TestMove::letterFromPieceType_queen()
{
	// setup
	Move move;
	char expected = 'q';

	//exercise
	char actual = move.letterFromPieceType(QUEEN);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * LETTER FROM PIECE TYPE king
  * Input : KING
  * Output:  'k'
  **************************************/
void TestMove::letterFromPieceType_king()
{
	// setup
	Move move;
	char expected = 'k';

	//exercise
	char actual = move.letterFromPieceType(KING);

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER pawn
  * Input : 'p'
  * Output:  PAWN
  **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
	// setup
	Move move;
	PieceType expected = PAWN;

	//exercise
	char actual = move.pieceTypeFromLetter('p');

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER bishop
  * Input : 'b'
  * Output:  BISHOP
  **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
	// setup
	Move move;
	PieceType expected = BISHOP;

	//exercise
	char actual = move.pieceTypeFromLetter('b');

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER knight
  * Input : 'n'
  * Output: KNIGHT
  **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
	// setup
	Move move;
	PieceType expected = KNIGHT;

	//exercise
	char actual = move.pieceTypeFromLetter('n');

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER rook
  * Input : 'r'
  * Output: ROOK
  **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
	// setup
	Move move;
	PieceType expected = ROOK;

	//exercise
	char actual = move.pieceTypeFromLetter('r');

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER queen
  * Input : 'q'
  * Output: QUEEN
  **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
	// setup
	Move move;
	PieceType expected = QUEEN;

	//exercise
	char actual = move.pieceTypeFromLetter('q');

	// verify
	assertUnit(expected == actual);
	//teardown
}

 /*************************************
  * PIECE TYPE FROM LETTER king
  * Input : 'k'
  * Output: KING
  **************************************/
void TestMove::pieceTypeFromLetter_king() 
{
	// setup
	Move move;
	PieceType expected = KING;

	//exercise
	char actual = move.pieceTypeFromLetter('k');

	// verify
	assertUnit(expected == actual);
	//teardown
}


/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
	//setup
	Move move1("b2b4");
	Move move2("b2b5");
	
	// no exercise for this

	// verify
	assertUnit(!(move1 == move2));
	//teardown
}

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: false
  **************************************/
void TestMove::equal_equals()
{
	//setup
	Move move1("b2b4");
	Move move2("b2b4");

	// no exercise for this

	// verify
	assertUnit(move1 == move2);
	//teardown
}


 /*************************************
  * LESS THAN - LESS THAN
  * Input : b2b2 < b2b4
  * Output: true
  **************************************/
void TestMove::lessthan_lessthan()
{
	// setup
	Move move1("b2b2");
	Move move2("b2b4");

	// no exercise for this

	//verify
	assertUnit(move1 < move2);
	// teardown
}

 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{
	// setup
	Move move1("b2b4");
	Move move2("b2b4");

	// no exercise for this

	//verify
	assertUnit(!(move1 < move2));
	// teardown
}


 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{
	// setup
	Move move1("b2b4");
	Move move2("b2b2");

	// no exercise for this

	//verify
	assertUnit(!(move1 < move2));
	// teardown
}