#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Node.h"
int gameover=0;
bool first = 1;
void fillButtons(std::vector<Button*> &Buttons, int GameArray[][7]){
	static sf::Image image;
	image.loadFromFile("image.png");
	for (int i=0;i<6;++i){
		for(int j =0;j<7;++j){
			sf::Vector2i Cords(25+80*j, 28+80*i);
			sf::Vector2i Size (75,75);
			GameArray[i][j] = 0;
			Button* b = new Button(&image, Cords, Size,  sf::Vector2i(i,j));
			Buttons.push_back(b);
			
		}
	}
	static sf::Image image1;
	image1.loadFromFile("redo.png");
	Button* b = new Button(&image1, sf::Vector2i(150,500), sf::Vector2i(30,30), sf::Vector2i(0,0), new int(-1));
	Buttons.push_back(b);
	static sf::Image image2;

	image2.loadFromFile("AI.png");
	b = new Button(&image2, sf::Vector2i(450,500), sf::Vector2i(30,30), sf::Vector2i(0,0), new int(-2));
	Buttons.push_back(b);


} 
void drawButton(sf::RenderWindow *window,Button* b){
	sf::Texture texture;
	texture = b->getTexture();

	// Создаем спрайт и устанавливаем ему нашу текстуру
	sf::Sprite sprite(texture);

	sprite.move (b->getCords().x,b->getCords().y);

	// Отрисовка спрайта	 
	window->draw(sprite);
}

void refreshWindow(sf::RenderWindow* window, std::vector<Button*>& Buttons){
	window->clear(sf::Color(68,59,49 ));
	for (auto b : Buttons){
		drawButton(window, b);
	}


}
const int MAX = 1000;
const int MIN = -1000;
  


int getValue(int GameArray[][7]){
	
	int value =0;

	for (int i=0; i<3;++i){
		for(int j=0;j<7;++j){
			if (GameArray[i][j]==GameArray[i+1][j]&&GameArray[i+1][j]==GameArray[i+2][j]&&GameArray[i+2][j]==GameArray[i+3][j])
				if (GameArray[i][j] == 1){
					value = 1;
					return value;
					

				}
				else if (GameArray[i][j] == 2) {
					//std::cout<<"Yes";
					value = -1;
					return value;
				}

		}
	}
	for (int i=0; i<6;++i){
		for(int j=0;j<4;++j){
			if (	GameArray[i][j]==GameArray[i][j+1]&&GameArray[i][j+1]==GameArray[i][j+2]&&GameArray[i][j+2]==GameArray[i][j+3])
				if (GameArray[i][j] == 1){
					value = 1;
					return value;
					

				}
				else if (GameArray[i][j] == 2) {
					//std::cout<<"Yes";
					value = -1;
					return value;
				}

		}
	}
	for (int i=0;i<3;++i){
		for (int j=0; j<4;++j){
			if(GameArray[i][j]==GameArray[i+1][j+1]&&GameArray[i+1][i+1]==GameArray[i+2][j+2]&&GameArray[i+2][j+2]==GameArray[i+3][j+3])
				if (GameArray[i][j] == 1){
					value = 1;
					return value;
					

				}
				else if (GameArray[i][j] == 2) {
					//std::cout<<"Yes";
					value = -1;
					return value;
				}
		}
	}
	for (int i=0;i<3;++i){
		for (int j=0; j<4;++j){
			if (GameArray[i][6-j]==GameArray[i+1][5-j]&&GameArray[i+1][5-j]==GameArray[i+2][4-j]&&GameArray[i+2][4-j]==GameArray[i+3][3-j])

				if (GameArray[i][6-j] == 1){
					value = 1;
					return value;
					

				}
				else if (GameArray[i][6-j] == 2) {
					//std::cout<<"Yes";
					value = -1;
					return value;
				}
		}
	}




	return value;


}

void fillTree(Node* root, bool player, int depth){
	if (depth == 5||getValue(root->GameArray) ==1 || getValue(root->GameArray)==-1){
		root->value = getValue(root->GameArray);
		return;
	}
	for(int i =0; i<6;++i){
		for (int j =0 ; j< 7 ; ++j){
			if (root->GameArray[i][j] == 0 &&( i == 5 ||root->GameArray[i+1][j] !=0)){
				Node* child = new Node ;
				child->copyArray(root->GameArray);
				root->child.push_back(child);
				child->GameArray[i][j] = player +1;
				//std::cout<<"test" << depth<<"\n";
			
				
				fillTree(child, !player, depth +1);

			}

		}
	}
	return;
		
}

