#ifndef UNDO_HH
#define UNDO_HH

#include "defs.hh"

struct Undo {
  int move;
  int castlePerm;
  int enPas;
  int fiftyMove;
  U64 posKey;
};

#endif // !UNDO_HH
