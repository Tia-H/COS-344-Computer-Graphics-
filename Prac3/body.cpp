#include "aircraft.h"

body::body()
{
    speed=0;
    timeInterval = 2;
    vSize = 30 + (10*9) + (15*108) +(3*204) + (6*72) + (4*108);
    cSize = 30 + (10*9) + (15*108) +(3*204) +(6*72) +(4*108);

    planeTail.move("up",0.01);
    planeTail.move("left",0.16);

    float mid[3];
    tailPart1.calcMidPoint(mid);
    tailPart1.setLength(0.09);
    tailPart1.setWidth(0.11);
    tailPart1.setHeight(0.02);
    tailPart1.makeLTrapezoid();
    tailPart1.move("right",0.6);
    tailPart1.degree = 1.5;
    tailPart1.rotateRightX(mid);
    tailPart1.degree = 0.1;
    tailPart1.move("incZ",0.005);
    tailPart1.move("up",0.015);
    tailPart1.setColour("orange");

    tailPart2.calcMidPoint(mid);
    tailPart2.setLength(0.11);
    tailPart2.setWidth(0.07);
    tailPart2.setHeight(0.02);
    tailPart2.makeRTrapezoid();
    tailPart2.move("right",0.692);
    tailPart2.degree = 1.5;
    tailPart2.rotateRightX(mid);
    tailPart2.degree = 0.1;
    tailPart2.move("incZ",0.005);
    tailPart2.move("up",0.015);
    tailPart2.setColour("yellow");

    tailPart3.calcMidPoint(mid);
    tailPart3.setLength(0.05);
    tailPart3.setWidth(0.1385);
    tailPart3.setHeight(0.02);
    tailPart3.makeTrapezoid();
    tailPart3.move("right",0.643);
    tailPart3.degree = 1.5;
    tailPart3.rotateRightX(mid);
    tailPart3.degree = 0.1;
    tailPart3.move("incZ",0.007);
    tailPart3.move("up",0.087);
    tailPart3.setColour("yellow");

    tailWheelLink.setWidth(0.01);
    tailWheelLink.setHeight(0.05);
    tailWheelLink.setLength(0.01);
    tailWheelLink.degree = 1;
    tailWheelLink.calcMidPoint(mid);
    tailWheelLink.rotateLeftZ(mid);
    tailWheelLink.degree = 0.1;
    tailWheelLink.move("right",0.6);
    tailWheelLink.move("down",0.08);
    tailWheelLink.move("decZ",0.005);
    tailWheelLink.setColour("black");


    tailWheel.setRadius(0.015);
    tailWheel.setWidth(0.02);
    tailWheel.calcMidPoint(mid);
    tailWheel.setDegree(1.6);
    tailWheel.rotateLeftZ(mid);
    tailWheel.rotateLeftX(mid);
    tailWheel.setDegree(0.1);
    tailWheel.move("right",0.5);
    tailWheel.move("down",0.07);
    tailWheel.move("decZ",0.105);
    tailWheel.setColour("black");

    leftTail1.setWidth(0.15);
    leftTail1.setHeight(0.01);
    leftTail1.move("right",0.57);
    leftTail1.degree = 1.5;
    leftTail1.rotateLeftX(mid);
    leftTail1.degree = 1.6;
    leftTail1.rotateLeftY(mid);
    leftTail1.degree = 0.1;
    leftTail1.move("right",0.505);
    leftTail1.move("incZ",0.435);
    leftTail1.move("down",0.045);
    leftTail1.front.vertex[6] = 0.4;
    leftTail1.back.vertex[6] = 0.4;
    leftTail1.front.vertex[8] += 0.05;
    leftTail1.back.vertex[8] += 0.05;
    leftTail1.changeVertices();
    leftTail1.updateVertices();
    leftTail1.setColour("orange");


    rightTail1.setWidth(0.15);
    rightTail1.setHeight(0.01);
    rightTail1.move("right",0.57);
    rightTail1.degree = 1.5;
    rightTail1.rotateLeftX(mid);
    rightTail1.degree = 1.6;
    rightTail1.rotateLeftY(mid);
    rightTail1.degree = 0.1;
    rightTail1.move("right",0.505);
    rightTail1.move("incZ",0.59);
    rightTail1.move("down",0.045);
    rightTail1.front.vertex[6] = 0.4;
    rightTail1.back.vertex[6] = 0.4;
    rightTail1.front.vertex[8] -= 0.05;
    rightTail1.back.vertex[8] -= 0.05;
    rightTail1.changeVertices();
    rightTail1.updateVertices();
    rightTail1.setColour("orange");

    leftTail2.setWidth(0.03);
    leftTail2.setHeight(0.01);
    leftTail2.setLength(0.135);
    leftTail2.move("right",0.71);
    leftTail2.move("decZ",0.085);
    leftTail2.move("down",0.045);
    leftTail2.setColour("yellow");

    rightTail2.setWidth(0.03);
    rightTail2.setHeight(0.01);
    rightTail2.setLength(0.135);
    rightTail2.move("right",0.71);
    rightTail2.move("incZ",0.085);
    rightTail2.move("down",0.045);
    rightTail2.setColour("yellow");

    window.setColour("blue");
    window.setWidth(0.15);
    window.setLength(0.13);
    window.setHeight(0.1);
    window.move("left",0.11);
    window.move("down",0.056);
    window.move("incZ",0.005);

    leftWindow.setColour("blue");
    leftWindow.front.vertex[1] = 0;
    leftWindow.front.vertex[2] = 0.14;
    leftWindow.front.vertex[4] = 0;
    leftWindow.front.vertex[5] = 0.1;
    leftWindow.front.vertex[7] = 0.1;
    leftWindow.front.vertex[8] = 0.14;
    for (int i=0;i<9;i+=3)
    {
        leftWindow.front.vertex[i] = 0;

        leftWindow.back.vertex[i] = -0.15;
        leftWindow.back.vertex[i+1] = leftWindow.front.vertex[i+1];
        leftWindow.back.vertex[i+2] = leftWindow.front.vertex[i+2];
    }
    leftWindow.changeVertices();
    leftWindow.updateVertices();
    leftWindow.move("decZ",0.3);
    leftWindow.move("down",0.088);
    leftWindow.move("left",0.13);

    rightWindow.setColour("blue");
    rightWindow.front.vertex[1] = 0;
    rightWindow.front.vertex[2] = 0.14;
    rightWindow.front.vertex[4] = 0;
    rightWindow.front.vertex[5] = 0.1;
    rightWindow.front.vertex[7] = 0.1;
    rightWindow.front.vertex[8] = 0.1;
    for (int i=0;i<9;i+=3)
    {
        rightWindow.front.vertex[i] = 0;

        rightWindow.back.vertex[i] = -0.15;
        rightWindow.back.vertex[i+1] = rightWindow.front.vertex[i+1];
        rightWindow.back.vertex[i+2] = rightWindow.front.vertex[i+2];
    }
    rightWindow.changeVertices();
    rightWindow.updateVertices();
    rightWindow.move("decZ",0.137);
    rightWindow.move("down",0.088);
    rightWindow.move("left",0.13);

    midBody.setColour("orange");
    midBody.setWidth(0.17);
    midBody.setHeight(0.1);
    midBody.setLength(0.2);
    midBody.move("down",0.15);
    midBody.move("left",0.105);

    nose.setColour("orange");
    nose.setWidth(0.13);
    nose.setHeight(0.1);
    nose.setLength(0.2);
    nose.move("down",0.15);
    nose.move("left",0.25);

    leftWheelStruct.setColour("darkOrange");
    leftWheelStruct.setWidth(0.1);
    leftWheelStruct.setHeight(0.01);
    leftWheelStruct.move("down",0.27);
    leftWheelStruct.move("left",0.25);
    leftWheelStruct.move("decZ",0.19);
    leftWheelStruct.front.vertex[7] -= 0.2;
    leftWheelStruct.back.vertex[7] -= 0.2;
    leftWheelStruct.front.vertex[8] -= 0.05;
    leftWheelStruct.back.vertex[8] -= 0.05;
    leftWheelStruct.changeVertices();
    leftWheelStruct.updateVertices();

    rightWheelStruct.setColour("darkOrange");
    rightWheelStruct.setWidth(0.1);
    rightWheelStruct.setHeight(0.01);
    rightWheelStruct.move("down",0.27);
    rightWheelStruct.move("left",0.25);
    rightWheelStruct.front.vertex[7] -= 0.2;
    rightWheelStruct.back.vertex[7] -= 0.2;
    rightWheelStruct.front.vertex[8] += 0.05;
    rightWheelStruct.back.vertex[8] += 0.05;
    rightWheelStruct.changeVertices();
    rightWheelStruct.updateVertices();

    leftWheel.setColour("black");
    leftWheel.setRadius(0.04);
    leftWheel.setWidth(0.03);
    leftWheel.calcMidPoint(mid);
    leftWheel.setDegree(1.6);
    leftWheel.rotateLeftZ(mid);
    leftWheel.rotateLeftX(mid);
    leftWheel.setDegree(0.1);
    leftWheel.move("down",0.27);
    leftWheel.move("left",0.21);
    leftWheel.move("decZ",0.26);

    rightWheel.setColour("black");
    rightWheel.setRadius(0.04);
    rightWheel.setWidth(0.03);
    rightWheel.calcMidPoint(mid);
    rightWheel.setDegree(1.6);
    rightWheel.rotateLeftZ(mid);
    rightWheel.rotateLeftX(mid);
    rightWheel.setDegree(0.1);
    rightWheel.move("down",0.27);
    rightWheel.move("left",0.21);
    rightWheel.move("incZ",0.06);

    propellerCenter.setColour("black");
    propellerCenter.setWidth(0.05);
    propellerCenter.setHeight(0.05);
    propellerCenter.setLength(0.05);
    propellerCenter.move("down",0.15);
    propellerCenter.move("left",0.33);

    propeller1.setColour("white");
    propeller1.setWidth(0.01);
    propeller1.setHeight(0.3);
    propeller1.setLength(0.02);
    propeller1.move("down",0.15);
    propeller1.move("left",0.349);

    wingStruct1.setColour("black"); 
    wingStruct1.setHeight(0.16);
    wingStruct1.setWidth(0.01);
    wingStruct1.setLength(0.01);
    wingStruct1.move("decZ",0.4);
    wingStruct1.move("down",0.09);
    wingStruct1.front.tri1[8] += 0.35;
    wingStruct1.back.tri1[8] += 0.35;
    wingStruct1.front.tri2[5] += 0.35;
    wingStruct1.back.tri2[5] += 0.35;
    wingStruct1.front.tri2[8] += 0.35;
    wingStruct1.back.tri2[8] += 0.35;
    wingStruct1.changeVertices();
    wingStruct1.updateVertices();
    wingStruct1.bottom.tri1[2] += 0.35;
    wingStruct1.bottom.tri1[5] += 0.35;
    wingStruct1.bottom.tri1[8] += 0.35;
    wingStruct1.bottom.tri2[2] += 0.35;
    wingStruct1.bottom.tri2[5] += 0.35;
    wingStruct1.bottom.tri2[8] += 0.35;
    

    wingStruct2.setColour("black");
    wingStruct2.setHeight(0.16);
    wingStruct2.setWidth(0.01);
    wingStruct2.setLength(0.01);
    wingStruct2.move("incZ",0.4);
    wingStruct2.move("down",0.09);
    wingStruct2.front.tri1[8] -= 0.35;
    wingStruct2.back.tri1[8] -= 0.35;
    wingStruct2.front.tri2[5] -= 0.35;
    wingStruct2.back.tri2[5] -= 0.35;
    wingStruct2.front.tri2[8] -= 0.35;
    wingStruct2.back.tri2[8] -= 0.35;
    wingStruct2.changeVertices();
    wingStruct2.updateVertices();
    wingStruct2.bottom.tri1[2] -= 0.35;
    wingStruct2.bottom.tri1[5] -= 0.35;
    wingStruct2.bottom.tri1[8] -= 0.35;
    wingStruct2.bottom.tri2[2] -= 0.35;
    wingStruct2.bottom.tri2[5] -= 0.35;
    wingStruct2.bottom.tri2[8] -= 0.35;

    wingStruct3.setColour("black");
    wingStruct3.setHeight(0.05);
    wingStruct3.setWidth(0.01);
    wingStruct3.setLength(0.01);
    wingStruct3.move("decZ",0.29);
    wingStruct3.move("down",0.04);

    wingStruct4.setColour("black");
    wingStruct4.setHeight(0.05);
    wingStruct4.setWidth(0.01);
    wingStruct4.setLength(0.01);
    wingStruct4.move("incZ",0.29);
    wingStruct4.move("down",0.04);


    decor1.setColour("black");
    decor1.setLength(0);
    decor1.setWidth(0.18);
    decor1.setHeight(0.018);
    decor1.move("down",0.12);
    decor1.move("decZ",0.103);
    decor1.move("left",0.14);

    decor2.setColour("black");
    decor2.setLength(0);
    decor2.setWidth(0.1);
    decor2.setHeight(0.01);
    decor2.move("down",0.13);
    decor2.move("decZ",0.103);
    decor2.move("left",0.25);

    decorR1.setColour("black");
    decorR1.setLength(0);
    decorR1.setWidth(0.18);
    decorR1.setHeight(0.018);
    decorR1.move("down",0.12);
    decorR1.move("incZ",0.103);
    decorR1.move("left",0.14);

    decorR2.setColour("black");
    decorR2.setLength(0);
    decorR2.setWidth(0.1);
    decorR2.setHeight(0.01);
    decorR2.move("down",0.13);
    decorR2.move("incZ",0.103);
    decorR2.move("left",0.25);
    


    for (int i=2;i<30;i+=3)
    {
        planeTail.base.vertices[i] -= 0.1;
    }
    for (int i=2;i<9;i+=3)
    {
        planeTail.t1.vertex[i] -= 0.1;
        planeTail.t2.vertex[i] -= 0.1;
        planeTail.t3.vertex[i] -= 0.1;
        planeTail.t4.vertex[i] -= 0.1;
        planeTail.t5.vertex[i] -= 0.1;
        planeTail.t6.vertex[i] -= 0.1;
        planeTail.t7.vertex[i] -= 0.1;
        planeTail.t8.vertex[i] -= 0.1;

    }

    for (int i=0;i<9;i++)
    {
        colours[i+30] = planeTail.t1.col[i];
        colours[i+39] = planeTail.t2.col[i];
        colours[i+48] = planeTail.t3.col[i];
        colours[i+57] = planeTail.t4.col[i];
        colours[i+66] = planeTail.t5.col[i];
        colours[i+75] = planeTail.t6.col[i];
        colours[i+84] = planeTail.t7.col[i];
        colours[i+93] = planeTail.t8.col[i];

    }
    for (int i=0;i<30;i++)
    {
        colours[i] = planeTail.base.col[i];
    }

    for (int i=0;i<108;i++)//cuboids
    {
        colours[i+102] = tailPart1.colours[i];
        colours[i+210] = tailPart2.colours[i];
        colours[i+318] = tailPart3.colours[i];
        colours[i+426] = tailWheelLink.colours[i];
        colours[i+882]= leftTail2.colours[i];
        colours[i+990]= rightTail2.colours[i];
        colours[i+1098]= window.colours[i];
        colours[i+1350] = midBody.colours[i];
        colours[i+1458] = nose.colours[i];
        colours[i+2118] = propellerCenter.colours[i];
        colours[i+2226] = propeller1.colours[i];
        colours[i+2334] = wingStruct1.colours[i];
        colours[i+2442] = wingStruct2.colours[i];
        colours[i+2550] = wingStruct3.colours[i];
        colours[i+2658] = wingStruct4.colours[i];

        colours[i+2766] = decor1.colours[i];
        colours[i+2874] = decor2.colours[i];
        colours[i+2982] = decorR1.colours[i];
        colours[i+3090] = decorR2.colours[i];
    }
    for (int i=0;i<72;i++)
    {
        colours[i+738]= leftTail1.colours[i];
        colours[i+810]= rightTail1.colours[i];
        colours[i+1206]= leftWindow.colours[i];
        colours[i+1278]= rightWindow.colours[i];
        colours[i+1566]= leftWheelStruct.colours[i];
        colours[i+1638]= rightWheelStruct.colours[i];
    }
    for (int i=0;i<204;i++)//cylinders
    {
        colours[i+534] = tailWheel.colours[i];
        colours[i+1710]= leftWheel.colours[i];
        colours[i+1914]= rightWheel.colours[i];
    }

    updateVertices();
}

