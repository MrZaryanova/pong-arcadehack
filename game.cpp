#include "sfml.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(256, 240), "game");
  sf::Texture ballTexture;
    if (!ballTexture.loadFromFile("ball.png")) {
    window.close();
}
  sf::Sprite ball;
  ball.setTexture(ballTexture);
  ball.setPosition(sf::Vector2f(0,0));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Cyan);
      

        // start of frame
      
        window.draw(ball);


        // end of frame
        window.display();
    }

    return 0;


}
