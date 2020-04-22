#include "coordinates.hpp"
#include "element.hpp"

class Boundaries {
public:
    Boundaries(Coordinates top_left, Coordinates bottom_right) : top_left(top_left), bottom_right(bottom_right){

    }

    bool CheckBoundary(Element* e);

    private:
        Coordinates top_left, bottom_right;
}