#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "feature.h"
#include "button.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    bool eraser =false; //eraser setting
    int stamp = -1; //default sticker
    float radius = 10.f; //brush width
    int pointCount =30; // 50 sided circle
    int textSize = 35;
    int screenWidth = 2650;
    int screenHeight = 1900;

    //window info
    sf::Color background=sf::Color::White;//(250,249,246);
    sf::Color offWhite(250,249,246);
    sf::Color cream(239,226,209);
    sf::Color darkVanilla(209, 190, 157);
    sf::Color parchment(247,223, 178);
    sf::Color pink(234,205,196);
    sf::Color eraserColor(255,182,193);
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "PNM Cartography");
    //window.clear(sf::Color::White);
    sf::CircleShape shape(radius,pointCount);
    shape.setFillColor(sf::Color::Black);

    //size display
    sf::CircleShape shapeDisplay(radius,pointCount);
    shapeDisplay.setFillColor(sf::Color::Black);

    //vectors for strokes and redo
    vector<feature> lines;
    vector<feature> redo;

    //scale for stamps
    float scale =1.0;

    //textures
    vector<sf::Texture> stamps;
    sf::Texture castle1;
    castle1.loadFromFile("FairyTaleCastle2.png");
    stamps.push_back(castle1);

    sf::Texture castle2;
    castle2.loadFromFile("Castle2.png");
    stamps.push_back(castle2);

    sf::Texture mount1;
    mount1.loadFromFile("mountains2.png");
    stamps.push_back(mount1);

    sf::Texture mount2;
    mount2.loadFromFile("mount3.png");
    stamps.push_back(mount2);

    sf::Texture mount3;
    mount3.loadFromFile("mount4.png");
    stamps.push_back(mount3);

    sf::Texture dunes1;
    dunes1.loadFromFile("dunes.png");
    stamps.push_back(dunes1);

    sf::Texture trees1;
    trees1.loadFromFile("trees1.png");
    stamps.push_back(trees1);

    sf::Texture trees2;
    trees2.loadFromFile("trees2.png");
    stamps.push_back(trees2);

    sf::Texture compass;
    compass.loadFromFile("Compass.png");
    stamps.push_back(compass);

    float spacer =5;
    //size control
    sf::Texture upArrowTexture;
    upArrowTexture.loadFromFile("upArrow.jpg");

    button upArrow(upArrowTexture,sf::Vector2f(0.3f, 0.28f),0,0);
    upArrow.setLength(upArrow.getLength()+35);

    sf::Texture downArrowTexture;
    downArrowTexture.loadFromFile("downArrow.jpg");
    button downArrow ( downArrowTexture, sf::Vector2f(0.3f, 0.275f), upArrow.getXPos()+upArrow.getWidth() +spacer, 0);

    //undo/redo buttons
    sf::Texture undoTexture;
    undoTexture.loadFromFile("undo.jpg");
    button undo(undoTexture,sf::Vector2f(0.3f, 0.275f),downArrow.getXPos()+downArrow.getWidth()+spacer,0);

    sf::Texture redoTexture;
    redoTexture.loadFromFile("redo.jpg");
    button redoS(redoTexture,sf::Vector2f(0.3f, 0.275f),undo.getXPos()+undo.getWidth()+spacer,0);

    button brushUp (upArrowTexture,sf::Vector2f(0.3f, 0.28f),redoS.getXPos()+redoS.getWidth()+spacer,0);
    button brushDown (downArrowTexture,sf::Vector2f(0.3f, 0.275f),brushUp.getXPos()+brushUp.getWidth()+spacer,0);

    sf::Texture blankTexture;
    blankTexture.loadFromFile("blankIcon.jpg");
    button blank (blankTexture,sf::Vector2f(0.3f, 0.275f),brushDown.getXPos()+brushDown.getWidth()+spacer,0);

    sf::Texture eraserTexture;
    eraserTexture.loadFromFile("eraser.jpg");
    button eraserButton (eraserTexture,sf::Vector2f(0.3f, 0.275f), blank.getXPos() +blank.getWidth() + spacer, 0);

    sf::Texture brushTexture;
    brushTexture.loadFromFile("brush.jpg");
    button brush (brushTexture, sf::Vector2f(0.3f, 0.275f), eraserButton.getXPos() + eraserButton.getWidth() + spacer,0);

    //sf::CircleShape color1(30,4);
    sf::RectangleShape color1;
    color1.setSize(sf::Vector2f(40,40));
    color1.setFillColor(sf::Color::White);
    color1.setOutlineColor(sf::Color::Black);
    color1.setOutlineThickness(10);
    color1.setPosition(brush.getXPos()+brush.getWidth()+30,upArrow.getLength()/2-color1.getSize().y/2-20);

    sf::RectangleShape color2;
    color2.setSize(sf::Vector2f(40,40));
    color2.setFillColor(offWhite);
    color2.setOutlineColor(sf::Color::Black);
    color2.setOutlineThickness(10);
    color2.setPosition(color1.getPosition().x+ color1.getSize().x +30,upArrow.getLength()/2-color1.getSize().y/2-20);

    sf::RectangleShape color3;
    color3.setSize(sf::Vector2f(40,40));
    color3.setFillColor(cream);
    color3.setOutlineColor(sf::Color::Black);
    color3.setOutlineThickness(10);
    color3.setPosition(color2.getPosition().x+ color2.getSize().x +30,upArrow.getLength()/2-color1.getSize().y/2-20);

    sf::RectangleShape color4;
    color4.setSize(sf::Vector2f(40,40));
    color4.setFillColor(parchment);
    color4.setOutlineColor(sf::Color::Black);
    color4.setOutlineThickness(10);
    color4.setPosition(color3.getPosition().x+ color3.getSize().x +30,upArrow.getLength()/2-color1.getSize().y/2-20);

