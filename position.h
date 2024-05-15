/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Yat Lam, Josue Molina, and Fabian Diaz Santiago
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/
#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
    int dRow;
    int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1, 0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;
/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
    friend class TestMove;
    friend class TestBoard;

public:

    // The Position class can work with other positions.
    Position(const Position& rhs) : colRow(rhs.colRow) { }
    Position() : colRow(0x99) { }
    bool isInvalid() const { return (colRow & 0x88) != 0; }
    bool isValid() const { return !isInvalid(); }
    void setValid() { colRow = 0x00; }
    void setInvalid() { colRow = 0xFF; }
    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }

    Position& operator=(const Position& rhs)
    {
        if (this != &rhs)
            colRow = rhs.colRow;
        return *this;
    }

    // Location : The Position class can work with locations, which
    //            are 0...63 where we start in row 0, then row 1, etc.
    Position(int location) : colRow(location) { }

    // DECLARATIONS
    int getLocation() const;
    void setLocation(int location);
    int getCol() const;
    int getRow() const;
    void setCol(int c);
    void setRow(int r);
    void set(int c, int r);
    void adjustRow(int dRow);
    void adjustCol(int dCol);
    Position& operator +=(const Delta& rhs);
    Position operator +(const Delta& rhs) const;


    // Row/Col : The position class can work with row/column, which are 0..7 and 0...7
    Position(int c, int r) : colRow(static_cast<uint8_t>(r * 8 + c)) { }


    // The Position class can work with textual coordinates, such as "d4".
    Position(const char* s) { set(s); }
    const Position& operator =  (const char* rhs) { set(rhs); return *this; }
    const Position& operator =  (const string& rhs) { set(rhs.c_str()); return *this; }


    // PIXELS: The Position class can work with screen coordinates X, Y coordinates.
    int getX() const { return getCol() * SIZE_SQUARE + OFFSET_BOARD; }
    int getY() const { return getRow() * SIZE_SQUARE + OFFSET_BOARD; }
    void setXY(double x, double y)
    {
        int c = static_cast<int>(x / squareWidth); // Convert the x coordinate to a column number
        int r = static_cast<int>(y / squareHeight); // Convert the y coordinate to a row number
        colRow = (c << 4) | r;
    }
    double getSquareWidth() const { return static_cast<double>(SIZE_SQUARE); }
    double getSquareHeight() const { return static_cast<double>(SIZE_SQUARE); }
    static void setSquareWidth(double width) { squareWidth = width; }
    static void setSquareHeight(double height) { squareHeight = height; }

    // Delta:The Position class can work with deltas, which are offsets from a given location.
    Position(const Position& rhs, const Delta& delta) : colRow(-1) {  }


private:
    void set(uint8_t colRowNew) { colRow = colRowNew; }
    void set(const char* s)
    {
        if (s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8') {
            colRow = 0xFF; // Invalid position
        }
        else {
            int c = s[0] - 'a';
            int r = s[1] - '1';
            colRow = (c << 4) | r;
        }
    }

    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;
};

ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);

