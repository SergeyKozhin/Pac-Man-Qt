#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "entity.hpp"

class Pacman : public Entity
{
  Q_OBJECT
public:
  explicit Pacman(Game* game);
  Field::Direction getDirection();

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

  void align();
  void checkFood();
  void checkGhosts();

  void nextFrame() override;
  void updateDirection() override;
};

#endif // PACMAN_HPP
