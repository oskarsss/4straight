#include "Button.h"


Button::Button (sf::Image* Image,sf::Vector2i Cords, sf::Vector2i Size,sf::Vector2i Indexes, int* Value, int(*fcnptr)(sf::RenderWindow* , std::vector<Button*>& , Button* )){
	this->Image = Image;
	//this->State = state;
	this->Cords = Cords;// position is set by declaration in array
	this->Size = Size;
	sf::Texture texture;
	texture.loadFromImage(*Image,sf ::IntRect(0,0, Size.x, Size.y));
	texture.setSmooth(true);
	this->Texture = texture;
	this->Value =Value; 
	
	this-> Indexes = Indexes;
	this-> fcnptr = fcnptr;



}
 Button::~Button (){
	//delete Value;
	//delete Image;
}

bool Button::checkClick (sf::Vector2i mousePos) {
	if (mousePos.x>=Cords.x+4
			&& mousePos.x<=Cords.x+Size.x+4
			&& mousePos.y>=Cords.y+32
			&& mousePos.y<=Cords.y+Size.y+32)
		return true;
	else 
		return false;

}
/*void Button::setState(int state) {
  this->State = state;
  return;
  }
 */
sf::Vector2i Button::getCords(){
	return this->Cords;
}
sf::Image* Button::getImage(){
	return this->Image;
}
sf::Vector2i Button::getSize(){
	return this->Size;
}
sf::Texture Button::getTexture(){
	return this->Texture;
}
int Button::getValue(){
	return *(this-> Value);
}
int* Button::getValueptr(){
	return this-> Value;
}

sf::Vector2i Button::getIndexes(){
	return this->Indexes;
}

void Button::setTexture(sf::Texture texture){
	this->Texture = texture;
	return;
}
void Button::setValue(int value){
	*(this->Value) = value;
	return;
}

void Button::changeTexture(int x,int y){
	this->Texture.loadFromImage(*Image, sf::IntRect(x,y,Size.x,Size.y));
	return;

}

int Button::doTheJob(sf::RenderWindow* Window, std::vector<Button*>& Buttons){
	return this->fcnptr(Window,Buttons, this);
	

}

