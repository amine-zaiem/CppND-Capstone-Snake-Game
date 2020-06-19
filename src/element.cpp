#include <memory>

#include "element.h"

Element::Element()
{
    // Initialising unique pointer
    _coordinates = std::unique_ptr<std::vector<Coordinate>>(new std::vector<Coordinate>);
}

void Element::create_element(const Coordinate &&coordinate)
{
    _coordinates->emplace_back(coordinate);
}

bool Element::element_is_of_type(const Coordinate &&coordinate)
{
    for ( auto &coordItem : *_coordinates)
    {
        if (coordItem == coordinate)
        {
            return true;
        }
    }
    return false;
}

int Element::get_element_ocurrence() const
{
    return _coordinates->size();
}

const std::vector<Coordinate> &Element::getCoordinates() const
{
    return *_coordinates;
}

void Special_food::delete_element(const Coordinate &&coordinate)
{
    if (_coordinates->size() != 0)
    {

        size_t index = 0;
        for (auto item = _coordinates->begin(); item != _coordinates->end();)
        {
            if (*item == coordinate)
            {
                item = _coordinates->erase(item);
            }
            else
            {
                ++item;
            }
        }
    }
}

