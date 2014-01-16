#include "defs.hh"

int sq120ToSq64[BRD_SQ_NUM];
int sq64ToSq120[64];

U64 pieceKeys[13][BRD_SQ_NUM];
U64 sideKey;
U64 castleKeys[16];

const char pceChar[]  = ".PNBRQKpnbrqk";
const char sideChar[] = "wb-";
const char rankChar[] = "12345678";
const char fileChar[] = "abcdefgh";
