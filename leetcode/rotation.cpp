// sudo apt-get install libglfw3-dev libglm-dev
// g++ -std=c++11 -o leetcode.out rotation.cpp -lglfw -lGL -lGLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function to apply Euler rotations
glm::mat4 applyEulerRotation(float angleX, float angleY, float angleZ) {
    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X
    rotation = glm::rotate(rotation, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y
    rotation = glm::rotate(rotation, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z
    return rotation;
}

// Function to apply Quaternion rotation
glm::mat4 applyQuaternionRotation(float angle, glm::vec3 axis) {
    glm::quat quaternion = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    return glm::toMat4(quaternion);
}

// Render function to draw a simple cube
void renderCube() {
    glBegin(GL_QUADS);
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Other faces omitted for brevity...
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Rotation Demo", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
    float quaternionAngle = 0.0f;
    glm::vec3 quaternionAxis(0.0f, 1.0f, 0.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply Euler rotation (Intrinsic rotation)
        glm::mat4 model = applyEulerRotation(angleX, angleY, angleZ);

        // Apply quaternion rotation as well
        model = applyQuaternionRotation(quaternionAngle, quaternionAxis) * model;

        // Set up the view and projection matrices
        glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 10.0f);

        // Load combined transformation into OpenGL
        glm::mat4 mvp = projection * view * model;
        glLoadMatrixf(&mvp[0][0]);

        // Render the cube
        renderCube();

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Update angles for rotation (to make it dynamic)
        angleX += 0.5f;
        angleY += 0.3f;
        angleZ += 0.1f;
        quaternionAngle += 0.5f;
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
