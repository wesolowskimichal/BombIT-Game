#include "Block.h"

Block::Block(int x, int y, bool can_be_blown, bool walkable, std::string texture_path) : x(x), y(y), can_be_blown(can_be_blown), walkable(walkable), exists(1) {
	try {
		texture = new sf::Texture();
		if (!texture->loadFromFile(texture_path))
			throw texture_path;
		texture->setRepeated(true);
		me = new sf::Sprite(*texture);
		me->setPosition(x, y);
	}
	catch (std::string error){
		std::cerr << "BLOCK::Resource not found!\nFile: " << error << '\n';
		exit(404);
	}
};

Block::Block(std::pair<int,int> position, bool can_be_blown, bool walkable, std::string texture_path) : x(position.first), y(position.second), can_be_blown(can_be_blown), walkable(walkable), exists(1) {
	try {
		texture = new sf::Texture();
		if (!texture->loadFromFile(texture_path))
			throw texture_path;
		texture->setRepeated(true);
		me = new sf::Sprite(*texture);
		me->setPosition(x, y);
	}
	catch (std::string error) {
		std::cerr << "BLOCK::Resource not found!\nFile: " << error << '\n';
		exit(404);
	}
};

bool Block::if_exist() const {
	return exists;
}

bool Block::if_walkable() const {
	return walkable;
}

bool Block::blowable() const {
	return can_be_blown;
}

sf::Texture& Block::get_texture() const{
	return *texture;
}

sf::Sprite& Block::get_me() const {
	return *me;
}

Block::~Block() {
	delete me;
	delete texture;
}