#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Button {
public:
	Button(){}

	Button(std::string t, Vector2f size,int charSize,  Color bgColor, Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		button.setFillColor(bgColor);
		button.setSize(size);
	}
	void setFont(Font& font)
	{
		text.setFont(font);
	}
	void setBackColor(Color color)
	{
		button.setFillColor(color);
	}
	void setTextColor(Color color)
	{
		text.setFillColor(color);
	}
	void setPos(Vector2f pos)
	{
		button.setPosition(pos); 
		float xPos = (pos.x + button.getGlobalBounds().width / 10) - (text.getGlobalBounds().width / 3);
		float yPos = (pos.y + button.getGlobalBounds().height / 4) - (text.getGlobalBounds().height / 3); 
		text.setPosition({ xPos,yPos });
	}

/*
text.setPosition(buton.getPosition().x + buton.getSize().x / 2 - text.getLocalBounds().width / 2, buton.getPosition().y + buton.getSize().y / 2 - text.getLocalBounds().height / 2);*/


	void drawTo(RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}
	bool isMouseOver(Window& window)
	{
		float mousex = Mouse::getPosition(window).x;
		float mousey = Mouse::getPosition(window).y;

		float btnPosx = button.getPosition().x;
		float btnPosy = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnxPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mousex<btnxPosWidth && mousex>btnPosx && mousey<btnxPosHeight && mousey>btnPosy)
		{
			return true;
		}
		return false;

	}
private:
	RectangleShape button;
	Text text;
};