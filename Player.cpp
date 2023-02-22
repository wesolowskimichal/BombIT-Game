#include "Player.h"


Player::Player(unsigned short id, float speed, int x, int y) : id(id), speed(speed), x(x), y(y), bombit(0), lifes(3), current_pos(anim::POSITION::FRONT), current_state(anim::STATE::STAY) {
	try {
		right_direction = 0;
		player_texture = new sf::Texture();
		if (!player_texture->loadFromFile(anim::texture_name[id]))
			throw 404;
		me = new sf::Sprite(*player_texture);
		me->setPosition(x, y);
		anim = new Animation(player_texture, sf::Vector2u(3, 6), 0.3f);
	}
	catch (int) {
		std::cerr << "PLAYER::Texture not found!\nError: " << anim::texture_name[id] << '\n';
		exit(404);
	}
}



void Player::update(float delta_time, const std::vector<std::vector<Block*>>& map, const std::vector<Bomb*>& bombs) {
	bombit = 0;
	current_state = anim::STATE::STAY;
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(anim::keys[id][0])) {
		right_direction = 0;
		current_pos = anim::POSITION::SIDE;
		current_state = anim::STATE::RUN;
		movement.x -= speed * delta_time;
		if (!good_move(movement, map, bombs))
			movement.x += speed * delta_time;
		
	} else if (sf::Keyboard::isKeyPressed(anim::keys[id][1])) {
		right_direction = 1;
		current_pos = anim::POSITION::SIDE;
		current_state = anim::STATE::RUN;
		movement.x += speed * delta_time;
		if (!good_move(movement, map, bombs))
			movement.x -= speed * delta_time;
		
	} else if (sf::Keyboard::isKeyPressed(anim::keys[id][2])) {
		current_pos = anim::POSITION::BACK;
		current_state = anim::STATE::RUN;
		movement.y -= speed * delta_time;
		if (!good_move(movement, map, bombs))
			movement.y += speed * delta_time;
	} else if (sf::Keyboard::isKeyPressed(anim::keys[id][3])) {
		current_pos = anim::POSITION::FRONT;
		current_state = anim::STATE::RUN;
		movement.y += speed * delta_time;
		if (!good_move(movement, map, bombs))
			movement.y -= speed * delta_time;
	}
	if (sf::Keyboard::isKeyPressed(anim::keys[id][4]))
		bombit = 1;
	me->move(movement);
	anim->update(current_pos, current_state, delta_time, right_direction);
	me->setTextureRect(anim->uv_rect);
}


unsigned short Player::get_id() const {
	return id;
}

unsigned short Player::get_lifes() const {
	return lifes;
}

bool Player::get_bombit() const{
	return bombit;
}


void Player::decrese_life() const {
	lifes--;
}


std::pair<int, int> Player::get_pos() const {
	return { me->getPosition().x + me->getGlobalBounds().width/2, me->getGlobalBounds().top + me->getGlobalBounds().height };
}

bool Player::good_move(sf::Vector2f movement, const std::vector<std::vector<Block*>>& map, const std::vector<Bomb*>& bombs) {
	std::pair<int, int> pos = get_pos();
	if (current_pos == anim::POSITION::SIDE) {
		if (right_direction) {
			pos.first += movement.x + me->getGlobalBounds().width / 2 + 1;
			pos.second += movement.y;
		}
		else {
			pos.first += movement.x - me->getGlobalBounds().width / 2 - 1;
			pos.second += movement.y;
		}
	}
	else if (current_pos == anim::POSITION::FRONT) {
		pos.first += movement.x;
		pos.second += 1;
	}
	else {
		pos.first += movement.x;
		pos.second -= 40;
	}
	
	std::pair<int, int> map_pos = Animation::scale_point(pos);
	bool res = 0;
	for (auto& bomb : bombs) {
		if (bomb == nullptr)
			continue;
		std::pair<int, int> b_pos = bomb->get_scaled_point();
		if (b_pos.first == map_pos.first && b_pos.second == map_pos.second)
			return 0;
	}
	return map[map_pos.second][map_pos.first]->if_walkable();

}


sf::Sprite& Player::get_me() {
	return *me;
}
