 
#include "Window.h"
#include <iostream>

Window::Window(sf::RenderWindow* window, std::vector<Button*>& Buttons){
	refreshWindow(window,Buttons);
	
	while (window->isOpen())
	{
		// Обрабатываем очередь событий в цикле
		sf::Event event;
		while (window->waitEvent(event))
		{			
			if (event.type == sf::Event::Closed){
				window->close(); // тогда закрываем его
				throw "end of game";
			}
			if (event.type != sf::Event::MouseMoved){
				refreshWindow(window,Buttons);
				window->display();
			}


			if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2i position = sf::Mouse::getPosition();
				sf::Vector2i window_pos = window->getPosition();
				for (auto b : Buttons){
					if(b->checkClick(sf::Vector2i(position.x-window_pos.x,position.y-window_pos.y))){//everything here into job to do
					}




				}
			}
		}


	}
}

void Window::drawButton(sf::RenderWindow *window,Button* b){
	sf::Texture texture;
	texture = b->getTexture();

	// Создаем спрайт и устанавливаем ему нашу текстуру
	sf::Sprite sprite(texture);

	sprite.move (b->getCords().x,b->getCords().y);

	// Отрисовка спрайта	 
	window->draw(sprite);
}

void Window::refreshWindow(sf::RenderWindow* window, std::vector<Button*>& Buttons){
	window->clear(sf::Color(68,59,49 ));
	for (auto b : Buttons){
		drawButton(window, b);
	}

}


