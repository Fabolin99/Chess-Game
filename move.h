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
	Move(Position from, Position to, MoveType mt, PieceType capturePiece, bool whiteTurn);

	// DECLARATIONS
	Move(const std::string& moveString); // Constructor for movements using strings ie: e6e5
	string getText() const;
	Position getSrc() const { return source; }
	Position getDes() const { return dest ;}
	PieceType getPromotion() const { return promote; }
	PieceType getCapture() const { return capture; }
	bool getCastleK() const { return CASTLE_KING; }
	bool getCastleQ() const { return CASTLE_QUEEN; }
	std::string getWhiteMove() const { return text; }
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

private:
	char letterFromPieceType(PieceType pt) const
	{
		// Map of PieceType to corresponding character
		std::map<PieceType, char> pieceTypeToChar = {
			{PAWN, 'p'},
			{KNIGHT, 'n'},
			{BISHOP, 'b'},
			{ROOK, 'r'},
			{QUEEN, 'q'},
			{KING, 'k'},
			{SPACE, ' '}
		};

		// Find the PieceType in the map
		auto it = pieceTypeToChar.find(pt);
		if (it != pieceTypeToChar.end())
			return it->second;  // Return the corresponding character
		else
			std::cout << "Invalid piece type" << std::endl;
	}


	PieceType pieceTypeFromLetter(char letter) const
	{
		// Map of character to corresponding PieceType
		std::map<char, PieceType> charToPieceType = {
			{'p', PAWN},
			{'n', KNIGHT},
			{'b', BISHOP},
			{'r', ROOK},
			{'q', QUEEN},
			{'k', KING},
			{' ', SPACE}
		};

		// Convert the letter to lowercase
		char lowerLetter = std::tolower(letter);

		// Find the letter in the map
		auto it = charToPieceType.find(lowerLetter);
		if (it != charToPieceType.end())
			return it->second;  // Return the corresponding PieceType
		else
			std::cout << "Invalid piece type" << std::endl;
	}

	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	string    text;      // what is the textual version of the move?
};


