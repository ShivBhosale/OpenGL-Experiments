Some OpenGL experimental code to get a better understanding of how graphics in OpenGL work

to Run:

g++ main_screen.cpp -lGL -lGLU -lglut && ./a.out
-----------------------------------------------------

Basic functionalities/features:

- The entire stage rotates
- camera angled for an isometric view
- ball's movement restricted only within a circle (to make the game play a bit more fun)
- jump physics written
- combo for jump + movements while in jump
- Procedurally generated ground. Everytime a new ground will be generated. Not of any use but to test my algorithm skills
------------------------------------------------------

To Do/ideas:

- make the procedurally generated ground act like a wave?
- experiment with polygons 
- try importing blender models
- try experimenting with shadows

------------------------------------------------------
A very simple procedural ground generation algorithm:


![Alt text](/procedural_ground_generation.png?raw=true "My procedural ground generation algo")
