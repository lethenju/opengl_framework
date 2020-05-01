#pragma once
#include <vector>
#include <array>
#include <thread>
#include "element.hpp"
class PhysicsElement{
public:
    Element* element;
    bool movable;
    std::array<float, 2> velocity;
    std::array<float, 2> acceleration;
};


class Physics {
public:
    int subscribe (Element* e);
    int subscribe (Element* e, float gravity);
    int subscribe (Element* e, float gravity, bool movable);
    int remove (Element* e);

    float get_gravity();
    int set_gravity(float g);

    int start();
    bool is_running();
    int stop();

    int set_velocity(Element* e, float vx, float vy);
    int set_acceleration(Element* e, float ax, float ay);
    std::array<float,2> get_velocity(Element* e);
    std::array<float,2> get_acceleration(Element* e);

    bool handle_collisions(PhysicsElement* element, float velocity_x, float velocity_y);

    std::vector<PhysicsElement> physics_subscribed_elements; 
    
private:
    float gravity = -0.001f;
    bool flag_continue = false;
    std::shared_ptr<std::thread>  physics_thread;
};

void my_physics_thread(Physics *physics_manager);
