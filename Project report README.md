# 1. Executive Summary
#• Overview
#Our project, Chicken Invasion, is a 2D space shooter game developed using C++ and SFML. The objective is to dodge falling eggs and shoot #enemy spaceships. The game implements core OOP concepts including encapsulation, inheritance, polymorphism, and abstraction. It includes #game objects like the player, enemies, bullets, eggs, and hearts, each with distinct behaviors and interactions.
#• Key Findings
#We successfully developed a fully playable game with responsive controls, dynamic spawning, real-time collision detection, and a user-#friendly interface. The implementation demonstrates a strong object-oriented design with well-separated classes and logical structure.
________________________________________









#2. Introduction
#• Background
#In OOP, managing interactions between entities through objects and classes helps build scalable and maintainable software. This project #explores the application of these principles through game development. A space shooter game provides a rich scenario to explore concepts #like inheritance (for bullets, enemies), encapsulation (private class members), and polymorphism (object behaviors).
#• Project Objectives
#•	Create a 2D space game using C++ and SFML.
•	Implement object-oriented design principles to structure game logic.
•	Apply collision detection, score management, and UI rendering.
•	Demonstrate teamwork, planning, and programming skills.
________________________________________














3. Project Description
• Scope
Included:
•	Player movement & shooting
•	Enemy ship spawning
•	Falling enemy eggs
•	Heart-based health
•	Collision detection
•	Game over screen
•	Score tracking
•	Level 2: 3 enemy waves (Meteors, Old Ones, Pirate Chickens – 2 hits)
•	Level 2: 250 points to win
Excluded:
•	Multiple levels or power-ups
•	Enemy shooting
•	Background music/sound effects (optional for future updates)
• Technical Overview
Tools Used:
•	Microsoft Visual Studio 2022
•	SFML 2.6.2 (Simple and Fast Multimedia Library)
•	C++ Language
________________________________________






4. Methodology
• Approach
We followed an agile, task-based approach with weekly goals. Initially, we brainstormed the game idea, identified required classes and interactions, then divided the development into sprints (e.g., player controls, enemies, bullets, collisions).
•	Team Responsibilities:
o	Muhammad Abdullah: Prepared the enemy.h file
o	Saad Sohail: Prepared main.cpp file
o	Hamza Farhan: Prepared the player.h file
o	Rayyan Ahmer: Prepared the bullet.h file and gathered resources
________________________________________
















5. Project Implementation
• Design and Structure
•	The main game window is organized with a fixed resolution.
•	Game objects are rendered through SFML's graphics module.
•	Object classes include Player, Bullet, Enemy, Egg, and Heart.
•	Assets (textures, fonts) are loaded via external files.
• Functionalities Developed
•	Player Movement & Shooting: Responsive controls using arrow keys and spacebar.
•	Enemy Spawning: Enemies appear at the top and move randomly.
•	Egg Dropping: Enemies drop eggs at random intervals.
•	Collision Detection: Eggs hit the player; bullets hit enemies.
•	Health System: Player starts with 3 hearts. Losing all ends the game.
•	Score System: Score increases when enemies are destroyed.
•	Game Over Mechanic: On zero health, game ends with a message.
•	Level System: Level 2 introduces 3 enemy waves (Meteors, Old Ones, Pirate Chickens – 2 hits each). 250 points are required to complete the level.
• Challenges Faced
•	Collision Detection: Ensuring real-time detection between multiple entities was tricky but solved using bounding box intersections.
•	Asset Management: Path issues with textures/fonts were resolved through relative file management.
•	Egg Dropping Logic: Making egg drops randomized and timed required careful clock handling in SFML.
________________________________________





6. Results
• Project Outcomes
We successfully created a functioning 2D space shooter with real-time gameplay, a scoring system, and health-based survival logic. All main objectives were met.
• Screenshots and Illustrations
(You can insert these into the actual document later using screenshots from gameplay.)
•	Screenshot 1: Player shooting
•	Screenshot 2: Enemies and eggs falling
•	Screenshot 3: Health bar in action
•	Screenshot 4: Game Over screen
• Testing and Validation
We manually tested all features:
•	Collision of bullets with enemies and eggs with player
•	Score increment
•	Health reduction and game over
•	Movement accuracy and frame updates
All passed functional tests, with smooth performance and accurate logic.
________________________________________








7. Conclusion
• Summary of Findings
The game reflects strong OOP design, proper use of SFML, and successful teamwork. Through this project, we gained hands-on experience in class design, real-time event handling, collision detection, and graphical rendering.
• Final Remarks
This project helped us understand how theoretical OOP concepts are used in real-world applications like game development. We also improved our teamwork, task planning, and debugging skills throughout the process.
________________________________________