void body::updateVertices()
{
    for (int i=0;i<9;i++)
    {
        vertices[i+30] = planeTail.t1.vertex[i];
        vertices[i+39] = planeTail.t2.vertex[i];
        vertices[i+48] = planeTail.t3.vertex[i];
        vertices[i+57] = planeTail.t4.vertex[i];
        vertices[i+66] = planeTail.t5.vertex[i];
        vertices[i+75] = planeTail.t6.vertex[i];
        vertices[i+84] = planeTail.t7.vertex[i];
        vertices[i+93] = planeTail.t8.vertex[i];

    }
    for (int i=0;i<30;i++)
    {
        vertices[i] = planeTail.base.vertices[i];
    }
    for (int i=0;i<108;i++)
    {
        vertices[i+102]= tailPart1.vertices[i];
        vertices[i+210]= tailPart2.vertices[i];
        vertices[i+318]= tailPart3.vertices[i];
        vertices[i+426]= tailWheelLink.vertices[i];
        //vertices[i+738]= leftTail1.vertices[i];
        //vertices[i+846]= rightTail1.vertices[i];
        vertices[i+882]= leftTail2.vertices[i];
        vertices[i+990]= rightTail2.vertices[i];
        vertices[i+1098]= window.vertices[i];
        vertices[i+1350] = midBody.vertices[i];
        vertices[i+1458] = nose.vertices[i];
        vertices[i+2118] = propellerCenter.vertices[i];
        vertices[i+2226] = propeller1.vertices[i];
        vertices[i+2334] = wingStruct1.vertices[i];
        vertices[i+2442] = wingStruct2.vertices[i];
        vertices[i+2550] = wingStruct3.vertices[i];
        vertices[i+2658] = wingStruct4.vertices[i];

        vertices[i+2766] = decor1.vertices[i];
        vertices[i+2874] = decor2.vertices[i];
        vertices[i+2982] = decorR1.vertices[i];
        vertices[i+3090] = decorR2.vertices[i];
    }
    for (int i=0;i<72;i++)
    {
        vertices[i+738]= leftTail1.vertices[i];
        vertices[i+810]= rightTail1.vertices[i];
        vertices[i+1206]= leftWindow.vertices[i];
        vertices[i+1278]= rightWindow.vertices[i];
        vertices[i+1566]= leftWheelStruct.vertices[i];
        vertices[i+1638]= rightWheelStruct.vertices[i];
    }
    for (int i=0;i<204;i++)//cylinders
    {
        vertices[i+534] = tailWheel.vertices[i];
        vertices[i+1710]= leftWheel.vertices[i];
        vertices[i+1914]= rightWheel.vertices[i];
    }

}

