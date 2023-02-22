#include "Screen.h"
int main()
{
    Screen* screen = new Screen("BombIT", anim::WIDTH, anim::HEIGHT + 36, "textures/mapa.png");
    sf::RenderWindow* window = &screen->_window();
    sf::Image icon;
    icon.loadFromFile("textures/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    float delta_time = 0.0f;
    sf::Clock clock;
    while (window->isOpen())
    {
        delta_time = clock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
 
        if(screen->get_running())
            screen->update(delta_time);
    }

    return 0;
}