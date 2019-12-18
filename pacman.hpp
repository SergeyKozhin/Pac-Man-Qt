#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "entity.hpp"

class Pacman : public Entity
{
  Q_OBJECT
public:
  explicit Pacman(Game* game);
  Field::Direction getDirection();
  void resetPos() override;

protected:
  void keyPressEvent(QKeyEvent* event) override;

private slots:
  void tick() override;

private:
  enum state
  {
    STANDING,
    MOVING
  };
  state state;
  int ghostsEaten_;

  void align();
  void checkFood();
  void checkGhosts();

  void nextFrame() override;
  void updateDirection() override;
};

#endif // PACMAN_HPP