void body::calcPlaneMidPoint(float* mid)
{
     planeTail.calcPlaneMidPoint(mid);
}

void body::rotateLeftX(float* mid)
{
    planeTail.rotateLeftX();
    tailPart1.rotateLeftX(mid);
    tailPart2.rotateLeftX(mid);
    tailPart3.rotateLeftX(mid);
    tailWheelLink.rotateLeftX(mid);
    tailWheel.rotateLeftX(mid);
    leftTail1.rotateLeftX(mid);
    rightTail1.rotateLeftX(mid);
    leftTail2.rotateLeftX(mid);
    rightTail2.rotateLeftX(mid);
    window.rotateLeftX(mid);
    leftWindow.rotateLeftX(mid);
    rightWindow.rotateLeftX(mid);
    midBody.rotateLeftX(mid);
    nose.rotateLeftX(mid);
    leftWheelStruct.rotateLeftX(mid);
    rightWheelStruct.rotateLeftX(mid);
    leftWheel.rotateLeftX(mid);
    rightWheel.rotateLeftX(mid);
    propellerCenter.rotateLeftX(mid);
    propeller1.rotateLeftX(mid);
    wingStruct1.rotateLeftX(mid);
    wingStruct2.rotateLeftX(mid);
    wingStruct3.rotateLeftX(mid);
    wingStruct4.rotateLeftX(mid);

    decor1.rotateLeftX(mid);
    decor2.rotateLeftX(mid);
    decorR1.rotateLeftX(mid);
    decorR2.rotateLeftX(mid);
    updateVertices();
}

