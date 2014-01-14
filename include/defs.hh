#ifndef DEFS_HH
#define DEFS_HH

#include <cstdio>  // printf
#include <cstdlib> // exit

// MACROS
#ifdef DEBUG
#define ASSERT(n)                               \
  if (!(n)) {                                   \
    printf("FAIL: %s", #n);                     \
    printf(", on %s", __DATE__);                \
    printf(", at %s", __TIME__);                \
    printf(", in file %s", __FILE__);           \
    printf(", at line %d\n", __LINE__);         \
    exit(1);                                    \
  }
#else
#define ASSERT(n)
#endif // DEBUG

// ALIASES
typedef unsigned long long U64;

// CONSTANTS
#define NAME "Vice 1.0"
#define BRD_SQ_NUM 120
#define MAXGAMEMOVES 2048

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { WHITE, BLACK, BOTH };
enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

// TYPES
struct Undo {
  int move;
  int castlePerm;
  int enPas;
  int fiftyMove;
  U64 posKey;
};

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
};

// GLOBALS
extern int sq120ToSq64[BRD_SQ_NUM];
extern int sq64ToSq120[64];
extern U64 setMask[64];
extern U64 clearMask[64];
extern U64 pieceKeys[13][BRD_SQ_NUM];
extern U64 sideKey;
extern U64 castleKeys[16];

// INLINE FUNCTIONS
inline int fr2sq(int f, int r) {
  return (21 + f) + (r * 10);
}

inline int sq64(int sq120) {
  return sq120ToSq64[sq120];
}

inline U64 clrbit(U64 bb, int sq64) {
  return bb &= clearMask[sq64];
}

inline U64 setbit(U64 bb, int sq64) {
  return bb |= setMask[sq64];
}

// FUNCTIONS
void initAll();
void printBitBoard(U64);
int  cnt(U64);
int  pop(U64*);
U64  generatePosKey(const Board&);

#endif // DEFS_HH
