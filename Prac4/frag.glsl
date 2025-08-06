#version 330 core

in vec4 fCol;
layout (location=0) out vec4 col;

void main(){
    col=fCol;
}