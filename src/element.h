#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <memory>
#include <vector>
//#include "Coordinate.h"

struct Coordinate
{
    Coordinate(const int x, const int y) : _x_coord(x), _y_coord(y){};

    // Getters
    int get_x_coord() const { return _x_coord; }
    int get_y_coord() const { return _y_coord; }
    bool operator==(const Coordinate &coordinate) const
    {
        return (_x_coord == coordinate._x_coord && _y_coord == coordinate._y_coord);
    }

private:
    int _x_coord;
    int _y_coord;
};

class Element
{
    public:
    Element();

    void create_element(const Coordinate &&coordinate);
    bool element_is_of_type(const Coordinate &&coordinate);
    int get_element_ocurrence() const;


    const std::vector<Coordinate> &getCoordinates() const;

    protected:
    std::unique_ptr<std::vector<Coordinate>> _coordinates;
};

class Trap : public Element
{};

class Special_food : public Element
{
public:
    void delete_element(const Coordinate &&coordinate);
};

#endif