void body::rotateRightX(float* mid)
{
    planeTail.rotateRightX();
    tailPart1.rotateRightX(mid);
    tailPart2.rotateRightX(mid);
    tailPart3.rotateRightX(mid);
    tailWheelLink.rotateRightX(mid);
    tailWheel.rotateRightX(mid);
    leftTail1.rotateRightX(mid);
    rightTail1.rotateRightX(mid);
    leftTail2.rotateRightX(mid);
    rightTail2.rotateRightX(mid);
    window.rotateRightX(mid);
    leftWindow.rotateRightX(mid);
    rightWindow.rotateRightX(mid);
    midBody.rotateRightX(mid);
    nose.rotateRightX(mid);
    leftWheelStruct.rotateRightX(mid);
    rightWheelStruct.rotateRightX(mid);
    leftWheel.rotateRightX(mid);
    rightWheel.rotateRightX(mid);
    propellerCenter.rotateRightX(mid);
    propeller1.rotateRightX(mid);
    wingStruct1.rotateRightX(mid);
    wingStruct2.rotateRightX(mid);
    wingStruct3.rotateRightX(mid);
    wingStruct4.rotateRightX(mid);

    decor1.rotateRightX(mid);
    decor2.rotateRightX(mid);
    decorR1.rotateRightX(mid);
    decorR2.rotateRightX(mid);
    updateVertices();
}

