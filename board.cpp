/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "pieceKing.h"
#include "pieceQueen.h"
#include "pieceRook.h"
#include "piecePawn.h"
#include "pieceBishop.h"
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   if (fFree)
   {
      free(); 
   }

   // put the kings into the right spots
   board[4][7] = new King  (4, 7, false /*isWhite*/);              // black king         (col: 4, row: 7)
   board[4][0] = new King  (4, 0, true  /*isWhite*/);              // white king         (col: 4, row: 0)
   // put the queens into the right spots
   board[3][7] = new Queen (3, 7, false /*isWhite*/);              // black queen        (col: 3, row: 7)
   board[3][0] = new Queen (3, 0, true  /*isWhite*/);              // white queen        (col: 3, row: 0)
   // put the knights into the right spots
   board[1][7] = new Knight(1, 7, false /*isWhite*/);              // left  black knight (col: 1, row: 7)
   board[6][7] = new Knight(6, 7, false /*isWhite*/);              // right black knight (col: 6, row: 7)
   board[1][0] = new Knight(1, 0, true  /*isWhite*/);              // left  white knight (col: 1, row: 0)
   board[6][0] = new Knight(6, 0, true  /*isWhite*/);              // right white knight (col: 6, row: 0)
   // put the rooks into the right spots
   board[0][7] = new Rook  (0, 7, false /*isWhite*/);              // left  black rook   (col: 0, row: 7)
   board[7][7] = new Rook  (7, 7, false /*isWhite*/);              // right black rook   (col: 7, row: 7)
   board[0][0] = new Rook  (0, 0, true  /*isWhite*/);              // left  white rook   (col: 0, row: 0)
   board[7][0] = new Rook  (7, 0, true  /*isWhite*/);              // right white rook   (col: 7, row: 0)
   // put the bishops into the right spots
   board[2][7] = new Bishop(2, 7, false /*isWhite*/);              // left  black bishop (col: 2, row: 7)
   board[5][7] = new Bishop(5, 7, false /*isWhite*/);              // right black bishop (col: 5, row: 7)
   board[2][0] = new Bishop(2, 0, true  /*isWhite*/);              // left  white bishop (col: 2, row: 0)
   board[5][0] = new Bishop(5, 0, true  /*isWhite*/);              // right white bishop (col: 5, row: 0)
   // put the pawns into the right spots
   for (int col = 0; col < 8; col++)
   {
      board[col][6] = new Pawn(col, 6, false /*isWhite*/);         // black pawns on row 6
      board[col][1] = new Pawn(col, 1, true  /*isWhite*/);         // white pawns on row 1
   }
                                                      
   // fill in spaces
   for (int c = 0; c < 8; c++)
   {
      for (int r = 0; r < 8; r++)
      {
         if (board[c][r] == nullptr)
         {
            board[c][r] = new Space(c, r);
         }
      }
   }
}

// we really REALLY need to delete this.
Space space(0, 0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   return *board[pos.getCol()][pos.getRow()];
}
Piece& Board::operator [] (const Position& pos)
{
   return *board[pos.getCol()][pos.getRow()];
}

/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   // set all the squares to nullptr
   for (int r = 0; r < 8; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         board[c][r] = nullptr;
      }
   }

   // reset board
   reset();
}

/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   for (auto& row : board)
   {
      for (auto& piece : row)
      {
         delete piece;
         piece = nullptr;
      }
   }
}

/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
   int pieceNum = 0;
   for (int r = 0; r < 8; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         if (board[c][r] != nullptr)
         {
            pieceNum++;
         }
      }
   }
   assert(pieceNum == 64);
}

/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move& move)
{
   // Check if the source and destination positions are valid
   if (!move.getSrc().isValid() || !move.getDes().isValid())
   {
      return;
   }
   // Deal with special moves
   // Check if it's a castling move
   if (move.getCastleK())
   {
      Piece* pieceRook = board[7][move.getSrc().getRow()];
      board[7][move.getSrc().getRow()] = board[5][move.getSrc().getRow()];
      board[5][move.getSrc().getRow()] = pieceRook;
      pieceRook->setPosition(board[7][move.getSrc().getRow()]->getPosition());
   }
   else if (move.getCastleQ())
   {
      Piece* pieceRook = board[0][move.getSrc().getRow()];
      board[0][move.getSrc().getRow()] = board[3][move.getSrc().getRow()];
      board[3][move.getSrc().getRow()] = pieceRook;
      pieceRook->setPosition(board[0][move.getSrc().getRow()]->getPosition());
   }
   // Check if it is an enpassant move
   else if (move.isEnpassant())
   {
      board[move.getDes().getCol()][move.getSrc().getRow()] = new Space(move.getDes().getCol(), move.getSrc().getRow());
   }
   // Check if there is a promotion
   else if (move.getPromotion() != SPACE)
   {
      if (move.getPromotion() == QUEEN)
      {
         board[move.getSrc().getCol()][move.getSrc().getRow()] = new Queen(move.getSrc().getCol(), move.getSrc().getRow(), move.getIsWhite());
      }
      else if (move.getPromotion() == ROOK)
      {
         board[move.getSrc().getCol()][move.getSrc().getRow()] = new Rook(move.getSrc().getCol(), move.getSrc().getRow(), move.getIsWhite());
      }
      else if (move.getPromotion() == BISHOP)
      {
         board[move.getSrc().getCol()][move.getSrc().getRow()] = new Bishop(move.getSrc().getCol(), move.getSrc().getRow(), move.getIsWhite());
      }
      else if (move.getPromotion() == KNIGHT)
      {
         board[move.getSrc().getCol()][move.getSrc().getRow()] = new Knight(move.getSrc().getCol(), move.getSrc().getRow(), move.getIsWhite());
      }
   }
   // Check if there is a capture piece
   if (move.getCapture() != SPACE || move.getCapture() != INVALID)
   {
      board[move.getDes().getCol()][move.getDes().getRow()] = new Space(move.getDes().getCol(), move.getDes().getRow());
   }

   // Get the pieces at the source position and destination position
   Piece* piece1 = board[move.getSrc().getCol()][move.getSrc().getRow()];
   Piece* piece2 = board[move.getDes().getCol()][move.getDes().getRow()];

   // Set the source position to a space
   board[move.getSrc().getCol()][move.getSrc().getRow()] = piece2;

   // Move the piece to the destination position
   board[move.getDes().getCol()][move.getDes().getRow()] = piece1;

   // Update the pieces' positions
   piece1->setPosition(move.getDes());
   piece2->setPosition(move.getSrc());

   // Increment the number of moves
   numMoves++;

   piece1->setLastMove(numMoves);
}

/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty()
{
   delete pSpace;
}

 //extra: 
void Board::display(const Position& posHov, Position& posSelect, set<Move>& moves) const
{
   // draw the squares
   pgout->drawBoard();

   // draw select and hover
   pgout->drawHover(posHov);
   pgout->drawSelected(posSelect);

   // draw possible moves
   for (auto move : moves)
   {
      pgout->drawPossible(move.getDes());
   }

   // draw pieces
   for (int c = 0; c < 8; c++)
   {
      for (int r = 0; r < 8; r++)
      {
         if (board[c][r]->getType() != SPACE)
         {
            board[c][r]->display(pgout);            // call the display method of the piece 
         }
      }
   }
}

