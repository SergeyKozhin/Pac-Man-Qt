#include "ghost.hpp"
#include <limits>

const Field::Tile Ghost::deathTile = {13, 11};

Ghost::Ghost(Game* game, Field::Direction startDirection, int startFrameX, int startFrameY) :
  Entity(game, startDirection, 1000. / config::GHOST_SPEED, startFrameX, startFrameY),
  state_(CHASE),
  targetTile_({0, 0}),
  frightTimer_(new QTimer(this))
{
  frightTimer_->setSingleShot(true);
  connect(frightTimer_, SIGNAL(timeout()), this, SLOT(backToNormal()));
}

Ghost::State Ghost::getState() const
{
  return state_;
}

void Ghost::frighten()
{
  if (state_ != DEAD)
  {
    state_ = FRIGHTENED;
    nextDirection_ = Field::opposite(currentDirection_);
    currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 8;
    currFrameY_ = config::BLINKY_START_Y;

    frightTimer_->start(5000);
  }
}

void Ghost::kill()
{
  state_ = DEAD;
  currFrameX_ = config::SPRITE_START_X + 8 * config::ENTITY_SIZE;
  currFrameY_ = config::PINKY_START_Y;
  frightTimer_->stop();
}

void Ghost::tick()
{
  if (tile_ != getTile())
  {
    nextFrame();
  }
  tile_ = getTile();

  Field::Tile currTile = Field::toTile(getCenter());
  if (state_ == FRIGHTENED)
  {
    currentSpeed_ = 1000. / (config::GHOST_SPEED * 0.6);
  }
  else if (currTile.getType() == Field::Tile::Type::SLOWDOWN)
  {
    currentSpeed_ = 1000. / (config::GHOST_SPEED * 0.5);
  }
  else
  {
    currentSpeed_ = 1000. / config::GHOST_SPEED;
  }
  timer_->setInterval(currentSpeed_);

  switch (state_)
  {
  case CHASE:
    targetTile_ = getTargetTile();
    break;
  case DEAD:
    if (getTile() == deathTile)
    {
      state_ = CHASE;
      setDefault();
    }
    targetTile_ = deathTile;
    timer_->setInterval(1000. / (config::GHOST_SPEED * 2));
    break;
  case CAGED:
    if (getTile() == deathTile)
    {
      state_ = CHASE;
      setDefault();
    }
    targetTile_ = deathTile;
    timer_->setInterval(1000. / (config::GHOST_SPEED * 0.6));
    break;
  default:
    break;
  }

  if (Field::onField(getCenter()) && getCenter() == (Field::toTile(getCenter()).toPoint()))
  {
    if (currentDirection_ != nextDirection_)
    {
      updateDirection();
    }
    currentDirection_ = nextDirection_;
    Field::Tile nextTile = currTile.nextTile(currentDirection_);
    if (Field::onField(nextTile.toPoint()))
    {
      if (state_ == FRIGHTENED)
      {
        nextDirection_ = static_cast<Field::Direction>(rand() % 4);
        while (!Field::canGo(nextTile, nextDirection_) || Field::opposite(currentDirection_) == nextDirection_)
        {
          nextDirection_ = static_cast<Field::Direction>(rand() % 4);
        }
      }
      else
      {
        int minDist = std::numeric_limits<int>().max();
        Field::Direction nextDir = currentDirection_;
        for (int i = Field::UP; i <= Field::RIGHT; ++i)
        {
          Field::Direction dir = static_cast<Field::Direction>(i);
          if ((Field::canGo(nextTile, dir) || (state_ == CAGED && nextTile.getType() == Field::Tile::Type::GHOST_ONLY))
              && dir != Field::opposite(currentDirection_) && nextTile.nextTile(dir).distSqr(targetTile_) < minDist)
          {
            if (dir == Field::UP
                && (currTile.getType() == Field::Tile::Type::BLOCK
                       || currTile.getType() == Field::Tile::Type::PELLET_BLOCK))
            {
              continue;
            }
            minDist = nextTile.nextTile(dir).distSqr(targetTile_);
            nextDir = dir;
          }
        }

        nextDirection_ = nextDir;
      }
    }
  }

  setPos(pos() + Field::getOffset(getCenter(), currentDirection_));
}

void Ghost::backToNormal()
{
  if (state_ == FRIGHTENED)
  {
    state_ = CHASE;
    setDefault();
    updateDirection();
  }
}

void Ghost::nextFrame()
{
  currFrameX_ += config::ENTITY_SIZE;
  if ((currFrameX_ - config::SPRITE_START_X) % (config::ENTITY_SIZE * 2) == 0)
  {
    currFrameX_ -= (config::ENTITY_SIZE * 2);
  }
  if (frightTimer_->isActive() && frightTimer_->remainingTime() < 2000)
  {
    if (currFrameX_ < config::SPRITE_START_X + config::ENTITY_SIZE * 10)
    {
      currFrameX_ += config::ENTITY_SIZE * 2;
    }
    else
    {
      currFrameX_ -= config::ENTITY_SIZE * 2;
    }
  }

  setPixmap(sheet_.copy(currFrameX_, currFrameY_, config::ENTITY_SIZE, config::ENTITY_SIZE));
}

void Ghost::updateDirection()
{
  if (state_ == FRIGHTENED)
  {
    return;
  }
  if (state_ == DEAD)
  {
    switch (nextDirection_)
    {
    case Field::UP:
      currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 10;
      break;
    case Field::LEFT:
      currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 9;
      break;
    case Field::DOWN:
      currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 11;
      break;
    case Field::RIGHT:
      currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 8;
      break;
    }
    return;
  }
  switch (nextDirection_)
  {
  case Field::UP:
    currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 4;
    break;
  case Field::LEFT:
    currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 2;
    break;
  case Field::DOWN:
    currFrameX_ = config::SPRITE_START_X + config::ENTITY_SIZE * 6;
    break;
  case Field::RIGHT:
    currFrameX_ = config::SPRITE_START_X;
    break;
  }
}
