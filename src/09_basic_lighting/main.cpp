#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>

#include "shader.h"

const int window_w = 800;
const int window_h = 600;
const char* window_name = "LearnOpenGL";
const std::string pre_fix = "./src/09_basic_lighting/";

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

// 初始化opengl
void setup_opengl();
// 窗口大小变化回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 输入处理
void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
// 加载纹理
void load_texture(char* path, unsigned int* texture);
unsigned int create_shader(const char* vertex, const char* fragment);
void create_vertex_data(unsigned int* VAO, unsigned int* EBO, unsigned int* VBO);

void test_glm();

/**********************************/
/*          Util Function         */
/**********************************/
std::string get_path(std::string local);
void dump(glm::vec4 vec);


glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
float move_speed = 5.0f;
float delta_time = 0.0f;
float last_frame = 0.0f;
glm::vec3 camera_direction;
float yaw = -90.0f, pitch = 0.0f;
float last_x = 400, last_y = 300;

glm::vec3 light_color = glm::vec3(1.0f, 0.5f, 0.31f);
glm::vec3 ambient_light = glm::vec3(0.1, 0.1, 0.1);
glm::vec3 light_pos = glm::vec3( 2.0f,  5.0f, -15.0f);

int main()
{
    test_glm();

    setup_opengl();

    GLFWwindow* window = glfwCreateWindow(window_w, window_h, window_name, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, window_w, window_h);
    // 告诉GLFW每当窗口调整大小的时候调整viewport大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    stbi_set_flip_vertically_on_load(true); 
    unsigned int texture1, texture2;
    load_texture("image/container.jpg", &texture1);
    load_texture("image/awesomeface.png", &texture2);

    Shader shader(get_path("shader/sample.vert").c_str(), 
        get_path("shader/sample.frag").c_str());

    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    shader.setInt("texture2", 1);
    unsigned int model_loc = glGetUniformLocation(shader.ID, "model");
    unsigned int view_loc = glGetUniformLocation(shader.ID, "view");
    unsigned int proj_loc = glGetUniformLocation(shader.ID, "proj");
    unsigned int light_color_loc = glGetUniformLocation(shader.ID, "light_color");
    glUniform3f(light_color_loc, light_color.x, light_color.y, light_color.z);
    unsigned int ambient_light_loc = glGetUniformLocation(shader.ID, "ambient_light");
    glUniform3f(ambient_light_loc, ambient_light.x, ambient_light.y, ambient_light.z);
    unsigned int light_pos_loc = glGetUniformLocation(shader.ID, "light_pos");
    glUniform3f(light_pos_loc, light_pos.x, light_pos.y, light_pos.z);
    unsigned int camera_pos_loc = glGetUniformLocation(shader.ID, "camera_pos");

    Shader light_shader = Shader(get_path("shader/light.vert").c_str(), 
        get_path("shader/light.frag").c_str());
    light_shader.use();
    unsigned int model_loc_light = glGetUniformLocation(light_shader.ID, "model");
    unsigned int view_loc_light = glGetUniformLocation(light_shader.ID, "view");
    unsigned int proj_loc_light = glGetUniformLocation(light_shader.ID, "proj");
    light_color_loc = glGetUniformLocation(light_shader.ID, "light_color");
    glUniform3f(light_color_loc, light_color.x, light_color.y, light_color.z);

    unsigned int VAO, EBO, VBO;
    create_vertex_data(&VAO, &EBO, &VBO);
    int angle = 0;
    
    glEnable(GL_DEPTH_TEST);

    // glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    // glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 camera_direction = glm::normalize(camera_pos - camera_target);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 camera_right = glm::normalize(glm::cross(up, camera_direction));
    // glm::vec3 camera_up = glm::normalize(glm::cross(camera_direction, camera_right));
    // glm::mat4 view = glm::lookAt(camera_pos, camera_target, up);

    const float radius = 10.0f;

    last_frame = glfwGetTime();
    camera_direction = glm::vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)),
        cos(glm::radians(pitch)) * sin(glm::radians(yaw)));
    while(!glfwWindowShouldClose(window))
    {
        delta_time = glfwGetTime() - last_frame;
        last_frame = glfwGetTime();

        process_input(window);
        
        // render
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        shader.use();
        float mixer = (sinf(glfwGetTime()) + 1) * 0.25;
        shader.setFloat("mixer", mixer);
        glUniform3f(camera_pos_loc, camera_pos.x, camera_pos.y, camera_pos.z);

        glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front,
            camera_up);
        view = glm::translate(view, glm::vec3(0, 0, -3));
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(45.0f), (float)window_w/window_h, 0.1f, 100.0f);
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[0]);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // draw light
        light_shader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[1]);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(model_loc_light, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_loc_light, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_loc_light, 1, GL_FALSE, glm::value_ptr(proj));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        // TODO 上面不是已经调用了process_input吗，为什么这里还需要pollEvents
        // 检测有没有触发什么事件(键盘输入、鼠标移动等)
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void load_texture(char* path, unsigned int* texture)
{

    int width, height, nrChannels;
    unsigned char* data = stbi_load(get_path(path).c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }
    glGenTextures(1, texture);
    std::cout << "texture : " << *texture << " width : " << width << " height : " << height << std::endl;
    // 就像其他对象一样，我们需要绑定它，让之后任何的纹理指令都可以配置当前绑定的纹理
    glBindTexture(GL_TEXTURE_2D, *texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    if (nrChannels == 3)
    {
        format = GL_RGB;
    }
    else
    {
        format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

unsigned int create_shader(const char* vertex, const char* fragment)
{
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex, NULL);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "[ERROR] vertex shader compile failed. " 
            << info_log << std::endl;
    }
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "[ERROR] fragment shader compile failed. " 
            << info_log << std::endl;
    }
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cout << "[ERROR] shader program linke failed. "
            << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

void create_vertex_data(unsigned int* VAO, unsigned int* EBO, unsigned int* VBO)
{
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void setup_opengl()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * move_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * move_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera_pos -= camera_front * move_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera_pos += camera_front * move_speed * delta_time;
    }
}

std::string get_path(std::string local)
{
    return pre_fix + local;
}


void dump(glm::vec4 vec)
{
    std::cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << std::endl;
}

void test_glm()
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0);
    // trans = glm::translate(trans, glm::vec3(1.0, 1.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    vec = trans * vec;
    dump(vec);
}


void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;
    last_x = xpos;
    last_y = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if(pitch > 89.0f)
    pitch =  89.0f;
    if(pitch < -89.0f)
    pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(direction);
}