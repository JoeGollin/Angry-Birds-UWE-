//
// Created by JoeGollin on 19/03/2021.
//

#ifndef ANGRYBIRDSSFML_ENEMIES_H
#define ANGRYBIRDSSFML_ENEMIES_H
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Enemies
{
 public:
  Enemies();
  ~Enemies();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  bool getVisibility() const;
  void setVisibility(bool value);
  Vector2* pigs_position = nullptr;

 private:
  sf::Sprite* sprite = nullptr;
  bool is_visible = true;
};

#endif // ANGRYBIRDSSFML_ENEMIES_H
