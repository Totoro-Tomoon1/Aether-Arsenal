#include "Button.h"
#include "SceneManager.h"

Button::Button(int type, sf::IntRect rect, sf::Vector2f scale, sf::Vector2f position) : Entity(rect, scale, position)
{
	mType = type;
}

void Button::Action(SceneManager* scenemanager) const
{
	switch (mType)
	{
	case 1:
		std::cout << "return menu" << std::endl;
		scenemanager->ChangeScene(scenemanager->GetMenu());
		break;

	case 2:
		std::cout << "return level" << std::endl;
		scenemanager->ChangeScene(scenemanager->GetLevel()[0]);
		break;
	}
}

std::string Button::GetType() const
{
	return "Button";
}
