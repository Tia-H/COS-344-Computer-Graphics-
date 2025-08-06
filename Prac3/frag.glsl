#version 330 core

in vec3 fCol;
layout (location=0) out vec3 col;

void main(){
    col=fCol;
}