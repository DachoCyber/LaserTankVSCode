#pragma once
#include <SFML/Graphics.hpp>
#include "direction.h"

class Bullet : public sf::Drawable {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    Direction dir;
    bool enemysBullet;

    Bullet() {
        shape.setSize(sf::Vector2f(0.f, 0.f));
        velocity = sf::Vector2f(0.f, 0.f);
        dir = UP;
    }

    Bullet(sf::Vector2f position, Direction dir) : dir(dir), enemysBullet(false) {
        switch(dir) {
            case RIGHT : case LEFT :
                shape.setSize(sf::Vector2f(20.f, 3.f));
                break;
            case UP : case DOWN:
                shape.setSize(sf::Vector2f(3.f, 20.f));
        }
        shape.setFillColor(sf::Color(159, 43, 104));
        shape.setOutlineThickness(1.f);
        shape.setPosition(position);
        setVelocity();
    }
    Bullet(sf::Vector2f position, Direction dir, bool enemysTank) : dir(dir), enemysBullet(true) {
        switch(dir) {
            case RIGHT : case LEFT :
                shape.setSize(sf::Vector2f(20.f, 3.f));
                break;
            case UP : case DOWN:
                shape.setSize(sf::Vector2f(3.f, 20.f));
        }
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineThickness(1.f);
        shape.setPosition(position);
        setVelocity();
    }

    void changeVelocity(Direction dir, int mirrorType) {
        switch(dir) {
            case RIGHT : case LEFT :
                shape.setSize(sf::Vector2f(20.f, 3.f));
                break;
            case UP : case DOWN:
                shape.setSize(sf::Vector2f(3.f, 20.f));
        }
        switch(dir) {
            case UP:
                velocity = sf::Vector2f(0.f, -1.f); dir = UP; break;
            case DOWN:
                velocity = sf::Vector2f(0.f, 1.f); dir = DOWN; break;
            case LEFT:
                velocity = sf::Vector2f(-1.f, 0.f); dir = LEFT;
                /*if(mirrorType == 1) {

                    shape.setPosition(sf::Vector2f(shape.getPosition().x - 10.f, shape.getPosition().y - 10.f));
                    
                }*/
                break;
            case RIGHT:
                velocity = sf::Vector2f(1.f, 0.f);
                dir = RIGHT;
                /*if(mirrorType == 1 || mirrorType == 3) {
                    shape.setPosition(sf::Vector2f(shape.getPosition().x + 10.f, shape.getPosition().y - 10.f));
                } */
                break;
        }
    }

    void setVelocity() {
        switch(dir) {
            case UP:
                velocity = sf::Vector2f(0.f, -1.f); break;
            case DOWN:
                velocity = sf::Vector2f(0.f, 1.f); break;
            case LEFT:
                velocity = sf::Vector2f(-1.f, 0.f); break;
            case RIGHT:
                velocity = sf::Vector2f(1.f, 0.f); break;
        }
    }
    void setTransparentColor() {
        shape.setFillColor(sf::Color(255, 0, 0, 0));
    }
    void returnOldColor() {
        shape.setFillColor(sf::Color::Red);
    }

    void update(sf::Time updateTime) {
        if(enemysBullet) {
            shape.move(velocity * static_cast<float>(updateTime.asMilliseconds()));
            
        }
        shape.move(velocity * static_cast<float>(updateTime.asMilliseconds()/1.5));
    
    }


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape);
    }

    sf::Vector2f getDimensions() const {
        return shape.getSize();
    }

    Direction getDirection() const {
        return dir;
    }

    void setPosition(float x, float y) { shape.setPosition(x, y); }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
};
