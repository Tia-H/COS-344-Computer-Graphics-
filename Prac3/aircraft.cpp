#include "aircraft.h"

wing::wing()
{
    vSize = (6*18) + (2*204);
    cSize = (6*18) + (2*204);

    bigWing.setColour("orange");
    bigWing.bottom.setColour("darkOrange");
    bigWing.updateCol();
    sideWing1.setColour("orange");
    sideWing1.top.setColour("darkOrange");

    sideWing1.setWidth(0.03);
    float mid[3];
    sideWing1.calcMidPoint(mid);

    sideWing1.setDegree(1.56);
    sideWing1.rotateLeftZ(mid);
    sideWing1.setDegree(0.1);

    for (int i=2;i<30;i+=3)
    {
        sideWing1.top.vertices[i] -= 0.6;
        sideWing1.bottom.vertices[i] -= 0.6;
    }
    sideWing1.move("left",0.115);
    sideWing1.move("up",0.016);

    sideWing2.setColour("orange");
    sideWing2.top.setColour("darkOrange");
    sideWing2.setWidth(0.03);
    float mid2[3];
    sideWing2.calcMidPoint(mid2);

    sideWing2.setDegree(1.56);
    sideWing2.rotateLeftZ(mid2);
    sideWing2.setDegree(0.1);

    for (int i=2;i<30;i+=3)
    {
        sideWing2.top.vertices[i] += 0.4;
        sideWing2.bottom.vertices[i] += 0.4;
    }
    sideWing2.move("left",0.115);
    sideWing2.move("up",0.016);


    updateVertices();

    for (int i=0;i<18;i++)
    {
        //wing colours
        colours[i] = bigWing.front.col[i];
        colours[i+18] = bigWing.back.col[i];
        colours[i+36] = bigWing.top.col[i];
        colours[i+54] = bigWing.bottom.col[i];
        colours[i+72] = bigWing.lSide.col[i];
        colours[i+90] = bigWing.rSide.col[i];

        colours[i+168] = sideWing1.r1.col[i];
        colours[i+186] = sideWing1.r2.col[i];
        colours[i+204] = sideWing1.r3.col[i];
        colours[i+222] = sideWing1.r4.col[i];
        colours[i+240] = sideWing1.r5.col[i];
        colours[i+258] = sideWing1.r6.col[i];
        colours[i+276] = sideWing1.r7.col[i];
        colours[i+294] = sideWing1.r8.col[i];

        colours[i+372] = sideWing2.r1.col[i];
        colours[i+390] = sideWing2.r2.col[i];
        colours[i+408] = sideWing2.r3.col[i];
        colours[i+426] = sideWing2.r4.col[i];
        colours[i+444] = sideWing2.r5.col[i];
        colours[i+462] = sideWing2.r6.col[i];
        colours[i+480] = sideWing2.r7.col[i];
        colours[i+498] = sideWing2.r8.col[i];
    }
    for (int i=0;i<30;i++)
    {
        colours[i+108] = sideWing1.top.col[i];
        colours[i+138] = sideWing1.bottom.col[i];

        colours[i+312] = sideWing2.top.col[i];
        colours[i+342] = sideWing2.bottom.col[i];
    }
}

