#pragma once
#include "element.hpp"
#include <vector>

class Physics {
public:
    int subscribe (Element* e);
    int remove (Element* e);

    int set_gravity(float g);

private:
    void physics_thread(void);
    std::vector<Element*> physics_subscribed_elements; 
}