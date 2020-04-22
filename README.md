# opengl_framework

A simple 2D openGL Framework written in C++

My ambition was to get familiar with modern C++ development, and to better understand the secrets of openGL development. 

The project in itself is in development, and might never actually get finished. 

## Presentation

The framework resolve around several blocks :

* A `Ogl_Wrapper` object that deals with OpenGL itself, shader loading, GLFW Window management etc
* A `Ogl_world` object that manages the world and all the elements inside. 
* A `Physics` object that manages the physics engine, wrapping world elements with velocity and acceleration parameters.


## Usage 

Look at the main.cpp file to see how its used.


Basic example :
```c

int main(void)
{
    // Creating the Ogl_wrapper object.
    static Ogl_wrapper ogl = Ogl_wrapper();
    // Creating the World object with the background color
    Ogl_world world = Ogl_world(Color(0.2f,0,0));
    // Instantiate a physics_manager and launch physics thread
    Physics physics_manager;
	std::thread physics_thread (my_physics_thread, &physics_manager);
     // Setting a callback called each time a user press a key
     // This callback is not shown in this example.
	ogl.setup_input_callback((void*)key_callback);
    // We have to link the world to the Ogl_wrapper
	ogl.ogl_link_world(&world);
    // Add a green square to the world
	world.add_element(Square(0,0,0.2f,0.2f, Color(0,1,0)));
    // Subscribe the square to the physics manager
	physics_manager.subscribe(world.get_element(0)); 
    
	
    // Main loop
    static bool continue_flag = true;
	while (continue_flag) {	
        // Recompute data from world to be sent to OpenGL
		ogl.ogl_calc_vertex_array();
        // Redraw screen accordingly
		ogl.ogl_redraw();
        // Wait for the next frame
		usleep(5000);
	}
	return 0;
}
```

