#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

void framebuffer_size_change(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window,GLFW_KEY_1)){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }

    if(glfwGetKey(window,GLFW_KEY_2)){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }

}




int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 800, "openglshit", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "FAILURE AFTER FAILURE AFTER FAILURE" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 800);

    float vertices[] = {
        -0.5,-0.5,0,
        0.5,-0.5,0,
        -0.5,0.5,0,
        0.5,0.5,0
    };

    unsigned int indices[] {
        0,1,2,
        1,2,3,
    };

    const char* vertex = "\
        #version 330 core\n\
        layout(location = 0) in vec3 aPos;\
        void main(){\
            gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\
        }";

    
    //vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader,1,&vertex,NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* frag = "#version 330 core\n"
        "out vec4 FragColor;"
        "void main(){"
        "   FragColor = vec4(1.,0.5,0.2,1.);}";
    
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShader,1,&frag,NULL);
    glCompileShader(fragShader);


    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Linking shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int VBO;
    glGenBuffers(1,&VBO);

    unsigned int EBO;
    glGenBuffers(1,&EBO);

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_change);
    while (!glfwWindowShouldClose(window))
    {
        // std::cout << "shitting fuck\n";
        processInput(window);

        glClearColor(0., 0., 0., 1.);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
