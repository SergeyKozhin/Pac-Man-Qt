#include "pacman.hpp"
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include "game.hpp"
#include "food.hpp"
#include <QtDebug>

Pacman::Pacman(Game* game) :
  Entity(game, Field::RIGHT, 1000. / config::PACMAN_SPEED, config::SPRITE_START_X, config::PACMAN_START_Y),
  state(STANDING),
  ghostsEaten_(0)
{
  resetPos();
  tile_ = getTile();

  setFlag(QGraphicsItem::ItemIsFocusable);
}

void Pacman::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
  {
  case Qt::Key_Up:
    nextDirection_ = Field::UP;
    break;
  case Qt::Key_Left:
    nextDirection_ = Field::LEFT;
    break;
  case Qt::Key_Down:
    nextDirection_ = Field::DOWN;
    break;
  case Qt::Key_Right:
    nextDirection_ = Field::RIGHT;
    break;
  case Qt::Key_Return:
    if (game_->getIsOver())
    {
      game_->reset();
      break;
    }
    game_->start();
    break;
  case Qt::Key_Escape:
    game_->stop();
  }
  state = MOVING;
}

Field::Direction Pacman::getDirection()
{
  return currentDirection_;
}

void Pacman::resetPos()
{
  setPos(Field::Tile{13, 23}.toPoint() - boundingRect().center() + QPointF(config::TILE_SIZE / 2, 0));
  currentDirection_ = Field::RIGHT;
  nextDirection_ = Field::RIGHT;
  updateDirection();
  nextFrame();
}

void Pacman::tick()
{
  if (tile_ != getTile())
  {
    timer_->stop();
    nextFrame();
    checkFood();
    timer_->start(1000. / config::PACMAN_SPEED);
  }
  tile_ = getTile();
  Field::Tile tile = Field::toTile(getCenter());
  if (Field::onField(getCenter()) && nextDirection_ != currentDirection_ && Field::canGo(tile, nextDirection_))
  {
    currentDirection_ = nextDirection_;
    updateDirection();
  }
  if (getCenter() == tile.toPoint() && !Field::canGo(tile, currentDirection_))
  {
    state = STANDING;
  }

  if (state == MOVING)
  {
    setPos(pos() + Field::getOffset(getCenter(), currentDirection_));
    align();
  }

  checkGhosts();
}

void Pacman::align()
{
  if (Field::isVertiacl(currentDirection_))
  {
    int currX = static_cast<int>(getCenter().x());
    if (currX % config::TILE_SIZE > config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::LEFT));
    }
    else if (currX % config::TILE_SIZE != config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::RIGHT));
    }
  }
  else
  {
    int currY = static_cast<int>(getCenter().y());
    if (currY % config::TILE_SIZE > config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::UP));
    }
    else if (currY % config::TILE_SIZE != config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::DOWN));
    }
  }
}

void Pacman::checkFood()
{
  auto collisions = collidingItems();
  for (QGraphicsItem* item : collisions)
  {
    if (typeid(*item) == typeid(Food))
    {
      Food* food = dynamic_cast<Food*>(item);
      switch (food->getType())
      {
      case Food::Type::PELLET:
        game_->increseScore(10);
        break;
      case Food::Type::BIG_PELLET:
        game_->increseScore(50);
        ghostsEaten_ = 0;
        for (auto ghost : game_->getGhosts())
        {
          ghost.second->frighten();
        }
      }

      delete food;
      game_->decreaseDots();
    }
  }
}

void Pacman::checkGhosts()
{
  for (auto ghost : game_->getGhosts())
  {
    if (ghost.second->getTile() == getTile())
    {
      if (ghost.second->getState() == Ghost::State::FRIGHTENED)
      {
        ghost.second->kill();
        game_->increseScore(200 >> ghostsEaten_);
        ghostsEaten_++;
      }
      else if (ghost.second->getState() == Ghost::State::CHASE)
      {
        game_->gameOver();
      }
    }
  }
}

void Pacman::nextFrame()
{
  currFrameX_ += config::ENTITY_SIZE;
  if (currFrameX_ == config::SPRITE_START_X + config::ENTITY_SIZE * 2)
  {
    currFrameY_ = config::PACMAN_START_Y;
  }
  else
  {
    updateDirection();
  }
  if (currFrameX_ == config::SPRITE_START_X + config::ENTITY_SIZE * 3)
  {
    currFrameX_ = config::SPRITE_START_X;
  }
  setPixmap(sheet_.copy(currFrameX_, currFrameY_, config::ENTITY_SIZE, config::ENTITY_SIZE));
}

void Pacman::updateDirection()
{
  switch (currentDirection_)
  {
  case Field::UP:
    currFrameY_ = config::PACMAN_START_Y + config::ENTITY_SIZE * 2;
    break;
  case Field::LEFT:
    currFrameY_ = config::PACMAN_START_Y + config::ENTITY_SIZE * 1;
    break;
  case Field::DOWN:
    currFrameY_ = config::PACMAN_START_Y + config::ENTITY_SIZE * 3;
    break;
  case Field::RIGHT:
    currFrameY_ = config::PACMAN_START_Y;
    break;
  }
}
