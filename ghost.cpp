#include "ghost.hpp"
#include <limits>
#include <QTimer>

const Field::Tile Ghost::deathTile = {13, 11};

Ghost::Ghost(Game* game, Field::Direction startDirection, int startFrameX, int startFrameY) :
  Entity(game, startDirection, 1000. / config::GHOST_SPEED, startFrameX, startFrameY),
  state_(CHASE),
  targetTile_({0, 0})
{
}

Ghost::State Ghost::getState() const
{
  return state_;
}

void Ghost::frighten()
{
  if (state_ == CHASE)
  {
//    setBrush(QBrush(Qt::blue));
    state_ = FRIGHTENED;
    nextDirection_ = Field::opposite(currentDirection_);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(backToNormal()));
    timer->setSingleShot(true);
    timer->start(5000);
  }
}

void Ghost::kill()
{
  state_ = DEAD;
}

void Ghost::tick()
{
  if (tile_ != getTile())
  {
    nextFrame();
  }
  tile_ = getTile();

  Field::Tile currTile = Field::toTile(getCenter());
  if (currTile.getType() == Field::Tile::Type::SLOWDOWN || state_ == FRIGHTENED)
  {
    currentSpeed_ = 1000. / (config::GHOST_SPEED / 2);
  }
  else
  {
    currentSpeed_ = 1000. / config::GHOST_SPEED;
  }
  timer_->setInterval(currentSpeed_);

  if (state_ == CHASE)
  {
    targetTile_ = getTargetTile();
  }
  if (state_ == DEAD)
  {
    if (getTile() == deathTile)
    {
      state_ = CHASE;
      setDefault();
    }
    targetTile_ = deathTile;
    timer_->setInterval(1000. / (config::GHOST_SPEED * 3));
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
          if (Field::canGo(nextTile, dir) && dir != Field::opposite(currentDirection_)
              && nextTile.nextTile(dir).distSqr(targetTile_) < minDist)
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
  state_ = CHASE;
  setDefault();
  nextDirection_ = Field::opposite(currentDirection_);
}

void Ghost::nextFrame()
{
  currFrameX_ += config::ENTITY_SIZE;
  if ((currFrameX_ - config::SPRITE_START_X) % (config::ENTITY_SIZE * 2) == 0)
  {
    currFrameX_ -= (config::ENTITY_SIZE * 2);
  }
  setPixmap(sheet_.copy(currFrameX_, currFrameY_, config::ENTITY_SIZE, config::ENTITY_SIZE));
}

void Ghost::updateDirection()
{
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
