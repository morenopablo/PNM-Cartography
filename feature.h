//
// Created by pablo on 6/6/2023.
//
#include <SFML/Graphics.hpp>
#ifndef CARTOGRAPHY_FEATURE_H
#define CARTOGRAPHY_FEATURE_H


class feature {
public:
    explicit feature(const sf::CircleShape &point, bool eraser);

    explicit feature(const sf::Sprite &sprite);

    void draw( sf::RenderWindow &window);
    bool isPoint;
    bool isErase;

     sf::Sprite &getSprite();

     sf::CircleShape &getPoint();

private:

    sf::CircleShape point;
    sf::Sprite sprite;

};



#endif //CARTOGRAPHY_FEATURE_H
