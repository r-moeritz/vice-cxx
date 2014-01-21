#include "board.hh"
#include "util.hh"
#include "bitboard.hh"

using namespace vice;

void Board::validate() const {
  int pceNum[13]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int bigPce[2]   = { 0, 0 };
  int majPce[2]   = { 0, 0 };
  int minPce[2]   = { 0, 0 };
  int material[2] = { 0, 0 };
  U64  pawns[3]   = { 0, 0, 0 };
  
  for (auto i = 0; i != 3; ++i) {
    pawns[i] = this->pawns[i];
  }
  
  // Check piece list
  // --------------------------------------------------
  for (int piece = wP; piece <= bK; ++piece) {
    for (auto pn = 0; pn != this->pceNum[piece]; ++pn) {
      auto sq = this->pList[piece][pn];
      ASSERT(this->pieces[sq] == piece);
    }
  }

  // Check piece count and other counters
  // --------------------------------------------------
  for (auto sq64 = 0; sq64 != 64; ++sq64) {
    auto sq = sq120(sq64);
    auto piece = this->pieces[sq];
    pceNum[piece] += 1;
    auto colour = pieceCol[piece];
    if (pieceBig[piece]) bigPce[colour] += 1;
    if (pieceMin[piece]) minPce[colour] += 1;
    if (pieceMaj[piece]) majPce[colour] += 1;
    material[colour] += pieceVal[piece];
  }

  for (int piece = wP; piece <= bK; ++piece) {
    ASSERT(pceNum[piece] == this->pceNum[piece]);
  }

  // Check bitboard counts
  // --------------------------------------------------
  auto pc = cnt(pawns[WHITE]);
  ASSERT(pc == this->pceNum[wP]);
  pc = cnt(pawns[BLACK]);
  ASSERT(pc == this->pceNum[bP]);
  pc = cnt(pawns[BOTH]);
  ASSERT(pc == this->pceNum[bP] + this->pceNum[wP]);

  // Check bitboard squares
  // --------------------------------------------------
  while (pawns[WHITE]) {
    auto sq64 = pop(pawns[WHITE]);
    ASSERT(this->pieces[sq120(sq64)] == wP);
  }
  while (pawns[BLACK]) {
    auto sq64 = pop(pawns[BLACK]);
    ASSERT(this->pieces[sq120(sq64)] == bP);
  }
  while (pawns[BOTH]) {
    auto sq64 = pop(pawns[BOTH]);
    auto sq = sq120(sq64);
    ASSERT(this->pieces[sq] == wP || this->pieces[sq] == bP);
  }

  // Sanity checks
  // --------------------------------------------------
  int colours[2] = { WHITE, BLACK };
  for (auto col : colours) {
    ASSERT(material[col] == this->material[col]);
    ASSERT(minPce[col]   == this->minPce[col]);
    ASSERT(majPce[col]   == this->majPce[col]);
    ASSERT(bigPce[col]   == this->bigPce[col]);
  }

  ASSERT(this->side == WHITE || this->side == BLACK);
  ASSERT(this->generatePosKey() == this->posKey);

  ASSERT(this->enPas == NO_SQ
         || (ranksBrd[this->enPas] == RANK_6 && this->side == WHITE)
         || (ranksBrd[this->enPas] == RANK_3 && this->side == BLACK));
  
  ASSERT(this->pieces[this->kingSq[WHITE]] == wK);
  ASSERT(this->pieces[this->kingSq[BLACK]] == bK);
}

void Board::updateMaterialLists() {
  for (auto i = 0; i != BRD_SQ_NUM; ++i) {
    auto piece = this->pieces[i];
    if (piece == NO_SQ || piece == EMPTY) continue;
    
    auto colour = pieceCol[piece];
    if (pieceBig[piece]) this->bigPce[colour] += 1;
    if (pieceMin[piece]) this->minPce[colour] += 1;
    if (pieceMaj[piece]) this->majPce[colour] += 1;

    this->material[colour] += pieceVal[piece];
    auto n = this->pceNum[piece];
    this->pList[piece][n] = i;
    this->pceNum[piece] += 1;

    if (piece == wK || piece == bK) {
      this->kingSq[colour] = i;
    }

    if (piece == wP || piece == bP) {
      setbit(this->pawns[colour], sq64(i));
      setbit(this->pawns[BOTH], sq64(i));
    }
  }
}

