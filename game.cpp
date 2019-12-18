#include "game.hpp"
#include "pacman.hpp"
#include "config.hpp"
#include "food.hpp"
#include <QMessageBox>
#include <QApplication>

Game::Game(QApplication* app, QWidget* parent) :
  QWidget(parent),
  app_(app),
  view_(new QGraphicsView(this)),
  scene_(new QGraphicsScene(this)),
  pacman_(new Pacman(this)),
  ghosts_(
      {{"Blinky", new Blinky(this)}, {"Pinky", new Pinky(this)}, {"Inky", new Inky(this)}, {"Clyde", new Clyde(this)}}),
  textScore_(new QGraphicsTextItem(pacman_)),
  textLive_(new QGraphicsTextItem(pacman_)),
  score_(0),
  lives_(3),
  dotsLeft_(244),
  isOver_(false)
{
  srand(time(0));

  view_->setFixedSize(config::FIELD_SIZE_X_PX + 1, config::FIELD_SIZE_Y_PX + 30 * config::FACTOR);
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setScene(scene_);

  scene_->setSceneRect(0, 0, config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX + 30 * config::FACTOR);
  scene_->setBackgroundBrush(QBrush(Qt::black));

  QGraphicsPixmapItem* field = new QGraphicsPixmapItem(pacman_);
  field->setPixmap(QPixmap(":/img/field.png").scaled(config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX));
  field->setPos(0, 0);

  textScore_->setPlainText(QString("Score: " + QString::number(score_)));
  textScore_->setDefaultTextColor(Qt::blue);
  textScore_->setFont(QFont("times", 8 * config::FACTOR));
  textScore_->setPos(0, config::FIELD_SIZE_Y_PX + 10 * config::FACTOR);

  textLive_->setPlainText(QString("Lives: " + QString::number(lives_)));
  textLive_->setDefaultTextColor(Qt::red);
  textLive_->setFont(QFont("times", 8 * config::FACTOR));
  textLive_->setPos(70 * config::FACTOR, config::FIELD_SIZE_Y_PX + 10 * config::FACTOR);

  scene_->addItem(field);
  scene_->addItem(textScore_);
  scene_->addItem(textLive_);

  for (int i = 0; i < config::FIELD_SIZE_Y; ++i)
  {
    for (int j = 0; j < config::FIELD_SIZE_Y; ++j)
    {
      const Field::Tile tile = {i, j};
      if (tile.getType() == Field::Tile::Type::PELLET || tile.getType() == Field::Tile::Type::PELLET_BLOCK)
      {
        scene_->addItem(new Food(this, tile, Food::Type::PELLET));
      }
      else if (tile.getType() == Field::Tile::Type::BIG_PELLET)
      {
        scene_->addItem(new Food(this, tile, Food::Type::BIG_PELLET));
      }
    }
  }

  scene_->addItem(pacman_);
  pacman_->setFocus();

  connect(this, SIGNAL(start()), pacman_, SLOT(start()));
  connect(this, SIGNAL(stop()), pacman_, SLOT(stop()));

  for (auto ghost : ghosts_)
  {
    scene_->addItem(ghost.second);
    connect(this, SIGNAL(start()), ghost.second, SLOT(start()));
    connect(this, SIGNAL(stop()), ghost.second, SLOT(stop()));
  }

  view_->show();
}

Field::Tile Game::getPacmanTile() const
{
  return Field::toTile(pacman_->getCenter());
}

Field::Direction Game::getPacmanDirection() const
{
  return pacman_->getDirection();
}

const std::map<std::string, Ghost*>& Game::getGhosts() const
{
  return ghosts_;
}

void Game::increseScore(int score)
{
  score_ += score;
  textScore_->setPlainText(QString("Score: " + QString::number(score_)));
}

void Game::decreaseDots()
{
  dotsLeft_--;

  if (dotsLeft_ == 0)
  {
    stop();
    scene_->clearFocus();

    QMessageBox msgBox;
    msgBox.setText("YOU WON!!!\n YOUR SCORE: " + QString::number(score_));
    msgBox.exec();
    app_->quit();
  }
}

void Game::gameOver()
{
  lives_--;
  textLive_->setPlainText(QString("Lives: " + QString::number(lives_)));

  isOver_ = true;

  stop();

  if (lives_ < 0)
  {
    scene_->clearFocus();
    QMessageBox msgBox;
    msgBox.setText("YOU LOST\n YOUR SCORE: " + QString::number(score_));
    msgBox.exec();
    app_->quit();
  }
}

void Game::reset()
{
  pacman_->resetPos();
  for (auto ghost : ghosts_)
  {
    ghost.second->resetPos();
  }

  isOver_ = false;
}

bool Game::getIsOver() const
{
  return isOver_;
}
