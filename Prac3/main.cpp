#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "cuboid.cpp"
#include "cone.cpp"
#include "cylinder.cpp"
#include "triangularPrism.cpp"
#include "aircraft.cpp"
#include "body.cpp"

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
    glClearColor(0.2, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_NEAREST);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    wing planeWing;
    planeWing.move("left");
    body planeBody;


    GLfloat vertices[(planeWing.vSize) + planeBody.vSize];
    for (int i=0;i<planeWing.vSize;i++)
    {
        vertices[i] = planeWing.vertices[i];
    }
    int index = planeWing.vSize;
    for (int i=0;i<planeBody.vSize;i++)
    {
        vertices[i+index] = planeBody.vertices[i];

    }
    index += planeBody.vSize;

    GLuint vertexBuff;
    glGenBuffers(1, &vertexBuff);

    GLfloat colours[(planeWing.cSize) + (planeBody.cSize)];
    for (int i=0;i<(planeWing.cSize);i++)
    {
        //wing colours
        colours[i] = planeWing.colours[i];
    }
    index = planeWing.cSize;
    for (int i=0;i<planeBody.cSize;i++)
    {
        colours[i+index] = planeBody.colours[i];
    }

    GLuint colourBuff;
    glGenBuffers(1, &colourBuff);
    bool wireframe=false;
    float enterKey = 0;
    float changeSpeed=0;
    float lastTime=0;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(pID);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
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
            //plane
            glDrawArrays(GL_TRIANGLES,0,36); //wing
            glDrawArrays(GL_TRIANGLE_FAN,36,10);
            glDrawArrays(GL_TRIANGLE_FAN,46,10);
            glDrawArrays(GL_TRIANGLES,56,48);
            glDrawArrays(GL_TRIANGLE_FAN,104,10);
            glDrawArrays(GL_TRIANGLE_FAN,114,10);
            glDrawArrays(GL_TRIANGLES,124,48);

            glDrawArrays(GL_TRIANGLE_FAN,172,10); //tail
            glDrawArrays(GL_TRIANGLES,182,169); 
            glDrawArrays(GL_TRIANGLE_FAN,351,10); //wheel
            glDrawArrays(GL_TRIANGLE_FAN,361,10); //wheel
            glDrawArrays(GL_TRIANGLES,370,372); 
            glDrawArrays(GL_TRIANGLE_FAN,742,10); //wheel
            glDrawArrays(GL_TRIANGLE_FAN,752,10); //wheel
            glDrawArrays(GL_TRIANGLES,762,48); 
            glDrawArrays(GL_TRIANGLE_FAN,810,10); //wheel
            glDrawArrays(GL_TRIANGLE_FAN,820,10); //wheel
            glDrawArrays(GL_TRIANGLES,830,288); 
            glDrawArrays(GL_TRIANGLES,1118,144); 
        }else{
            //wing
            glDrawArrays(GL_LINES,0,418); 
            glDrawArrays(GL_LINE_LOOP,30,6); //bigWing ->108/3 = 36 (cuboid)
            glDrawArrays(GL_LINE_LOOP,24,6);
            glDrawArrays(GL_LINE_LOOP,36,10); //sidewing ->204/3 = 68 (cylinder)
            for (int i=0;i<10;i++)
            {
                glDrawArrays(GL_LINE_LOOP,36,i);
                glDrawArrays(GL_LINE_LOOP,46,i);
                glDrawArrays(GL_LINE_LOOP,104,i);
                glDrawArrays(GL_LINE_LOOP,114,i);
                glDrawArrays(GL_LINE_LOOP,172,i); //cone base
                glDrawArrays(GL_LINE_LOOP,350,i); //tailWheel
                glDrawArrays(GL_LINE_LOOP,360,i); //tailWheel
                glDrawArrays(GL_LINE_LOOP,742,i); //fWheel
                glDrawArrays(GL_LINE_LOOP,752,i); 
                glDrawArrays(GL_LINE_LOOP,810,i); //bWheel
                glDrawArrays(GL_LINE_LOOP,820,i); 
            }
            for (int i=0;i<40;i++)
            {
                glDrawArrays(GL_LINE_LOOP,56+i,3);
                glDrawArrays(GL_LINE_LOOP,124+i,3);
                glDrawArrays(GL_LINE_LOOP,370+i,3); //tailWheel
                glDrawArrays(GL_LINE_LOOP,762+i,3); //fWheel
                glDrawArrays(GL_LINE_LOOP,830+i,3); //bWheel
            }
            //body
            //cone -> 120/3 = 40
            glDrawArrays(GL_LINE_LOOP,230,6); //tail1
            glDrawArrays(GL_LINE_LOOP,236,6); 
            glDrawArrays(GL_LINE_LOOP,272,6); //tail2
            glDrawArrays(GL_LINE_LOOP,266,6); 
            glDrawArrays(GL_LINE_LOOP,308,6); //tail3
            glDrawArrays(GL_LINE_LOOP,302,6); 
            glDrawArrays(GL_LINE_LOOP,344,6); //wheelLink
            glDrawArrays(GL_LINE_LOOP,338,6); 
            //triangularPrism -> 72/3 = 24
            for (int i=0;i<24;i+=3) //triangularPrisms
            {
                glDrawArrays(GL_LINE_LOOP,418+i,3); //tail2
                glDrawArrays(GL_LINE_LOOP,442+i,3); //tail3
                glDrawArrays(GL_LINE_LOOP,574+i,3); //windowL
                glDrawArrays(GL_LINE_LOOP,598+i,3); //windowR
                glDrawArrays(GL_LINE_LOOP,694+i,3); //wheelStruct
                glDrawArrays(GL_LINE_LOOP,718+i,3); //wheelStruct
            }
            for (int i=0;i<36;i+=3) //cuboids
            {
                glDrawArrays(GL_LINE_LOOP,466+i,3);
                glDrawArrays(GL_LINE_LOOP,502+i,3);
                glDrawArrays(GL_LINE_LOOP,538+i,3);
                glDrawArrays(GL_LINE_LOOP,622+i,3);
                glDrawArrays(GL_LINE_LOOP,658+i,3);
                glDrawArrays(GL_LINE_LOOP,878+i,3);
                glDrawArrays(GL_LINE_LOOP,914+i,3);
                glDrawArrays(GL_LINE_LOOP,950+i,3);
                glDrawArrays(GL_LINE_LOOP,986+i,3);
                glDrawArrays(GL_LINE_LOOP,1022+i,3);
                glDrawArrays(GL_LINE_LOOP,1058+i,3);

                glDrawArrays(GL_LINE_LOOP,1094+i,3);
                glDrawArrays(GL_LINE_LOOP,1130+i,3);
                glDrawArrays(GL_LINE_LOOP,1160+i,3);
                glDrawArrays(GL_LINE_LOOP,1196+i,3);
            }
            glDrawArrays(GL_LINES,742,68); 
            glDrawArrays(GL_LINES,810,68); 
        }

        if (planeBody.speed>0)
        {
            //float currT = glfwGetTime();
            
            float timeInterval = 0.2/planeBody.speed;
            if (lastTime > timeInterval)
            {
                float otherMid[3];
                planeBody.nose.calcMidPoint(otherMid);
                planeBody.propeller1.rotate(otherMid);
                planeBody.updateVertices();
                int index = planeWing.vSize;
                for (int i=0;i<planeBody.vSize;i++)
                {
                    vertices[i+index] = planeBody.vertices[i];
                }
                //lastTime=currT;
                lastTime=0;
            }else{
                lastTime+=0.1;
            }
        }

        glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glfwSwapBuffers(window);
            glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //anti-clockwise X
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
            //mid[0] = 0;mid[1] =0;mid[2] =0;
            planeBody.rotateLeftX(mid);
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
            planeWing.rotateLeftX(mid);
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //clockwise X
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
            //mid[0] = 0;mid[1] =0;mid[2] =0;
            planeWing.rotateRightX(mid);
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

                planeBody.rotateRightX(mid);
                int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }

        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//anti-clockwise Y
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
           // mid[0] = 0;mid[1] =0;mid[2] =0;
            planeWing.rotateLeftY(mid);
           for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

            planeBody.rotateLeftY(mid);
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //clockwise Y
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
            //mid[0] = 0;mid[1] =0;mid[2] =0;
            planeWing.rotateRightY(mid);
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

                planeBody.rotateRightY(mid);
                int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }

        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)//anti-clockwise Z
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
            //mid[0] = 0;mid[1] =0;mid[2] =0;
            planeWing.rotateLeftZ(mid);
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

                planeBody.rotateLeftZ(mid);
                int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }

        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) //clockwise Z
        {
            float mid[3];
            planeBody.calcPlaneMidPoint(mid);
            //mid[0] = 0;mid[1] =0;mid[2] =0;
            planeWing.rotateRightZ(mid);
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

                planeBody.rotateRightZ(mid);
                int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }

        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) 
        {
            planeWing.move("up");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }

            planeBody.move("up");
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }

        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) 
        {
            planeWing.move("down");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
            planeBody.move("down");
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
        {
            planeWing.move("right");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
            planeBody.move("right");
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) 
        {
            planeWing.move("left");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
            planeBody.move("left");
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) 
        {
            planeWing.move("incZ");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
            
            planeBody.move("incZ");
            planeBody.updateVertices();
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) 
        {
            planeWing.move("decZ");
            for (int i=0;i<(planeWing.vSize);i++)
            {
                vertices[i] = planeWing.vertices[i];
            }
            planeBody.move("decZ");
            planeBody.updateVertices();
            int index = planeWing.vSize;
            for (int i=0;i<planeBody.vSize;i++)
            {
                vertices[i+index] = planeBody.vertices[i];
            }
        }

        if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) 
        {
            float currT = glfwGetTime();
            if (currT-changeSpeed > 0.2)
            {
                planeBody.increaseSpeed();
                int index = planeWing.vSize;
                for (int i=0;i<planeBody.vSize;i++)
                {
                    vertices[i+index] = planeBody.vertices[i];
                }
                changeSpeed=currT;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) 
        {
            float currT = glfwGetTime();
            if (currT-changeSpeed > 0.2)
            {
                planeBody.decreaseSpeed();
                int index = planeWing.vSize;
                for (int i=0;i<planeBody.vSize;i++)
                {
                    vertices[i+index] = planeBody.vertices[i];
                }
                changeSpeed=currT;
            }
        }
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
