#include "util.hh"

using namespace vice;

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

void initRankFileBrd() {
  for (auto i = 0; i != BRD_SQ_NUM; ++i) {
    ranksBrd[i] = NO_SQ;
    filesBrd[i] = NO_SQ;
  }

  for (int r = RANK_1; r != RANK_NONE; ++r) {
    for (int f = FILE_A; f != FILE_NONE; ++f) {
      auto sq = fr2sq(f, r);
      ranksBrd[sq] = r;
      filesBrd[sq] = f;
    }
  }
}

void vice::init() {
  initSq120To64();
  initBitMasks();
  initHashKeys();
  initRankFileBrd();
}
