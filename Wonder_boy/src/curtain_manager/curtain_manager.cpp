#include "curtain_manager.h"

#include <iostream>

using sf::View;
using sf::Color;
using sf::Uint8;

namespace the_wonder_boy
{
	RenderWindow* CurtainManager::_window;

	CURTAIN_TYPE CurtainManager::_wayToHide = CURTAIN_TYPE::FADE;
	CURTAIN_TYPE CurtainManager::_wayToShow = CURTAIN_TYPE::FADE;

	bool CurtainManager::_fadingOut = false;
	bool CurtainManager::_fadingIn = true;

	RectangleShape CurtainManager::_curtain;

	const float CurtainManager::_timeToFinishCurtainAction = 1.0f;
	const float CurtainManager::_maxUint8Value = 255.0f;


	// Funciones públicas.
	void CurtainManager::initValues(RenderWindow* window)
	{
		_window = window;
		_curtain.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
		_curtain.setFillColor(Color::Black);
		_curtain.setOrigin(_curtain.getGlobalBounds().width / 2.0f, _curtain.getGlobalBounds().height / 2.0f);
		_curtain.setPosition(Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));
	}
	void CurtainManager::update(float deltaTime)
	{
		if (_fadingOut)
		{
			cover(deltaTime);
		}
		else if (_fadingIn)
		{
			show(deltaTime);
		}
	}
	void CurtainManager::draw(RenderWindow* window)
	{
		window->draw(_curtain);
	}

	void CurtainManager::startToCover(CURTAIN_TYPE curtainType)
	{
		resetCurtainValues();
		_fadingOut = true;
		_wayToHide = curtainType;
	}
	void CurtainManager::startToShow(CURTAIN_TYPE curtainType)
	{
		resetCurtainValues();
		_fadingIn = true;
		_wayToHide = curtainType;
	}

	void CurtainManager::setCurtainPosition(Vector2f position)
	{
		_curtain.setPosition(position);
	}

	bool CurtainManager::isActive()
	{
		return _fadingOut || _fadingIn;
	}
	bool CurtainManager::screenIsBlack()
	{
		return _curtain.getFillColor().a == static_cast<Uint8>(255);
	}


	// Funciones privadas.
	void CurtainManager::cover(float deltaTime)
	{
		const float diffPerFrame = _maxUint8Value / _timeToFinishCurtainAction * deltaTime;
		float alpha = static_cast<float>(_curtain.getFillColor().a);


		if (alpha + diffPerFrame >= _maxUint8Value)
		{
			alpha = _maxUint8Value;
			_fadingOut = false;
		}
		else
		{
			alpha += diffPerFrame;
		}

		_curtain.setFillColor(Color(_curtain.getFillColor().b, _curtain.getFillColor().g, _curtain.getFillColor().b, static_cast<Uint8>(alpha)));
	}
	void CurtainManager::show(float deltaTime)
	{
		float alpha = static_cast<float>(_curtain.getFillColor().a);
		const float diffPerSecond = _maxUint8Value / _timeToFinishCurtainAction * deltaTime;


		if (alpha - diffPerSecond <= 0.0f)
		{
			alpha = 0.0f;
			_fadingIn = false;
		}
		else
		{
			alpha -= diffPerSecond;
		}

		_curtain.setFillColor(Color(_curtain.getFillColor().b, _curtain.getFillColor().g, _curtain.getFillColor().b, static_cast<Uint8>(alpha)));
	}

	void CurtainManager::resetCurtainValues()
	{
		View view;
		view.setSize(_window->getSize().x, _window->getSize().y);
		view.setCenter(view.getSize().x / 2.0f, view.getSize().y / 2.0f);
		_window->setView(view);

		_curtain.setSize(Vector2f(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y)));
		_curtain.setOrigin(_curtain.getGlobalBounds().width / 2.0f, _curtain.getGlobalBounds().height / 2.0f);
		_curtain.setPosition(Vector2f(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f));
	}
}