void Board::print() const {
  puts("\nGame Board:\n");

  for (int rank = RANK_8; rank >= RANK_1; --rank) {
    printf("%d |", rank + 1);
    for (int file = FILE_A; file != FILE_NONE; ++file) {
      auto sq    = fr2sq(file, rank);
      auto piece = this->pieces[sq];
      auto fmt   = file == FILE_A ? "%2c" : "%3c";
      printf(fmt, pceChar[piece]);
    }
    puts("");
  }

  printf("  +-----------------------\n  ");
  for (int file = FILE_A; file != FILE_NONE; ++file) {
    printf("%3c", 'a' + file);
  }
  puts("\n");

  printf("side:   %c\n",  sideChar[this->side]);
  printf("enPas:  %d\n", this->enPas);
  printf("castle: %c%c%c%c\n",
         this->castlePerm & WKCA ? 'K' : '-',
         this->castlePerm & WQCA ? 'Q' : '-',
         this->castlePerm & BKCA ? 'k' : '-',
         this->castlePerm & BQCA ? 'q' : '-');
  printf("posKey: %llX\n", this->posKey);
}

void Board::parseFEN(const char* fen) {
  int rank  = RANK_8;
  int file  = FILE_A;
  auto piece = 0;
  auto count = 0;
  auto sq64  = 0;
  auto sq120 = 0;

  this->reset();

  while ((rank >= RANK_1) && *fen) {
    count = 1;
    switch (*fen) {
    case 'p': piece = bP; break;
    case 'r': piece = bR; break;
    case 'n': piece = bN; break;
    case 'b': piece = bB; break;
    case 'q': piece = bQ; break;
    case 'k': piece = bK; break;
    case 'P': piece = wP; break;
    case 'R': piece = wR; break;
    case 'N': piece = wN; break;
    case 'B': piece = wB; break;
    case 'Q': piece = wQ; break;
    case 'K': piece = wK; break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
      piece = EMPTY;
      count = *fen - '0';
      break;

    case '/':
    case ' ':
      --rank;
      file = FILE_A;
      ++fen;
      continue;

    default:
      return; // TODO: throw exception with error detail.
    }

    for (auto i = 0; i != count; ++i) {
      sq64 = rank * 8 + file;
      sq120 = ::sq120(sq64);
      if (piece != EMPTY) {
        this->pieces[sq120] = piece;
      }
      ++file;
    }
    ++fen;
  }

  ASSERT(*fen == 'w' || *fen == 'b');

  this->side = (*fen == 'w') ? WHITE : BLACK;
  fen += 2;

  for (auto i = 0; i != 4; ++i) {
    if (*fen == ' ') {
      break;
    }

    switch (*fen) {
    case 'K': this->castlePerm |= WKCA; break;
    case 'Q': this->castlePerm |= WQCA; break;
    case 'k': this->castlePerm |= BKCA; break;
    case 'q': this->castlePerm |= BQCA; break;
    default: break;
    }
    ++fen;
  }
  ++fen;

  ASSERT(this->castlePerm > -1 && this->castlePerm < 16);

  if (*fen != '-') {
    file = fen[0] - 'a';
    rank = fen[1] - '1';

    ASSERT(file >= FILE_A && file < FILE_NONE);
    ASSERT(rank >= RANK_1 && rank < RANK_NONE);

    this->enPas = fr2sq(file, rank);
  }

  this->posKey = this->generatePosKey();
  this->updateMaterialLists();
}

void Board::reset() {
  for (auto& p : this->pieces) {
    p = NO_SQ;
  }
  for (auto i = 0; i != 64; ++i) {
    this->pieces[sq120(i)] = EMPTY;
  }
  for (auto i = 0; i != 3; ++i) {
    this->bigPce[i] = 0;
    this->majPce[i] = 0;
    this->minPce[i] = 0;
    this->material[i] = 0;
  }
  for (auto& p : this->pawns) {
    p = 0;
  }
  for (auto& n : this->pceNum) {
    n = 0;
  }
  this->kingSq[WHITE] = this->kingSq[BLACK] = NO_SQ;
  this->side = BOTH;
  this->enPas = NO_SQ;
  this->fiftyMove = 0;
  this->ply = 0;
  this->hisPly = 0;
  this->castlePerm = 0;
  this->posKey = 0;
}

U64 Board::generatePosKey() const {
  U64 finalKey = 0;
  
  for (auto sq = 0; sq != BRD_SQ_NUM; ++sq) {
    auto piece = this->pieces[sq];
    if (piece != NO_SQ && piece != EMPTY) {
      ASSERT(piece >= wP &&  piece <= bK);
      finalKey ^= pieceKeys[piece][sq];
    }
  }

  if (this->side == WHITE) {
    finalKey ^= sideKey;
  }

  if (this->enPas != NO_SQ) {
    ASSERT(this->enPas >= 0 && this->enPas < BRD_SQ_NUM);
    finalKey ^= pieceKeys[EMPTY][this->enPas];
  }

  ASSERT(this->castlePerm >= 0 && this->castlePerm <= 15);
  finalKey ^= castleKeys[this->castlePerm];

  return finalKey;
}
