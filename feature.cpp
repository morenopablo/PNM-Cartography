//
// Created by pablo on 6/6/2023.
//

#include "feature.h"
feature::feature(const sf::CircleShape &point,  bool eraser) {
    isPoint = true;
    this->point = point;
    this->isErase = eraser;
}

feature::feature(const sf::Sprite &sprite)  {
    isPoint = false;
    this->sprite =  sprite;
    this->isErase = false;
}

void feature::draw( sf::RenderWindow &window) {
    if(isPoint){
        window.draw(point);
    } else{
        window.draw(sprite);
    }
}

 sf::Sprite &feature::getSprite()  {
    return sprite;
}

 sf::CircleShape &feature::getPoint()  {
    return point;
}
