#pragma once
#include "cryptoTools/Common/Defines.h"
#ifdef ENABLE_CIRCUITS

#include "BetaCircuit.h"
#include <unordered_map>
#include "cryptoTools/Common/BitVector.h"

namespace osuCrypto {
class BetaLibrary {
public:
  BetaLibrary();
  ~BetaLibrary();
  enum class Optimized {
    Size,
    Depth
  };

  enum class IntType {
    TwosComplement,
    Unsigned
  };
  enum class AdderType {
    Addition,
    Subtraction
  };

  std::unordered_map<u64, BetaCircuit*> mCirMap;

  BetaCircuit* int_int_add(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_add_msb(u64 aSize, Optimized op = Optimized::Size);

  BetaCircuit* uint_uint_add(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_intConst_add(u64 aSize, u64 bSize, i64 bVal, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_subtract(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_sub_msb(u64 aSize, u64 bSize, Optimized op = Optimized::Size);
  BetaCircuit* uint_uint_subtract(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* uint_uint_sub_msb(u64 aSize, u64 bSize, Optimized op = Optimized::Size);

  BetaCircuit* int_intConst_subtract(u64 aSize, u64 bSize, i64 bVal, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_mult(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_div(u64 aSize, u64 bSize, u64 cSize);

  BetaCircuit* int_eq(u64 aSize);
  BetaCircuit* int_neq(u64 aSize);

  BetaCircuit* int_int_lt(u64 aSize, u64 bSize, Optimized op = Optimized::Size);
  BetaCircuit* int_int_gteq(u64 aSize, u64 bSize, Optimized op = Optimized::Size);

  BetaCircuit* uint_uint_lt(u64 aSize, u64 bSize, Optimized op = Optimized::Size);
  BetaCircuit* uint_uint_gteq(u64 aSize, u64 bSize, Optimized op = Optimized::Size);
  BetaCircuit* uint_uint_mult(u64 aSize, u64 bSize, u64 cSize, Optimized op = Optimized::Size);

  BetaCircuit* int_int_multiplex(u64 aSize);

  BetaCircuit* int_removeSign(u64 aSize, Optimized op = Optimized::Size);
  BetaCircuit* int_addSign(u64 aSize, Optimized op = Optimized::Size);
  BetaCircuit* int_negate(u64 aSize, Optimized op = Optimized::Size);
  BetaCircuit* int_isZero(u64 aSize);

  BetaCircuit* int_bitInvert(u64 aSize);
  BetaCircuit* int_int_bitwiseAnd(u64 aSize, u64 bSize, u64 cSize);
  BetaCircuit* int_int_bitwiseOr(u64 aSize, u64 bSize, u64 cSize);
  BetaCircuit* int_int_bitwiseXor(u64 aSize, u64 bSize, u64 cSize);

  BetaCircuit* aes_exapnded(u64 rounds);


  // begin origin interface
  // base algorithm for depth optimized addition and subtraction.
  static void parallelPrefix_build(
      BetaCircuit& cd,
      BetaBundle a1,
      BetaBundle a2,
      const BetaBundle& out,
      IntType it,
      AdderType at);

  // base algorithm for size optimized addition and subtraction.
  static void rippleAdder_build(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& out,
      const BetaBundle& temps,
      IntType it,
      AdderType at);

  static void add_build(
      BetaCircuit& cd,
      BetaBundle a1,
      BetaBundle a2,
      const BetaBundle & sum,
      const BetaBundle & temps,
      IntType it,
      Optimized op);

  static void subtract_build(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& diff,
      const BetaBundle& temps,
      IntType it,
      Optimized op);

  // add or subtract a1,a2 and then get the bit of the result at the provided index.
  // Can be size or depth optimized. Inputs can be twos complement or unsigned.
  static void extractBit_build(
    BetaCircuit& cd,
    const BetaBundle & a1,
    const BetaBundle & a2,
    const BetaBundle & bit,
    const BetaBundle & temps,
    u64 bitIdx,
    IntType it,
    AdderType at,
    Optimized op);

  static void mult_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & prod,
      Optimized o,
      IntType it);

  static void div_rem_build(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& quot,
      const BetaBundle& rem,
      IntType it,
      Optimized op);

  static void isZero_build(
      BetaCircuit& cd,
      BetaBundle & a1,
      BetaBundle & out);

  static void eq_build(
      BetaCircuit& cd,
      BetaBundle & a1,
      BetaBundle & a2,
      BetaBundle & out);

  static void lessThan_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out,
      IntType it,
      Optimized op);

  static void greaterThanEq_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out,
      IntType it,
      Optimized op);


  // get the absolute value
  static void removeSign_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out,
      const BetaBundle & temp,
      Optimized op);

  // set the sign. a1 assumed unsigned.
  static void int_addSign_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & sign,
      const BetaBundle & out,
      const BetaBundle & temp,
      Optimized op);

  static void int_negate_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out,
      const BetaBundle & temp,
      Optimized op);

  static void bitwiseInvert_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out);