void wing::updateVertices()
{
    for (int i=0;i<9;i++)
    {
        vertices[i] = bigWing.front.tri1[i];
        vertices[i+9] = bigWing.front.tri2[i];
        vertices[i+18] = bigWing.back.tri1[i];
        vertices[i+27] = bigWing.back.tri2[i];
        vertices[i+36] = bigWing.top.tri1[i];
        vertices[i+45] = bigWing.top.tri2[i];
        vertices[i+54] = bigWing.bottom.tri1[i];
        vertices[i+63] = bigWing.bottom.tri2[i];
        vertices[i+72] = bigWing.lSide.tri1[i];
        vertices[i+81] = bigWing.lSide.tri2[i];
        vertices[i+90] = bigWing.rSide.tri1[i];
        vertices[i+99] = bigWing.rSide.tri2[i];
    
        vertices[i+168] = sideWing1.r1.tri1[i];
        vertices[i+177] = sideWing1.r1.tri2[i];
        vertices[i+186] = sideWing1.r2.tri1[i];
        vertices[i+195] = sideWing1.r2.tri2[i];
        vertices[i+204] = sideWing1.r3.tri1[i];
        vertices[i+213] = sideWing1.r3.tri2[i];
        vertices[i+222] = sideWing1.r4.tri1[i];
        vertices[i+231] = sideWing1.r4.tri2[i];
        vertices[i+240] = sideWing1.r5.tri1[i];
        vertices[i+249] = sideWing1.r5.tri2[i];
        vertices[i+258] = sideWing1.r6.tri1[i];
        vertices[i+267] = sideWing1.r6.tri2[i];
        vertices[i+276] = sideWing1.r7.tri1[i];
        vertices[i+285] = sideWing1.r7.tri2[i];
        vertices[i+294] = sideWing1.r8.tri1[i];
        vertices[i+303] = sideWing1.r8.tri2[i];

        vertices[i+372] = sideWing2.r1.tri1[i];
        vertices[i+381] = sideWing2.r1.tri2[i];
        vertices[i+390] = sideWing2.r2.tri1[i];
        vertices[i+399] = sideWing2.r2.tri2[i];
        vertices[i+408] = sideWing2.r3.tri1[i];
        vertices[i+417] = sideWing2.r3.tri2[i];
        vertices[i+426] = sideWing2.r4.tri1[i];
        vertices[i+435] = sideWing2.r4.tri2[i];
        vertices[i+444] = sideWing2.r5.tri1[i];
        vertices[i+453] = sideWing2.r5.tri2[i];
        vertices[i+462] = sideWing2.r6.tri1[i];
        vertices[i+471] = sideWing2.r6.tri2[i];
        vertices[i+480] = sideWing2.r7.tri1[i];
        vertices[i+489] = sideWing2.r7.tri2[i];
        vertices[i+498] = sideWing2.r8.tri1[i];
        vertices[i+507] = sideWing2.r8.tri2[i];
    }
    for (int i=0;i<30;i++)
    {
        vertices[i+108] = sideWing1.top.vertices[i];
        vertices[i+138] = sideWing1.bottom.vertices[i];

        vertices[i+312] = sideWing2.top.vertices[i];
        vertices[i+342] = sideWing2.bottom.vertices[i];
    }
}

void wing::rotateLeftX(float* mid)
{
    bigWing.rotateLeftX(mid);
    sideWing1.rotateLeftX(mid);
    sideWing2.rotateLeftX(mid);
    updateVertices();
}

void wing::rotateRightX(float* mid)
{
    bigWing.rotateRightX(mid);
    sideWing1.rotateRightX(mid);
    sideWing2.rotateRightX(mid);
    updateVertices();
}

void wing::rotateLeftY(float* mid)
{
    bigWing.rotateLeftY(mid);
    sideWing1.rotateLeftY(mid);
    sideWing2.rotateLeftY(mid);
    updateVertices();
}

void wing::rotateRightY(float* mid)
{
    bigWing.rotateRightY(mid);
    sideWing1.rotateRightY(mid);
    sideWing2.rotateRightY(mid);
    updateVertices();
}

void wing::rotateLeftZ(float* mid)
{
    bigWing.rotateLeftZ(mid);
    sideWing1.rotateLeftZ(mid);
    sideWing2.rotateLeftZ(mid);
    updateVertices();
}

void wing::rotateRightZ(float* mid)
{
    bigWing.rotateRightZ(mid);
    sideWing1.rotateRightZ(mid);
    sideWing2.rotateRightZ(mid);
    updateVertices();
}

void wing::move(std::string d)
{
    bigWing.move(d,0.01);
    sideWing1.move(d,0.01);
    sideWing2.move(d,0.01);
    updateVertices();
}