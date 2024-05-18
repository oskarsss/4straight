#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include <bitset>
#include <iostream>

class Button {
	public:
		Button (sf::Image* Image  ,sf::Vector2i Cords,sf::Vector2i Size =  sf::Vector2i(75,75),sf::Vector2i Index =  sf::Vector2i(0,0), int* Value=new int (0), int(*)(sf::RenderWindow*, std::vector<Button*>& , Button*)=nullptr);
		~Button();
		sf::Vector2i getCords();
		sf::Image* getImage();
		sf::Vector2i getSize();
		sf::Texture getTexture();
		int getValue();
		int* getValueptr();
		sf::Vector2i getIndexes();

		void setTexture(sf::Texture);
		void setValue(int);
		void setState(int);

		void changeTexture(int, int);
		bool checkClick(sf::Vector2i);
		int doTheJob(sf::RenderWindow*, std::vector<Button*>& );


	private:
		sf::Image* Image;
		sf::Vector2i Cords;
		sf::Vector2i Size;
		sf::Texture Texture;
		sf::Vector2i Indexes;
		int *Value;
		int(*fcnptr)(sf::RenderWindow* , std::vector<Button*>& , Button*);
};



#endif
