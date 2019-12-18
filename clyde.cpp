#include "clyde.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Clyde::Clyde(Game* game) :
  Ghost(game, Field::LEFT, config::SPRITE_START_X, config::CLYDE_START_Y)
{
  resetPos();
}

void Clyde::resetPos()
{
  setPos(Field::Tile{15, 14}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  currentDirection_ = Field::LEFT;
  nextDirection_ = currentDirection_;
  state_ = CAGED;
  setDefault();
  updateDirection();
  nextFrame();
}

Field::Tile Clyde::getTargetTile()
{
  Field::Tile pacmanTile = game_->getPacmanTile();
  if (Field::toTile(getCenter()).distSqr(pacmanTile) >= 64)
  {
    return pacmanTile;
  }

  return getScatterTile();
}

Field::Tile Clyde::getScatterTile()
{
  return {0, config::FIELD_SIZE_Y};
}

void Clyde::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::CLYDE_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
  currFrameX_ = config::SPRITE_START_X;
  currFrameY_ = config::CLYDE_START_Y;
}
