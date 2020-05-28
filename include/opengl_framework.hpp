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
/*
 ============= OPENGL_FRAMEWORK SOURCE CODE ===========
 @Description : Little framework to build graphics-based applications in openGL
 @Author : Julien LE THENO
 =============================================
*/
#include <vector>
#include <array>
#include <memory>
#include <stdlib.h>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*** LoadShaders loads some shader files and returns the program ID
 *  @param vertex_file_path the path of the vertex shader
    @param fragment_file_path the path of the fragment shader
	@return the openGL programID of the shader  
 */
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);


/*** Class coordinates represent 2D coordinates x and y.
 *   Basically is just a pair of float structure.
 */
class Coordinates {
public:
	float x, y;
};

// A coordinate is set to be inferior to another one if the sum of its components is inferior
bool operator<(const Coordinates& c1, const Coordinates& c2);
// A coordinate is set to be superior to another one if the sum of its components is superior
bool operator>(const Coordinates& c1, const Coordinates& c2);
// A coordinate is set to be equal to another one if both of their components are equal
bool operator==(const Coordinates& c1, const Coordinates& c2);

std::array<float, 2> operator-(const Coordinates& c1, const Coordinates& c2);
std::array<float, 2> operator+(const Coordinates& c1, const Coordinates& c2);


// Class color represent a color (in rgb definition only).
class Color
{
public:
	// Basic constructor create a black color
	Color() {
		this->r = 0;
		this->v = 0;
		this->b = 0;
	};
	// Custom constructor to initialize a color.
	Color(float r, float v, float b) {
		this->r = r;
		this->v = v;
		this->b = b;
	};
	float r;
	float v;
	float b;
};


/*** Class Triangle reprensents a triangle with its 3 coordinates and a color.
 *
 */
class Triangle
{
public:
	Triangle(Coordinates p1, Coordinates p2, Coordinates p3, Color inside_color);
	/*** is_inside checks if a point is inside a triangle or not. 
	 *   @param coord the coordinates of the point to test
	 *   @return true if the point is inside the coordinate.
	 */
	bool is_inside(Coordinates coord);

	Color color;
	std::array<Coordinates, 3> coordinates;

};



// Element class, overloading std::vector.
class Element : public std::vector<Triangle>
{
public:
    int translate(float x, float y);
    int resize(float factor);
    int rotate(float degrees);

    Coordinates get_position();
    std::array<float,2>  get_dimensions();
    bool is_colliding_with(Element another_element);
    int get_direction(Element another_element);

};

bool operator==(const Element& e1, const Element& e2);

/** 
 * a PhysicsElement is an Element object with extra physics properties.
 */
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

/**
 * Represent a Square, as an Element
 */
class Square : public Element {
public:
    Square(float x, float y, float width, float height, Color color);
};

/**
 * Represent the 2D "world" with primarily a list of elements.
 */ 
class Ogl_world
{
public:
	/**
	 *  Constructor of Ogl_World, take the background color of the world
	 */
	Ogl_world(Color background): bg(background) {};
	
	/** Add an element to the world
	 *  @param new_element : the new element to add in the world. It will copy it, so the previous lvalue can be freed.
	 *                       You can use (and its actually better) rvalue with directly creating a new element in add_element
	 * 						 like so : world.add_element(Element(...)); or any derived element class from geom
	 *  @return Error code, 0 if it worked, -1 if it didnt.
	 */
	int add_element(Element new_element);
	
	/** Remove an element from the world. 
	 *  @param element_to_remove : The old element to be removed from the world.
	 *  @return Error code, 0 if it worked, -1 if it didnt.
	 */
	int remove_element(Element element_to_remove);
	
	/** Gets an element from the coordinates given
	 *  @param coord : The coordinates of the element 
	 *  @return A pointer to the element found.
	 */
	Element* get_element(Coordinates coord);
	
	/** Gets an element from the index in the list of elements
	 *  @param nb : Index of the element to retrieve
	 *  @return A pointer to the element found.
	 */
	Element* get_element(int nb);

	/** Return an ro version of the element list 
	 * (to prevent modification from outside the class.. We can expose our world but not expose the ways to modify it
	 * @returns ro version of the element list.
	 */
	const std::vector<Element> get_elements();

	/**
	 * @returns The size of the raw coord array that is built in get_raw_coord_array
	 */
	int get_raw_coord_array_size();
	
	/** Creates an array with all the vertex values that will be used by opengl
	 * @param pointer_to_tab the pointer to the array that will be filled
	 * @return error code : 0 if success, -1 if failure.
	 */
	int get_raw_coord_array(float* pointer_to_tab);
	
	/** Creates an array with all the color values that will be used by opengl
	 * @param pointer_to_tab the pointer to the array that will be filled
	 * @return error code : 0 if success, -1 if failure.
	 */
	int get_raw_color_array(float* pointer_to_tab);

	/** Sets a new background for the world.
	 * @param new_background the new background for the world.
	 * @return error code : 0 if success, -1 if failure.
	 */ 
	int set_background(Color new_background);

	/** Return the background color of the world.
	 */
	Color get_background();

private:
	/** List of elements contained in the world.
	 */  
	std::vector<Element> elements;
	
	/** Background color of the world.
	 */  
	Color bg;
};



/**
 * Represent OpenGL, act as a layer to put everything directly related to opengl, glfw and glew inside
 */ 
class Ogl_wrapper {
public:
	/**
	 * Constructor of Ogl_wrapper
	 */
	Ogl_wrapper(int width, int height, char* name);
	int ogl_glfw_init();
	int setup_window(int width, int height, const char* name);
	int ogl_glew_init();
	int ogl_redraw();

	// Link a Ogl_world object for getting elements structure and prepare vertex buffers
	int ogl_link_world(Ogl_world* world);
	int ogl_calc_vertex_array();
	int setup_input_callback(void* cb);
private:
	
	GLFWwindow* window = nullptr;
	Ogl_world* world = nullptr;
	int vertex_array_size = 0;
	float* vertex_array = nullptr;
	float* color_array = nullptr;
	
	GLuint vaoID[1];
	GLuint vboID[1];
	GLuint shaderProgram; 
};
