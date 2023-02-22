#include "Screen.h"
Screen::Screen(const string title, unsigned int width, unsigned int height, string map_path, sf::Color clearColor)
	:title(title), W(width), H(height), clearColor(clearColor), map_path(map_path), running(1)
{
	this->window.create(sf::VideoMode(this->W, this->H), title);
	sf::Image img;
	try {
		if (!img.loadFromFile(map_path))
			throw map_path;

		if (!font.loadFromFile("fonts/Teko-Bold.ttf"))
			throw string("fonts/Teko-Bold.ttf");

		heads.assign(4, nullptr);

		for (int i{}; i < 4; i++) {
			heads[i] = new sf::Texture();
			if (!heads[i]->loadFromFile(anim::heads[i]))
				throw anim::heads[i];
		}

		int Y = img.getSize().y, X = img.getSize().x;

		map.resize(Y);
		for (int y{}; y < Y; y++)
			for (int x{}; x < X; x++) {
				if (img.getPixel(x, y) == sf::Color(0, 0, 0)) {
					if(y == 0)
						map[y].push_back(new Solid(x * anim::BLOCK_SIZE, y * anim::BLOCK_SIZE, "textures/upper_block.png"));
					else
						map[y].push_back(new Solid(x * anim::BLOCK_SIZE, y * anim::BLOCK_SIZE));
				}
				else if (img.getPixel(x, y) == sf::Color(255, 0, 0))
					map[y].push_back(new Pav(x * anim::BLOCK_SIZE, y * anim::BLOCK_SIZE));
				else {
					map[y].push_back(new Obstacle(x * anim::BLOCK_SIZE, y * anim::BLOCK_SIZE - 20));
				}
			}

		bombs.assign(4, nullptr);
		head_sprites.assign(4, nullptr);

		players.push_back(new Player(0, 40.f, 50, 50));
		players.push_back(new Player(1, 40.f, 690, 690));
		players.push_back(new Player(2, 40.f, 50, 690));
		players.push_back(new Player(3, 40.f, 690, 50));

		float distance = anim::WIDTH / 4;
		for (int i{}; i < 4; i++) {
			head_sprites[i] = new sf::Sprite(*heads[i]);
;			head_sprites[i]->setPosition(sf::Vector2f(i * distance, anim::HEIGHT));
		}

	}
	catch (string error) {
		std::cerr << "Resource not found\nFile that is missing: " << error << '\n';
		exit(404);
	}
}

sf::RenderWindow& Screen::_window() {
	return this->window;
}

bool Screen::get_running() const{
	return running;
}

void Screen::update(float delta_time) {
	this->window.clear(sf::Color::White);
	for (auto& r : map)
		for (auto& c : r)
			if(c->if_exist())
				this->window.draw(c->get_me());
	manage_bombs(delta_time);
	unsigned short deaths{};
	for (auto& p : players) {
		if (p->get_lifes() == 0) {
			deaths++;
			continue;
		}
		p->update(delta_time, map, bombs);
		this->window.draw(p->get_me());
		if (p->get_bombit()) {
			if (bombs[p->get_id()] == nullptr)
				bombs[p->get_id()] = new Bomb(p->get_pos());
		}
	}
	if (deaths >= 3) {
		winner_menu(deaths);
		running = 0;
	}
	draw_menu();
	this->window.display();
}

