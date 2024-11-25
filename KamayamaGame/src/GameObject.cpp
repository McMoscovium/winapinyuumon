#include "GameObject.h"
//開発用
#include <iostream>
#include <string>
#include "Window.h"
#include <cmath>



GameObject::GameObject(const std::string& objectName):
	objectName(objectName)
{
}

GameObject::~GameObject()
{
	//std::wstring message = L"オブジェクト " + objectName + L"を破棄しました\n";
	//OutputDebugString(message.c_str());
}

void GameObject::setObjectPosition(POINT point)
{
	position = point;
}

const POINT GameObject::getPosition() const
{
	return position;
}



bool GameObject::isVisible() const
{
	return visible;
}

void GameObject::appear()
{
	visible = true;
}

void GameObject::hide()
{
	visible = false;
}


void GameObject::changeSizeRate(float r)
{
	sizeRate = r;
}


const std::string& GameObject::getName() const
{
	return objectName;
}

const int GameObject::getPositionX() const
{
	return position.x;
}

const int GameObject::getPositionY() const
{
	return position.y;
}

float GameObject::getSizeRate() const
{
	return sizeRate;
}
