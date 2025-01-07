#version 330 core

layout(location = 0) in vec3 aPos;  // 顶点位置
layout(location = 1) in vec2 aTexCoord;  
layout(location = 2) in vec3 aNormal;   // 法线

out vec3 Normal;    // 输出给片段着色器的法线
out vec3 FragPos;   // 输出给片段着色器的世界空间坐标

uniform mat4 transform;       // 模型矩阵
uniform mat4 view;        // 观察矩阵
uniform mat4 projection;  // 投影矩阵

void main() {
    // 计算世界空间的顶点位置
    FragPos = vec3(transform * vec4(aPos, 1.0));

    // 变换法线（需要模型矩阵的逆转置矩阵来保持法线方向正确）
    Normal = mat3(transpose(inverse(transform))) * aNormal;

    // 标准的顶点变换
    gl_Position = projection * view * vec4(FragPos, 1.0);
}