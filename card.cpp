#include "card.h"

namespace {
std::size_t cardValue(const avalluri::Card& card) {
    return card.color() * 1000 + card.shape() * 100 +
           card.shading() * 10 + card.number();
}
}

namespace avalluri {

std::size_t CardHash::operator()(const Card& card) const {
    return cardValue(card);
}

bool Card::operator==(const Card& other) const {
    return (cardValue(*this) == cardValue(other));
}

std::string Card::colorStr() const {
    switch (d_color) {
        case Color::red:
            return "red";
        case Color::green:
            return "green";
        case Color::purple:
            return "purple";
    }
}

std::string Card::shapeStr() const {
    std::string shape;
    switch (d_shape) {
        case Shape::oval:
            shape = "oval";
            break;
        case Shape::squiggle:
            shape = "squiggle";
            break;
        case Shape::diamond:
            shape = "diamond";
            break;
    }

    if (d_number > 1) {
        shape += "s";
    }

    return shape;
}

std::string Card::numberStr() const {
    switch (d_number) {
        case Number::one:
            return "one";
        case Number::two:
            return "two";
        case Number::three:
            return "three";
    }
}

std::string Card::shadingStr() const {
    switch (d_shading) {
        case Shading::solid:
            return "solid";
        case Shading::striped:
            return "striped";
        case Shading::open:
            return "open";
    }
}

}
