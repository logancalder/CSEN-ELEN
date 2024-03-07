
class RatNum
{
public:
    RatNum(int, unsigned int);

private:
    int whole int nom;
    unsigned int den;
friend std::ostream &operator<<(std::ostream &os, const RatNum &n);
};

// RatNum operator-(const RatNum &r1, const RatNum &r2)