#pragma once
#include <SFML/Graphics.hpp>
namespace anim {
	enum class POSITION { FRONT = 0, SIDE = 1, BACK = 2 };	// pozycja w ktorej gracz sie znajduje
	enum class STATE { STAY = 0, RUN = 3 };					// czynnosc jaka gracz robi
	const unsigned int WIDTH = 800;			// szerokosc okna
	const unsigned int HEIGHT = 800;		// wysokosc okna
	const unsigned int BLOCK_SIZE = 40;		// wielkosc bloku
	const sf::Keyboard::Key keys[][5] = { 
									{sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::Space},
									{sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::Slash},
									{sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Numpad0},
									{sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8, sf::Keyboard::Numpad5, sf::Keyboard::Numpad3} 
										};	// przypisanie klawiszy do kazdego z graczy
	const std::string texture_name[] = { "textures/A.png", "textures/B.png","textures/C.png","textures/D.png" };			// przypisanie sciezek tekstur do graczy
	const std::string heads[] = { "textures/headA.png", "textures/headB.png","textures/headC.png","textures/headD.png" };	// przypisanie sciezek tekstur do glow
};