//    sf::RectangleShape color5;
//    color5.setSize(sf::Vector2f(40,40));
//    color5.setFillColor(sf::Color::Transparent);
//    color5.setOutlineColor(sf::Color::Black);
//    color5.setOutlineThickness(10);
//    color5.setPosition(color4.getPosition().x+ color4.getSize().x +30,upArrow.getLength()/2-color1.getSize().y/2-20);
//
//    sf::RectangleShape color6;
//    color6.setSize(sf::Vector2f(40,40));
//    color6.setFillColor(sf::Color::Transparent);
//    color6.setOutlineColor(sf::Color::Black);
//    color6.setOutlineThickness(10);
//    color6.setPosition(color5.getPosition().x+ color5.getSize().x +30,upArrow.getLength()/2-color1.getSize().y/2-20);

    //castle button
    sf::Sprite text0;
    text0.setTexture(castle1);
    text0.setScale(sf::Vector2f(0.2f, 0.2f));
    text0.setPosition(0,upArrow.getLength());
    float length0 = (float)text0.getTexture()->getSize().y*text0.getScale().y;
    float width0 = (float)text0.getTexture()->getSize().x*text0.getScale().x;


    //castle2 button
    sf::Sprite text1;
    text1.setTexture(castle2);
    text1.setScale(sf::Vector2f(0.15f, 0.15f));
    text1.setPosition(0,upArrow.getLength()+length0);
    float length1 = (float)text1.getTexture()->getSize().y*text1.getScale().y;
    float width1 = (float)text1.getTexture()->getSize().x*text1.getScale().x;

    //mountain1 button
    sf::Sprite text2;
    text2.setTexture(mount1);
    text2.setScale(sf::Vector2f(0.15f, 0.15f));
    text2.setPosition(0,upArrow.getLength()+length0+length1);
    float length2 = (float)text2.getTexture()->getSize().y*text2.getScale().y;
    float width2 = (float)text2.getTexture()->getSize().x*text2.getScale().x;

    //mountain2 button
    sf::Sprite text3;
    text3.setTexture(mount2);
    text3.setScale(sf::Vector2f(0.25f, 0.25f));
    text3.setPosition(0,upArrow.getLength()+length0+length1+length2);
    float length3 = (float)text3.getTexture()->getSize().y*text3.getScale().y;
    float width3 = (float)text3.getTexture()->getSize().x*text3.getScale().x;

    //mountain3 button
    sf::Sprite text4;
    text4.setTexture(mount3);
    text4.setScale(sf::Vector2f(0.15f, 0.15f));
    text4.setPosition(0,upArrow.getLength()+length0+length1+length2+length3);
    float length4 = (float)text4.getTexture()->getSize().y*text4.getScale().y;
    float width4 = (float)text4.getTexture()->getSize().x*text4.getScale().x;

    //dunes button
    sf::Sprite text5;
    text5.setTexture(dunes1);
    text5.setScale(sf::Vector2f(0.15f, 0.15f));
    text5.setPosition(0,upArrow.getLength()+length0+length1+length2+length3+length4);
    float length5 = (float)text5.getTexture()->getSize().y*text5.getScale().y;
    float width5 = (float)text5.getTexture()->getSize().x*text5.getScale().x;

    //trees1 button
    sf::Sprite text6;
    text6.setTexture(trees1);
    text6.setScale(sf::Vector2f(0.1f, 0.1f));
    text6.setPosition(0,upArrow.getLength()+length0+length1+length2+length3+length4+length5);
    float length6 = (float)text6.getTexture()->getSize().y*text6.getScale().y;
    float width6 = (float)text6.getTexture()->getSize().x*text6.getScale().x;

    //trees2 button
    sf::Sprite text7;
    text7.setTexture(trees2);
    text7.setScale(sf::Vector2f(0.1f, 0.1f));
    text7.setPosition(0,upArrow.getLength()+length0+length1+length2+length3+length4+length5+length6);
    float length7 = (float)text7.getTexture()->getSize().y*text7.getScale().y;
    float width7 = (float)text7.getTexture()->getSize().x*text7.getScale().x;

    //compass button
    sf::Sprite text8;
    text8.setTexture(compass);
    text8.setScale(sf::Vector2f(0.23f, 0.23f));
    text8.setPosition(0,upArrow.getLength()+length0+length1+length2+length3+length4+length5+length6+length7);
    float length8 = (float)text8.getTexture()->getSize().y*text8.getScale().y;
    float width8 = (float)text8.getTexture()->getSize().x*text8.getScale().x;

    //stamp border
    float borderPos= upArrow.getWidth()+downArrow.getWidth()+5;
    vector<sf::CircleShape> borderline;
    for(int i =(int)upArrow.getLength(); i< window.getSize().y;i++){
        sf::CircleShape pix(2,4);
        pix.setPosition(borderPos-1,(float)i);
        pix.setFillColor(sf::Color::Black);
        borderline.push_back(pix);
    }

    float topBorderPos= upArrow.getLength();
    vector<sf::CircleShape> topBorderline;
    for(int i =0; i< window.getSize().x;i++){
        sf::CircleShape pix(2,4);
        pix.setPosition(float (i),topBorderPos-1);
        pix.setFillColor(sf::Color::Black);
        topBorderline.push_back(pix);
    }

    sf::RectangleShape menu(sf::Vector2f(borderPos,(float)screenHeight));
    sf::RectangleShape topBar(sf::Vector2f((float)screenWidth,upArrow.getLength()));
    sf::Color menuColor(176,196,232);
    sf::Color topmenuColor(230,238,255);
    menu.setFillColor(topmenuColor);
    topBar.setFillColor(topmenuColor);




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //}




            window.clear(background);

            //draw features this early for erase
            for (feature i: lines) {
                // i.draw(window);
                if(!i.isPoint){
                    i.getSprite().setColor(background);
                } else if(i.isErase) {
                    i.getPoint().setFillColor(background);
                }
                i.draw(window);
            }


            //select background color
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color1.getPosition().x && (float)sf::Mouse::getPosition(window).x<color1.getPosition().x+color1.getSize().x
            && (float)sf::Mouse::getPosition(window).y>color1.getPosition().y && (float)sf::Mouse::getPosition(window).y<color1.getPosition().y + color1.getSize().y) {
                background = color1.getFillColor();

            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color2.getPosition().x && (float)sf::Mouse::getPosition(window).x<color2.getPosition().x+color2.getSize().x
            && (float)sf::Mouse::getPosition(window).y>color2.getPosition().y && (float)sf::Mouse::getPosition(window).y<color2.getPosition().y + color2.getSize().y) {
                background = color2.getFillColor();

            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color3.getPosition().x && (float)sf::Mouse::getPosition(window).x<color3.getPosition().x+color3.getSize().x
                       && (float)sf::Mouse::getPosition(window).y>color3.getPosition().y && (float)sf::Mouse::getPosition(window).y<color3.getPosition().y + color3.getSize().y) {
                background = color3.getFillColor();

            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color4.getPosition().x && (float)sf::Mouse::getPosition(window).x<color4.getPosition().x+color4.getSize().x
                      && (float)sf::Mouse::getPosition(window).y>color4.getPosition().y && (float)sf::Mouse::getPosition(window).y<color4.getPosition().y + color4.getSize().y) {
                background = color4.getFillColor();
            } //else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color5.getPosition().x && (float)sf::Mouse::getPosition(window).x<color5.getPosition().x+color5.getSize().x
