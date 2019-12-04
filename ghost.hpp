#ifndef GHOST_HPP
#define GHOST_HPP

#include "entity.hpp"

class Ghost : public Entity
{
public:
  Ghost(Game* game, Field::Direction startDirection);

private slots:
  void tick() override;

protected:
  enum state
  {
    SCATTER,
    CHASE,
    FRIGHTENED,
    DEAD
  };

  state state_ = CHASE;
  Field::Tile targetTile_ = {0, 0};

  virtual Field::Tile getTargetTile() = 0;
  virtual Field::Tile getScatterTile() = 0;
};

#endif // GHOST_HPP
