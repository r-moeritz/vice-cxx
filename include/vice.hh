#ifndef VICE_HH
#define VICE_HH

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>
#include <cstdint>

// ----------------------------------------------------------------------
// CONSTANTS
// ----------------------------------------------------------------------

#define NAME         "Vice 1.0"
#define BRD_SQ_NUM   120
#define MAXGAMEMOVES 2048
#define START_FEN    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

namespace vice {
  // ----------------------------------------------------------------------
  // ALIASES
  // ----------------------------------------------------------------------

  typedef uint_fast64_t U64;

  // ----------------------------------------------------------------------
  // ENUMERATIONS
  // ----------------------------------------------------------------------

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

  // ----------------------------------------------------------------------
  // GLOBAL VARIABLES
  // ----------------------------------------------------------------------

  extern int sq120ToSq64[BRD_SQ_NUM];
  extern int sq64ToSq120[64];

  extern U64 setMask[64];
  extern U64 clearMask[64];

  extern U64 pieceKeys[13][BRD_SQ_NUM];
  extern U64 sideKey;
  extern U64 castleKeys[16];

  extern int filesBrd[BRD_SQ_NUM];
  extern int ranksBrd[BRD_SQ_NUM];

  extern const char pceChar[];
  extern const char sideChar[];
  extern const char rankChar[];
  extern const char fileChar[];

  extern const bool pieceBig[13];
  extern const bool pieceMaj[13];
  extern const bool pieceMin[13];
  extern const int  pieceVal[13];
  extern const int  pieceCol[13];

  // ----------------------------------------------------------------------
  // FUNCTIONS
  // ----------------------------------------------------------------------

  void init();
}

#endif // !VICE_HH