//                       && (float)sf::Mouse::getPosition(window).y>color5.getPosition().y && (float)sf::Mouse::getPosition(window).y<color5.getPosition().y + color5.getSize().y) {
//                background = color5.getFillColor();
//
//            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x>color6.getPosition().x && (float)sf::Mouse::getPosition(window).x<color6.getPosition().x+color6.getSize().x
//                      && (float)sf::Mouse::getPosition(window).y>color6.getPosition().y && (float)sf::Mouse::getPosition(window).y<color6.getPosition().y + color6.getSize().y) {
//                background = color6.getFillColor();
//            }


            //selecting stamps
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && (float)sf::Mouse::getPosition(window).x<borderPos) {
                if((float)sf::Mouse::getPosition(window).y<=upArrow.getLength() -35 && (float)sf::Mouse::getPosition(window).x<=upArrow.getWidth()) {
                    //35 pixel gap between button and canvas
                    scale+=0.1;
               } else if((float)sf::Mouse::getPosition(window).y<=upArrow.getLength() -35 && (float)sf::Mouse::getPosition(window).x>=upArrow.getWidth()){
                 if(scale>0.1) {
                     scale -= 0.1;
                 }
               } else if((float)sf::Mouse::getPosition(window).y<=length0+upArrow.getLength()) {
                   stamp = 0;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+upArrow.getLength()){
                   stamp =1;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+upArrow.getLength()){
                   stamp =2;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+upArrow.getLength()){
                   stamp =3;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+length4+upArrow.getLength()){
                   stamp =4;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+length4+length5+upArrow.getLength()){
                   stamp =5;
                } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+length4+length5+length6+upArrow.getLength()){
                   stamp =6;
               } else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+length4+length5+length6+length7+upArrow.getLength()){
                   stamp =7;
               }  else if((float)sf::Mouse::getPosition(window).y>length0 && (float)sf::Mouse::getPosition(window).y<length1+length0+length2+length3+length4+length5+length6+length7+length8+upArrow.getLength()){
                   stamp =8;
               }
            }

            //drawing
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !eraser && (float)sf::Mouse::getPosition(window).x>borderPos && (float)sf::Mouse::getPosition(window).y>topBorderPos) {
                redo.clear();
                sf::CircleShape point(radius, pointCount);
                point.setFillColor(sf::Color::Black);
                point.setPosition((float)sf::Mouse::getPosition(window).x - radius, (float)sf::Mouse::getPosition(window).y - radius);
                feature f(point, false);
                lines.push_back(f);
            }

            //erase
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && eraser && (float)sf::Mouse::getPosition(window).x>borderPos && (float)sf::Mouse::getPosition(window).y>topBorderPos) {

                sf::CircleShape point(radius, pointCount);
                point.setFillColor(background);
                point.setPosition((float)sf::Mouse::getPosition(window).x - radius, (float)sf::Mouse::getPosition(window).y - radius);
                feature f(point, true);
                lines.push_back(f);
            }


            //undo
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> upArrow.getWidth()+spacer + downArrow.getWidth() + spacer +1  && (float)sf::Mouse::getPosition(window).x< upArrow.getWidth()+spacer + downArrow.getWidth() + spacer +1 +undo.getWidth() && (float)sf::Mouse::getPosition(window).y<undo.getLength())) {
                if (!lines.empty()) {
                    redo.push_back(lines[lines.size() - 1]);
                    lines.erase(lines.end() - 1);
                }
            }

            //redo
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Y)
            || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> upArrow.getWidth()+spacer + downArrow.getWidth() + spacer +1 +undo.getWidth() + spacer && (float)sf::Mouse::getPosition(window).x< upArrow.getWidth()+spacer + downArrow.getWidth() + spacer +1 +undo.getWidth() +spacer +redoS.getWidth() && (float)sf::Mouse::getPosition(window).y<redoS.getLength())) {
                if (!redo.empty()) {
                    lines.push_back(redo[redo.size() - 1]);
                    redo.erase(redo.end() - 1);
                }
            }


            //arrow mouse control
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                //radius += 0.25;
                sf::Vector2<int> pos((int)sf::Mouse::getPosition(window).x,(int)sf::Mouse::getPosition(window).y-1);
                sf::Mouse::setPosition(pos,window);

            }
            //down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                sf::Vector2<int> pos((int)sf::Mouse::getPosition(window).x,(int)sf::Mouse::getPosition(window).y+1);
                sf::Mouse::setPosition(pos,window);
            }
            //left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //radius += 0.25;
                sf::Vector2<int> pos((int)sf::Mouse::getPosition(window).x-1,(int)sf::Mouse::getPosition(window).y);
                sf::Mouse::setPosition(pos,window);

            }
            //right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
                sf::Vector2<int> pos((int)sf::Mouse::getPosition(window).x+1,(int)sf::Mouse::getPosition(window).y);
                sf::Mouse::setPosition(pos,window);
            }

            // size control
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
            || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> brushUp.getXPos() && (float)sf::Mouse::getPosition(window).x<brushUp.getXPos()+brushUp.getWidth() && (float)sf::Mouse::getPosition(window).y<brushUp.getLength())) {
                if(radius <60) {
                    radius += 0.25;
                }

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> brushDown.getXPos() && (float)sf::Mouse::getPosition(window).x<brushDown.getXPos()+brushDown.getWidth() && (float)sf::Mouse::getPosition(window).y<brushDown.getLength())) {
                if (radius > 1) {
                    radius -= 0.25;
                }
            }

            //size display
            shapeDisplay.setRadius(radius);
            shapeDisplay.setPosition(blank.getXPos()+blank.getWidth()/2-radius,blank.getLength()/2-radius);

            //eraser toggle
            if (eraser && (sf::Keyboard::isKeyPressed(sf::Keyboard::B)||
                (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> brush.getXPos() && (float)sf::Mouse::getPosition(window).x<brush.getXPos()+brush.getWidth() && (float)sf::Mouse::getPosition(window).y<brush.getLength()))) {
                eraser = false;
                shape.setFillColor(sf::Color::Black);
                shapeDisplay.setFillColor(sf::Color::Black);
            }
            if (!eraser && (sf::Keyboard::isKeyPressed(sf::Keyboard::E)||
            (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (float)sf::Mouse::getPosition(window).x> eraserButton.getXPos() && (float)sf::Mouse::getPosition(window).x<eraserButton.getXPos()+eraserButton.getWidth() && (float)sf::Mouse::getPosition(window).y<eraserButton.getLength()))) {
                eraser = true;
                shape.setFillColor(eraserColor);
                shapeDisplay.setFillColor(eraserColor);
            }




            //stampClick
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right) &&  (float)sf::Mouse::getPosition(window).x > borderPos && (float)sf::Mouse::getPosition(window).y>topBorderPos){

                if(stamp != -1) {

                    sf::Sprite sprite;
                    sprite.setTexture(stamps[stamp]);
                    //cout << stamp << endl;

                    //size
                    if (stamp == 0) { //castle size
                        sprite.setScale(sf::Vector2f(0.2f*scale, 0.2f*scale));
                    } else if (stamp == 1) { //mountain size
                        sprite.setScale(sf::Vector2f(0.15f*scale, 0.15f*scale));
                    } else if (stamp == 2) {
                        sprite.setScale(sf::Vector2f(0.15f*scale, 0.15f*scale));
                    } else if (stamp == 3) {
                        sprite.setScale(sf::Vector2f(0.25f*scale, 0.25f*scale));
                    } else if (stamp == 4) {
                        sprite.setScale(sf::Vector2f(0.17f*scale, 0.17f*scale));
                    } else if (stamp == 5) {
                        sprite.setScale(sf::Vector2f(0.15f*scale, 0.15f*scale));
                    } else if (stamp == 6) {
                        sprite.setScale(sf::Vector2f(0.1f*scale, 0.1f*scale));
                    } else if (stamp == 7) {
                        sprite.setScale(sf::Vector2f(0.1f*scale, 0.1f*scale));
                    } else if (stamp == 8) {
                        sprite.setScale(sf::Vector2f(0.23f*scale, 0.23f*scale));
                    }

                    float length = (float)sprite.getTexture()->getSize().y * sprite.getScale().y;
                    float width = (float)sprite.getTexture()->getSize().x * sprite.getScale().x;
                    sprite.setPosition((float)sf::Mouse::getPosition(window).x - width / 2,
                                       (float)sf::Mouse::getPosition(window).y - length / 2);
                    sprite.setColor(background);
                    feature f(sprite);
                    lines.push_back(f);
                }

            }

            //consider having relative to desktop
            if((float)sf::Mouse::getPosition(window).x>borderPos && (float)sf::Mouse::getPosition(window).y>topBorderPos) {
                shape.setPosition((float)sf::Mouse::getPosition(window).x - radius, (float)sf::Mouse::getPosition(window).y - radius);
                shape.setRadius(radius);
                window.draw(shape);

            }
            //at end so cant be erased
            //draw menu color
            window.draw(menu);
            window.draw(topBar);

            for (sf::CircleShape &i: borderline) {
                window.draw(i);
            }
            for (sf::CircleShape &i: topBorderline) {
                window.draw(i);
            }


            //stamp menu- cant be erased
            window.draw(upArrow.getSprite());
            window.draw(downArrow.getSprite());
            window.draw(undo.getSprite());
            window.draw(redoS.getSprite());
            window.draw(brushUp.getSprite());
            window.draw(brushDown.getSprite());
            window.draw(blank.getSprite());
            window.draw(shapeDisplay);
            window.draw(eraserButton.getSprite());
            window.draw(brush.getSprite());
            window.draw(color1);
            window.draw(color2);
            window.draw(color3);
            window.draw(color4);
