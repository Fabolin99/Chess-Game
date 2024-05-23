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

using namespace std; // DELETE!!!!!!!!!!!!


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

   // VERIFY the number of moves
   cout << "Number of moves: " << moves.size() << endl;
   assertUnit(moves.size() == 9);

   // VERIFY each expected move
   bool hasMove_d3 = moves.find(Move("c2d3")) != moves.end();
   bool hasMove_e4 = moves.find(Move("c2e4")) != moves.end();
   bool hasMove_f5 = moves.find(Move("c2f5")) != moves.end();
   bool hasMove_g6 = moves.find(Move("c2g6")) != moves.end();
   bool hasMove_h7 = moves.find(Move("c2h7")) != moves.end();
   bool hasMove_d1 = moves.find(Move("c2d1")) != moves.end();
   bool hasMove_b1 = moves.find(Move("c2b1")) != moves.end();
   bool hasMove_b3 = moves.find(Move("c2b3")) != moves.end();
   bool hasMove_a4 = moves.find(Move("c2a4")) != moves.end();

   assertUnit(hasMove_d3);  // North East
   assertUnit(hasMove_e4);
   assertUnit(hasMove_f5);
   assertUnit(hasMove_g6);
   assertUnit(hasMove_h7);
   assertUnit(hasMove_d1);  // South East
   assertUnit(hasMove_b1);  // South West
   assertUnit(hasMove_b3);  // North West
   assertUnit(hasMove_a4);

   // TEARDOWN
   board.board[2][1] = nullptr;         // white bishop
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
   BoardEmpty board;
   Bishop bishop(2, 1, true /*white*/);
   board.board[2][1] = &bishop;
   Black pawn1(PAWN); board.board[2][0] = &pawn1; // Changed to Black
   Black pawn2(PAWN); board.board[1][0] = &pawn2; // Changed to Black
   White pawn3(PAWN); board.board[0][1] = &pawn3;
   White pawn4(PAWN); board.board[0][3] = &pawn4;
   White pawn5(PAWN); board.board[3][0] = &pawn5;
   White pawn6(PAWN); board.board[7][1] = &pawn6;
   White pawn7(PAWN); board.board[7][6] = &pawn7;
   White pawn8(PAWN); board.board[2][7] = &pawn8;
   set <Move> moves;


   // EXERCISE
   bishop.getMoves(moves, board);

   // DEBUGGING: Print the moves generated
   std::cout << "Generated moves for Bishop at c2:\n";
   for (const auto& move : moves)
   {
      std::cout << move.getText() << std::endl;
   }

   // VERIFY
   assertUnit(moves.size() == 5); // Correct the number of possible moves
   assertUnit(moves.find(Move("c2d3")) != moves.end()); // North East
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end()); // South East
   assertUnit(moves.find(Move("c2b1")) != moves.end()); // South West
   assertUnit(moves.find(Move("c2b3")) != moves.end()); // North West
   assertUnit(moves.find(Move("c2a4")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // white bishop
   board.board[2][0] = nullptr; // white pawn 1
   board.board[1][0] = nullptr; // white pawn 2
   board.board[0][1] = nullptr; // white pawn 3
   board.board[0][3] = nullptr; // white pawn 4
   board.board[3][0] = nullptr; // white pawn 5
   board.board[7][1] = nullptr; // white pawn 6
   board.board[7][6] = nullptr; // white pawn 7
   board.board[2][7] = nullptr; // white pawn 8
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
   assertUnit(NOT_YET_IMPLEMENTED);
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
