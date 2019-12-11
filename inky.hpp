#ifndef INKY_HPP
#define INKY_HPP


#include "ghost.hpp"

class Inky : public Ghost
{
public:
  explicit Inky(Game* game);

private:
  Field::Tile getTargetTile() override;
  Field::Tile getScatterTile() override;
  void setDefault() override;
};
#endif // INKY_HPP