  static void bitwiseAnd_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void bitwiseOr_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void bitwiseXor_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  // if choice = 1, the take the first parameter (ifTrue). Otherwise take the second parameter (ifFalse).
  static void multiplex_build(
      BetaCircuit& cd,
      const BetaBundle & ifTrue,
      const BetaBundle & ifFalse,
      const BetaBundle & choice,
      const BetaBundle & out,
      const BetaBundle & temp);
  // end origin interface

  static void aes_sbox_build(
      BetaCircuit& cd,
      const BetaBundle & in,
      const BetaBundle & out);

  static void aes_shiftRows_build(
      BetaCircuit& cd,
      const BetaBundle & in,
      const BetaBundle & out);

  static void aes_mixColumns_build(
      BetaCircuit& cd,
      const BetaBundle & in,
      const BetaBundle & out);

  static void aes_exapnded_build(
      BetaCircuit& cd,
      const BetaBundle & message,
      const BetaBundle & expandedKey,
      const BetaBundle & ciphertext);

  static bool areDistint(BetaCircuit& cd,
                        const BetaBundle& a1,
                        const BetaBundle& a2);
      //u64 aSize, u64 bSize, u64 cSize);
  // compatible interface
  static void int_int_add_build_so(
    BetaCircuit& cd,
    const BetaBundle & a1,
    const BetaBundle & a2,
    const BetaBundle & sum,
    const BetaBundle & temps);

  static void int_int_add_build_do(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & sum,
      const BetaBundle & temps);

  static void int_int_add_build_do(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & sum) {
    BetaBundle  temps(a1.size() * 2);
    cd.addTempWireBundle(temps);
    int_int_add_build_do(cd, a1, a2, sum, temps);
  }

  static void int_int_add_msb_build_do(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & sum,
      const BetaBundle & temps);

  static void uint_uint_add_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & sum,
      const BetaBundle & temps);

  static void int_int_subtract_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & diff,
      const BetaBundle & temps);

  static void int_int_sub_msb_build_do(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& diff,
      const BetaBundle& temps);

  static void uint_uint_subtract_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & diff,
      const BetaBundle & temps);

  static void int_int_mult_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & prod,
      Optimized o,
      bool useTwoComplement);

  static void int_int_div_rem_build(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& quot,
      const BetaBundle& rem);

  static void uint_uint_div_rem_build(
      BetaCircuit& cd,
      const BetaBundle& a1,
      const BetaBundle& a2,
      const BetaBundle& quot,
      const BetaBundle& rem);

  static void int_isZero_build(
      BetaCircuit& cd,
      BetaBundle & a1,
      BetaBundle & out);

  static void int_int_eq_build(
      BetaCircuit& cd,
      BetaBundle & a1,
      BetaBundle & a2,
      BetaBundle & out);

  static void int_int_lt_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void int_int_gteq_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void uint_uint_lt_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void uint_uint_gteq_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void int_removeSign_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out,
      const BetaBundle & temp);

  static void int_addSign_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & sign,
      const BetaBundle & out,
      const BetaBundle & temp);

  static void int_bitInvert_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out);

  static void int_negate_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & out,
      const BetaBundle & temp);

  static void int_int_bitwiseAnd_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void int_int_bitwiseOr_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  static void int_int_bitwiseXor_build(
      BetaCircuit& cd,
      const BetaBundle & a1,
      const BetaBundle & a2,
      const BetaBundle & out);

  // if choice = 1, the take the first parameter (ifTrue).
  // Otherwise take the second parameter (ifFalse).
  static void int_int_multiplex_build(
      BetaCircuit& cd,
      const BetaBundle & ifTrue,
      const BetaBundle & ifFalse,
      const BetaBundle & choice,
      const BetaBundle & out,
      const BetaBundle & temp);

};


inline std::ostream& operator<<(std::ostream& o, BetaLibrary::Optimized op) {
  if (op == BetaLibrary::Optimized::Depth)
    o << "Optimized::Depth";
  else
    o << "Optimized::Size";
  return o;
}

}
#endif  // ENABLE_CIRCUITS
