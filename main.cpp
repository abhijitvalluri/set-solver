#include "set.h"
#include "card.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

using namespace avalluri;

class InputError: public std::exception
{
    public:
      InputError(std::string error)
      : d_error(error) { }
      virtual const char* what() const throw() {
          return d_error.c_str();
      }
    private:
      std::string d_error;
};

std::vector<Card> getAllCards() {
    std::vector<Card> cards;

    Card::Color colors[] = {Card::red, Card::green, Card::purple};
    Card::Shape shapes[] = {Card::oval, Card::squiggle, Card::diamond};
    Card::Number numbers[] = {Card::one, Card::two, Card::three};
    Card::Shading shadings[] = {Card::solid, Card::striped, Card::open};

    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 3; ++k) {
                for (int l = 0; l != 3; ++l) {
                    cards.push_back(Card(colors[i], shapes[j], numbers[k], shadings[l]));
                }
            }
        }
    }

    return cards;
}

bool isValidSet(Card card1, Card card2, Card card3) {
    bool isColorOk = (card1.color() == card2.color() && card1.color() == card3.color()) ||
                     (card1.color() != card2.color() && card1.color() != card3.color() && card2.color() != card3.color());

    bool isShapeOk = (card1.shape() == card2.shape() && card1.shape() == card3.shape()) ||
                     (card1.shape() != card2.shape() && card1.shape() != card3.shape() && card2.shape() != card3.shape());

    bool isNumberOk = (card1.number() == card2.number() && card1.number() == card3.number()) ||
                      (card1.number() != card2.number() && card1.number() != card3.number() && card2.number() != card3.number());

    bool isShadingOk = (card1.shading() == card2.shading() && card1.shading() == card3.shading()) ||
                       (card1.shading() != card2.shading() && card1.shading() != card3.shading() && card2.shading() != card3.shading());

    return isColorOk && isShapeOk && isNumberOk && isShadingOk;
}

Card::Color parseColor(std::string& color) {
    if (color == "red") {
        return Card::red;
    } else if (color == "green") {
        return Card::green;
    } else if (color == "purple") {
        return Card::purple;
    }

    throw InputError("Invalid Color '" + color + "' in input");
}

Card::Number parseNumber(std::string& number) {
    if (number == "one") {
        return Card::one;
    } else if (number == "two") {
        return Card::two;
    } else if (number == "three") {
        return Card::three;
    }

    throw InputError("Invalid Number '" + number + "' in input");
}

Card::Shape parseShape(std::string& shape) {
    if (shape == "oval" || shape == "ovals") {
        return Card::oval;
    } else if (shape == "squiggle" || shape == "squiggles") {
        return Card::squiggle;
    } else if (shape == "diamond" || shape == "diamonds") {
        return Card::diamond;
    }

    throw InputError("Invalid Shape '" + shape + "' in input");
}

Card::Shading parseShading(std::string& shading) {
    if (shading == "solid") {
        return Card::solid;
    } else if (shading == "striped") {
        return Card::striped;
    } else if (shading == "open") {
        return Card::open;
    }

    throw InputError("Invalid Shading '" + shading + "' in input");
}

std::vector<Card> getCardsFromInput(std::fstream& puzzle) {
    std::string line;
    std::vector<Card> cards;
    while (std::getline(puzzle, line)) {
        std::string number, color, shading, shape;
        std::istringstream iss(line);
        if (!(iss >> number >> color >> shading >> shape)) {
            break;
         }
         cards.push_back(Card(parseColor(color), parseShape(shape), parseNumber(number), parseShading(shading)));
    }

    return cards;
}

std::vector<Set> getAllSets(std::vector<Card>& cards) {
    std::vector<Set> sets;

    for (size_t i = 0; i != cards.size(); ++i) {
        for (size_t j = i + 1; j != cards.size(); ++j) {
            for (size_t k = j + 1; k != cards.size(); ++k) {
                if (isValidSet(cards[i], cards[j], cards[k])) {
                    sets.push_back(Set(cards[i], cards[j], cards[k]));
                }
            }
        }
    }

    return sets;
}

int main (int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Invalid number of arguments!\n"
                  << "Usage: set_solver <puzzle_file>" << std::endl;
        return 1;
    }

    std::fstream puzzle(argv[1], std::ios::in);
    if (!puzzle.is_open())  {
        std::cerr << "Unable to open puzzle file" << std::endl;
        return 2;
    }

    std::vector<Card> cards;
    try {
        cards = getCardsFromInput(puzzle);
    } catch(InputError& e) {
        std::cerr << "Error while reading input: " << e.what() << std::endl;
        return 3;
    }

    std::vector<Set> sets = getAllSets(cards);

    for (size_t i = 0; i != sets.size(); ++i) {
        std::cout << "Set #" << i << " " << sets[i].toString() << std::endl;
    }

    return 0;
}