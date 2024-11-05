#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
out vec4 vertexColor; // specify a color output to the fragment shader
out vec4 NDCpos;

uniform float time;
void main()
{
    const float PI = 3.1415926535897932384626433832795;
    
    
    NDCpos = vec4(aPos * sin(PI * time), 1.0)
    gl_Position = NDCpos; // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
    vertexColor = vec4(aColor, 1.0f); // set the output variable to vertex color
    

}