//            window.draw(color5);
//            window.draw(color6);
            window.draw(text0);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.draw(text5);
            window.draw(text6);
            window.draw(text7);
            window.draw(text8);

            //scale size
            stringstream stream;

            stream << fixed << setprecision(0) << scale * 100;
            string s =stream.str();
            sf::Font font;
            font.loadFromFile("OpenSans-Semibold.ttf"); // font file downloaded from Apache
            sf::Text text;
            text.setString("Stamp Scale: " + s +"%" );
            text.setCharacterSize(31);
            text.setFont(font);
            text.setFillColor(sf::Color::Black);
            text.setPosition(13,upArrow.getLength()-38); //length1+length0+length2+length3+length4+length5+length6+length7+length8+lengthA);
            window.draw(text);

            //brush Size
            stringstream brushStream;
            brushStream << fixed << setprecision(2) << radius;
             s =brushStream.str();
            sf::Text brushText;
            brushText.setString("Brush Size: " + s );
            brushText.setCharacterSize(31);
            brushText.setFont(font);
            brushText.setFillColor(sf::Color::Black);
            brushText.setPosition(brushUp.getXPos()+brushUp.getWidth()/2+15,brushUp.getLength());
            window.draw(brushText);

            //undo text
            sf::Text undoText;
            undoText.setString("Undo");
            undoText.setCharacterSize(31);
            undoText.setFont(font);
            undoText.setFillColor(sf::Color::Black);
            undoText.setPosition(undo.getXPos() + undo.getWidth()/4,undo.getLength());
            window.draw(undoText);

            //redo text
            sf::Text redoText;
            redoText.setString("Redo");
            redoText.setCharacterSize(31);
            redoText.setFont(font);
            redoText.setFillColor(sf::Color::Black);
            redoText.setPosition(redoS.getXPos() + redoS.getWidth()/4,redoS.getLength());
            window.draw(redoText);


            //eraser text
            sf::Text eraserText;
            eraserText.setString("Erase");
            eraserText.setCharacterSize(31);
            eraserText.setFont(font);
            eraserText.setFillColor(sf::Color::Black);
            eraserText.setPosition(eraserButton.getXPos() + eraserButton.getWidth()/4,eraserButton.getLength());
            window.draw(eraserText);


            //draw text
            sf::Text drawText;
            drawText.setString("Draw");
            drawText.setCharacterSize(31);
            drawText.setFont(font);
            drawText.setFillColor(sf::Color::Black);
            drawText.setPosition(brush.getXPos() + brush.getWidth()/4,brush.getLength());
            window.draw(drawText);




            window.display();

        }
    }
    return 0;
}
