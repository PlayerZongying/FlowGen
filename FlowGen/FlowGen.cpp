// // #include <string>
// // #include <fstream>
// // #include <sstream>
// #include <src/shader_s.h>
//
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include <iostream>
//
//
//
// unsigned int CreateShaderProgramWithShaderSource(const char* vertexShaderSource, const char* fragmentShaderSource) {
//     unsigned int vertexShader;
//     vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);
//
//     int  success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//     if (!success)
//     {
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//         return -1;
//     }
//
//     unsigned int fragmentShader;
//     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);
//
//
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//
//     if (!success)
//     {
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//         return -1;
//     }
//
//
//     unsigned int shaderProgram;
//     shaderProgram = glCreateProgram();
//
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
//
//     return shaderProgram;
// }
//
// void drawTriangle() {
// 	
// 	const char* vertexShaderSource = R"(
//     #version 330 core
//     layout (location = 0) in vec3 aPos; // 输入的顶点位置
//
//     void main() {
//         gl_Position = vec4(aPos, 1.0); // 输出的位置坐标
//     }
// )";
//     const char* fragmentShaderSource = R"(
//     #version 330 core
//     out vec4 FragColor; // 输出的颜色
//
//     void main() {
//         FragColor = vec4(1.0, 0.5, 0.2, 1.0); // 设置片段的颜色为橙色
//     }
// )";
//
//     const char* fragmentShaderSource2 = R"(
//     #version 330 core
//     out vec4 FragColor; // 输出的颜色
//
//     void main() {
//         FragColor = vec4(1.0, 1.0, 0.0, 1.0); // 设置片段的颜色为黄色
//     }
// )";
//     unsigned int shaderProgram = CreateShaderProgramWithShaderSource(vertexShaderSource, fragmentShaderSource);
//     unsigned int shaderProgram2 = CreateShaderProgramWithShaderSource(vertexShaderSource, fragmentShaderSource2);
//
//     float vertices[] = {
//      0.5f,  0.5f, 0.0f,  // top right
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  // bottom left
//     -0.5f,  0.5f, 0.0f   // top left 
//     };
//     unsigned int indices[] = {  // note that we start from 0!
//         0, 1, 3,   // first triangle
//         1, 2, 3    // second triangle
//     };
//
// 	unsigned int VBO;
// 	glGenBuffers(1, &VBO);
//
//     unsigned int EBO;
//     glGenBuffers(1, &EBO);
//
//
//     unsigned int VAO;
//     glGenVertexArrays(1, &VAO);
//
//     glBindVertexArray(VAO);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//
//     glUseProgram(shaderProgram);
//     glBindVertexArray(VAO);
//    
//     glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//
//     glUseProgram(shaderProgram2);
//
//     glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
// }
//
//
//
// int main() {
//
//     const char* vertexPath = "fragmentShader.glsl";
//
//     std::string vertexCode;
//      std::ifstream vShaderFile;
//      vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//
//      vShaderFile.open(vertexPath);
//      std::stringstream vShaderStream;
//      vShaderStream << vShaderFile.rdbuf();
//      vShaderFile.close();
//      vertexCode   = vShaderStream.str();
//
//      std::cout <<vertexCode<< std::endl;
//
//     
//     // 初始化GLFW
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }
//
//     // 创建窗口
//     GLFWwindow* window = glfwCreateWindow(800, 600, "Hello GLFW", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//
//     // 将窗口的上下文设置为当前线程的上下文
//     glfwMakeContextCurrent(window);
//
//     // 初始化GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }
//
//     
//     // 主循环
//     while (!glfwWindowShouldClose(window)) {
//         // 清除窗口
//         glClear(GL_COLOR_BUFFER_BIT);
//
//         drawTriangle();
//
//         // 交换缓冲区并轮询事件
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//
//     // 清理并退出
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <src/Shader/shader_s.h>
#include <src/Tests/Tests.h>
#include <src/Render.h>
#include <iostream>

int main()
{

    // DrawTriangleWithShader();
    TextureTest();
}
