#include "vice.hh"
#include "move.hh"
#include "util.hh"

using namespace vice;

int main(int argc, char* argv[])
{
  init();

  int from = A2; int to = H7;
  int capt = wR; int prom = bQ;
  
  Move m;
  m.move = from | (to << 7) | (capt << 14) | (prom << 20);
  
  printf("from: %s\n", prSq( m.fromSq() ));
  printf("to:   %s\n", prSq( m.toSq() ));
  printf("move: %s\n", m.print());
}