void body::rotateLeftY(float* mid)
{
    planeTail.rotateLeftY();
    tailPart1.rotateLeftY(mid);
    tailPart2.rotateLeftY(mid);
    tailPart3.rotateLeftY(mid);
    tailWheelLink.rotateLeftY(mid);
    tailWheel.rotateLeftY(mid);
    leftTail1.rotateLeftY(mid);
    rightTail1.rotateLeftY(mid);
    leftTail2.rotateLeftY(mid);
    rightTail2.rotateLeftY(mid);
    window.rotateLeftY(mid);
    leftWindow.rotateLeftY(mid);
    rightWindow.rotateLeftY(mid);
    midBody.rotateLeftY(mid);
    nose.rotateLeftY(mid);
    leftWheelStruct.rotateLeftY(mid);
    rightWheelStruct.rotateLeftY(mid);
    leftWheel.rotateLeftY(mid);
    rightWheel.rotateLeftY(mid);
    propellerCenter.rotateLeftY(mid);
    propeller1.rotateLeftY(mid);
    wingStruct1.rotateLeftY(mid);
    wingStruct2.rotateLeftY(mid);
    wingStruct3.rotateLeftY(mid);
    wingStruct4.rotateLeftY(mid);

    decor1.rotateLeftY(mid);
    decor2.rotateLeftY(mid);
    decorR1.rotateLeftY(mid);
    decorR2.rotateLeftY(mid);
    updateVertices();
}

