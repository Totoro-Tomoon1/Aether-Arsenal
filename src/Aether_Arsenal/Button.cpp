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
	{
		scenemanager->ChangeScene(scenemanager->GetMenu());
	}
	break;

	case 2:
	{
		scenemanager->ChangeScene(scenemanager->GetLevel()[0]);
	}
	break;
	case 3:
	{
		scenemanager->ChangeScene(scenemanager->GetInfinite());
	}
	}
}

std::string Button::GetType() const
{
	return "Button";
}