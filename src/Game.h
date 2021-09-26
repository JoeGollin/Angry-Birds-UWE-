
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Birds.h"
#include "Enemies.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2);
  bool collisionClickCheck(sf::Vector2i click, sf::Sprite sprite);

 private:
  sf::RenderWindow& window;
  sf::Sprite menu_background;
  sf::Texture menu_background_texture;
  sf::Sprite level_background;
  sf::Texture level_background_texture;
  sf::Sprite level_floor;
  sf::Texture level_floor_texture;
  sf::Sprite catapult;
  sf::Texture catapult_texture;
  sf::Texture birds_texture;
  sf::Texture pigs_texture;
  sf::Font font;
  sf::Text menu_text;
  sf::Text controls_text;
  sf::Text score_text;
  sf::Text score_text_number;
  sf::Text winner_text;
  sf::Text loser_text;

  Birds* birds = nullptr;
  Enemies* pigs = nullptr;


  int bird_count = 5;
  int pig_count = 3;
  int player_score;
  int player_round = bird_count;


  float catapult_position_x = 140;
  float catapult_position_y = 500;
  float bird_speed = 200;

  bool player_lose{};
  bool player_win{};
  bool in_menu{};
  bool in_game{};

};

#endif // ANGRYBIRDS_GAME_H
