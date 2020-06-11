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
#include <map>
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
    int set_position(float x, float y);

    int resize(Coordinates resizePoint, float factorX, float factorY);
    int rotate(Coordinates rotationPoint, float rad);
    Coordinates get_center();
    Coordinates get_position();
    std::array<float,2>  get_dimensions();
    bool is_colliding_with(Element another_element);
};

bool operator==(const Element& e1, const Element& e2);
/** 
 * a PhysicsElement is an Element object with extra physics properties.
 */

class PhysicsElement{
public:
    PhysicsElement(Element* e, bool m, std::array<float, 2> v, std::array<float, 2> a)
        : element(e), movable(m), velocity(v), acceleration(a) {};
    Element* element;
    bool movable;
    std::array<float, 2> velocity;
    std::array<float, 2> acceleration;
    int set_stickyness(float s);
    float get_stickyness();
private:
    float stickyness = 0;
};


class Physics {
public:
    int subscribe (Element* e);
    int subscribe (Element* e, float gravity);
    int subscribe (Element* e, float gravity, bool movable);
    int subscribe (Element* e, float gravity, bool movable, float stickyness);

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
 * Represent a Rectangle, as an Element
 */
class Rectangle : public Element {
public:
    Rectangle();
    Rectangle(float x, float y, float width, float height, Color color);
};

/**
 * Represent a Circle, as an Element
 */ 
class Circle : public Element {
public:
    Circle(float x, float y, float radius, Color color);
};


/**
 * Represent a Tetragon (polygon with 4 sides), as an Element
 */ 
class Tetragon : public Element {
public:
    Tetragon(float x1, float y1, float x2, float y2, 
             float x3, float y3, float x4, float y4, Color color);
};

/**
 * Represent a Line as an Element
 */ 
class Line : public Element {
public:
	Line(float x1, float y1, float x2, float y2, float thickness, Color color);
};


class SevenSegment : public Element {
public:
    //  |=b1=|
    // b2    b3
    //  * b4 *
    // b5    b5
    //  |=b6=|
    SevenSegment(bool segments[7], float x, float y,float width,float height, Color color);
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
	 *  @return the ID of the created element
	 */
	int add_element(Element new_element);
	
	/** Remove an element from the world. 
	 *  @param element_ID : The old element ID to be removed from the world.
	 *  @return Error code, 0 if it worked, -1 if it didnt.
	 */
	int remove_element(int element_ID);
	
	/** Gets an element from the coordinates given
	 *  @param coord : The coordinates of the element 
	 *  @return A pointer to the element found.
	 */
	Element* get_element(Coordinates coord);
	
	/** Gets an element from the index in the list of elements
	 *  @param id : ID of the element to retrieve
	 *  @return A pointer to the element found.
	 */
	Element* get_element(int id);

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
	std::map<int, Element> elements;
	
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
	 * @param width : width of the window
	 * @param height : height of the window
	 * @param name : title of the window
	 */
	Ogl_wrapper(int width, int height, const char* name);

	/**
	 * Gets the mouse position in the screen
	 * @param x : a pointer to the float that will get updated
	 * @param y : a pointer to the float that will get updated
	 * @return 0 if it worked
	 */
	int ogl_get_mouse_position(float* x, float* y);

	/**
	 * Link a Ogl_world object for getting elements structure and prepare vertex buffers
	 * @param world : a pointer to the Ogl_world instance
	 * @return 0 if it worked
	 */
	int ogl_link_world(Ogl_world* world);
	
	/**
	 * Recomputes the vertex array from the world : each time this function is called
	 * it will get the data in the world and computes vertices and color data that
	 * are understandable by OpenGL
	 * So it needs to be called between adding a shape in your world and calling ogl_redraw
	 */
	int ogl_calc_vertex_array();

	/**
	 * Send the vertex arrays and colors array to opengl, for it to be really displayed on the screen
	 */
	int ogl_redraw();


	/**
	 * Setup an input callback that will be called if there's any type of glfw-sensed input
	 * @param cb : the callback function with the following parameters : GLFWwindow* window, int key, int scancode, int action, int mode
	 */
	int setup_input_callback(void* cb);
private:

	/**
	 * Initialize glfw
	 * @return 0 if it worked
	 */  
	int ogl_glfw_init();

	/**
	 * Setup a window
	 * @param width : width of the window
	 * @param height : height of the window
	 * @param name : title of the window
	 * @return 0 if it worked
	 */  
	int setup_window(int width, int height, const char* name);

	/**
	 * Initialize glew
	 * @return 0 if it worked
	 */  
	int ogl_glew_init();

	// The pointer to the window	
	GLFWwindow* window = nullptr;

	// The pointer to the world
	Ogl_world* world = nullptr;

	// The size of the vertex array
	int vertex_array_size = 0;

	// The vertex array itself
	float* vertex_array = nullptr;
	// The color array (which size is indexed from the vertex array size)
	float* color_array = nullptr;
	
	GLuint vaoID[1];
	GLuint vboID[1];
	GLuint shaderProgram; 
};