void body::rotateRightY(float* mid)
{
    planeTail.rotateRightY();
    tailPart1.rotateRightY(mid);
    tailPart2.rotateRightY(mid);
    tailPart3.rotateRightY(mid);
    tailWheelLink.rotateRightY(mid);
    tailWheel.rotateRightY(mid);
    leftTail1.rotateRightY(mid);
    rightTail1.rotateRightY(mid);
    leftTail2.rotateRightY(mid);
    rightTail2.rotateRightY(mid);
    window.rotateRightY(mid);
    leftWindow.rotateRightY(mid);
    rightWindow.rotateRightY(mid);
    midBody.rotateRightY(mid);
    nose.rotateRightY(mid);
    leftWheelStruct.rotateRightY(mid);
    rightWheelStruct.rotateRightY(mid);
    leftWheel.rotateRightY(mid);
    rightWheel.rotateRightY(mid);
    propellerCenter.rotateRightY(mid);
    propeller1.rotateRightY(mid);
    wingStruct1.rotateRightY(mid);
    wingStruct2.rotateRightY(mid);
    wingStruct3.rotateRightY(mid);
    wingStruct4.rotateRightY(mid);

    decor1.rotateRightY(mid);
    decor2.rotateRightY(mid);
    decorR1.rotateRightY(mid);
    decorR2.rotateRightY(mid);

    updateVertices();
}

