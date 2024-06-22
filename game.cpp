#include "sfml.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(256, 240), "game");
  sf::Texture ballTexture;
    if (!ballTexture.loadFromFile("ball.png")) {
    window.close();
}
sf::Sprite ball;
ball.setTexture(ballTexture);

}
