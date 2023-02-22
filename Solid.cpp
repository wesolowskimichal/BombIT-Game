#include "Solid.h"

Solid::Solid(int x, int y) : Block(x, y, 0, 0, "textures/block.png") {}
Solid::Solid(int x, int y, std::string texture) : Block(x, y, 0, 0, texture) {}
