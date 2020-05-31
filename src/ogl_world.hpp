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
#pragma once
#include "coordinates.hpp"
#include "element.hpp"
#include <map>
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


