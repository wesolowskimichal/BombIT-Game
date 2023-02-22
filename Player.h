#pragma once
#include "Animation.h"
#include "Block.h"
#include "Bomb.h"

class Player
{
private:
	const unsigned short id;		// id gracza

	const float speed;				// predkosc gracza
	int x;							// polozenie gracza w osi x
	int y;							// polozenie gracza w osi y

	bool bombit;					// flaga do podlozenia bomby

	mutable unsigned short lifes;	// ilosc zyc

	bool right_direction;			// czy gracz porusza sie w prawa strone
	anim::POSITION current_pos;		// aktualna pozycja gracza
	anim::STATE current_state;		// aktualna czynnosc gracza

	sf::Texture* player_texture;	// tekstura gracza
	sf::Sprite* me;					// "obrazek" gracza

	sf::Vector2u texture_szie;		// polozenie tekstury gracza
	Animation* anim;				// animacja poruszania sie gracza
public:
	Player(unsigned short id, float speed, int x, int y);
	void update(float delta_time, const std::vector<std::vector<Block*>>& map, const std::vector<Bomb*>& bombs);
	unsigned short get_id() const;
	unsigned short get_lifes() const;
	bool get_bombit() const;
	void decrese_life() const;
	std::pair<int, int> get_pos() const;
	sf::Sprite& get_me();
private:
	bool good_move(sf::Vector2f movement, const std::vector<std::vector<Block*>>& map, const std::vector<Bomb*>& bombs);
};

