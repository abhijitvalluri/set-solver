#ifndef SET_H
#define SET_H

#include <string>
#include <unordered_set>
#include "card.h"

namespace avalluri {

class Set {
    private:
      std::unordered_set<Card, CardHash> d_set;

    public:
      Set(Card& card1, Card& card2, Card& card3) {
        d_set.insert(card1);
        d_set.insert(card2);
        d_set.insert(card3);
      }

      std::string toString() const {
          std::string setStr = "";
          for (auto it = d_set.cbegin(); it != d_set.cend(); it++)
          {
            setStr += it->toString() + " ";
          }

          return setStr;
      }
};

}

#endif