//
// Created by pablo on 7/18/2023.
//

#ifndef CARTOGRAPHY_BUTTON_H
#define CARTOGRAPHY_BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>

class button {


private:
    sf::Texture text;
    sf::Vector2f scale;
    float xPos;
    float yPos;

    sf::Sprite sprite;
    float length;
    float width;

public:
    button( const sf::Texture text, const sf::Vector2f &scale, float xPos, float yPos);

    const sf::Sprite &getSprite() const;

    const sf::Texture &getText() const;

    float getXPos() const;

    float getYPos() const;

    float getLength() const;

    void setLength(float length);

    float getWidth() const;
};


#endif //CARTOGRAPHY_BUTTON_H
