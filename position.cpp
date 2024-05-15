/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>

 /******************************************
  * POSITION INSERTION OPERATOR
  ******************************************/
ostream& operator << (ostream& out, const Position& rhs)
{
    out << "error";
    return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator >> (istream& in, Position& rhs)
{
    return in;
}

/*************************************
 * GET LOCATION
 **************************************/
int Position::getLocation() const
{
    if (isInvalid()) {
        return -1;
    }
    return getRow() * 8 + getCol();
}

/*************************************
 *  SET LOCATION
 **************************************/
void Position::setLocation(int location)
{
    int c = location % 8; // Convert the location to a column number
    int r = location / 8; // Convert the location to a row number
    colRow = (c << 4) | r;
}
/*************************************
 *  GET COLUMN
 **************************************/
int Position::getCol() const
{
    if (isInvalid()) {
        return -1;
    }
    return ((colRow & 0xF0) >> 4);
}

/*************************************
 *  GET ROW
 **************************************/
int Position::getRow() const
{
    if (isInvalid()) {
        return -1;
    }
    return (colRow & 0x0F);
}

/*************************************
 *  SET COLUMN
 **************************************/
void Position::setCol(int c)
{
    if (c < 0 || c > 7) {
        colRow = 0xFF;
    }
    else {
        int r = getRow();
        colRow = (c << 4) | r;
    }
}

/*************************************
 *  SET ROW
 **************************************/
void Position::setRow(int r)
{
    if (r < 0 || r > 7) {
        colRow = 0xFF; // Invalid position
    }
    else {
        int c = getCol();
        colRow = (r | (c << 4));
    }
}

/*************************************
 *  SET
 **************************************/
void Position::set(int c, int r)
{
    if (c < 0 || c > 7 || r < 0 || r > 7) {
        colRow = 0xFF; // Invalid position
    }
    else {
        colRow = (c << 4) | r;
    }
}

/*************************************
 *  ADJUST ROW
 **************************************/
void Position::adjustRow(int dRow)
{
    int r = getRow() + dRow;
    if (r >= 0 && r < 8)
        setRow(r);
}

/*************************************
 *  ADJUST COLUMN
 **************************************/
void Position::adjustCol(int dCol)
{
    int c = getCol() + dCol;
    if (c >= 0 && c < 8)
        setCol(c);
}

/*************************************
 *  PLUS EQUALS OPERATOR
 **************************************/
Position& Position::operator +=(const Delta& rhs)
{
    int newRow = getRow() + rhs.dRow;
    int newCol = getCol() + rhs.dCol;
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
        set(newCol, newRow);
    else
        colRow = 0xFF; // Invalid position
    return *this;
}

/*************************************
 *  PLUS OPERATOR
 **************************************/
Position Position::operator +(const Delta& rhs) const
{
    Position newPos(*this);
    newPos += rhs;
    return newPos;
}



