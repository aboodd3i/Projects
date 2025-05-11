#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include <iostream>

class PirateChicken : public Enemy {
private:
    int hitPoints;

public:
    PirateChicken(float x, float y) : Enemy(x, y), hitPoints(2) {
        if (!texture.loadFromFile("D:/My Documents/OOP/Project/images/piratechicken.png")) {
            std::cout << "Failed to load enemy image!" << std::endl;
        }

    }

    //checking for collision with a bullet
    bool takeHit() {
        hitPoints--;
        return hitPoints <= 0; // true when 2 bullets are hit
    }
};
