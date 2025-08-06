#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono> 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"

#include "cuboid.cpp"

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
    window = glfwCreateWindow(1000, 1000, "Experiment", NULL, NULL);
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

int main(int argc, char *argv[])
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
    int numRectangles = 0;
    stringstream ss;
    ss << argc;
    ss >> numRectangles;
    cout << numRectangles;
    cout << argv[0] <<endl;

    GLuint pID = LoadShaders("v.glsl", "frag.glsl");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0, 0.7, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_NEAREST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    cuboid bottomSheet;
    bottomSheet.setColour("grey",1);
    bottomSheet.setHeight(0.015);
    bottomSheet.setWidth(0.8);
    bottomSheet.setLength(0.8);
    bottomSheet.move("down",0.355);
    cuboid backSheet1;
    backSheet1.setColour("red",1);
    backSheet1.setHeight(0.35);
    backSheet1.setWidth(0.001);
    backSheet1.setLength(0.4);
    backSheet1.move("left",0.395);
    backSheet1.move("up",0.175);
    backSheet1.move("incZ",0.21);
    cuboid backSheet2;
    backSheet2.setColour("red",1);
    backSheet2.setHeight(0.35);
    backSheet2.setWidth(0.001);
    backSheet2.setLength(0.4);
    backSheet2.move("left",0.395);
    backSheet2.move("up",0.175);
    backSheet2.move("decZ",0.19);
    cuboid backSheet3;
    backSheet3.setColour("red",1);
    backSheet3.setHeight(0.35);
    backSheet3.setWidth(0.001);
    backSheet3.setLength(0.4);
    backSheet3.move("left",0.395);
    backSheet3.move("down",0.175);
    backSheet3.move("incZ",0.21);
    cuboid backSheet4;
    backSheet4.setColour("red",1);
    backSheet4.setHeight(0.35);
    backSheet4.setWidth(0.001);
    backSheet4.setLength(0.4);
    backSheet4.move("left",0.395);
    backSheet4.move("down",0.175);
    backSheet4.move("decZ",0.19);
    cuboid glass;
    glass.setColour("green",1);
    glass.setHeight(0.7);
    glass.setWidth(0.1);
    glass.setLength(0.8);
    cuboid light;
    light.setColour("white",1);
    light.setHeight(0.05);
    light.setWidth(0.05);
    light.setLength(0.05);
    light.move("right",0.3);

    backSheet1.calNormal();
    light.pointLight(&backSheet1);
    backSheet2.calNormal();
    light.pointLight(&backSheet2);
    backSheet3.calNormal();
    light.pointLight(&backSheet3);
    backSheet4.calNormal();
    light.pointLight(&backSheet4);

    

    GLfloat vertices[bottomSheet.vSize*7];
    for (int i=0;i<bottomSheet.vSize;i++)
    {
        vertices[i] = bottomSheet.vertices[i];
        vertices[i+108] = backSheet1.vertices[i];
        vertices[i+216] = backSheet2.vertices[i];
        vertices[i+324] = backSheet3.vertices[i];
        vertices[i+432] = backSheet4.vertices[i];
        vertices[i+540] = light.vertices[i];
        vertices[i+648] = glass.vertices[i];
    }
    GLuint vertexBuff;
    glGenBuffers(1, &vertexBuff);

    GLfloat colours[bottomSheet.cSize*7];
    for (int i=0;i<bottomSheet.cSize;i++)
    {
        colours[i] = bottomSheet.colours[i];
        colours[i+144] = backSheet1.colours[i];
        colours[i+288] = backSheet2.colours[i];
        colours[i+432] = backSheet3.colours[i];
        colours[i+576] = backSheet4.colours[i];
        colours[i+720] = light.colours[i];
        colours[i+864] = glass.colours[i];
    }
    GLuint colourBuff;
    glGenBuffers(1, &colourBuff);

    int backSheetNum=0;
    int lightNum=8;
    int glassNum=3;
    float glassAlpha=1;
    float backSheetKey=0;
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
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glDrawArrays(GL_TRIANGLES,0,252);
        for (int i=0;i<bottomSheet.cSize;i+=4)
        {
            glass.colours[i] -= 0.5;glass.colours[i+1] -= 0.5;glass.colours[i+2] -= 0.5;
        }
        for (int i=0;i<bottomSheet.cSize;i++)
        {
            colours[i+864] = glass.colours[i];
        }
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glDrawArrays(GL_LINE_LOOP,216,2);
        glDrawArrays(GL_LINE_LOOP,220,2);
        glDrawArrays(GL_LINE_LOOP,222,2);
        glDrawArrays(GL_LINE_LOOP,226,2);
        glDrawArrays(GL_LINE_LOOP,228,2);
        glDrawArrays(GL_LINE_LOOP,232,2);
        glDrawArrays(GL_LINE_LOOP,234,2);
        glDrawArrays(GL_LINE_LOOP,236,2);
        glDrawArrays(GL_LINE_LOOP,238,2);
        glDrawArrays(GL_LINE_LOOP,240,2);
        glDrawArrays(GL_LINE_LOOP,244,2);
        glDrawArrays(GL_LINE_LOOP,246,2);
        glDrawArrays(GL_LINE_LOOP,250,2);
        glDrawArrays(GL_LINE_LOOP,231,2);
        glDrawArrays(GL_LINE_LOOP,228,3);
        for (int i=0;i<bottomSheet.cSize;i+=4)
        {
            glass.colours[i] += 0.5;glass.colours[i+1] += 0.5;glass.colours[i+2] += 0.5;
        }
        for (int i=0;i<bottomSheet.cSize;i++)
        {
            colours[i+864] = glass.colours[i];
        }
        glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glfwSwapBuffers(window);
            glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //anti-clockwise X
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateLeftX(mid);
                backSheet1.rotateLeftX(mid);
                backSheet2.rotateLeftX(mid);
                backSheet3.rotateLeftX(mid);
                backSheet4.rotateLeftX(mid);
                glass.rotateLeftX(mid);
                light.rotateLeftX(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //clockwise X
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateRightX(mid);
                backSheet1.rotateRightX(mid);
                backSheet2.rotateRightX(mid);
                backSheet3.rotateRightX(mid);
                backSheet4.rotateRightX(mid);
                glass.rotateRightX(mid);
                light.rotateRightX(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
    
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//anti-clockwise Y
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateLeftY(mid);
                backSheet1.rotateLeftY(mid);
                backSheet2.rotateLeftY(mid);
                backSheet3.rotateLeftY(mid);
                backSheet4.rotateLeftY(mid);
                glass.rotateLeftY(mid);
                light.rotateLeftY(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //clockwise Y
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateRightY(mid);
                backSheet1.rotateRightY(mid);
                backSheet2.rotateRightY(mid);
                backSheet3.rotateRightY(mid);
                backSheet4.rotateRightY(mid);
                glass.rotateRightY(mid);
                light.rotateRightY(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];

                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)//anti-clockwise Z
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateLeftZ(mid);
                backSheet1.rotateLeftZ(mid);
                backSheet2.rotateLeftZ(mid);
                backSheet3.rotateLeftZ(mid);
                backSheet4.rotateLeftZ(mid);
                glass.rotateLeftZ(mid);
                light.rotateLeftZ(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
    
            }
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) //clockwise Z
            {
                float mid[3];
                glass.calcMidPoint(mid);
                //mid[0] = 0;mid[1] =0;mid[2] =0;
                bottomSheet.rotateRightZ(mid);
                backSheet1.rotateRightZ(mid);
                backSheet2.rotateRightZ(mid);
                backSheet3.rotateRightZ(mid);
                backSheet4.rotateRightZ(mid);
                glass.rotateRightZ(mid);
                light.rotateRightZ(mid);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
            }

            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    backSheetNum++;
                
                    if (backSheetNum>9)
                    {
                        backSheetNum = 0;
                    }
                        switch (backSheetNum)
                        {
                            case 0:{
                                backSheet1.setColour("red",1);
                                backSheet3.setColour("red",1);
                                backSheet2.setColour("red",1);
                                backSheet4.setColour("red",1);
                                break;
                            }
                            case 1:{
                                backSheet1.setColour("orange",1);
                                backSheet2.setColour("orange",1);
                                backSheet3.setColour("orange",1);
                                backSheet4.setColour("orange",1);
                                break;
                            }
                            case 2:{
                                backSheet1.setColour("yellow",1);
                                backSheet2.setColour("yellow",1);
                                backSheet3.setColour("yellow",1);
                                backSheet4.setColour("yellow",1);
                                break;
                            }
                            case 3:{
                                backSheet1.setColour("green",1);
                                backSheet2.setColour("green",1);
                                backSheet3.setColour("green",1);
                                backSheet4.setColour("green",1);
                                break;
                            }
                            case 4:{
                                backSheet1.setColour("blue",1);
                                backSheet2.setColour("blue",1);
                                backSheet3.setColour("blue",1);
                                backSheet4.setColour("blue",1);
                                break;
                            }
                            case 5:{
                                backSheet1.setColour("teal",1);
                                backSheet2.setColour("teal",1);
                                backSheet3.setColour("teal",1);
                                backSheet4.setColour("teal",1);
                                break;
                            }
                            case 6:{
                                backSheet1.setColour("purple",1);
                                backSheet2.setColour("purple",1);
                                backSheet3.setColour("purple",1);
                                backSheet4.setColour("purple",1);
                                break;
                            }
                            case 7:{
                                backSheet1.setColour("pink",1);
                                backSheet2.setColour("pink",1);
                                backSheet3.setColour("pink",1);
                                backSheet4.setColour("pink",1);
                                break;
                            }
                            case 8:{
                                backSheet1.setColour("black",1);
                                backSheet2.setColour("black",1);
                                backSheet3.setColour("black",1);
                                backSheet4.setColour("black",1);
                                break;
                            }
                            case 9:{
                                backSheet1.setColour("white",1);
                                backSheet2.setColour("white",1);
                                backSheet3.setColour("white",1);
                                backSheet4.setColour("white",1);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<bottomSheet.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                        colours[i+144] = backSheet1.colours[i];
                        colours[i+288] = backSheet2.colours[i];
                        colours[i+432] = backSheet3.colours[i];
                        colours[i+576] = backSheet4.colours[i];
                        colours[i+720] = light.colours[i];
                        colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    backSheetNum--;
                
                    if (backSheetNum<0)
                    {
                        backSheetNum = 9;
                    }
                        switch (backSheetNum)
                        {
                            case 0:{
                                backSheet1.setColour("red",1);
                                backSheet2.setColour("red",1);
                                backSheet3.setColour("red",1);
                                backSheet4.setColour("red",1);
                                break;
                            }
                            case 1:{
                                backSheet1.setColour("orange",1);
                                backSheet2.setColour("orange",1);
                                backSheet3.setColour("orange",1);
                                backSheet4.setColour("orange",1);
                                break;
                            }
                            case 2:{
                                backSheet1.setColour("yellow",1);
                                backSheet2.setColour("yellow",1);
                                backSheet3.setColour("yellow",1);
                                backSheet4.setColour("yellow",1);
                                break;
                            }
                            case 3:{
                                backSheet1.setColour("green",1);
                                backSheet2.setColour("green",1);
                                backSheet3.setColour("green",1);
                                backSheet4.setColour("green",1);
                                break;
                            }
                            case 4:{
                                backSheet1.setColour("blue",1);
                                backSheet2.setColour("blue",1);
                                backSheet3.setColour("blue",1);
                                backSheet4.setColour("blue",1);
                                break;
                            }
                            case 5:{
                                backSheet1.setColour("teal",1);
                                backSheet2.setColour("teal",1);
                                backSheet3.setColour("teal",1);
                                backSheet4.setColour("teal",1);
                                break;
                            }
                            case 6:{
                                backSheet1.setColour("purple",1);
                                backSheet2.setColour("purple",1);
                                backSheet3.setColour("purple",1);
                                backSheet4.setColour("purple",1);
                                break;
                            }
                            case 7:{
                                backSheet1.setColour("pink",1);
                                backSheet2.setColour("pink",1);
                                backSheet3.setColour("pink",1);
                                backSheet4.setColour("pink",1);
                                break;
                            }
                            case 8:{
                                backSheet1.setColour("black",1);
                                backSheet2.setColour("black",1);
                                backSheet3.setColour("black",1);
                                backSheet4.setColour("black",1);
                                break;
                            }
                            case 9:{
                                backSheet1.setColour("white",1);
                                backSheet2.setColour("white",1);
                                backSheet3.setColour("white",1);
                                backSheet4.setColour("white",1);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<bottomSheet.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }

            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    glassNum++;
                
                    if (glassNum>9)
                    {
                        glassNum = 0;
                    }
                        switch (glassNum)
                        {
                            case 0:{
                                glass.setColour("red",glassAlpha);
                                break;
                            }
                            case 1:{
                                glass.setColour("orange",glassAlpha);
                                break;
                            }
                            case 2:{
                                glass.setColour("yellow",glassAlpha);
                                break;
                            }
                            case 3:{
                                glass.setColour("green",glassAlpha);
                                break;
                            }
                            case 4:{
                                glass.setColour("blue",glassAlpha);
                                break;
                            }
                            case 5:{
                                glass.setColour("teal",glassAlpha);
                                break;
                            }
                            case 6:{
                                glass.setColour("purple",glassAlpha);
                                break;
                            }
                            case 7:{
                                glass.setColour("pink",glassAlpha);
                                break;
                            }
                            case 8:{
                                glass.setColour("black",glassAlpha);
                                break;
                            }
                            case 9:{
                                glass.setColour("white",glassAlpha);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<glass.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    glassNum--;
                
                    if (glassNum<0)
                    {
                        glassNum = 9;
                    }
                        switch (glassNum)
                        {
                            case 0:{
                                glass.setColour("red",glassAlpha);
                                break;
                            }
                            case 1:{
                                glass.setColour("orange",glassAlpha);
                                break;
                            }
                            case 2:{
                                glass.setColour("yellow",glassAlpha);
                                break;
                            }
                            case 3:{
                                glass.setColour("green",glassAlpha);
                                break;
                            }
                            case 4:{
                                glass.setColour("blue",glassAlpha);
                                break;
                            }
                            case 5:{
                                glass.setColour("teal",glassAlpha);
                                break;
                            }
                            case 6:{
                                glass.setColour("purple",glassAlpha);
                                break;
                            }
                            case 7:{
                                glass.setColour("pink",glassAlpha);
                                break;
                            }
                            case 8:{
                                glass.setColour("black",glassAlpha);
                                break;
                            }
                            case 9:{
                                glass.setColour("white",glassAlpha);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<glass.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                        colours[i+144] = backSheet1.colours[i];
                        colours[i+288] = backSheet2.colours[i];
                        colours[i+432] = backSheet3.colours[i];
                        colours[i+576] = backSheet4.colours[i];
                        colours[i+720] = light.colours[i];
                        colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }

            if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    lightNum++;
                
                    if (lightNum>8)
                    {
                        lightNum = 0;
                    }
                        switch (lightNum)
                        {
                            case 0:{
                                light.setColour("red",1);
                                break;
                            }
                            case 1:{
                                light.setColour("orange",1);
                                break;
                            }
                            case 2:{
                                light.setColour("yellow",1);
                                break;
                            }
                            case 3:{
                                light.setColour("green",1);
                                break;
                            }
                            case 4:{
                                light.setColour("blue",1);
                                break;
                            }
                            case 5:{
                                light.setColour("teal",1);
                                break;
                            }
                            case 6:{
                                light.setColour("purple",1);
                                break;
                            }
                            case 7:{
                                light.setColour("pink",1);
                                break;
                            }
                            case 8:{
                                light.setColour("white",1);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<bottomSheet.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                        colours[i+144] = backSheet1.colours[i];
                        colours[i+288] = backSheet2.colours[i];
                        colours[i+432] = backSheet3.colours[i];
                        colours[i+576] = backSheet4.colours[i];
                        colours[i+720] = light.colours[i];
                        colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }

            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    lightNum--;
                
                    if (lightNum<0)
                    {
                        lightNum = 8;
                    }
                        switch (lightNum)
                        {
                            case 0:{
                                light.setColour("red",1);
                                break;
                            }
                            case 1:{
                                light.setColour("orange",1);
                                break;
                            }
                            case 2:{
                                light.setColour("yellow",1);
                                break;
                            }
                            case 3:{
                                light.setColour("green",1);
                                break;
                            }
                            case 4:{
                                light.setColour("blue",1);
                                break;
                            }
                            case 5:{
                                light.setColour("teal",1);
                                break;
                            }
                            case 6:{
                                light.setColour("purple",1);
                                break;
                            }
                            case 7:{
                                light.setColour("pink",1);
                                break;
                            }
                            case 8:{
                                light.setColour("white",1);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                    light.pointLight(&backSheet1);
                    backSheet2.calNormal();
                    light.pointLight(&backSheet2);
                    backSheet3.calNormal();
                    light.pointLight(&backSheet3);
                    backSheet4.calNormal();
                    light.pointLight(&backSheet4);
                    for (int i=0;i<bottomSheet.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                        colours[i+144] = backSheet1.colours[i];
                        colours[i+288] = backSheet2.colours[i];
                        colours[i+432] = backSheet3.colours[i];
                        colours[i+576] = backSheet4.colours[i];
                        colours[i+720] = light.colours[i];
                        colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }

            if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    glassAlpha+=0.1;
                
                    if (glassAlpha>1)
                    {
                        glassAlpha = 1;
                    }
                        switch (glassNum)
                        {
                            case 0:{
                                glass.setColour("red",glassAlpha);
                                break;
                            }
                            case 1:{
                                glass.setColour("orange",glassAlpha);
                                break;
                            }
                            case 2:{
                                glass.setColour("yellow",glassAlpha);
                                break;
                            }
                            case 3:{
                                glass.setColour("green",glassAlpha);
                                break;
                            }
                            case 4:{
                                glass.setColour("blue",glassAlpha);
                                break;
                            }
                            case 5:{
                                glass.setColour("teal",glassAlpha);
                                break;
                            }
                            case 6:{
                                glass.setColour("purple",glassAlpha);
                                break;
                            }
                            case 7:{
                                glass.setColour("pink",glassAlpha);
                                break;
                            }
                            case 8:{
                                glass.setColour("black",glassAlpha);
                                break;
                            }
                            case 9:{
                                glass.setColour("white",glassAlpha);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                    for (int i=0;i<glass.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) //clockwise Z
            {
                float currT = glfwGetTime();
                if (currT-backSheetKey > 0.2)
                {
                    glassAlpha-=0.1;
                
                    if (glassAlpha<0)
                    {
                        glassAlpha = 0;
                    }
                        switch (glassNum)
                        {
                            case 0:{
                                glass.setColour("red",glassAlpha);
                                break;
                            }
                            case 1:{
                                glass.setColour("orange",glassAlpha);
                                break;
                            }
                            case 2:{
                                glass.setColour("yellow",glassAlpha);
                                break;
                            }
                            case 3:{
                                glass.setColour("green",glassAlpha);
                                break;
                            }
                            case 4:{
                                glass.setColour("blue",glassAlpha);
                                break;
                            }
                            case 5:{
                                glass.setColour("teal",glassAlpha);
                                break;
                            }
                            case 6:{
                                glass.setColour("purple",glassAlpha);
                                break;
                            }
                            case 7:{
                                glass.setColour("pink",glassAlpha);
                                break;
                            }
                            case 8:{
                                glass.setColour("black",glassAlpha);
                                break;
                            }
                            case 9:{
                                glass.setColour("white",glassAlpha);
                                break;
                            }
                    }
                    backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                    for (int i=0;i<glass.cSize;i++)
                    {
                        colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                    }
                    backSheetKey = currT;
                }
            }

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
            {
                light.move("up",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
            {
                light.move("down",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
            {
                light.move("left",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
            {
                light.move("right",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) 
            {
                light.move("incZ",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) 
            {
                light.move("decZ",0.05);
                for (int i=0;i<bottomSheet.vSize;i++)
                {
                    vertices[i] = bottomSheet.vertices[i];
                    vertices[i+108] = backSheet1.vertices[i];
                    vertices[i+216] = backSheet2.vertices[i];
                    vertices[i+324] = backSheet3.vertices[i];
                    vertices[i+432] = backSheet4.vertices[i];
                    vertices[i+540] = light.vertices[i];
                    vertices[i+648] = glass.vertices[i];
                }
                backSheet1.calNormal();
                light.pointLight(&backSheet1);
                backSheet2.calNormal();
                light.pointLight(&backSheet2);
                backSheet3.calNormal();
                light.pointLight(&backSheet3);
                backSheet4.calNormal();
                light.pointLight(&backSheet4);
                for (int i=0;i<bottomSheet.cSize;i++)
                {
                    colours[i] = bottomSheet.colours[i];
                    colours[i+144] = backSheet1.colours[i];
                    colours[i+288] = backSheet2.colours[i];
                    colours[i+432] = backSheet3.colours[i];
                    colours[i+576] = backSheet4.colours[i];
                    colours[i+720] = light.colours[i];
                    colours[i+864] = glass.colours[i];
                }
            }

        } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

}
