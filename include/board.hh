#ifndef BOARD_HH
#define BOARD_HH

#include "undo.hh"

struct Board {
  int pieces[BRD_SQ_NUM];
  U64 pawns[3];
  int kingSq[2];
  int side;
  int enPas;
  int fiftyMove;
  int ply;
  int hisPly;
  U64 posKey;
  int pceNum[13];
  int bigPce[3];
  int majPce[3];
  int minPce[3];
  int castlePerm;
  Undo history[MAXGAMEMOVES];
  int pList[13][10];

  void reset();
  U64 generatePosKey() const;
  void parseFEN(const char*);
  void print() const;
};

#endif // !BOARD_HH