void body::rotateLeftZ(float* mid)
{
    planeTail.rotateLeftZ();
    tailPart1.rotateLeftZ(mid);
    tailPart2.rotateLeftZ(mid);
    tailPart3.rotateLeftZ(mid);
    tailWheelLink.rotateLeftZ(mid);
    tailWheel.rotateLeftZ(mid);
    leftTail1.rotateLeftZ(mid);
    rightTail1.rotateLeftZ(mid);
    leftTail2.rotateLeftZ(mid);
    rightTail2.rotateLeftZ(mid);
    window.rotateLeftZ(mid);
    leftWindow.rotateLeftZ(mid);
    rightWindow.rotateLeftZ(mid);
    midBody.rotateLeftZ(mid);
    nose.rotateLeftZ(mid);
    leftWheelStruct.rotateLeftZ(mid);
    rightWheelStruct.rotateLeftZ(mid);
    leftWheel.rotateLeftZ(mid);
    rightWheel.rotateLeftZ(mid);
    propellerCenter.rotateLeftZ(mid);
    propeller1.rotateLeftZ(mid);
    wingStruct1.rotateLeftZ(mid);
    wingStruct2.rotateLeftZ(mid);
    wingStruct3.rotateLeftZ(mid);
    wingStruct4.rotateLeftZ(mid);

    decor1.rotateLeftZ(mid);
    decor2.rotateLeftZ(mid);
    decorR1.rotateLeftZ(mid);
    decorR2.rotateLeftZ(mid);

    updateVertices();

}

void body::rotateRightZ(float* mid)
{
    planeTail.rotateRightZ();
    tailPart1.rotateRightZ(mid);
    tailPart2.rotateRightZ(mid);
    tailPart3.rotateRightZ(mid);
    tailWheelLink.rotateRightZ(mid);
    tailWheel.rotateRightZ(mid);
    leftTail1.rotateRightZ(mid);
    rightTail1.rotateRightZ(mid);
    leftTail2.rotateRightZ(mid);
    rightTail2.rotateRightZ(mid);
    window.rotateRightZ(mid);
    leftWindow.rotateRightZ(mid);
    rightWindow.rotateRightZ(mid);
    midBody.rotateRightZ(mid);
    nose.rotateRightZ(mid);
    leftWheelStruct.rotateRightZ(mid);
    rightWheelStruct.rotateRightZ(mid);
    leftWheel.rotateRightZ(mid);
    rightWheel.rotateRightZ(mid);
    propellerCenter.rotateRightZ(mid);
    propeller1.rotateRightZ(mid);
    wingStruct1.rotateRightZ(mid);
    wingStruct2.rotateRightZ(mid);
    wingStruct3.rotateRightZ(mid);
    wingStruct4.rotateRightZ(mid);

    decor1.rotateRightZ(mid);
    decor2.rotateRightZ(mid);
    decorR1.rotateRightZ(mid);
    decorR2.rotateRightZ(mid);

    updateVertices();
}

void body::move(std::string d)
{
    planeTail.move(d,0.01);
    tailPart1.move(d,0.01);
    tailPart2.move(d,0.01);
    tailPart3.move(d,0.01);
    tailWheelLink.move(d,0.01);
    tailWheel.move(d,0.01);
    leftTail1.move(d,0.01);
    rightTail1.move(d,0.01);
    leftTail2.move(d,0.01);
    rightTail2.move(d,0.01);
    window.move(d,0.01);
    leftWindow.move(d,0.01);
    rightWindow.move(d,0.01);
    midBody.move(d,0.01);
    nose.move(d,0.01);
    leftWheelStruct.move(d,0.01);
    rightWheelStruct.move(d,0.01);
    leftWheel.move(d,0.01);
    rightWheel.move(d,0.01);
    propellerCenter.move(d,0.01);
    propeller1.move(d,0.01);
    wingStruct1.move(d,0.01);
    wingStruct2.move(d,0.01);
    wingStruct3.move(d,0.01);
    wingStruct4.move(d,0.01);
    if (d=="left")
    {
        float mid[3];
        rightWheel.calcMidPoint(mid);
        leftWheel.rotate(mid,-0.1);
        leftWheel.calcMidPoint(mid);
        rightWheel.rotate(mid,-0.1);
    }
    if (d=="right")
    {
        float mid[3];
        rightWheel.calcMidPoint(mid);
        leftWheel.rotate(mid,0.1);
        leftWheel.calcMidPoint(mid);
        rightWheel.rotate(mid,0.1);
    }

    decor1.move(d,0.01);
    decor2.move(d,0.01);
    decorR1.move(d,0.01);
    decorR2.move(d,0.01);

    updateVertices();
}

void body::increaseSpeed()
{
    if (speed!=0)
    {
        speed *= 2;
    }else{
        speed = 0.1;
    }

}
void body::decreaseSpeed()
{
    if (speed==0.1)
    {
        speed=0;
    }
    if (speed>0)
    {
        speed /=2;
    }
}