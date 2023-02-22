#include "Animation.h"
#include <iostream>

// funkcja zwraca wartosc z enum class'a
template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

Animation::Animation(sf::Texture* texture, sf::Vector2u img_count, float switch_time) : img_count(img_count), switch_time(switch_time) {
	total_time = 0.0;
	curr_image.x = 0;
	uv_rect.width = texture->getSize().x / float(img_count.x);
	uv_rect.height = texture->getSize().y / float(img_count.y);
}

void Animation::update(anim::POSITION posistion, anim::STATE state, float delta_time, bool right_direction) {
	curr_image.y = as_integer(posistion) + as_integer(state);
	total_time += delta_time;
	if (total_time >= switch_time) {
		total_time -= switch_time;
		if (curr_image.x++ >= img_count.x - 1)
			curr_image.x = 0;
	}
	uv_rect.top = curr_image.y * uv_rect.height;
	if (right_direction) {
		uv_rect.left = curr_image.x * uv_rect.width;
		uv_rect.width = abs(uv_rect.width);
	}
	else {
		uv_rect.left = (curr_image.x + 1) * abs(uv_rect.width);
		uv_rect.width = -abs(uv_rect.width);
	}
}

bool Animation::update(float delta_time) {
	bool res{};
	curr_image.y = 0;
	total_time += delta_time;
	if (total_time >= switch_time) {
		total_time -= switch_time;
		if (curr_image.x++ >= img_count.x - 1)
			curr_image.x = 0;
		res = 1;
	}
	uv_rect.top = curr_image.y * uv_rect.height;
	uv_rect.left = curr_image.x * uv_rect.width;
	uv_rect.width = abs(uv_rect.width);
	return res;
}

std::pair<int, int> Animation::scale_point(std::pair<int, int> point) {
	return { point.first / anim::BLOCK_SIZE, point.second / anim::BLOCK_SIZE };
}

std::pair<int, int> Animation::center_point(std::pair<int, int> point) {
	return { point.first / anim::BLOCK_SIZE * anim::BLOCK_SIZE,point.second / anim::BLOCK_SIZE * anim::BLOCK_SIZE };
}

sf::Texture& Animation::get_texure_from_string(std::string texture_path) {
	try {
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(texture_path))
			throw texture_path;
		texture->setRepeated(true);
		return *texture;
	}
	catch (std::string error) {
		std::cerr << "Resource not found!\n Error with file: " << error << '\n';
		exit(404);
	}
}