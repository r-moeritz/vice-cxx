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

const bool pieceBig[13] = { false, false, true,  true,  true,  true,  true,  false, true,  true,  true,  true,  true };
const bool pieceMaj[13] = { false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true };
const bool pieceMin[13] = { false, false, true,  true,  false, false, false, false, true,  true,  false, false, false };
const int pieceVal[13]  = { 0,     100,   325,   325,   550,   1000,  50000, 100,   325,   325,   550,   1000,  50000 };
const int pieceCol[13]  = { BOTH,  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
