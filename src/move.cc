#include "move.hh"
#include "vice.hh"

using namespace vice;

char* Move::print() const {
  static char mvStr[6];
  
  auto ff = filesBrd[this->fromSq()];
  auto rf = ranksBrd[this->fromSq()];
  auto ft = filesBrd[this->toSq()];
  auto rt = ranksBrd[this->toSq()];

  auto pce = this->promotedPce();
  
  if (pce) {
    char pc = 'q';
    
    if (pieceKn[pce]) { 
      pc = 'n';
    } else if (pieceRQ[pce] && !pieceBQ[pce]) {
      pc = 'r';
    } else if (!pieceRQ[pce] && pieceBQ[pce]) {
      pc = 'b';
    }

    snprintf(mvStr, sizeof (mvStr), "%c%c%c%c%c",
             'a' + ff, '1' + rf, 'a' + ft, '1' + rt, pc);
  } else {
    snprintf(mvStr, sizeof (mvStr), "%c%c%c%c",
             'a' + ff, '1' + rf, 'a' + ft, '1' + rt);
  }

  return mvStr;
}
