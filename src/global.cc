#include "vice.hh"

using namespace vice;

int vice::sq120ToSq64[BRD_SQ_NUM];
int vice::sq64ToSq120[64];

U64 vice::pieceKeys[13][BRD_SQ_NUM];
U64 vice::sideKey;
U64 vice::castleKeys[16];

int vice::filesBrd[BRD_SQ_NUM];
int vice::ranksBrd[BRD_SQ_NUM];

const char vice::pceChar[]  = ".PNBRQKpnbrqk";
const char vice::sideChar[] = "wb-";
const char vice::rankChar[] = "12345678";
const char vice::fileChar[] = "abcdefgh";

const bool vice::pieceBig[13] = { false, false, true,  true,  true,  true,  true,  false, true,  true,  true,  true,  true };
const bool vice::pieceMaj[13] = { false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true };
const bool vice::pieceMin[13] = { false, false, true,  true,  false, false, false, false, true,  true,  false, false, false };
const int  vice::pieceVal[13] = { 0,     100,   325,   325,   550,   1000,  50000, 100,   325,   325,   550,   1000,  50000 };
const int  vice::pieceCol[13] = { BOTH,  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
