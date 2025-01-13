#version 330 core

in vec3 Normal;    // 从顶点着色器传入的法线
in vec3 FragPos;   // 从顶点着色器传入的世界空间坐标
in vec2 uv;

out vec4 FragColor;  // 输出的片段颜色

void main() {
    // 将法线从 (-1, 1) 范围映射到 (0, 1) 范围
    // normlized normal is (-1,1) for x, y, z, (-1,1) * 
    vec3 normalColor = normalize(Normal) * 0.5f + 0.5f;

    // 可视化法线颜色
    FragColor = vec4(normalColor, 1.0);
    
}