void Screen::manage_bombs(float delta_time) {
	for (int i{}; i < bombs.size(); i++) {
		if (bombs[i] != nullptr) {
			bombs[i]->update(delta_time);
			if (!bombs[i]->if_exist()) {
				pair<int, int> pos = bombs[i]->get_scaled_point();
				pair<int, int> dir[] = { {0,1}, {1, 0}, {0, -1}, {-1, 0} };
				for (int d{}; d < 4; d++) {
					if (map[pos.second + dir[d].second][pos.first + dir[d].first]->blowable()) {
						delete map[pos.second + dir[d].second][pos.first + dir[d].first];
						map[pos.second + dir[d].second][pos.first + dir[d].first] = new Pav((pos.first + dir[d].first) * anim::BLOCK_SIZE, (pos.second + dir[d].second) * anim::BLOCK_SIZE);
					}
					for (auto& p : players) {
						if (p->get_lifes() == 0)
							continue;
						pair<int, int> ppos = Animation::scale_point(p->get_pos());
						if (ppos.first == pos.first + dir[d].first && ppos.second == pos.second + dir[d].second)
							p->decrese_life();
						
					}

				}
				for (auto& p : players) {
					if (p->get_lifes() == 0)
						continue;
					pair<int, int> ppos = Animation::scale_point(p->get_pos());
					if (ppos.first == pos.first && ppos.second == pos.second)
						p->decrese_life();
				}
				
				delete bombs[i];
				bombs[i] = nullptr;
			}
			else
				this->window.draw(bombs[i]->get_me());
		}
	}
}

void Screen::draw_menu() {
	sf::RectangleShape res(sf::Vector2f(anim::WIDTH, anim::BLOCK_SIZE));
	res.setPosition(0, anim::HEIGHT);
	res.setFillColor(sf::Color(48, 180, 209));
	window.draw(res);
	for (auto& s : head_sprites)
		window.draw(*s);
	float distance = anim::WIDTH / 4;
	
	for (int i = 0; i < 4; i++) {
		sf::Text text;
		text.setString(std::to_string(players[i]->get_lifes()));
		text.setFillColor(sf::Color::Black);
		text.setFont(font);
		text.setCharacterSize(30);
		text.setPosition(distance * i + distance/2, anim::HEIGHT);
		window.draw(text);
	}
}

void Screen::winner_menu(unsigned short deaths) {
	sf::RectangleShape rect(sf::Vector2f(anim::WIDTH, anim::HEIGHT));
	sf::Text text;
	sf::Sprite w;
	if (deaths == 4) {
		rect.setFillColor(sf::Color(77, 77, 77, 120));
		text.setFillColor(sf::Color(246, 197, 29));
		text.setString("REMIS");
	}
	else {
		unsigned short winner = -1;
		for (auto& p : players)
			winner = p->get_lifes() != 0 ? p->get_id() : winner;
		if (winner == 0) {
			w.setTexture(Animation::get_texure_from_string("textures/headA-big.png"));
			rect.setFillColor(sf::Color(227, 64, 41, 120));
			text.setFillColor(sf::Color(140, 111, 64));
			text.setString("CZEROWNY WYGRYWA");
		}
		else if (winner == 1) {
			w.setTexture(Animation::get_texure_from_string("textures/headB-big.png"));
			rect.setFillColor(sf::Color(214, 105, 254, 120));
			text.setFillColor(sf::Color(82, 177, 102));
			text.setString("ROZOWY WYGRYWA");
		}
		else if (winner == 2) {
			w.setTexture(Animation::get_texure_from_string("textures/headC-big.png"));
			rect.setFillColor(sf::Color(6, 196, 237, 120));
			text.setFillColor(sf::Color(43, 58, 88));
			text.setString("BLEKITNY WYGRYWA");
		}
		else if (winner == 3) {
			w.setTexture(Animation::get_texure_from_string("textures/headD-big.png"));
			rect.setFillColor(sf::Color(0, 14, 150, 120));
			text.setFillColor(sf::Color(0, 233, 52));
			text.setString("GRANATOWY WYGRYWA");
		}
	}
	w.setPosition(anim::WIDTH / 2 - w.getLocalBounds().width / 2, anim::HEIGHT / 2 - w.getLocalBounds().height);
	text.setFont(font);
	text.setCharacterSize(60);
	text.setPosition(anim::WIDTH / 2 - text.getGlobalBounds().width / 2, anim::HEIGHT / 2 - text.getGlobalBounds().height / 2);
	window.draw(rect);
	window.draw(w);
	window.draw(text);
}