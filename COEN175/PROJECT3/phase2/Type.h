#ifndef TYPE_H
#define TYPE_H
#include <vector>
#include <ostream>

enum
{
    POINTER,
    ARRAY,
    FUNCTION
};
typedef std::vector<class Type> Types;

struct Parameters
{
    bool variadic;
    Types types;
};

class Declarator
{
    int _kind;
    unsigned _length;
    Parameters *_parameters;
    bool operator==(const Declarator &that) const;
    bool operator!=(const Declarator &that) const;

public:
    Declarator(int kind, unsigned length = 0, Parameters *parameters = nullptr);
    int kind() const { return _kind; }
    unsigned length() const;
    Parameters *parameters() const;
};

std::ostream &
operator<<(std::ostream &ostr, const Declarator &decl);

typedef std::vector<Declarator> Declarators;

class Type
{
    int _specifier;
    Declarators _decls;

public:
    Type(int specifier, const Declarators &decls);
    int specifier() const;
    const Declarators &declarators() const;
    bool operator==(const Type &that) const;
    bool operator!=(const Type &that) const;
};

std::ostream &
operator<<(std::ostream &ostr, const Type &type);


#define Pointer() Declarator(POINTER)
#define Array(n) Declarator(ARRAY, n)
#define Function(p) Declarator(FUNCTION, 0, p)



#endif