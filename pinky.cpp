#include "pinky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Pinky::Pinky(Game* game) :
  Ghost(game, Field::RIGHT, config::SPRITE_START_X, config::PINKY_START_Y)
{
  resetPos();
}

void Pinky::resetPos()
{
  setPos(Field::Tile{13, 14}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  currentDirection_ = Field::RIGHT;
  nextDirection_ = Field::UP;
  state_ = CAGED;
  setDefault();
  updateDirection();
  nextFrame();
}

Field::Tile Pinky::getTargetTile()
{
  return game_->getPacmanTile().nextTile(game_->getPacmanDirection(), 4);
}

Field::Tile Pinky::getScatterTile()
{
  return {0, 0};
}

void Pinky::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::PINKY_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
  currFrameX_ = config::SPRITE_START_X;
  currFrameY_ = config::PINKY_START_Y;
}
