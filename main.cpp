// # #######################
// # 
// # @Author: Estenio Garcia
// # 
// # @License: MIT
// # 
// # @Description:
// # 
// # This code was developed
// # for my study about collision
// # responses for video games.
// # 
// # #######################

// # Languagem include
#include <iostream>
#include <string>

// # Thirdparty include
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player{

public:
	// # Transform Variables
	sf::Vector2f location;
	sf::Vector2f size;
	sf::Vector2f velocity;

	// # -> Settings Variables
	float movespeed = 150;

	// # Graphics
	sf::Texture tex;
	sf::Sprite spr;

public:
	explicit Player(){

		// # Initialize Variables

		this->location.x = 50;
		this->location.y = 50;

		this->tex.loadFromFile("p.png");
		this->spr.setTexture(tex);

		this->size.x = tex.getSize().x;
		this->size.y = tex.getSize().y;

		this->velocity.x = 0.f;
		this->velocity.y = 0.f;

		this->spr.setPosition(location.x, location.y);
	}

	void draw(sf::RenderWindow& app){

		app.draw(spr);
	}

	void update(const float& dt){

		this->velocity.x = 0;
		this->velocity.y = 0;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			this->velocity.y += -this->movespeed * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->velocity.y += this->movespeed * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->velocity.x += -this->movespeed * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->velocity.x += this->movespeed * dt;

		this->location.x += this->velocity.x;
		this->location.y += this->velocity.y;

		this->spr.setPosition(this->location);
	}

};


class Block{

public:
	// # Transform Variables
	sf::Vector2f location;
	sf::Vector2f size;

	// # Graphcis
	sf::Texture tex;
	sf::Sprite spr;

	// # Instances
	Player* player;

public:
	explicit Block(Player* p_player, const sf::Vector2f& p_loc, sf::Texture& p_tex){

		// # Initilize Variables

		this->player = p_player;

		this->tex = p_tex;
		this->location = p_loc;

		this->size.x = tex.getSize().x;
		this->size.y = tex.getSize().y;

		this->spr.setTexture(tex);
		this->spr.setPosition(location);
	}

	// # Draw object of this class
	void draw(sf::RenderWindow& app){

		// # Draw Sprite
		app.draw(spr);
	}

	void update(const float& dt){


		// # Check if player overlaping

		if( player->location.x - 3 < this->location.x + this->size.x
		 && ( player->location.x + player->size.x ) + 3 > this->location.x
		 && player->location.y - 3 < this->location.y + this->size.y
		 && ( player->location.y + player->size.y ) + 3 > this->location.y){

		 	// # Collision responses

			// # Top Reponses
		 	if( player->location.y < this->location.y 
		 	&& player->location.y + player->size.y < this->location.y + this->size.y
		 	&& player->location.x < this->location.x + this->size.x
		 	&& player->location.x + player->size.x > this->location.x ){

		 		player->velocity.y = 0.f;
		 		player->location.y = ( this->location.y - player->size.y ) - 3;
		 	}

		 	// # Bottom Reponses
		 	else if( player->location.y > this->location.y 
		 		&& player->location.y + player->size.y > this->location.y + this->size.y 
		 		&& player->location.x < this->location.x + this->size.x
		 		&& player->location.x + player->size.x > this->location.x ){

		 		player->velocity.y = 0.f;
		 		player->location.y = ( this->location.y + this->size.y ) + 3;
		 	}

		 	// # Left Reponses
		 	if( player->location.x < this->location.x 
		 	&& player->location.x + player->size.x < this->location.x + this->size.x
		 	&& player->location.y < this->location.y + this->size.y
		 	&& player->location.y + player->size.y > this->location.y ){

		 		player->velocity.x = 0.f;
		 		player->location.x = ( this->location.x - player->size.x ) - 3;
		 	}

		 	// # Right reponses
		 	else if( player->location.x > this->location.x 
		 		&& player->location.x + player->size.x > this->location.x + this->size.x 
		 		&& player->location.y < this->location.y + this->size.y 
		 		&& player->location.y + player->size.y > this->location.y ){

		 		player->velocity.x = 0.f;
		 		player->location.x = ( this->location.x + this->size.x ) + 3;
		 	}

		}
	}

};

int main(){

	sf::RenderWindow app(sf::VideoMode(700, 600), "Collision Work", sf::Style::Close);
	app.setFramerateLimit(60);
	sf::Event event;

	//System Variables
	float dt = 0;
	sf::Clock clock;

	// # Load font and display deltaTime
	sf::Font font;
	font.loadFromFile("ff.ttf");
	sf::Text displayDeltaTime;
	displayDeltaTime.setFont(font);
	displayDeltaTime.setPosition(30, 30);
	displayDeltaTime.setFillColor(sf::Color::Green);
	displayDeltaTime.setCharacterSize(13);

	// # it´s here, load block texture
	sf::Texture persistent_texture_block;
	persistent_texture_block.loadFromFile("block.png");

	// Object Instance
	Player* player = new Player();
	Block* block1 = new Block(player, sf::Vector2f(150, 150), persistent_texture_block);
	Block* block2 = new Block(player, sf::Vector2f(300, 250), persistent_texture_block);
	Block* block3 = new Block(player, sf::Vector2f(500, 250), persistent_texture_block);

	while(app.isOpen()){

		// # Get DeltaTime
		dt = clock.restart().asSeconds();

		// # Load DeltaTime
		displayDeltaTime.setString( "MS: " + std::to_string( dt * 1000.0f ) );

		while(app.pollEvent(event)){

			if(event.type == sf::Event::Closed)
				app.close();
		}

		player->update(dt);
		block1->update(dt);
		block2->update(dt);
		block3->update(dt);

		app.clear();

		// # Draw DeltaTime
		app.draw(displayDeltaTime);

		// # Draw Player
		player->draw(app);

		// # Draw Blocks
		block1->draw(app);
		block2->draw(app);
		block3->draw(app);

		app.display();
	}

	return 0;
}