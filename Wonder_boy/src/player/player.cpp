#include "player.h"

#include <iostream>

#include "game_manager/game_manager.h"

using std::cout;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		if (!tex_idle.loadFromFile("../res/sprites/player/idle.png"))
		{
			cout << "La textura idle.png no se ha cargado.\n";
		}

		spr_idle.setTexture(tex_idle);
		spr_idle.setOrigin(spr_idle.getGlobalBounds().width / 2.0f, spr_idle.getGlobalBounds().height);
		spr_idle.setPosition(x, y);

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		cout << "El jugador ha sido eliminado de la memoria.\n";
	}

	void Player::update(float deltaTime)
	{

	}
	void Player::draw(RenderWindow* window)
	{
		window->draw(spr_idle);
	}
}