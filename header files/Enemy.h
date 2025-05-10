#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Enemy {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    Bullet* bullets[10];
    int bulletCount = 0;
    sf::Clock shootClock;

public:
    Enemy(float x, float y) {
        if (!texture.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/ChickenLevel2.png")) {
            std::cout << "Failed to load enemy image!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.15f, 0.15f);
        sprite.setPosition(x, y);

        for (int i = 0; i < 10; ++i)
            bullets[i] = nullptr;
    }

    void update() {
        sprite.move(3.0f, 2);

        // Automatic shooting
        if (shootClock.getElapsedTime().asSeconds() > 1.0f && bulletCount < 10) {
            shoot();
            shootClock.restart();
        }
    }

    void shoot() {
        sf::Vector2f pos = sprite.getPosition();
        bullets[bulletCount++] = new Bullet(pos.x + 20, pos.y + 40, "C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/Egg.png", 5.0f);
    }

    void updateBullets() {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i]) {
                bullets[i]->moveDown();
                if (bullets[i]->getPosition().y > 600) {
                    delete bullets[i];
                    for (int j = i; j < bulletCount - 1; ++j)
                        bullets[j] = bullets[j + 1];
                    bullets[--bulletCount] = nullptr;
                    --i;
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void drawBullets(sf::RenderWindow& window) {
        for (int i = 0; i < bulletCount; ++i) {
            if (bullets[i])
                bullets[i]->draw(window);
        }
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();  // Returns the enemy's bounding box
    }


    bool isOffScreen() const {
        return sprite.getPosition().y > 600;
    }
    Bullet** getBullets() {
        return bullets;
    }

    ~Enemy() {
        for (int i = 0; i < bulletCount; ++i)
            delete bullets[i];
    }
};
