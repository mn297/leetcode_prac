// sudo apt-get install libsfml-dev
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>

// Shared variables for multithreaded access
std::atomic<float> circle_x(400.0f);
std::atomic<float> circle_y(300.0f);

// Function to update the circle position in a separate thread
void updatePosition()
{
    float speed_x = 0.1f;
    float speed_y = 0.1f;
    while (true)
    {
        // Update position
        circle_x += speed_x;
        circle_y += speed_y;

        // Bounce off the window edges (assumed window size: 800x600)
        if (circle_x >= 800.0f || circle_x <= 0.0f)
            speed_x = -speed_x;
        if (circle_y >= 600.0f || circle_y <= 0.0f)
            speed_y = -speed_y;

        // Sleep for a short duration to control the speed
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Multithreaded Graphics Demo");

    // Create a circle shape
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin(circle.getRadius(), circle.getRadius()); // Center the origin

    // Start the thread to update the circle's position
    std::thread position_thread(updatePosition);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update circle position based on shared variables
        circle.setPosition(circle_x, circle_y);

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the circle
        window.draw(circle);

        // Display the content drawn
        window.display();
    }

    // Join the thread before exiting
    if (position_thread.joinable())
    {
        position_thread.detach(); // Detach instead of join to allow graceful exit
    }

    return 0;
}
