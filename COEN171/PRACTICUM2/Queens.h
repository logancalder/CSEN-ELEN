// Name: Logan Calder
// Class: CSEN 171 MWF 9:15
// Assignment: Homework 2 - 8 Queens Problem
// Description: This file implements the structures for solving the 8 queens problem using composition, as opposed to virtual inheritance.

#include <cmath>

class Piece
{
protected:
    int _row, _column;

public:
    int row() const
    {
        return _row;
    }
    int column() const
    {
        return _column;
    }
    virtual void place(int row, int column)
    {
        _row = row;
        _column = column;
    }
    virtual bool menaces(const Piece *p) const = 0; // Pure virtual function
};

struct Rook : public Piece
{
    bool menaces(const Piece *p) const override
    {
        return _row == p->row() || _column == p->column();
    }
};

struct Knight : public Piece
{
    bool menaces(const Piece *p) const override
    {
        int rows = std::abs(_row - p->row());
        int cols = std::abs(_column - p->column());
        return (rows == 2 && cols == 1) || (rows == 1 && cols == 2);
    }
};

struct Bishop : public Piece
{
    bool menaces(const Piece *p) const override
    {
        int rows = std::abs(_row - p->row());
        int cols = std::abs(_column - p->column());
        return rows == cols;
    }
};

struct Queen : public Rook
{
    Bishop b;

    // Override place to set positions for both Rook and Bishop
    void place(int row, int column) override
    {
        Rook::place(row, column);
        b.place(row, column);
    }

    bool menaces(const Piece *p) const override
    {
        return Rook::menaces(p) || b.menaces(p);
    }
};

struct Amazon : public Queen
{
    Knight k;

    // Override place to set positions for both Queen and Knight
    void place(int row, int column) override
    {
        Queen::place(row, column);
        k.place(row, column);
    }

    bool menaces(const Piece *p) const override
    {
        return Queen::menaces(p) || k.menaces(p);
    }
};
