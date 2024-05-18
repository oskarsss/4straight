#ifndef WINDOW
#define WINDOW
#include <SFML/Graphics.hpp>	
#include "Button.h"

class Window{
	public:
	Window(sf::RenderWindow* Window, std::vector<Button*>& Buttons);
		
	private:
	
        void drawButton(sf::RenderWindow *window,Button* b);
	int changeTexture(std::vector<Button*>&, Button*);
	void refreshWindow(sf::RenderWindow* window, std::vector<Button*>& Buttons);
};



#endif

