/*
MIT License

Copyright (c) 2020 Julien LE THENO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <iostream>
#include <unistd.h>
#include <thread>
#include "physics.hpp"


int Physics::start() {
	this->flag_continue = true;
	this->physics_thread = std::make_shared<std::thread>(my_physics_thread, this);
	return 0;
}

bool Physics::is_running() {
	return this->flag_continue;
}
int Physics::stop() {
	this->flag_continue = false;
	this->physics_thread->join();
	return 0;
}

int Physics::subscribe (Element* e) {
	PhysicsElement *physicsElement = new PhysicsElement	{
		e, true, std::array<float, 2> {0 , 0}, std::array<float, 2> {0 , this->gravity}
	};
	this->physics_subscribed_elements.push_back(*physicsElement);
	return 0;
}

int Physics::subscribe (Element* e, float gravity) {
	PhysicsElement *physicsElement = new PhysicsElement	{
		e, true, std::array<float, 2> {0 , 0}, std::array<float, 2> {0 , gravity}
	};
	this->physics_subscribed_elements.push_back(*physicsElement);
	return 0;
}

int Physics::subscribe (Element* e, float gravity, bool movable) {
	PhysicsElement *physicsElement = new PhysicsElement	{
		e, movable, std::array<float, 2> {0 , 0}, std::array<float, 2> {0 , gravity}
	};
	this->physics_subscribed_elements.push_back(*physicsElement);
	return 0;
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


float Physics::get_gravity() {
	return this->gravity;
}


int Physics::set_gravity(float g) {
	this->gravity = g;
	// TODO update all elements with gravity
	return 0;
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

bool Physics::handle_collisions(PhysicsElement* element, float velocity_x, float velocity_y) {
	bool rv;
	// check collision with other elements
	for (auto & second_element : this->physics_subscribed_elements) {
		if (&second_element == element) {
			continue;
		}
		if (element->element->is_colliding_with(*second_element.element)){
			//std::cout << "Info : Collision" << std::endl;
			PhysicsElement *element_to_move, *other_one;
			if (element->movable) {
				element_to_move = element;
				other_one = &second_element;
			} else if (second_element.movable) {
				element_to_move = &second_element;
				other_one = element;
			} else {
				std::cout << "Warning : Both colliding objects are non movable.." << std::endl;
				continue;
			}
			// Go back
			element_to_move->element->translate(-velocity_x, -velocity_y);

			if (element->velocity[0] != 0 || element->velocity[1] != 0) {
				int direction = element_to_move->element->get_direction(*other_one->element);
				switch (direction) {
					case 0 :
						element->velocity[1] =  element->velocity[1] * -1;
						std::cout << "Direction : up" << std::endl;
						break;
					case 1 :
						std::cout << "Direction : right" << std::endl;
						element->velocity[0] =  element->velocity[0] * -1;
						break;
					case 2 :
						std::cout << "Direction : down" << std::endl;
						element->velocity[1] =  element->velocity[1] * -1;
						break;
					case 3 :
						std::cout << "Direction : left" << std::endl;
						element->velocity[0] =  element->velocity[0] * -1;
						break;
					default:
						break;
				}
			}
			rv =  true;
		}
	}
	return rv;
}

void my_physics_thread(Physics *physics_manager) {
	
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	while (physics_manager->is_running()) {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		usleep(50000 * fElapsedTime);
		for (auto & element : physics_manager->physics_subscribed_elements){
		
			physics_manager->handle_collisions(&element,element.velocity[0]/100, element.velocity[1]/100);
			element.element->translate(element.velocity[0]/100, element.velocity[1]/100);
				// Should be great to override += for std::array
			element.velocity[0] += element.acceleration[0]/100;
			element.velocity[1] += element.acceleration[1]/100;
		}
	}
}
