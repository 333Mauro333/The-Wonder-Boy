#include "curtain_manager.h"

#include <iostream>

using sf::Color;
using sf::Uint8;


namespace the_wonder_boy
{
	CURTAIN_TYPE CurtainManager::wayToHide = CURTAIN_TYPE::FADE;
	CURTAIN_TYPE CurtainManager::wayToShow = CURTAIN_TYPE::FADE;

	bool CurtainManager::fadingOut = false;
	bool CurtainManager::fadingIn = true;

	RectangleShape CurtainManager::curtain;

	float CurtainManager::timeToFinishCurtainAction = 1.0f;
	const float CurtainManager::maxUint8Value = 255.0f;


	// Funciones públicas.
	void CurtainManager::initValues(Vector2u curtainSize)
	{
		curtain.setSize(Vector2f(static_cast<float>(curtainSize.x), static_cast<float>(curtainSize.y)));
		curtain.setFillColor(Color::Black);
		curtain.setOrigin(curtain.getGlobalBounds().width / 2.0f, curtain.getGlobalBounds().height / 2.0f);
		curtain.setPosition(Vector2f(curtainSize.x / 2.0f, curtainSize.y / 2.0f));
	}
	void CurtainManager::update(float deltaTime)
	{
		if (fadingOut)
		{
			cover(deltaTime);
		}
		else if (fadingIn)
		{
			show(deltaTime);
		}
	}
	void CurtainManager::draw(RenderWindow* window)
	{
		window->draw(curtain);
	}

	void CurtainManager::startToCover(CURTAIN_TYPE curtainType)
	{
		fadingOut = true;
		wayToHide = curtainType;
	}
	void CurtainManager::startToShow(CURTAIN_TYPE curtainType)
	{
		fadingIn = true;
		wayToHide = curtainType;
	}

	void CurtainManager::setCurtainPosition(Vector2f position)
	{
		curtain.setPosition(position);
	}

	bool CurtainManager::isActive()
	{
		return fadingOut || fadingIn;
	}
	bool CurtainManager::screenIsBlack()
	{
		return curtain.getFillColor().a == static_cast<Uint8>(255);
	}


	// Funciones privadas.
	void CurtainManager::cover(float deltaTime)
	{
		float alpha = static_cast<float>(curtain.getFillColor().a);
		float diffPerFrame = maxUint8Value / timeToFinishCurtainAction * deltaTime;


		if (alpha + diffPerFrame >= maxUint8Value)
		{
			alpha = maxUint8Value;
			fadingOut = false;
		}
		else
		{
			alpha += diffPerFrame;
		}

		curtain.setFillColor(Color(curtain.getFillColor().b, curtain.getFillColor().g, curtain.getFillColor().b, static_cast<sf::Uint8>(alpha)));
	}
	void CurtainManager::show(float deltaTime)
	{
		float alpha = static_cast<float>(curtain.getFillColor().a);
		float diffPerSecond = maxUint8Value / timeToFinishCurtainAction * deltaTime;


		if (alpha - diffPerSecond <= 0.0f)
		{
			alpha = 0.0f;
			fadingIn = false;
		}
		else
		{
			alpha -= diffPerSecond;
		}

		std::cout << "Valor del alpha: " << alpha << std::endl;

		curtain.setFillColor(Color(curtain.getFillColor().b, curtain.getFillColor().g, curtain.getFillColor().b, static_cast<Uint8>(alpha)));
	}
}
