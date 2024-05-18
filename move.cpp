/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *     Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "position.h" // gain access to Position. 
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <cctype> // for isdigit and isalpha
#include <stdexcept> // for std::invalid_argument
#include <map> // for the auto it on the move constructor
#include <vector>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
    source = INVALID;
    dest = INVALID;
    promote = INVALID;
    capture = INVALID;
    moveType = MOVE;
    isWhite = true;
    text = "";
}

/***************************************************
 * MOVE :CONSTRUCTOR
 ***************************************************/
Move::Move(Position from, Position to, MoveType mt, PieceType capturePiece, bool whiteTurn)
{
   this->source = from;
   this->dest = to;
   this->moveType = mt;
   this->capture = capturePiece;
   this->isWhite = whiteTurn;
   this->text = getText();
}

/***************************************************
 * MOVE : STRING MOVES CONSTRUCTOR.
 ***************************************************/
Move::Move(const std::string& moveString)
{
    assign(moveString);
}

/***************************************************
 * GetText
 ***************************************************/
string Move::getText() const
{
    vector<string> column
    {
        "a", "b", "c", "d", "e", "f", "g", "h"
    };
    vector<string> row
    {
        "1", "2", "3", "4", "5", "6", "7", "8"
    };
    map<MoveType, string> moveTypeChar
    {
        {ENPASSANT, "E"}, {CASTLE_KING, "c"}, {CASTLE_QUEEN, "C"},
    };
    map<PieceType, string> captureChar
    {
        {PAWN,   "p"}, {KNIGHT, "n"}, {ROOK,   "r"},
        {QUEEN,  "q"}, {KING,   "k"}, {BISHOP, "b"},
    };
    int srcCol = source.getCol();
    int srcRow = source.getRow();
    int destCol = dest.getCol();
    int destRow = dest.getRow();
    if (moveType == MOVE_ERROR)
    {
        return "Error";
    }
    string text;
    text = column[srcCol] + row[srcRow] + column[destCol] + row[destRow];
    if (moveType != INVALID || moveType != MOVE)
    {
        text += moveTypeChar[moveType];
    }
    else
    {
        if (capture != INVALID)
        {
            text += captureChar[capture];
        }
    }
    return text;
}


/***************************************************
 * MOVE:  ASSIGN MOVE
 ***************************************************/
void Move::assign(const Move& other)
{
    // Assigning attributes from 'other' to the current object
    this->source = other.source;
    this->dest = other.dest;
    this->promote = other.promote;
    this->capture = other.capture;
    this->moveType = other.moveType;
    this->isWhite = other.isWhite;
    this->text = other.text;
}

/***************************************************
 * MOVE:
 ***************************************************/
bool Move::assign(const std::string& str)
{
    // Ensure the str has a valid length
    if (str.length() < 4) {
        return false;
    }

    // Extract source and destination positions from str
    std::string sourcePos = str.substr(0, 2);
    std::string destPos = str.substr(2, 2);

    // Set source and destination positions
    source = Position(sourcePos.c_str());
    dest = Position(destPos.c_str());

    // If there's a fifth character, it should be the promotion piece, the captured piece, 'E' for en passant, or 'c' for castle
    if (str.length() >= 5) {
        char fifthChar = str[4];
        if (fifthChar == 'E') {
            moveType = ENPASSANT;
        }
        else if (fifthChar == 'c') {
            moveType = CASTLE_KING;
        }
        else if (fifthChar == 'C') {
            moveType = CASTLE_QUEEN;
        }
        else if (fifthChar == 'q' || fifthChar == 'r' || fifthChar == 'b' || fifthChar == 'n' || fifthChar == 'p' || fifthChar == 'k') {
            capture = pieceTypeFromLetter(fifthChar);
            moveType = MOVE; // Regular move
        }
        else {
            promote = pieceTypeFromLetter(fifthChar);
            moveType = MOVE; // Regular move
        }
    }
    else {
        promote = SPACE; // No promotion
        capture = SPACE; // No capture
        moveType = MOVE; // Regular move
    }

    // Set other attributes to default values
    isWhite = true; // White's move by default
    text = str; // Textual version of the move

    return true;
}


/***************************************************
 *  INSERTION OPERATOR
 ***************************************************/
std::ostream& operator<<(std::ostream& os, const Move& move)
{
    // Implement the behavior of how a Move object should be output
    os << "Move from " << move.getSrc() << " to " << move.getDes();
    return os;
}

/***************************************************
 *  EXTRACTION OPERATOR
 ***************************************************/
 // Still need extraction operator.

// extra operators:
bool Move::operator==(const Move& other) const {
    // Two moves are equal if their source and destination positions are the same
    return source == other.source && dest == other.dest;
}

bool Move::operator<(const Move& other) const {
   // One move is less than another if its source position is less,
   // or if their sources are equal and its destination is less
   return source < other.source || (source == other.source && dest < other.dest);
}
