#include <iostream>
#include "physics.hpp"



int Physics::subscribe (Element* e) {
	PhysicsElement *physicsElement = new PhysicsElement	{
		e, 0, 0
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
	return -1 // element not found
}

int Physics::set_gravity(float g) {
	this->gravity = g;
}

void Physics::physics_thread(void) {
	while (1) {
		std::cout << "Physics_thread" << std::endl;
	}
}

int Physics::set_velocity(Element* e, float v) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			physics_element.velocity = v;
			return 0;
		}
	}
	return -1; // Element not found
}
float Physics::get_velocity(Element* e) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			return physics_element.velocity;
		}
	}
	return -1; // Element not found
}
int Physics::set_acceleration(Element* e, float a) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			physics_element.acceleration = a;
			return 0;
		}
	}
	return -1; // Element not found
}

float Physics::get_acceleration(Element* e) {
	for (auto& physics_element : this->physics_subscribed_elements) {
		if (physics_element.element == e) {
			return physics_element.acceleration;
		}
	}
	return -1; // Element not found
}