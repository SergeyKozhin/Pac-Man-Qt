#include "ghost.hpp"
#include <limits>
#include <QTimer>

Ghost::Ghost(Game* game, Field::Direction startDirection) : Entity(game, startDirection)
{
}

void Ghost::tick()
{
  if (state_ == SCATTER)
  {
    targetTile_ = getScatterTile();
  }
  else if (state_ == CHASE)
  {
    targetTile_ = getTargetTile();
  }

  if (Field::onField(getCenter()) && getCenter() == Field::toPoint(Field::toTile(getCenter())))
  {
    currentDirection_ = nextDirection_;

    Field::Tile nextTile = Field::toTile(getCenter()).nextTile(currentDirection_);
    if (Field::onField(Field::toPoint(nextTile)))
    {
      int minDist = std::numeric_limits<int>().max();
      Field::Direction nextDir = currentDirection_;
      for (int i = Field::UP; i <= Field::RIGHT; ++i)
      {
        Field::Direction dir = static_cast<Field::Direction>(i);
        if (Field::canGo(nextTile, dir) && dir != Field::opposite(currentDirection_)
            && nextTile.nextTile(dir).distSqr(targetTile_) < minDist)
        {
          minDist = nextTile.nextTile(dir).distSqr(targetTile_);
          nextDir = dir;
        }
      }

      nextDirection_ = nextDir;
    }
  }

  setPos(pos() + Field::getOffset(getCenter(), currentDirection_));
}
