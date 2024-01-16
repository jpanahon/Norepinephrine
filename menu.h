#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu(sf::RenderWindow& window) : window(window) {
		sf::Texture background;
		background.loadFromFile("resources/textures/mainmenu.jpg");
		menuBg.setTexture(background, true);
		menuBg.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		menuBg.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
	}

	void draw();
private:
	sf::Sprite menuBg;
	sf::RenderWindow& window;
};

