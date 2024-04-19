// Copyright Eric Chauvin 2022 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/StIO.h"


class ByteHex
  {
  private:

  public:

  static char intToChar( Int32 c )
    {
    switch( c )
      {
      case 0: return '0';
      case 1: return '1';
      case 2: return '2';
      case 3: return '3';
      case 4: return '4';
      case 5: return '5';
      case 6: return '6';
      case 7: return '7';
      case 8: return '8';
      case 9: return '9';
      case 10: return 'A';
      case 11: return 'B';
      case 12: return 'C';
      case 13: return 'D';
      case 14: return 'E';
      case 15: return 'F';
      }

    return '?';
    }


  static char valToChar( Uint8 c )
    {
    switch( c )
      {
      case 0: return '0';
      case 1: return '1';
      case 2: return '2';
      case 3: return '3';
      case 4: return '4';
      case 5: return '5';
      case 6: return '6';
      case 7: return '7';
      case 8: return '8';
      case 9: return '9';
      case 10: return 'A';
      case 11: return 'B';
      case 12: return 'C';
      case 13: return 'D';
      case 14: return 'E';
      case 15: return 'F';
      }

    return '?';
    }

  static char getRightChar( Uint8 theByte )
    {
    return valToChar( theByte & 0xF );
    }

  static char getLeftChar( Uint8 theByte )
    {
    return valToChar( (theByte >> 4) & 0xF );
    }


  static Uint8 charToU8( const char c )
    {
    switch( c )
      {
      case '0': return 0;
      case '1': return 1;
      case '2': return 2;
      case '3': return 3;
      case '4': return 4;
      case '5': return 5;
      case '6': return 6;
      case '7': return 7;
      case '8': return 8;
      case '9': return 9;

      case 'a': return 10;
      case 'b': return 11;
      case 'c': return 12;
      case 'd': return 13;
      case 'e': return 14;
      case 'f': return 15;

      case 'A': return 10;
      case 'B': return 11;
      case 'C': return 12;
      case 'D': return 13;
      case 'E': return 14;
      case 'F': return 15;
      }

    return 128;
    }

  static bool isValidChar( const char c )
    {
    switch( c )
      {
      case '0': return true;
      case '1': return true;
      case '2': return true;
      case '3': return true;
      case '4': return true;
      case '5': return true;
      case '6': return true;
      case '7': return true;
      case '8': return true;
      case '9': return true;

      case 'a': return true;
      case 'b': return true;
      case 'c': return true;
      case 'd': return true;
      case 'e': return true;
      case 'f': return true;

      case 'A': return true;
      case 'B': return true;
      case 'C': return true;
      case 'D': return true;
      case 'E': return true;
      case 'F': return true;
      }

    return false;
    }


  static void showByte( const Uint8 val )
    {
    char c = getLeftChar( val );
    StIO::putChar( c );
    c = ByteHex::getRightChar( val );
    StIO::putChar( c );
    }

  static void showUint32( const Uint32 val )
    {
    Uint8 aByte = (val >> 24) & 0xFF;
    showByte( aByte );

    aByte = (val >> 16) & 0xFF;
    showByte( aByte );

    aByte = (val >> 8) & 0xFF;
    showByte( aByte );

    aByte = val & 0xFF;
    showByte( aByte );
    }


  static Int32 charBufToInt32(
                         const CharBuf& inBuf )
    {
    Int32 result = 0;
    const Int32 base = 16;
    Int32 positionBase = 1;
    const Int32 max = inBuf.getLast();

    for( Int32 count = max - 1; count >= 0;
                                     count-- )
      {
      Int32 digit = charToU8(
                  inBuf.getC( count )) & 0xFF;

      digit = digit * positionBase;
      result += digit;

      positionBase = positionBase * base;

      // Don't multiply too big of a
      // positionBase.
      if( positionBase > 0x3FFFFFF )
        break;

      }

    return result;
    }


  };
