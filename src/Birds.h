//
// Created by JoeGollin on 19/03/2021.
//

#ifndef ANGRYBIRDSSFML_BIRDS_H
#define ANGRYBIRDSSFML_BIRDS_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Birds
{
 public:
  Birds();
  ~Birds();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  bool getVisibility() const;
  void setVisibility(bool value);
  bool getClicked() const;
  void setClicked(bool value);
  bool getFired() const;
  void setFired(bool value);
  Vector2* birds_position = nullptr;
  Vector2* birds_direction = nullptr;
  float gravity = 0.0001f;

 private:
  sf::Sprite* sprite = nullptr;
  bool is_visible = true;
  bool is_clicked = false;
  bool is_fired = false;


};

#endif // ANGRYBIRDSSFML_BIRDS_H
