#ifndef PINKY_HPP
#define PINKY_HPP

#include "ghost.hpp"

class Pinky : public Ghost
{
public:
  explicit Pinky(Game* game);

private:
  Field::Tile getTargetTile() override;
  Field::Tile getScatterTile() override;
  void setDefault() override;
};

#endif // PINKY_HPP
