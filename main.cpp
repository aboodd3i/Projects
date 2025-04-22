#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

void resetGame(Player& player, Enemy* enemies[], int& enemyCount, int& score, int& health) {
    player.reset();
    for (int i = 0; i < enemyCount; ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemyCount = 0;
    score = 0;
    health = 3;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter");
    window.setFramerateLimit(60);

    // Load background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/bg_star3.png")) {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }
    sf::Sprite bgSprite(bgTexture);
    sf::Sprite bgSprite2(bgTexture);
    bgSprite2.setPosition(0, -600);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/Orbitron/Orbitron-VariableFont_wght.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }
    //audio setup
    sf::SoundBuffer chicken_dyingbuffer;
    chicken_dyingbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/chicken_dying.wav");
    if (!chicken_dyingbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/chicken_dying.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound chicken_dying;
    chicken_dying.setBuffer(chicken_dyingbuffer);

    sf::SoundBuffer bulletbuffer;
    bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/bullet.wav");
    if (!bulletbuffer.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/bullet.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound bullet;
    bullet.setBuffer(bulletbuffer);


    // Score and UI
    int score = 0, health = 3;
    sf::Text scoreText, lifeText, gameOverText, finalScoreText, restartText, levelclearText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    lifeText.setFont(font);
    lifeText.setCharacterSize(20);
    lifeText.setFillColor(sf::Color::White);
    lifeText.setPosition(10, 40);

    levelclearText.setFont(font);
    levelclearText.setCharacterSize(48);
    levelclearText.setFillColor(sf::Color::Green);
    levelclearText.setString("LEVEL CLEARED");
    levelclearText.setPosition(250, 200);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(250, 200);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(28);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(250, 270);

    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setString("Press R to Restart");
    restartText.setPosition(250, 320);


    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("C:/Users/Choudry Shb/source/repos/Chicken_Invaders/assets/Hit Points.png")) {
        std::cout << "Failed to load heart image!" << std::endl;
        return -1;
    }
    sf::Sprite hearts[3];
    for (int i = 0; i < 3; ++i) {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.1f, 0.1f);
        hearts[i].setPosition(10 + i * 35, 70);
    }

    // Game entities
    Player player;
    Enemy* enemies[50];
    int enemyCount = 0;
    sf::Clock enemySpawnClock;

    bool isGameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                
                resetGame(player, enemies, enemyCount, score, health);
                isGameOver = false;
                enemySpawnClock.restart();
            }
        }

        // Check if player collides with any enemies
        for (int i = 0; i < enemyCount; ++i) {
            if (player.getBounds().intersects(enemies[i]->getBounds())) {
                health--;
                if (health == 0) {
                    isGameOver = true;
                }
                delete enemies[i];
                enemies[i] = enemies[enemyCount - 1];
                enemies[enemyCount - 1] = nullptr;
                enemyCount--;
            }
        }
        //check score
        if (score >= 100) {
            isGameOver = true;
            window.draw(levelclearText);
            window.draw(finalScoreText);
            window.draw(restartText);
            window.display();
        }

        // Collision: Player and enemy bullets
        
        for (int i = 0; i < enemyCount; ++i) {
            if (!enemies[i]) continue;

            Bullet** enemyBullets = enemies[i]->getBullets();
            for (int j = 0; j < 10; ++j) {
                if (!enemyBullets[j]) continue;

                if (player.getBounds().intersects(enemyBullets[j]->getBounds())) {
                    delete enemyBullets[j];

                    for (int k = j; k < 9; ++k) {
                        enemyBullets[k] = enemyBullets[k + 1];
                    }
                    enemyBullets[9] = nullptr;
                    health--;
                    
                    if (health <= 0) {
                        isGameOver = true;
                        finalScoreText.setString("Final Score: " + std::to_string(score));
                        window.draw(gameOverText);
                        window.draw(finalScoreText);
                        window.draw(restartText);
                        window.display();
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                            resetGame(player, enemies, enemyCount, score, health);
                            isGameOver = false;
                            enemySpawnClock.restart();

                        }


                    }
                    break;
                }
            }
        }




        if (!isGameOver) {
            // Player controls
            player.move();
            player.shoot();
            //bullet.play();
            player.updateBullets();

            // Spawn enemies
            if (enemySpawnClock.getElapsedTime().asSeconds() > 1.0f && enemyCount < 50) {
                float x = static_cast<float>(rand() % (window.getSize().x - 100));  // Safe X position
                float y = static_cast<float>(rand() % (window.getSize().y / 4));   // Y between 0 and 300
                enemies[enemyCount++] = new Enemy(x, y);
                enemySpawnClock.restart();
            }

            // Update and draw enemies
            for (int i = 0; i < enemyCount; ++i) {
                enemies[i]->update();
                enemies[i]->updateBullets();
                if (enemies[i]->isOffScreen()) {
                    delete enemies[i];
                    enemies[i] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                    i--;
                }
            }

            // Bullet-enemy collision
            
            for (int i = 0; i < player.getBulletCount(); ++i) {
                Bullet** bullets = player.getBullets();
                if (!bullets[i]) continue;
                for (int j = 0; j < enemyCount; ++j) {
                    if (enemies[j] && bullets[i]->getBounds().intersects(enemies[j]->getBounds())) {
                        player.removeBullet(i);
                        delete enemies[j];
                        chicken_dying.play();
                        enemies[j] = enemies[--enemyCount];
                        enemies[enemyCount] = nullptr;
                        score += 10;
                        i--;
                        break;
                    }
                }
            }

            // Enemy-player collision
            for (int i = 0; i < enemyCount; ++i) {
                if (player.getBounds().intersects(enemies[i]->getBounds())) {
                    health--;
                    if (health == 0)
                        isGameOver = true;
                    delete enemies[i];
                    enemies[i] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                    i--;
                }
            }
            // Move background downward
            bgSprite.move(0, 3);
            bgSprite2.move(0, 3);

            // Reset position when background moves off screen
            if (bgSprite.getPosition().y >= 600) {
                bgSprite.setPosition(0, -600);
            }
            if (bgSprite2.getPosition().y >= 600) {
                bgSprite2.setPosition(0, -600);
            }

            // Rendering
            window.clear();
            window.draw(bgSprite);
            window.draw(bgSprite2);

            player.draw(window);
            player.drawBullets(window);

            for (int i = 0; i < enemyCount; ++i) {
                enemies[i]->draw(window);
                enemies[i]->drawBullets(window);
            }

            for (int i = 0; i < health; ++i)
                window.draw(hearts[i]);

            scoreText.setString("Score: " + std::to_string(score));
            lifeText.setString("Lives: " + std::to_string(health));
            window.draw(scoreText);
            window.draw(lifeText);

            if (isGameOver) {
                finalScoreText.setString("Final Score: " + std::to_string(score));
                window.draw(gameOverText);
                window.draw(finalScoreText);
                window.draw(restartText);
            }

            window.display();
        }
    }

    return 0;
}
