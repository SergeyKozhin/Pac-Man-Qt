#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "ghost.hpp"

class Blinky : public Ghost
{
public:
  explicit Blinky(Game* game);
  void resetPos() override;

private:
  Field::Tile getTargetTile() override;
  Field::Tile getScatterTile() override;
  void setDefault() override;
};

#endif // BLINKY_HPP
