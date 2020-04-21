#pragma once
#include "element.hpp"
#include <vector>

class PhysicsElement{
public:
    Element* element;
    float velocity;
    float acceleration;
};


class Physics {
public:
    int subscribe (Element* e);
    int remove (Element* e);

    int set_gravity(float g);

    int set_velocity(Element* e, float v);
    float get_velocity(Element* e);
    int set_acceleration(Element* e, float a);
    float get_acceleration(Element* e);
    
private:
    float gravity = 1;
    void physics_thread(void);
    std::vector<PhysicsElement> physics_subscribed_elements; 
};