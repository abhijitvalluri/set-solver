#ifndef CARD_H
#define CARD_H

#include <string>

namespace avalluri {

class Card {
    public:
      enum Color
      {
          red = 1,
          green,
          purple
      };

      enum Shape
      {
          oval = 1,
          squiggle,
          diamond
      };

      enum Shading
      {
          solid = 1,
          striped,
          open
      };

      enum Number
      {
          one = 1,
          two,
          three
      };

    private:
      Color d_color;
      Shape d_shape;
      Number d_number;
      Shading d_shading;

      std::string colorStr() const;
      std::string shapeStr() const;
      std::string numberStr() const;
      std::string shadingStr() const;

    public:
      Card (Color color, Shape shape, Number number, Shading shading)
      : d_color(color)
      , d_shape(shape)
      , d_number(number)
      , d_shading(shading) { }

      Color color() const { return d_color; }
      Shape shape() const { return d_shape; }
      Number number() const { return d_number; }
      Shading shading() const { return d_shading; }
      
      std::string toString() const {
          return "{ " + numberStr() + " " + colorStr() + " " + shadingStr() + " " + shapeStr() + " }";
      }

    public:
      bool operator==(const Card &other) const;
};

class CardHash {
    public:
     std::size_t operator()(const Card &s) const;
};

}

#endif