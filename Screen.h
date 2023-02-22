#pragma once
#include "Solid.h"
#include "Pav.h"
#include "Obstacle.h"
#include "Bomb.h"
#include "Player.h"
using namespace std;
class Screen {
private:
	const string title;					// tytul okna
	const unsigned int W;				// szerokosc okna
	const unsigned int H;				// wysokosc okna
	string map_path;					// sciezka do zdjecia w ktorym przetrzymywany jest wzor mapy
	sf::Color clearColor;				// kolor ktorym silnik czysci bufer
	sf::RenderWindow window;			// okno
	sf::Font font;						// czcionka ktora jest wyswietlana ilosc zyc

	vector<Bomb*>bombs;					// tablica bomb
	vector<vector<Block*>> map;			// mapa zlozona z blokow

	vector<Player*> players;			// tablica graczy
	
	vector<sf::Texture*> heads;			// tablica tekstur glow
	vector<sf::Sprite*> head_sprites;	// tablica glow

	bool running;						// czy gra sie zakonczyla

public:
	Screen(const string title, unsigned int width, unsigned int height, string map_path,sf::Color clearColor = sf::Color::Black);
	sf::RenderWindow& _window();		// zwraca okno
	bool get_running() const;			// czy gra sie zakonczyla
	void update(float delta_time);		// czysci bufer, rysuje na nim zmienne przechowywane w tablicach oraz je wyswielta na oknie
private:
	void manage_bombs(float delta_time);	// zajmuje sie bombami, dokladniej co niszczy w obrebie, i czy zabiera zycie ktoremus z graczy
	void draw_menu();						// rysuje dolne menu z iloscia zyc
	void winner_menu(unsigned short deaths);						// po zakonczonej rozgrywce pokazuje zwyciezce
};

