#include "Grid.hpp"

int main()
{
    sf::RenderWindow window (sf::VideoMode (1280, 720), "Temporary title");
    window.setFramerateLimit (1000);

    sf::Event ev;

    Grid grid (64, 36);

    while (window.isOpen () && grid.isAlive())
    {
        while (window.pollEvent (ev))
        {
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                window.close ();
            else if (ev.type == sf::Event::Closed)
                window.close ();
        }

        grid.updateSnake();
        grid.updateVertexArray();

        window.clear (sf::Color (120, 120, 120));
        window.draw (grid);
        window.display ();
    }
    std::cout << grid.score << " " << grid.moves;

    return 0;
}
