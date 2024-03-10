// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
// #include "../CppBase/StIO.h"


class ByteSet64
  {
  private:

  public:
  static inline Uint8 getByte( const Int32 where,
                               const Int64 from )
    {
    Int64 from2 = from;
    from2 >>= 8 * where;
    Uint8 aByte = from2 & 0xFF;
    return aByte;
    }

  static inline Int64 setByte( const Int32 where,
                               const Int64 from,
                               const Uint8 aByte )
    {
    Int64 bigByte = aByte;
    bigByte <<= 8 * where;

    Int64 bitsFF = 0xFF;
    bitsFF <<= 8 * where;

    Int64 oldByte = from & bitsFF;

    Int64 clearedVal = from ^ oldByte;
    Int64 result = clearedVal | bigByte;
    return result;
    }

  };
