#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "ghost.hpp"

class Blinky : public Ghost
{
public:
  explicit Blinky(Game* game);

private:
  Field::Tile getTargetTile() override;
  Field::Tile getScatterTile() override;
};

#endif // BLINKY_HPP
