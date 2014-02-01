#include "util.hh"
#include <cstdio>

char* vice::prSq(int sq) {
  static char sqStr[3];
  
  auto file = filesBrd[sq];
  auto rank = ranksBrd[sq];
  
  snprintf(sqStr, sizeof (sqStr), "%c%c", 
           'a' + file, '1' + rank);
 
  return sqStr;
}
