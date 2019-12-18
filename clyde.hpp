#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "ghost.hpp"

class Clyde : public Ghost
{
public:
  explicit Clyde(Game* game);
  void resetPos() override;

private:
  Field::Tile getTargetTile() override;
  Field::Tile getScatterTile() override;
  void setDefault() override;
};

#endif // CLYDE_HPP
