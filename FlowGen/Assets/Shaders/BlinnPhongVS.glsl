#version 330 core

layout(location = 0) in vec3 aPosition;  // 顶点位置
layout(location = 1) in vec2 aTexCoord;  // 
layout(location = 2) in vec3 aNormal;    // 顶点法线

uniform mat4 transform;       // 模型矩阵
uniform mat4 view;        // 视图矩阵
uniform mat4 projection;  // 投影矩阵

out vec3 FragPos;         // 片段位置（世界空间）
out vec2 uv;
out vec3 Normal;          // 片段法线（世界空间）
out vec3 ViewPos;         // 



vec3 getCameraPositionFromViewMatrix(mat4 view) {
    // 提取旋转部分（左上 3x3）
    mat3 rotation = mat3(view);
    
    // 提取平移部分（右上 1x3）
    vec3 translation = vec3(view[3]);
    
    // 计算摄像机位置
    return -transpose(rotation) * translation;
}

void main() {
    FragPos = vec3(transform * vec4(aPosition, 1.0));  // 计算世界空间的片段位置
    Normal = mat3(transpose(inverse(transform))) * aNormal;  // 转换法线到世界空间
    //Normal = aNormal;
    ViewPos = getCameraPositionFromViewMatrix(view);
    
    uv = vec2(aTexCoord.x, aTexCoord.y);

    gl_Position = projection * view * vec4(FragPos, 1.0);  // 最终顶点位置
    
}


