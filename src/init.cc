#include "defs.hh"
#include <cstdlib>

int sq120ToSq64[BRD_SQ_NUM];
int sq64ToSq120[64];

U64 setMask[64];
U64 clearMask[64];

U64 pieceKeys[13][BRD_SQ_NUM];
U64 sideKey;
U64 castleKeys[16];

inline U64 rand64() {
  return
    (U64) rand()
    + (U64) rand() << 15
    + (U64) rand() << 30
    + (U64) rand() << 45
    + ((U64) rand() & 0xf) << 60;
}

void initHashKeys() {
  for (auto x = 0; x != 13; ++x) {
    for (auto y = 0; y != BRD_SQ_NUM; ++y) {
      pieceKeys[x][y] = rand64();
    }
  }
  sideKey = rand64();
  for (auto& n : castleKeys) {
    n = rand64();
  }
}

void initBitMasks() {
  for (auto i = 0; i != 64; ++i) {
    setMask[i] = 0;
    clearMask[i] = 0;

    setMask[i] |= (1ULL << i);
    clearMask[i] = ~setMask[i];
  }
}

void initSq120To64() {
  for (auto& n : sq120ToSq64) {
    n = 65;
  }
  for (auto& n : sq64ToSq120) {
    n = 120;
  }

  auto sq64 = 0;
  for (int rank = RANK_1; rank != RANK_NONE; ++rank) {
    for (int file = FILE_A; file != FILE_NONE; ++file) {
      auto sq = fr2sq(file, rank);
      sq64ToSq120[sq64] = sq;
      sq120ToSq64[sq] = sq64;
      ++sq64;
    }
  }
}

void initAll() {
  initSq120To64();
  initBitMasks();
  initHashKeys();
}
