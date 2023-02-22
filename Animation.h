#pragma once
#include "PLAYER_ANIM.h"
class Animation
{
private:
	sf::Vector2u img_count;		// ilosc tekstur w rzedzie i ilosc kolumn
	sf::Vector2u curr_image;	// aktualna tekstura
	float total_time;			// ile minelo czasu
	float switch_time;			// co ile zmienia sie tekstura
public:
	sf::IntRect uv_rect;		// pozycja tekstury na zdjeciu
	Animation(sf::Texture* texture, sf::Vector2u img_count, float switch_time);
	void update(anim::POSITION posistion, anim::STATE state, float delta_time, bool right_direction);		// zarzadza tekstura
	bool update(float delta_time);											// zarzadza tekstura, zwraca prawde kiedy osiagniemy czas zmiany tekstury
	static std::pair<int, int> scale_point(std::pair<int, int> point);		// skaluje punkt na mape
	static std::pair<int, int> center_point(std::pair<int, int> point);		// centruje punkt na srodek
	static sf::Texture& get_texure_from_string(std::string texture_path);	// zwraca teksture ze sciezki pliku
	~Animation() {};
};

