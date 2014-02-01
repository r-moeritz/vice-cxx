#ifndef MOVE_HH
#define MOVE_HH

namespace vice {
  struct Move {
    const int EP   = 0x40000;
    const int PS   = 0x80000;
    const int CA   = 0x100000;
    const int CAPT = 0x7C000;
    const int PROM = 0xF00000;

    /* move layout: 
       
       0000 0000 0000 0000 0000 0111 1111          0x7F        from square
       0000 0000 0000 0011 1111 1000 0000    >> 7  0x7F        to square
       0000 0000 0011 1100 0000 0000 0000    >> 14 0xF         captured piece
       0000 0000 0100 0000 0000 0000 0000          0x40000     en passant
       0000 0000 1000 0000 0000 0000 0000          0x80000     pawn start
       0000 1111 0000 0000 0000 0000 0000    >> 20 0xF         promoted piece
       0001 0000 0000 0000 0000 0000 0000          0x100000    castle
     */
    int move;
    int score;

    inline int fromSq() const {
      return this->move & 0x7F;
    }

    inline int toSq() const {
      return (this->move >> 7) & 0x7F;
    }

    inline int capturedPce() const {
      return (this->move >> 14) & 0xF;
    }

    inline int promotedPce() const {
      return (this->move >> 20) & 0xF;
    }

    char* print() const;
  };
}

#endif // !MOVE_HH
