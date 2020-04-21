#pragma once
#include <vector>
#include <array>
#include "element.hpp"
class PhysicsElement{
public:
    Element* element;
    std::array<float, 2> velocity;
    std::array<float, 2> acceleration;
};


class Physics {
public:
    int subscribe (Element* e);
    int remove (Element* e);

    int set_gravity(float g);

    int set_velocity(Element* e, float vx, float vy);
    int set_acceleration(Element* e, float ax, float ay);
    std::array<float,2> get_velocity(Element* e);
    std::array<float,2> get_acceleration(Element* e);

    std::vector<PhysicsElement> physics_subscribed_elements; 
    float gravity = 0.01f;
    
private:
};

void my_physics_thread(Physics *physics_manager);
