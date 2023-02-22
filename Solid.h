#pragma once
#include "Block.h"

// Solid - blok ktorego nie da sie wsadzic

class Solid : public Block
{
public:
    Solid(int x, int y);
    Solid(int x, int y, std::string texture);
};

