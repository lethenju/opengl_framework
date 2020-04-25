#include <iostream>
#include <unistd.h>
#include "physics.hpp"



int Physics::subscribe (Element* e) {
	PhysicsElement *physicsElement = new PhysicsElement	{
		e, std::array<float, 2> {0 , 0}, std::array<float, 2> {0 , this->gravity}
	};
	this->physics_subscribed_elements.push_back(*physicsElement);
}
int Physics::remove (Element* e) {
	for (int count = 0; count < this->physics_subscribed_elements.size(); count++) {
		if (this->physics_subscribed_elements.at(count).element == e) {
			PhysicsElement *to_delete = &(this->physics_subscribed_elements.at(count));
			this->physics_subscribed_elements.erase(this->physics_subscribed_elements.begin()+count);
			delete to_delete;
			return 0;
		}
	}
	return -1; // element not found
}

int Physics::set_gravity(float g) {
	this->gravity = g;
}



int Physics::set_velocity(Element* e, float vx, float vy) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			physics_element.velocity[0] = vx;
			physics_element.velocity[1] = vy;
			return 0;
		}
	}
	return -1; // Element not found
}
std::array<float,2> Physics::get_velocity(Element* e) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			return physics_element.velocity;
		}
	}
	return std::array<float,2>{0,0}; // Element not found
}
int Physics::set_acceleration(Element* e, float ax, float ay) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			physics_element.acceleration[0] = ax;
			physics_element.acceleration[1] = ay;
			return 0;
		}
	}
	return -1; // Element not found
}

std::array<float,2> Physics::get_acceleration(Element* e) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			return physics_element.acceleration;
		}
	}
	return std::array<float,2>{0,0}; // Element not found
}


void my_physics_thread(Physics *physics_manager) {
	while (1) {
		usleep(5000);
		for (auto & element : physics_manager->physics_subscribed_elements){
			std::array<float, 2> collision_vector = element.element->translate(element.velocity[0]/10, element.velocity[1]/10);
			element.velocity[0] =  element.velocity[0] * collision_vector[0];
			element.velocity[1] =  element.velocity[1] * collision_vector[1];
				// Should be great to override += for std::array
			element.velocity[0] += element.acceleration[0]/10;
			element.velocity[1] += element.acceleration[1]/10;
		}
	}
}
