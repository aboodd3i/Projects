#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    Bullet* bullets[50];
    int bulletCount;
    sf::Clock shootTimer;

public:
    Player() {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/Spacecraft.png")) {
            std::cout << "Failed to load player texture!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.23f, 0.23f);
        sprite.setPosition(400, 500);

        bulletCount = 0;
        for (int i = 0; i < 50; ++i) bullets[i] = nullptr;
    }

    void move() {
        float speed = 5.0f;

        // Move left (Left Arrow or A)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            && sprite.getPosition().x > 0)
            sprite.move(-speed, 0);

        // Move right (Right Arrow or D)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            && sprite.getPosition().x + sprite.getGlobalBounds().width < 800)
            sprite.move(speed, 0);

        // Move up (Up Arrow or W)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            && sprite.getPosition().y > 0)
            sprite.move(0, -speed);

        // Move down (Down Arrow or S)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            && sprite.getPosition().y + sprite.getGlobalBounds().height < 600)
            sprite.move(0, speed);
    }



    void shoot() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && shootTimer.getElapsedTime().asSeconds() > 0.5f && bulletCount < 50) {
            bullets[bulletCount++] = new Bullet(sprite.getPosition().x + 35, sprite.getPosition().y - 20, "C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/Fire Bullet.png", 7.0f);
            /*sf::SoundBuffer bulletbuffer;
            bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/bullet.wav");
            if (!bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/bullet.wav")) {
                std::cout << "Failed to load sound!" << std::endl;
                return -1;
            }
            sf::Sound bullet;
            bullet.setBuffer(bulletbuffer);
            bullet.play();*/
            shootTimer.restart();
        }
    }

    void updateBullets() {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i]) {
                bullets[i]->update();
                if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0) {
                    delete bullets[i];
                    bullets[i] = bullets[bulletCount - 1];
                    bullets[bulletCount - 1] = nullptr;
                    bulletCount--;
                    i--;
                }
            }
        }
    }

    void drawBullets(sf::RenderWindow& window) {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i]) {
                bullets[i]->draw(window);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();  // Returns the player's bounding box
    }


    Bullet** getBullets() {
        return bullets;
    }

    int getBulletCount() const {
        return bulletCount;
    }

    void removeBullet(int index) {
        if (index >= 0 && index < bulletCount && bullets[index]) {
            delete bullets[index];
            bullets[index] = bullets[bulletCount - 1];
            bullets[bulletCount - 1] = nullptr;
            bulletCount--;
        }
    }

    void reset() {
        sprite.setPosition(400, 500);
        for (int i = 0; i < bulletCount; ++i) {
            delete bullets[i];
            bullets[i] = nullptr;
        }
        bulletCount = 0;
    }

    ~Player() {
        for (int i = 0; i < bulletCount; ++i) {
            delete bullets[i];
        }
    }
};
