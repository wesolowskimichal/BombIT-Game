#include "Bomb.h"
Bomb::Bomb(int x, int y):Block(x, y, 0, 0, "textures/bomb.png") {
	try {
		explosion_texture = new sf::Texture();
		if (!explosion_texture->loadFromFile("textures/explosion_small.png"))
			throw 404;
		explosion_texture->setRepeated(true);
		this->anim = new Animation(&get_texture(), sf::Vector2u(3, 1), 1.0f);
		this->explosion = new Animation(explosion_texture, sf::Vector2u(14, 1), 0.1f);
		reps = 0;
		second_animation = 0;
	}
	catch (int) {
		std::cerr << "BOMB:CONSTRUCTOR:NORM::Resource not found!\n";
		exit(404);
	}
};

Bomb::Bomb(std::pair<int, int> pos) : Block(Animation::center_point(pos), 0, 0, "textures/bomb.png") {
	try {
		explosion_texture = new sf::Texture();
		original_position = get_me().getPosition();
		if (!explosion_texture->loadFromFile("textures/explosion.png"))
			throw 404;
		explosion_texture->setRepeated(true);
		this->anim = new Animation(&get_texture(), sf::Vector2u(3, 1), 1.0f);
		this->explosion = new Animation(explosion_texture, sf::Vector2u(14, 1), 0.1f);
		reps = 0;
		second_animation = 0;
	}
	catch (int) {
		std::cerr << "BOMB:CONSTRUCTOR:PARAM:Resource not found!\n";
		exit(404);
	}
	
}

void Bomb::update(float delta_time) {
	get_me().setPosition(original_position);
	if (!second_animation) {
		if (anim->update(delta_time))
			increase_reps();
		if (reps == 3) {
			reps = 0;
			second_animation = 1;
		}
		get_me().setTextureRect(anim->uv_rect);
	}
	else {
		if (explosion->update(delta_time))
			increase_reps();
		sf::Vector2f pos = original_position;
		get_me().setTexture(*explosion_texture);
		exists = !(reps == 4);
		pos.x -= anim::BLOCK_SIZE;
		pos.y -= anim::BLOCK_SIZE;
		get_me().setPosition(pos);
		get_me().setTextureRect(explosion->uv_rect);
	}
}

void Bomb::increase_reps() const{
	reps++;
}

std::pair<int, int> Bomb::get_scaled_point() const {
	return Animation::scale_point({ x,y });
}

Bomb::~Bomb() {
	delete anim;
	delete explosion;
	delete explosion_texture;
}