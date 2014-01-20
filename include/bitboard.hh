#ifndef BITBOARD_HH
#define BITBOARD_HH

#include "defs.hh"

inline U64 clrbit(U64& bb, int sq64) {
  return bb &= clearMask[sq64];
}

inline U64 setbit(U64& bb, int sq64) {
  return bb |= setMask[sq64];
}

int  cnt(U64);
int  pop(U64&);
void printBitBoard(U64);

#endif // !BITBOARD_HH
