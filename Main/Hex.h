#ifndef SIM_HEX
#define SIM_HEX 1

class Hex
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int x, const unsigned int y, const double hexRadius);

    void update();

    int getX();

    int getY();

    int getCol();

    int getRow();

private:
    // X/Y Locations
    const int x;
    const int y;
    const double hexRadius;

    //Where in the grid that it is located
    int col;
    int row;
};

#endif
