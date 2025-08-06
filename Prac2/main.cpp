#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"

#include "seats.cpp"

using namespace glm;
using namespace std;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    //ensure opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1000, 1000, "u23562732", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
}

int main()
{
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        cout << e << endl;
        throw;
    }

    //Add code here
    GLuint pID = LoadShaders("v.glsl", "frag.glsl");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.05, 0.2, 0, 1);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //coordinates for 2 triangles ->each point (x,y,z) ->2D so z=0
    GLfloat floor[] = {
        -0.9, -0.9, 0,   //x,y,z
        0.9, -0.9, 0,
        -0.9, 0.9, 0,

        0.9, -0.9, 0,
        0.9, 0.9, 0,
        -0.9, 0.9, 0
    };


    GLfloat wall[] = {
        -0.95, -0.95, 0,   //x,y,z
        0.95, -0.95, 0,
        -0.95, 0.95, 0,
        
        0.95, -0.95, 0,
        0.95,  0.95, 0,
        -0.95,  0.95, 0
    };

    GLfloat door1[] = {
        -0.9, 0.4, 0,   //x,y,z
        -0.875, 0.4, 0,
        -0.9, 0.8, 0,
        //-0.875, 0.8, 0
        -0.875, 0.4, 0,
        -0.875, 0.8, 0,
        -0.9,  0.8, 0
    };
    GLfloat door2[] = {
        -0.9, -0.4, 0,   //x,y,z
        -0.875, -0.4, 0,
        -0.9, -0.8, 0,
        //-0.875, -0.8, 0
        -0.875, -0.4, 0,
        -0.875, -0.8, 0,
        -0.9,  -0.8, 0
    };

    GLfloat cafe[] = {
        0.8, -0.5, 0,   //x,y,z
        0.65, -0.5, 0,
        0.8, 0.6, 0,

        0.65, -0.5, 0,
        0.65, 0.6, 0,
        0.8, 0.6, 0
    };

    GLfloat window1[] = {
        -0.5, 0.8, 0,   //x,y,z
        -0.35, 0.8, 0,
        -0.5, 0.9, 0,

        -0.35, 0.8, 0,
        -0.35, 0.9, 0,
        -0.5, 0.9, 0
    };
    GLfloat window2[] = {
        -0.2, 0.8, 0,   //x,y,z
        -0.05, 0.8, 0,
        -0.2, 0.9, 0,

        -0.05, 0.8, 0,
        -0.05, 0.9, 0,
        -0.2, 0.9, 0
    };
    GLfloat window3[] = {
        0.1, 0.8, 0,   //x,y,z
        0.25, 0.8, 0,
        0.1, 0.9, 0,

        0.25, 0.8, 0,
        0.25, 0.9, 0,
        0.1, 0.9, 0
    };
    GLfloat window4[] = {
        0.4, 0.8, 0,   //x,y,z
        0.55, 0.8, 0,
        0.4, 0.9, 0,

        0.55, 0.8, 0,
        0.55, 0.9, 0,
        0.4, 0.9, 0
    };
    triangleSeat triangleSeat1;//purple
    triangleSeat triangleSeat2;
    triangleSeat triangleSeat3;
    squareSeat squareSeat1;//blue
    squareSeat squareSeat3;
    squareSeat squareSeat2;
    squareSeat squareSeat4;
    squareSeat squareSeat5;
    circleSeat circleSeat1;//red
    circleSeat redSeat1;
    circleSeat redSeat2;
    highCircleSeat yellowSeat1;
    highCircleSeat yellowSeat2;
    highCircleSeat yellowSeat3;
    higherCircleSeat circleSeat3;

    
        for (int i=0;i<34;i++)
        {
            squareSeat1.move("up");
            squareSeat2.move("up");
            squareSeat3.move("up");
            squareSeat4.move("up");
            squareSeat5.move("up");
        }
        for (int i=0;i<26;i++)
        {
            squareSeat1.move("left");
            circleSeat1.move("up");
            redSeat1.move("down");
        }
        for (int i=0;i<11;i++)
        {
            triangleSeat2.move("up");triangleSeat2.move("up");
            triangleSeat3.move("down");
            triangleSeat3.move("down");
            triangleSeat2.move("left");
            squareSeat2.move("left");
            squareSeat3.move("right");
            squareSeat3.move("right");
            squareSeat3.move("right");
            redSeat1.move("right");
            circleSeat1.move("right");
        }
        for (int i=0;i<4;i++)
        {
            triangleSeat2.move("right");
            squareSeat4.move("right");
            redSeat2.move("right");
        }

        for (int i=0;i<19;i++)
        {
            squareSeat5.move("right");
        }
        yellowSeat1.scaleDown(); yellowSeat1.scaleDown(); 
        yellowSeat2.scaleDown();yellowSeat2.scaleDown();
        yellowSeat3.scaleDown();yellowSeat3.scaleDown();
        
        for (int i=0; i<28; i++)
        {
            yellowSeat1.move("left");
            yellowSeat2.move("left");
            yellowSeat3.move("left");
        }
        yellowSeat2.move("right");
        yellowSeat2.move("right");
        for (int i=0; i<10; i++)
        {
            yellowSeat1.move("up");
            yellowSeat3.move("down");
        }
        float e=0.5;
        for (int i=0;i<180;i+=3)
        {
            circleSeat3.vertices[i] -= e;
            circleSeat3.vertices[i+1] -= e;
        }
    trianglePlant trianglePlant1;//green
    trianglePlant trianglePlant2;
    trianglePlant trianglePlant3;
    circleTable circleTable1;//pink
    circleTable circleTable2;
    circleTable circleTable3;
    Square table1;//teal
    Square table2;
    Square table3;
    Rectangle counter;
    Square microwave;//grey
    bin bin1; 
    bin bin2;

    counter.scaleUp();counter.scaleUp();counter.scaleUp();
    table1.scaleUp(); 
    table2.scaleUp();
    table3.scaleUp();
    microwave.scaleDown();microwave.scaleDown();microwave.scaleDown();microwave.scaleDown();microwave.scaleDown();
        for (int i=0; i<35; i++)
        {
            counter.move("down");
            trianglePlant1.move("down");
            circleTable1.move("left");
            circleTable2.move("left");
            circleTable3.move("left");
            bin2.move("left");
            bin1.move("down");
        }
        for (int i=0; i<15;i++)
        {
            trianglePlant2.move("left");
            trianglePlant2.move("up");
            trianglePlant3.move("left");
            trianglePlant3.move("down");
            circleTable1.move("up");
            circleTable2.move("down");
            table3.move("right");
            counter.move("down");
            microwave.move("down");
            microwave.move("down");
        }
        for (int i=0;i <31;i++)
        {
            trianglePlant1.rotateRight();
        }
        for (int i=0;i<10;i++)
        {
            bin2.move("left");
            bin2.move("down");
            trianglePlant1.move("right");
            trianglePlant1.move("down");
            microwave.move("down");
        }
        trianglePlant1.move("right");trianglePlant1.move("right");
        counter.move("up");
        microwave.move("down");microwave.move("down");
        microwave.move("left");microwave.move("left");microwave.move("left");
        for (int i=0; i<25;i++)
        {
            counter.move("right");
            microwave.move("right");
            table1.move("up");
            table2.move("down");
        }
    std::string seatType="triangle";
    string decorType="bin";
    

    GLfloat vertices[(9*18)+(27*9)+(3*30)+(3*24)+(3*150)+180+(2*153)];

    for (int i=0;i<18;i++)
    {
        vertices[i] = wall[i];
        vertices[i+18] = floor[i];
        vertices[i+36] = door1[i];
        vertices[i+54] = door2[i];
        vertices[i+72] = cafe[i];
        vertices[i+90] = window1[i];
        vertices[i+108] = window2[i];
        vertices[i+126] = window3[i];
        vertices[i+144] = window4[i];
    }
    for (int i=0;i<9;i++)
    {
        vertices[i+162] = triangleSeat1.vertex[i];
        vertices[i+171] = squareSeat1.tri1[i];
        vertices[i+180] = squareSeat1.tri2[i];
        vertices[i+189] = trianglePlant1.vertex[i];

        vertices[i+630] = squareSeat2.tri1[i];
        vertices[i+630+9] = squareSeat2.tri2[i];
        vertices[i+630+18] = squareSeat3.tri1[i];
        vertices[i+630+27] = squareSeat3.tri2[i];
        vertices[i+630+36] = squareSeat4.tri1[i];
        vertices[i+630+45] = squareSeat4.tri2[i];
        vertices[i+630+54] = squareSeat5.tri1[i];
        vertices[i+630+63] = squareSeat5.tri2[i];

        vertices[i+1002] = table1.tri1[i];
        vertices[i+1002+9] = table1.tri2[i];
        vertices[i+1002+18] = table2.tri1[i];
        vertices[i+1002+27] = table2.tri2[i];
        vertices[i+1002+36] = table3.tri1[i];
        vertices[i+1002+45] = table3.tri2[i];

        vertices[i+1116] = counter.tri1[i];
        vertices[i+1116+9] = counter.tri2[i];
        vertices[i+1116+18] = microwave.tri1[i];
        vertices[i+1116+27] = microwave.tri2[i];
        vertices[i+1116+36] = trianglePlant2.vertex[i];
        vertices[i+1116+45] = trianglePlant3.vertex[i];
        vertices[i+1116+54] = triangleSeat2.vertex[i];
        vertices[i+1116+63] = triangleSeat3.vertex[i];
    }
    for (int i=0;i<30;i++)
    {
        vertices[i+198] = circleSeat1.vertices[i];

        vertices[i+1056] = redSeat1.vertices[i];
        vertices[i+1056+30] = redSeat2.vertices[i];
    }
    for (int i=0;i<24;i++)
    {
        vertices[i+228] = circleTable1.vertices[i];
        vertices[i+582] = circleTable2.vertices[i];
        vertices[i+582+24] = circleTable3.vertices[i];
    }
    for (int i=0;i<150;i++)
    {
        vertices[i+252] = yellowSeat1.vertices[i];
        vertices[i+702] = yellowSeat2.vertices[i];
        vertices[i+702+150] = yellowSeat3.vertices[i];
    }
    for (int i=0;i<180;i++)
    {
        vertices[i+402] = circleSeat3.vertices[i];
    }
    for (int i=0;i<153;i++)
    {
        vertices[i+1188] = bin1.vertices[i];
        vertices[i+1188+153] = bin2.vertices[i];
    }


    GLuint vertexBuff;
    glGenBuffers(1, &vertexBuff);

    GLfloat colours[] = {
        //wall colours ->white
        1, 1, 1,
        1, 1, 1, 
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        //floor colours -> dark grey
        0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3,
        //door1 colours -> light grey
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        //door2 colours
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        0.8, 0.8, 0.8,
        //cafe colours -> black
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            //window colours -> white
            1, 1, 1,
            1, 1, 1, 
            1, 1, 1,
            1, 1, 1,
            1, 1, 1,
            1, 1, 1,
        //window colours
        1, 1, 1,
        1, 1, 1, 
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
         //window colours
       1, 1, 1,
       1, 1, 1, 
       1, 1, 1,
       1, 1, 1,
       1, 1, 1,
       1, 1, 1,
         //window colours
         1, 1, 1,
         1, 1, 1, 
         1, 1, 1,
         1, 1, 1,
         1, 1, 1,
         1, 1, 1,
         //triangleSeat1 colours -> purple
        0.5, 0, 1,
        0.5, 0, 1, 
        0.5, 0, 1,
        //square Seat1 colours -> blue
        0, 0, 1,
        0, 0, 1, 
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,  
        0, 0, 1,
        //trianglePlant colours -> green
        0, 1, 0,
        0, 1, 0, 
        0, 1, 0,
        //circleSeat1 Colours -> red
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        //circleTable1 colours -> pink
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        //circleSeat2 Colours ->yellow
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,
        //circleSeat3 Colours ->orange
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        1,0.5,0, 1,0.5,0, 1,0.5,0, 1,0.5,0, 
        //circleTable2 colours -> pink
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        //circleTable3 colours -> pink
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,0,1,
        //square Seat2 colours -> blue
        0, 0, 1,
        0, 0, 1, 
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,  
        0, 0, 1,
        //square Seat3 colours -> blue
        0, 0, 1,
        0, 0, 1, 
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,  
        0, 0, 1,
        //square Seat4 colours -> blue
        0, 0, 1,
        0, 0, 1, 
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,  
        0, 0, 1,
        //square Seat5 colours -> blue
        0, 0, 1,
        0, 0, 1, 
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,  
        0, 0, 1,
        //yellowSeat2 Colours ->yellow
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,
        //yellowSeat3 Colours ->yellow
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,  1,1,0,
        1,1,0,  1,1,0,
        //square table1 colours -> teal
        0, 1, 1,
        0, 1, 1, 
        0, 1, 1,
        0, 1, 1,
        0, 1, 1,  
        0, 1, 1,
        //square table2 colours -> teal
        0, 1, 1,
        0, 1, 1, 
        0, 1, 1,
        0, 1, 1,
        0, 1, 1,  
        0, 1, 1,
        //square table3 colours -> teal
        0, 1, 1,
        0, 1, 1, 
        0, 1, 1,
        0, 1, 1,
        0, 1, 1,  
        0, 1, 1,
        //circleSeat2 Colours -> red
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        //circleSeat2 Colours -> red
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        //counter colours -> black
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        //microwave colours -> dark grey
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        //trianglePlant2 colours -> green
        0, 1, 0,
        0, 1, 0, 
        0, 1, 0,
        //trianglePlant3 colours -> green
        0, 1, 0,
        0, 1, 0, 
        0, 1, 0,
        //triangleSeat2 colours -> purple
        0.5, 0, 1,
        0.5, 0, 1, 
        0.5, 0, 1,
        //triangleSeat3 colours -> purple
        0.5, 0, 1,
        0.5, 0, 1, 
        0.5, 0, 1,
        //bin1 colours -> dark grey
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1, 
        //bin2 colours -> dark grey
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,
        0.1,0.1,0.1,    0.1,0.1,0.1,    0.1,0.1,0.1,     
    };
    int seatColour=108+54;
    int decorColour=135+54;
    int squareP = 18;
    int triangleP = 9;
    int circleP = 30;
    GLuint colourBuff;
    glGenBuffers(1, &colourBuff);
    float enterKey = 0;
    /*glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);*/
    bool wireframe=false;
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(pID);

        glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
                glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        if (glfwGetKey(window,GLFW_KEY_ENTER)==GLFW_PRESS)
        {
            //std::this_thread::sleep_for(std::chrono::nanoseconds(100));
            float currT = glfwGetTime();
            if (currT-enterKey > 0.2)
            {
                if (wireframe==true)
                {
                    wireframe=false;
                    enterKey = currT;
                    //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
                }else{
                    wireframe=true;
                    enterKey = currT;
                    //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
                }
            }
        }

        if (wireframe==false)
            {
                //glDrawArrays(GL_SHAPE, indexOfFirstVertexInVertexBuff, Number of vertices)
                glDrawArrays(GL_TRIANGLES, 0, 66);
                glDrawArrays(GL_TRIANGLE_FAN, 66, 10); //circleSeat1 ->red
                glDrawArrays(GL_TRIANGLE_FAN, 76, 8); //circleTable1 ->pink
                glDrawArrays(GL_TRIANGLE_FAN, 84, 50); //circleSeat2 ->yellow circle
                glDrawArrays(GL_TRIANGLE_FAN, 134, 60); //circleSeat3 ->orange
                glDrawArrays(GL_TRIANGLE_FAN, 194, 8); //circleTable2 ->pink
                glDrawArrays(GL_TRIANGLE_FAN, 202, 8);//circleTable3 ->pink
                glDrawArrays(GL_TRIANGLES, 210, 24);
                glDrawArrays(GL_TRIANGLE_FAN, 234, 50); //yellowSeat2 ->yellow circle
                glDrawArrays(GL_TRIANGLE_FAN, 284, 50);//yellowSeat3 ->yellow circle
                glDrawArrays(GL_TRIANGLES, 334, 18);
                glDrawArrays(GL_TRIANGLE_FAN, 352, 10); //circleSeat2 ->red
                glDrawArrays(GL_TRIANGLE_FAN, 362, 10); //circleSeat3 ->red
                glDrawArrays(GL_TRIANGLES, 372, 24);
                glDrawArrays(GL_TRIANGLE_FAN, 396, 51); //bin1 ->grey circle
                glDrawArrays(GL_TRIANGLE_FAN, 447, 51); //bin2 ->grey circle
            }else{
                glDrawArrays(GL_LINES, 0,54);   //wall,floor,cafe,doors,windows
                glDrawArrays(GL_LINE_LOOP, 0,6); //wall
                glDrawArrays(GL_LINE_LOOP, 6,6); //floor
                glDrawArrays(GL_LINE_LOOP, 12,6); //cafe
                glDrawArrays(GL_LINE_LOOP, 18,6);//door1
                glDrawArrays(GL_LINE_LOOP, 24,6);//door2
                glDrawArrays(GL_LINE_LOOP, 30,6);//windows
                glDrawArrays(GL_LINE_LOOP, 36,6);
                glDrawArrays(GL_LINE_LOOP, 42,6);
                glDrawArrays(GL_LINE_LOOP, 48,6);
                glDrawArrays(GL_LINE_LOOP, 54,3);//purple triangle
                glDrawArrays(GL_LINE_LOOP, 57,6);//blue square1
                glDrawArrays(GL_LINE_LOOP, 63,3);//green triangle1
                glDrawArrays(GL_LINE_LOOP, 76,8);//pink circle1
                for (int i=1; i<8;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 76,i);
                }
                glDrawArrays(GL_LINE_LOOP, 84,50);//yellow circle1
                for (int i=1; i<50;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 84,i);
                }
                glDrawArrays(GL_LINE_LOOP, 134,60);//orange circle1
                for (int i=1; i<60;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 134,i);
                }
                glDrawArrays(GL_LINES, 67,8);   //red circle1
                glDrawArrays(GL_LINES, 64,148);   
                for (int i=1; i<10;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 66,i);
                }
                glDrawArrays(GL_LINES, 195,6); //pink circle2
                glDrawArrays(GL_LINES, 203,6); //pink circle3
                for (int i=1; i<8;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 194,i);
                    glDrawArrays(GL_LINE_LOOP, 202,i);
                }
                glDrawArrays(GL_LINE_LOOP, 210,6);//blue square2
                glDrawArrays(GL_LINE_LOOP, 216,6);//blue square3
                glDrawArrays(GL_LINE_LOOP, 222,6);//blue square4
                glDrawArrays(GL_LINE_LOOP, 228,6);//blue square5
                glDrawArrays(GL_LINES, 234,100); //yellow circle2,3
                glDrawArrays(GL_LINES, 235,48); //yellow circle2
                glDrawArrays(GL_LINES, 285,48); //yellow circle3
                for (int i=1; i<50;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 234,i);
                    glDrawArrays(GL_LINE_LOOP, 284,i);
                }
                glDrawArrays(GL_LINE_LOOP, 334,6); //teal square1
                glDrawArrays(GL_LINES, 334,8);
                glDrawArrays(GL_LINES, 338,4);//teal square2
                glDrawArrays(GL_LINE_LOOP, 340,6); 
                glDrawArrays(GL_LINES, 346,2);//teal square3
                glDrawArrays(GL_LINE_LOOP, 346,6); 

                glDrawArrays(GL_LINES, 352,20);  //red circle2,3
                glDrawArrays(GL_LINES, 353,8);
                glDrawArrays(GL_LINES, 363,8);
                for (int i=1; i<10;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 352,i);
                    glDrawArrays(GL_LINE_LOOP, 362,i);
                }

                glDrawArrays(GL_LINES, 372,4);//black counter
                glDrawArrays(GL_LINE_LOOP, 372,6); 
                glDrawArrays(GL_LINES, 378,4);//microwave
                glDrawArrays(GL_LINE_LOOP, 378,6); 

                glDrawArrays(GL_LINES, 384,2);//green triangle2
                glDrawArrays(GL_LINE_LOOP, 384,3); 
                glDrawArrays(GL_LINES, 387,2);//green triangle3
                glDrawArrays(GL_LINE_LOOP, 387,3); 

                //glDrawArrays(GL_LINES, 390,6);
                glDrawArrays(GL_LINE_LOOP, 390,3); //purple triangle2
                glDrawArrays(GL_LINE_LOOP, 393,3); //purple triangle3
                glDrawArrays(GL_LINES, 396,51);//grey circle1
                glDrawArrays(GL_LINES, 397,50);
                glDrawArrays(GL_LINES, 447,51);//grey circle2
                glDrawArrays(GL_LINES, 448,50);
                for (int i=1; i<51;i++)
                {
                    glDrawArrays(GL_LINE_LOOP, 396,i);
                    glDrawArrays(GL_LINE_LOOP, 447,i);
                }
                /*glDrawArrays(GL_LINES, 0,54);   //wall,floor,cafe,doors,windows
                glDrawArrays(GL_LINES, 1,4);   //wall
                glDrawArrays(GL_LINES, 6,2);   //floor

                glDrawArrays(GL_LINES, 54,2);   //purple triangle
                glDrawArrays(GL_LINES, 55,2);   //blue square1
                glDrawArrays(GL_LINES, 57,2);
                glDrawArrays(GL_LINES, 58,4);
                glDrawArrays(GL_LINES, 63,2);   //green triangle1
                glDrawArrays(GL_LINES, 64,148);   //red circle1
                glDrawArrays(GL_LINES, 67,8);   //red circle1
                glDrawArrays(GL_LINES, 77,6);   //pink circle
                glDrawArrays(GL_LINES, 85,48); //yellow circle
                glDrawArrays(GL_LINES, 135,59); //orange circle
                glDrawArrays(GL_LINES, 195,6); //pink circle2
                glDrawArrays(GL_LINES, 203,6); //pink circle3

                glDrawArrays(GL_LINES, 216,2); //blue square3
                glDrawArrays(GL_LINES, 217,4); //blue square3
                glDrawArrays(GL_LINES, 220,4); //blue square4
                glDrawArrays(GL_LINES, 223,4); //blue square4
                glDrawArrays(GL_LINES, 228,2); //blue square5
                glDrawArrays(GL_LINES, 229,4); //blue square5

                glDrawArrays(GL_LINES, 234,100); //yellow circle2,3
                glDrawArrays(GL_LINES, 235,48); //yellow circle2
                glDrawArrays(GL_LINES, 285,48); //yellow circle3

                glDrawArrays(GL_LINES, 335,4); //teal square1
                glDrawArrays(GL_LINES, 334,2);
                glDrawArrays(GL_LINES, 338,4);//teal square2
                glDrawArrays(GL_LINES, 341,4);
                glDrawArrays(GL_LINES, 346,2);//teal square3
                glDrawArrays(GL_LINES, 347,4);*/
            }

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glfwSwapBuffers(window);
            glfwPollEvents();

        if (glfwGetKey(window,GLFW_KEY_0)==GLFW_PRESS)
        {
            //Deselect objects
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+decorColour] = trianglePlant1.col[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
            }
            if (bin1.selected==true)
                {
                    bin1.deselect();
                    for (int i=0;i<153;i++)
                    {
                        colours[i+1188] = bin1.col[i];
                    }

                }
        }
        if (glfwGetKey(window,GLFW_KEY_1)==GLFW_PRESS)
        {
            //Select seating object
            //if (seatType=="square" || seatType)
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
                trianglePlant1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+decorColour] = trianglePlant1.col[i];
                }
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
                if (bin1.selected==true)
                {
                    bin1.deselect();
                    for (int i=0;i<153;i++)
                    {
                        colours[i+1188] = bin1.col[i];
                    }

                }
            }
            seatType="triangle";
            triangleSeat1.select();
            for (int i=0;i<9;i++)
            {
                colours[i+seatColour] = triangleSeat1.col[i];
            }
        }
        if (glfwGetKey(window,GLFW_KEY_2)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+decorColour] = trianglePlant1.col[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.deselect();
                for (int i=0;i<153;i++)
                {
                    colours[i+1188] = bin1.col[i];
                }

            }
            //if (seatType=="triangle")
            {
                triangleSeat1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }

                seatType="square";
                squareSeat1.select();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            }/*else if (seatType=="square")
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }

                seatType="triangle";
                triangleSeat1.select();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }
            }*/
        }

        if (glfwGetKey(window,GLFW_KEY_3)==GLFW_PRESS)
        {
            //Select decor object
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            }
        
            if (circleTable1.selected==true)
            {
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
            }
            decorType="bin";
            bin1.select();
            for (int i=0;i<153;i++)
            {
                colours[i+1188] = bin1.col[i];
            }
        }
        if (glfwGetKey(window,GLFW_KEY_4)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+seatColour] = triangleSeat1.col[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.deselect();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.deselect();
                for (int i=0;i<9;i++)
                {
                    colours[i+decorColour] = trianglePlant1.col[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.deselect();
                for (int i=0;i<153;i++)
                {
                    colours[i+1188] = bin1.col[i];
                }

            }
            //if (decorType=="bin")
            {
                bin1.deselect();
                for (int i=0;i<153;i++)
                {
                    colours[i+1188] = bin1.col[i];
                }

                decorType="table";
                circleTable1.select();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
            }/*else if (decorType=="table")
            {
                circleTable1.deselect();
                for (int i=0;i<24;i++)
                {
                    colours[i+decorColour+9+30] = circleTable1.col[i];
                }
                decorType="bin";
                bin1.select();
                for (int i=0;i<153;i++)
                {
                    colours[i+1188] = bin1.col[i];
                }
            }*/
            
        }

        if (glfwGetKey(window,GLFW_KEY_5)==GLFW_PRESS)
        {
            triangleSeat1.select();
            for (int i=0;i<9;i++)
            {
                colours[i+seatColour] = triangleSeat1.col[i];
            }
            trianglePlant1.select();
                for (int i=0;i<9;i++)
                {
                    colours[i+decorColour] = trianglePlant1.col[i];
                }
            circleTable1.select();
            for (int i=0;i<24;i++)
            {
                colours[i+decorColour+9+30] = circleTable1.col[i];
            }
            squareSeat1.select();
                for (int i=0;i<18;i++)
                {
                    colours[i+seatColour+9] = squareSeat1.col[i];
                }
            bin1.select();
            for (int i=0;i<153;i++)
            {
                colours[i+1188] = bin1.col[i];
            }
        }
        //MOVE
        if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.move("up");
                for (int i=0;i<9;i++)
                {
                    vertices[i+162] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.move("up");
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.move("up");
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.move("up");
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.move("up");
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.move("down");
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.move("down");
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.move("down");
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.move("down");
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.move("down");
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.move("left");
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.move("left");
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.move("left");
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.move("left");
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.move("left");
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.move("right");
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.move("right");
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.move("right");
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.move("right");
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.move("right");
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        //SCALE
        if ((glfwGetKey(window,GLFW_KEY_EQUAL)==GLFW_PRESS && glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS) || glfwGetKey(window,GLFW_KEY_KP_ADD)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.scaleUp();
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.scaleUp();
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.scaleUp();
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.scaleUp();
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.scaleUp();
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_KP_SUBTRACT)==GLFW_PRESS || glfwGetKey(window,GLFW_KEY_MINUS)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.scaleDown();
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.scaleDown();
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.scaleDown();
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.scaleDown();
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.scaleDown();
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_E)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.rotateRight();
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.rotateRight();
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.rotateRight();
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.rotateRight();
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.rotateRight();
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }
        if (glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS)
        {
            if (triangleSeat1.selected==true)
            {
                triangleSeat1.rotateLeft();
                for (int i=0;i<9;i++)
                {
                    vertices[i+108+54] = triangleSeat1.vertex[i];
                }
            }
            if (trianglePlant1.selected==true)
            {
                trianglePlant1.rotateLeft();
                for (int i=0;i<9;i++)
                {
                    vertices[i+135+54] = trianglePlant1.vertex[i];
                }
            }
            if (squareSeat1.selected==true)
            {
                squareSeat1.rotateLeft();
                for (int i=0;i<9;i++)
                {
                    vertices[i+117+54] = squareSeat1.tri1[i];
                    vertices[i+126+54] = squareSeat1.tri2[i];
                }
            }
            if (circleTable1.selected==true)
            {
                circleTable1.rotateLeft();
                for (int i=0;i<24;i++)
                {
                    vertices[i+135+30+9+54] = circleTable1.vertices[i];
                }
            }
            if (bin1.selected==true)
            {
                bin1.rotateLeft();
                for (int i=0;i<153;i++)
                {
                    vertices[i+1188] = bin1.vertices[i];
                }
            }
        }

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

