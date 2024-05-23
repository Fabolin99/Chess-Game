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

    // put the knights into the right spots
    board[1][7] = new Knight(1, 7, false /*isWhite*/);              // left  black knight (col: 1, row: 7)
    board[6][7] = new Knight(6, 7, false /*isWhite*/);              // right black knight (col: 6, row: 7)
    board[1][0] = new Knight(1, 0, true  /*isWhite*/);              // left  white knight (col: 1, row: 0)
    board[6][0] = new Knight(6, 0, true  /*isWhite*/);              // right white knight (col: 6, row: 0)

    // fill in spaces
    for (int col = 0; col < 8; col++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (board[col][row] == nullptr)
            {
                board[col][row] = new Space(col, row);
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

/***********************************************
* BOARD : DISPLAY
*         Display the board
***********************************************/
void Board::display() const
{
    // draw the squares
    pgout->drawBoard();

    // draw pieces
    for (int col = 0; col < 8; col++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (board[col][row]->getType() != SPACE)
                board[col][row]->display(pgout);            // call the display method of the piece         
        }
    }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{

    // set all the squares to nullptr
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;
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
        for (int c = 0; c < 8; c++)
            if (board[c][r] != nullptr)
                pieceNum++;
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
        return;

    // Check if there is a capture piece
    if (move.getCapture() != SPACE || move.getCapture() != INVALID)
    {
        board[move.getDes().getCol()][move.getDes().getRow()] = new Space(move.getDes().getCol(), move.getDes().getRow());
    }

    // Get the piece at the source position
    Piece* piece = board[move.getSrc().getCol()][move.getSrc().getRow()];

    // Set the source position to a space
    board[move.getSrc().getCol()][move.getSrc().getRow()] = board[move.getDes().getCol()][move.getDes().getRow()];

    // Move the piece to the destination position
    board[move.getDes().getCol()][move.getDes().getRow()] = piece;

    // Increment the number of moves
    numMoves++;
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