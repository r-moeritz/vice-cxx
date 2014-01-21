#ifndef UNDO_HH
#define UNDO_HH

#include "vice.hh"

namespace vice {
  struct Undo {
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;
  };
}

#endif // !UNDO_HH
