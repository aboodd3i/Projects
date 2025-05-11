#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "PirateChicken.h"

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
    if (!bgTexture.loadFromFile("D:/My Documents/OOP/Project/images/bg.png")) {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }
    sf::Sprite bgSprite(bgTexture);
    sf::Sprite bgSprite2(bgTexture);
    bgSprite2.setPosition(0, -600);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }
    //audio setup
    sf::SoundBuffer chicken_dyingbuffer;
    chicken_dyingbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/Chicken_Dying.wav");
    if (!chicken_dyingbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/Chicken_Dying.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound chicken_dying;
    chicken_dying.setBuffer(chicken_dyingbuffer);

    sf::SoundBuffer egg_collisionbuffer;
    if (!egg_collisionbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/egg_collision.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound egg_collision;
    egg_collision.setBuffer(egg_collisionbuffer);


    sf::SoundBuffer backgroundbuffer;
    backgroundbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/background.wav");
    if (!backgroundbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/background.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound background;
    background.setBuffer(backgroundbuffer);

    sf::SoundBuffer background2buffer;
    if (!background2buffer.loadFromFile("D:/My Documents/OOP/Project/audio/background.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound background2;
    background2.setBuffer(backgroundbuffer);


    sf::SoundBuffer bulletbuffer;
    bulletbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/Bullet.wav");
    if (!bulletbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/Bullet.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound bullet;
    bullet.setBuffer(bulletbuffer);

    background.setLoop(true);
    background.play();
    background.setVolume(80);
    chicken_dying.setVolume(40);

    background2.setLoop(true);
    background2.play();
    background2.setVolume(80);

    sf::SoundBuffer transitionbuffer;
    transitionbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/transition.wav");
    if (!transitionbuffer.loadFromFile("D:/My Documents/OOP/Project/audio/transition.wav")) {
        std::cout << "Failed to load sound!" << std::endl;
        return -1;
    }
    sf::Sound transition;
    transition.setBuffer(transitionbuffer);



    sf::Clock transitionClock;
    float fadeAlpha = 0.0f;
    bool transitionSoundPlayed = false;

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
    levelclearText.setString("GAME CLEARED");
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
    if (!heartTexture.loadFromFile("D:/My Documents/OOP/Project/images/health.png")) {
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
    PirateChicken* pirateChickens[30];
    int pirateCount = 0;


    int enemyCount = 0;
    sf::Clock enemySpawnClock;
    sf::Clock pirateSpawnClock;
    bool isGameOver = false;


    enum GameState { LEVEL1, TRANSITION_TO_LEVEL2, LEVEL2 };
    GameState gameState = LEVEL1;
    sf::Clock deltaClock;




    while (window.isOpen()) {
        float backgroundScrollSpeed = 3.0f;
        float deltaTime = deltaClock.restart().asSeconds();

        if (gameState == LEVEL1) {

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    background.stop();
                    resetGame(player, enemies, enemyCount, score, health);
                    isGameOver = false;
                    enemySpawnClock.restart();
                }
            }


            // Check if player collides with any enemies
            for (int i = 0; i < enemyCount; ++i) {
                if (isGameOver) { break; }
                if (player.getBounds().intersects(enemies[i]->getBounds())) {
                    health--;
                    if (health == 0) {
                        background.stop();
                        isGameOver = true;
                    }
                    delete enemies[i];
                    enemies[i] = enemies[enemyCount - 1];
                    enemies[enemyCount - 1] = nullptr;
                    enemyCount--;
                }
            }
            //check score
            if (score >= 150) {
            
                background.stop();
                gameState = TRANSITION_TO_LEVEL2;
            }

            // Collision: Player and enemy bullets

            for (int i = 0; i < enemyCount; ++i) {
                if (!enemies[i]) continue;
                if (isGameOver) { break; }

                Bullet** enemyBullets = enemies[i]->getBullets();
                for (int j = 0; j < 10; ++j) {
                    if (isGameOver) { break; }
                    if (!enemyBullets[j]) continue;

                    if (player.getBounds().intersects(enemyBullets[j]->getBounds())) {
                        delete enemyBullets[j];

                        for (int k = j; k < 9; ++k) {
                            enemyBullets[k] = enemyBullets[k + 1];
                            if (isGameOver) { break; }
                        }
                        enemyBullets[9] = nullptr;
                        health--;

                        if (health <= 0) {
                            isGameOver = true;
                            background.stop();
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
                    if (isGameOver) { break; }
                    float x = static_cast<float>(rand() % (window.getSize().x - 100));  // Safe X position
                    float y = static_cast<float>(rand() % (window.getSize().y / 4));   // Y between 0 and 300
                    enemies[enemyCount++] = new Enemy(x, y);
                    enemySpawnClock.restart();
                }

                // Update and draw enemies
                for (int i = 0; i < enemyCount; ++i) {
                    if (isGameOver) { break; }
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
                    if (isGameOver) { break; }
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
                    if (isGameOver) { break; }
                    bgSprite.setPosition(0, -600);
                }
                if (bgSprite2.getPosition().y >= 600) {
                    if (isGameOver) { break; }
                    bgSprite2.setPosition(0, -600);
                }

                // Rendering
                window.clear();
                window.draw(bgSprite);
                window.draw(bgSprite2);

                player.draw(window);
                player.drawBullets(window);

                for (int i = 0; i < enemyCount; ++i) {
                    if (isGameOver) { break; }
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
        else if (gameState == TRANSITION_TO_LEVEL2) {
            if (!transitionSoundPlayed)
            {
                background.stop();
                transition.play();
                transitionSoundPlayed = true;
                transitionClock.restart();
            }

            backgroundScrollSpeed += 50.0f * deltaTime;

            // Scroll backgrounds
            bgSprite.move(0.0f, backgroundScrollSpeed * deltaTime);
            bgSprite2.move(0.0f, backgroundScrollSpeed * deltaTime);

            // If backgrounds move out of screen, reset (your original logic)
            if (bgSprite.getPosition().y >= 600)
            {
                bgSprite.setPosition(0.0f, bgSprite2.getPosition().y - bgSprite.getGlobalBounds().height);
            }
            if (bgSprite2.getPosition().y >= 600)
            {
                bgSprite2.setPosition(0.0f, bgSprite.getPosition().y - bgSprite2.getGlobalBounds().height);
            }

            // Move spaceship upward
            player.getSprite().move(0.0f, -300.0f * deltaTime);

            // After 2.5 seconds, start fade out
            if (transitionClock.getElapsedTime().asSeconds() > 2.5f)
            {
                fadeAlpha += 150.0f * deltaTime;
                if (fadeAlpha >= 255.0f)
                {
                    fadeAlpha = 255.0f;

                    // Transition complete
                    gameState = LEVEL2;

                    // Reset things
                    backgroundScrollSpeed = 5.0f;
                    player.getSprite().setPosition(400.0f, 500.0f); // (example start pos for Level 2)
                    //transitionSoundPlayed = false;
                    fadeAlpha = 0.0f;
                }
            }

            // Draw everything
            if (bgSprite.getPosition().y >= 600) bgSprite.setPosition(0, -600);
            if (bgSprite2.getPosition().y >= 600) bgSprite2.setPosition(0, -600);
            window.clear();
            window.draw(bgSprite);
            window.draw(bgSprite2);
            window.draw(player.getSprite());
            // (draw bullets or enemies if needed)

            // Fade-out black rectangle
            sf::RectangleShape fadeRect(sf::Vector2f(800, 600)); // your window size
            fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
            window.draw(fadeRect);

            window.display();
        }
        else if (gameState == LEVEL2) {
            window.clear();
            window.draw(bgSprite);
            window.draw(bgSprite2);
            background.play();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    background.stop();
                    resetGame(player, enemies, enemyCount, score, health);
                    isGameOver = false;
                    enemySpawnClock.restart();
                }
            }
            if (score >= 100) {
                isGameOver = true;
                window.draw(levelclearText);
                window.draw(finalScoreText);
                background.stop();
                window.display();
                window.close();
                
            }

            float bgHeight = bgSprite.getTexture()->getSize().y;

            // Scroll both sprites
            bgSprite.move(0, 3);
            bgSprite2.move(0, 3);

            // Reset position when a sprite moves off the bottom
            if (bgSprite.getPosition().y >= bgHeight) {
                bgSprite.setPosition(0, bgSprite2.getPosition().y - bgHeight);
            }
            if (bgSprite2.getPosition().y >= bgHeight) {
                bgSprite2.setPosition(0, bgSprite.getPosition().y - bgHeight);
            }


            player.draw(window);
            player.drawBullets(window);
            player.move();
            player.shoot();
            player.updateBullets();

            sf::Texture heartTexture;
            if (!heartTexture.loadFromFile("D:/My Documents/OOP/Project/images/health.png")) {
                std::cout << "Failed to load heart image!" << std::endl;
                return -1;
            }


            if (pirateSpawnClock.getElapsedTime().asSeconds() > 5.0f && pirateCount < 10) {
                pirateChickens[pirateCount++] = new PirateChicken(rand() % 700, -50);  // random x position
                pirateSpawnClock.restart();
            }
            for (int i = 0; i < pirateCount; ++i) {
                if (pirateChickens[i]) {
                    pirateChickens[i]->update();
                    pirateChickens[i]->draw(window);
                    pirateChickens[i]->updateBullets();
                    pirateChickens[i]->drawBullets(window);
                }
            }
            for (int i = 0; i < pirateCount; ++i) {
                if (!pirateChickens[i]) continue;

                for (int j = player.getBulletCount() - 1; j >= 0; --j) {
                    Bullet* b = player.getBullets()[j];
                    if (b && pirateChickens[i]->getBounds().intersects(b->getBounds())) {
                        if (pirateChickens[i]->takeHit()) {
                            chicken_dying.play();
                            score += 10;
                            scoreText.setString("Score: " + std::to_string(score));
                            window.draw(scoreText);
                            delete pirateChickens[i];
                            pirateChickens[i] = pirateChickens[--pirateCount];
                            pirateChickens[pirateCount] = nullptr;
                            --i; // re-check current index
                        }
                        player.removeBullet(j);
                        break;
                    }
                }
            }
            //enemy_bullet-player collision
            for (int i = 0; i < pirateCount; ++i) {
                if (!pirateChickens[i]) continue;
                if (isGameOver) { break; }

                Bullet** enemyBullets = pirateChickens[i]->getBullets();
                for (int j = 0; j < 10; ++j) {
                    if (isGameOver) { break; }
                    if (!enemyBullets[j]) continue;

                    if (player.getBounds().intersects(enemyBullets[j]->getBounds())) {
                        delete enemyBullets[j];

                        for (int k = j; k < 9; ++k) {
                            enemyBullets[k] = enemyBullets[k + 1];
                            if (isGameOver) { break; }
                        }
                        enemyBullets[9] = nullptr;
                        health--;
                        egg_collision.play();
                        if (health <= 0) {
                            isGameOver = true;
                            background.stop();
                            finalScoreText.setString("Final Score: " + std::to_string(score));
                            window.draw(gameOverText);
                            window.draw(finalScoreText);
                            window.draw(restartText);
                            window.display();
                            
                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed)
                                    window.close();
                                if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                                    background.stop();
                                    resetGame(player, enemies, enemyCount, score, health);
                                    isGameOver = false;
                                    enemySpawnClock.restart();
                                }
                            }
                        }
                        break;
                    }
                }
            }
            //enemy-player collision
            for (int i = 0; i < pirateCount; ++i) {
                if (isGameOver) { break; }
                if (player.getBounds().intersects(pirateChickens[i]->getBounds())) {
                    health--;
                    if (health == 0)
                        isGameOver = true;
                    delete pirateChickens[i];
                    pirateChickens[i] = pirateChickens[--pirateCount];
                    pirateChickens[pirateCount] = nullptr;
                    i--;
                }
            }


            for (int i = 0; i < 3; ++i) {
                hearts[i].setTexture(heartTexture);
                hearts[i].setScale(0.1f, 0.1f);
                hearts[i].setPosition(10 + i * 35, 70);
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
    for (int i = 0; i < enemyCount; ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemyCount = 0;
    return 0;
}
