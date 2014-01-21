#include "vice.hh"
#include "board.hh"
#include "bitboard.hh"

int main(int argc, char* argv[])
{
  vice::init();

  const char* positions[] = {
    START_FEN,
    "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
    "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2",
    "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2",
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
  };
  
  vice::Board board;
  
  for (auto fen : positions) {
    board.parseFEN(fen);
    board.print();
    board.validate();
  }
}
