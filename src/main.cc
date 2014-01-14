#include "defs.hh"

int main(int argc, char* argv[])
{
  initAll();
        
  auto bb = 0ULL;

  puts("Start:");
  printBitBoard(bb);

  bb |= (1ULL << sq64(D2));
  puts("D2 added:");
  printBitBoard(bb);

  bb |= (1ULL << sq64(G2));
  puts("G2 added:");
  printBitBoard(bb);

  printf("Count: %d\n", cnt(bb));

  auto ix = pop(&bb);
  printf("Index: %d\n", ix);
  printBitBoard(bb);

  getc(stdin); // keep console window open
}
