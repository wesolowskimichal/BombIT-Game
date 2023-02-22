#pragma once
#include "Block.h"
#include "Animation.h"

class Bomb :
    public Block
{
private:
    Animation* anim;                    // animacja bomby
    Animation* explosion;               // animacja wybuchu
    sf::Texture* explosion_texture;     // tekstura wybychu
    sf::Vector2f original_position;     // oryginalna pozycja bomby ( tekstura wybuchu ma wymiary 120x120 kiedy bomba 40x40, zmienna jest potrzebna do odpowiedniego ustawienia tekstury wybuchu)
    mutable int reps;                   // ilosc wykonan animacji
    bool second_animation;              // czy animacja ekspolzji zaczela dzialac
public:
    Bomb(int x, int y);
    Bomb(std::pair<int, int> pos);
    void update(float delta_time);      // aktualizuje animacje bomby
    void increase_reps() const;         // inkrementuje ilosc wykonan animacji
    std::pair<int, int> get_scaled_point() const;   // zwraca pozycje bomby przeskalowana na mapa w tym przypadku (40, 40) => (1,1)
    ~Bomb() override;
};

