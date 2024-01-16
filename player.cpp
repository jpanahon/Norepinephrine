/*
    player.cpp
    Norepinephrine
    
    This file has all the definitions for the player class.
*/

#include "player.h"
#include <iostream>

void Player::detectCollision() {
    // Checks if player is trying to go out of window on the left side.
    if (player.getPosition().x <= 0.0f) {
        player.setPosition(0.0f, player.getPosition().y);
    }

    // Checks if player is trying to go out of window going up.
    if (player.getPosition().y <= 0.0f) {
        player.setPosition(player.getPosition().x, 0.0f);
    }

    // Checks if player is trying to go out of window on the right side.
    if (player.getPosition().x + getBounds().width >= window.getSize().x) {
        player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
    }
}

void Player::update(float delta) {

    // Has various checks needed for movement.
    move(delta);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        if (!blocking && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !punched ||
            !blocking && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !punched) {
            player.setTexture(blockingTexture, true);
            blocking = true;
        }
    }
    else if (blocking && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) ||
             blocking && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        blocking = false;
        player.setTexture(texture, true);
    }

    if (!blocking) {
        if (!punched && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            player.setTexture(punchTexture, true);
            punched = true;
        }
        else if (punched && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            player.setTexture(texture, true);
            punched = false;
        }
    }

    // Updates the player on screen.
    window.draw(player);
}

void Player::move(float delta) {
    // Physics modifiers.
    const float multiplier = 200.0f; // Used in conjunction with delta time
    const float speed = 2.0f * delta;
    const float jumpSpeed = -8.75f * delta;
    const float gravity = 5.5f * delta;
    const float ground = (platform.getPosition().y - player.getGlobalBounds().height) + 25.0f;
    const float apex = ground - getBounds().height;

    // Collision detection.
    detectCollision();

    // Checks if player has reached the jump height limit
    if (player.getPosition().y < apex) airborne = false;

    // Checks if player has initiated a jump and accelerates them upward.
    if (airborne) player.move(0.0f, jumpSpeed * multiplier);

    // Checks if player has touched the ground after jumping.
    if (!grounded && player.getPosition().y >= ground) grounded = true;

    // Checks if player has already finished jumping and make them fall
    if (!grounded && !airborne) player.move(0.0, gravity * multiplier);

    // Moves the player to the left.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (facingRight) {
            player.setScale(-1.0, 1.0);
            player.setOrigin(getBounds().width, 0.0f);
            facingRight = false;
        }

        player.move(-speed * multiplier, 0.0f);
    }

    // Makes the player crouch.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        // TODO: Make player crouch.
        if (facingRight) { player.move(-speed * multiplier, 0.0f); }
        else { player.move(speed * multiplier, 0.0f); }
    }

    // Makes the player go right.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (!facingRight) {
            player.setScale(1.0, 1.0);
            player.setOrigin(0.0f, 0.0f);
            facingRight = true;
        }

        player.move(speed * multiplier, 0.0f);
    }

    // Makes the player jump by initiating jumping sequence.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && grounded ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && grounded) {
        grounded = false;
        airborne = true;
    }

}

void Player::place(sf::Vector2u coords) {
    // Uses sf::Sprite's setPosition method.
    player.setPosition(coords.x, coords.y);
}

sf::FloatRect Player::getBounds(bool local) {
    if (!local) return player.getGlobalBounds();
    return player.getLocalBounds();
}

void Player::damage(int hp) {
    // Checks if player is blocking, taking half damage instead of full.
    if (blocking) { health -= hp / 2; } 
    else { health -= hp;  }
}

bool Player::canHit(Player& player2, float range) {
    if (player.getPosition().x + range >= player2.getBounds().width) {
        return true;
    }

    return false;
}