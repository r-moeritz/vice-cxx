#include "defs.hh"
#include "util.hh"

U64 setMask[64];
U64 clearMask[64];

const int bitTable[64] = {
  63, 30, 3,  32, 25, 41, 22, 33, 
  15, 50, 42, 13, 11, 53, 19, 34, 
  61, 29, 2,  51, 21, 43, 45, 10, 
  18, 47, 1,  54, 9,  57, 0,  35, 
  62, 31, 40, 4,  49, 5,  52, 26, 
  60, 6,  23, 44, 46, 27, 56, 16, 
  7,  39, 48, 24, 59, 14, 12, 55, 
  38, 28, 58, 20, 37, 17, 36, 8
};

int pop(U64* bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return bitTable[(fold * 0x783a9b23) >> 26];
}

int cnt(U64 bb) {
  int c;
  for (c = 0; bb; ++c, bb &= bb - 1);
  return c;
}

void printBitBoard(U64 bb) {
  puts("");
  for (int rank = RANK_8; rank >= RANK_1; --rank) {
    for (int file = FILE_A; file != FILE_NONE; ++file) {
      auto sq = fr2sq(file, rank);
      auto sq64 = ::sq64(sq);
      printf(((1ULL << sq64) & bb) ? "X" : "-");
    }
    puts("");
  }
  puts("\n");
}
