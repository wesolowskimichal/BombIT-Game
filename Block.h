#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Block{
private:
	sf::Sprite* me;			// "obrazek" bloku
	sf::Texture* texture;	// tekstura bloku
protected:
	const int x;			// pozycja bloku wzgledem osi x
	const int y;			// pozycja bloku wzgledem osi y
	const bool can_be_blown;	// czy blok moze ulec destrukcji
	const bool walkable;		// czy da sie przejsc przez blok
	bool exists;				// czy blok istnieje
public:
	Block(int x, int y, bool can_be_blown, bool walkable, std::string texture_path);
	Block(std::pair<int,int> position, bool can_be_blown, bool walkable, std::string texture_path);
	bool if_exist() const;		// getter zmiennej exists
	bool if_walkable() const;	// getter zmiennej walkable
	bool blowable() const;		// getter zmiennej can_be_blown
	sf::Texture& get_texture() const;	// zwraca teksture bloku
	sf::Sprite& get_me() const;			// zwraca "obrazek" bloku
	virtual ~Block();
};

