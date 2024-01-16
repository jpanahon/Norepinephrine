/*
	player.h
	Norepinephrine

	This file has all declarations for the player class.
*/

#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	// Constructor creates a new player with parameters.
	Player(sf::RenderWindow& window, std::string texturePath, sf::Sprite& platform) : 
		window(window), platform(platform) {
		texture.loadFromFile(texturePath, sf::IntRect());
		player.setTexture(texture, true);

		blockingTexture.loadFromFile("resources/textures/batmanblock.png", sf::IntRect());
		punchTexture.loadFromFile("resources/textures/batmanhqpunch.png", sf::IntRect());
	}
	
	// Updates the player on screen.
	void update(float delta);

	// Places the player somewhere on screen.
	void place(sf::Vector2u coords);

	// Gets statistics of player.
	sf::FloatRect getBounds(bool local = false); // Hitbox
	int getHealth() { return health; }

	// Update states of player.
	void damage(int hp);

	// Checks if player successfully hit another player.
	bool canHit(Player& player2, float range);
private:
	// Detects if player is colliding with something.
	void detectCollision();

	// Handles player movement
	void move(float delta);

	// Represents the player on screen.
	sf::Texture texture;
	sf::Sprite player;
	sf::Texture blockingTexture;
	sf::Texture punchTexture;

	// Platform the player stands on.
	sf::Sprite& platform;
	
	// The screen itself.
	sf::RenderWindow& window;

	// Player statistics
	int health = 200;

	// Player states
	bool grounded = true;
	bool airborne = false;
	bool facingRight = true;
	bool blocking = false;
	bool punched = false;
};