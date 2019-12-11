#ifndef GHOST_HPP
#define GHOST_HPP

#include "entity.hpp"
#include <QObject>

class Ghost : public Entity
{
  Q_OBJECT
public:
  enum State
  {
    CHASE,
    FRIGHTENED,
    DEAD
  };

  Ghost(Game* game, Field::Direction startDirection, int startFrameX, int startFrameY);
  State getState() const;
  void frighten();
  void kill();

private slots:
  void tick() override;
  void backToNormal();

protected:
  static const Field::Tile deathTile;
  State state_;
  Field::Tile targetTile_;

  void nextFrame() override;
  void updateDirection() override;

  virtual Field::Tile getTargetTile() = 0;
  virtual Field::Tile getScatterTile() = 0;
  virtual void setDefault() = 0;
};

#endif // GHOST_HPP
