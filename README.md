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
- ball now looks like a wire ball just for the fun
------------------------------------------------------

To Do/ideas:

- make the procedurally generated ground act like a wave? -- X (looks like glitch rather than waves)
- experiment with polygons and wires -- X
- try importing blender models
- try experimenting with shadows

------------------------------------------------------
A very simple procedural ground generation algorithm:


![Alt text](/procedural_ground_generation.png?raw=true "My procedural ground generation algo")
------------------------------------------------------

Some important concepts to remember:

-Bitmasking
you can allow some value to be modified by ANDing, ORing or XORing it with a bit mask

So, ANDing gets the intersection between value and mask
ORing, gets union of value and mask
XORing toggles the values in the value

So in the glutInitDisplayMode(A|B|C) sets A,B and C as the bitmasks and initializes the display mode by
kind of setting some specifc options true!
------------------------------------------------------

-Double Buffering
in the glutInitDisplayMode() a bitmask GLUT_DOUBLE enables double buffering
Okay the need for this one is very clever. 
in single buffering, often it can happen that our image  to be shown on the screen is not
in sync with the screens refresh rate.
Due to this, the screen might refresh after rendering only a part of the image.

To overcome this, we prepare another decoy buffer. when we send a frame to the graphic card.
We draw this frame 1 and also store it into the second buffer. While drawing the second frame, we show image from the buffer (i.e. first frame) and swap the buffer once the second image is completely drawn.

This creates an effect of contant buffering
-----------------------------------------------------

-Depth Buffer
glEnable(GL_DEPTH_TEST);
this function allows the application to have a proper depth wise rendering.
This makes the animation look much more believable
-----------------------------------------------------

-GL Line primitives
so apparently in function glBegin(), the argument passed defines the primitives that are used for drawing

GL_POINT: vertex n map to point n
GL_LINES: vertex 2n-1, 2n define the line n

similarly we have GL_TRIANGLE_FAN, GL_QUADS etc

GL_POLYGON can be used to directly define this polygon

Here are my tests for polygon render:

![Alt text](/polygon_render.png?raw=true "strangeness")
