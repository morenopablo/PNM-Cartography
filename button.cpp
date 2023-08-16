//
// Created by pablo on 7/18/2023.
//
#include <iostream>
#include "button.h"

button::button( const sf::Texture text, const sf::Vector2f &scale, float xPos, float yPos) : text(text), scale(scale),
                                                                                             xPos(xPos), yPos(yPos) {

    sprite.setTexture(this->text);
    sprite.setScale(this->scale);
    sprite.setPosition(this->xPos,this->yPos);
    length = (float)sprite.getTexture()->getSize().y*sprite.getScale().y;
     width = (float)sprite.getTexture()->getSize().x*sprite.getScale().x;
}

const sf::Sprite &button::getSprite() const {
    return sprite;
}

const sf::Texture &button::getText() const {
    return text;
}

float button::getXPos() const {
    return xPos;
}

float button::getYPos() const {
    return yPos;
}

float button::getLength() const {
    return length;
}

float button::getWidth() const {
    return width;
}

void button::setLength(float length) {
    button::length = length;
}
