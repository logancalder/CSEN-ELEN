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
    void place(int row, int column)
    {
        _row = row;
        _column = column;
    }
    virtual bool menaces(const Piece *p) const = 0;
};

struct Rook : public virtual Piece
{
    virtual bool menaces(const Piece *p) const
    {
        return _row == p->row() || _column == p->column();
    }
};

struct Knight : public virtual Piece
{
    virtual bool menaces(const Piece *p) const
    {
        int rows = abs(_row - p->row());
        int cols = abs(_column - p->column());
        return (rows == 2 && cols == 1) || (rows == 1 && cols == 2);
    }
};

struct Bishop : public virtual Piece
{
    virtual bool menaces(const Piece *p) const
    {
        int rows = abs(_row - p->row());
        int cols = abs(_column - p->column());
        return rows == cols;
    }
};

struct Queen : public Rook, Bishop
{
    virtual bool menaces(const Piece *p) const
    {
        return Rook::menaces(p) || Bishop::menaces(p);
    }
};

struct Amazon : public Queen, Knight
{
    virtual bool menaces(const Piece *p) const
    {
        return Queen::menaces(p) || Knight::menaces(p);
    }
};
