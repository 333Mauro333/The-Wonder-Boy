#include "level_test.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	LevelTest::LevelTest(RenderWindow* window)
	{
		cout << "Se ha creado un nivel de prueba.\n\n";

		this->window = window;
	}
	LevelTest::~LevelTest()
	{
		cout << "El nivel de prueba ha sido eliminado de la memoria.\n";
	}

	void LevelTest::init()
	{

	}
	void LevelTest::update(float deltaTime)
	{

	}
	void LevelTest::draw()
	{

	}
	void LevelTest::destroy()
	{

	}
}
