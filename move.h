/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *     Yat Lam, Fabian Santiago, Josue Molina
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type
#include <map>
#include <iostream>


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
	enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

	// DECLARATIONS
	Move(const std::string& moveString); // Constructor for movements using strings ie: e6e5
	string getText() const;
	Position getSrc() const { return source; }
	Position getDes() const { return dest ;}
	PieceType getPromotion() const { return promote; }
	PieceType getCapture() const { return capture; }
	bool getCastleK() const { return (moveType == CASTLE_KING ? true : false); }
	bool getCastleQ() const { return (moveType == CASTLE_QUEEN ? true : false); }
	bool isEnpassant() const { return (moveType == ENPASSANT ? true : false); }
	std::string getWhiteMove() const { return text; }
	bool getIsWhite() const { return isWhite; } // extra to get the white turn
	void setEnPassant() { this->moveType = ENPASSANT; }
	void setCastle(bool isKing) {this->moveType = isKing ? CASTLE_KING : CASTLE_QUEEN; }
	void setCastleQ() { this->moveType = CASTLE_QUEEN; }
	void setWhiteMove(bool isWhite) { this->isWhite = isWhite; }
	void assign(const Move& other);
	bool assign(const std::string& str);

	// extra operators:
	bool operator==(const Move& other) const;
	bool operator<(const Move& other) const;




	friend TestMove;
	friend TestBoard;
	// constructor
	Move();
	Move(Position from, Position to, MoveType mt, PieceType capturePiece, bool whiteTurn, bool fPromotion = false);

private:
	char letterFromPieceType(PieceType pt) const;
	PieceType pieceTypeFromLetter(char letter) const;

	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	string    text;      // what is the textual version of the move?
};