// Returns optimal value for
// current player(Initially called
// for root and maximizer)
Node* minimax(int depth, Node* root,
		bool maximizingPlayer, int alpha, 
		int beta)
{
    // Terminating condition. i.e 
    // leaf node is reached

	

    if (root->child.size()==0){
	    root->value =getValue(root->GameArray);
	    
	    return root;
    }
  
    if (maximizingPlayer)
    {
        int best = MIN;
  
        // Recur for left and 
        // right children
        for (int i = 0; i < root->child.size(); i++)
        {
              
            int val = minimax(depth + 1, root->child[i], 
                              false, alpha, beta)->value;
            best = std::max(best, val);
            alpha = std::max(alpha, best);
  
            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
	root->value = best;
        return root;
    }
    else
    {
        int best = MAX;
  
        // Recur for left and
        // right children
        for (int i = 0; i < root->child.size(); i++)
        {
            int val = minimax(depth + 1, root->child[i],
                              true, alpha, beta)->value;
            best = std::min(best, val);
            beta = std::min(beta, best);
  
            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
	root->value = best;
        return root;
    }
}

int getAIMove(int GameArray[][7], bool player){

	//player = !player;

	Node* root = new Node;
	root->copyArray(GameArray);
	fillTree(root, !player,0);
	Node* result=minimax(0,root,player, MIN,MAX);
	int max=-10001,num;
	
	for (int x = 0; x < result->child.size(); x++)
	{
		if (result->child[x]->value>max)
		{
			max = result->child[x]->value;
			num = x;
		}
	}
	if(max!=0)
		gameover = max;
	for (int i=0; i<6;++i){
		for (int j = 0; j<7;++j){
			GameArray[i][j] = result->child[num]->GameArray[i][j];
			//std::cout<<result->child[num]->value<<"\n "; std::cout.flush();
								std::cout<<result->child[num]->GameArray[i][j]<<"\t "; std::cout.flush();
				}std::cout<<"\n";
			}	
			std::cout<<"\nValue " <<result->child[num]->value<<std::endl;std::cout.flush();
			std::cout<<"________________\n";
	return max;
	
}	








int main(){
	while (true)
		try{

			int GameArray[6][7];
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			std::vector<Button*> Buttons ;
			fillButtons(Buttons, GameArray);


			sf::RenderWindow window(sf::VideoMode(600,550), "4straight", sf::Style::Titlebar|sf::Style::Close, settings);
			bool player = true;

			while (window.isOpen())
			{
				// Обрабатываем очередь событий в цикле
				sf::Event event;
				while (window.waitEvent(event))
				{			
					if (event.type == sf::Event::Closed){
						window.close(); // тогда закрываем его
						throw "exception";

					}
					if (event.type != sf::Event::MouseMoved){
						refreshWindow(&window,Buttons);
						window.display();
					}
					if (first){
						getAIMove(GameArray,!player);
						first = !first;
					}

					if (event.type == sf::Event::MouseButtonPressed){
						sf::Vector2i position = sf::Mouse::getPosition();
						sf::Vector2i window_pos = window.getPosition();
						for (auto b : Buttons){
							if(b->checkClick(sf::Vector2i(position.x-window_pos.x,position.y-window_pos.y))){//everything here into job to do	
								if (b->getValue() ==-2)
								{
									player = !player;
									getAIMove(GameArray,player);
									first = !first;
								Buttons.erase(Buttons.begin()+43);
								
								}
								if (first){
									first = ! first;
								Buttons.erase(Buttons.begin()+43);
								}

								if(b->getValue() == -1){
									gameover=0;
									first = 1;
									window.close();
								}
							

								if (!gameover)
									if (GameArray[b->getIndexes().x][b->getIndexes().y]==0&&(b->getIndexes().x == 5 || GameArray[b->getIndexes().x+1][b->getIndexes().y]!=0)){

										GameArray[b->getIndexes().x][b->getIndexes().y] = player +1;
										if(getAIMove(GameArray, player)){
											std::cout<<"gameover";
											//window.close();

											std::cout.flush();}

									}


							}

						}
						for (auto b : Buttons)
							b->changeTexture(GameArray[b->getIndexes().x][b->getIndexes().y]*75,0);

					}
				}


			}
		}
	catch(...){return 0;}


}
