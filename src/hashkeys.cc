#include "defs.hh"

U64 generatePosKey(const Board& pos) {
  U64 finalKey = 0;
  
  for (auto sq = 0; sq != BRD_SQ_NUM; ++sq) {
    auto piece = pos.pieces[sq];
    if (piece != NO_SQ && piece != EMPTY) {
      ASSERT(piece >= wP &&  piece <= bK);
      finalKey ^= pieceKeys[piece][sq];
    }
  }

  if (pos.side == WHITE) {
    finalKey ^= sideKey;
  }

  if (pos.enPas != NO_SQ) {
    ASSERT(pos.enPas >= 0 && pos.enPas < BRD_SQ_NUM);
    finalKey ^= pieceKeys[EMPTY][pos.enPas];
  }

  ASSERT(pos.castlePerm >= 0 && pos.castle <= 15);
  finalKey ^= castleKeys[pos.castlePerm];

  return finalKey;
}
