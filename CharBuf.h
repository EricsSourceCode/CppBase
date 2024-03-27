// Copyright Eric Chauvin 2022 - 2024



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
#include "RangeC.h"
#include "../CppMem/ByteArray.h"
#include "../CppMem/OpenCharArray.h"



class CharBuf
  {
  private:
  bool testForCopy = false;
  ByteArray cArray;
  Int32 last = 0;

  void increaseSize( Int32 howMuch );

  public:
  CharBuf( void )
    {
    setSize( 64 * 1024 );
    }

  CharBuf( const char* pStr );

  CharBuf( const Int64 n )
    {
    setFromInt64( n );
    }

  CharBuf( const CharBuf &in );

  inline ~CharBuf( void )
    {
    }

  void setFromCharPoint( const char* pStr );
  void setFromInt64( const Int64 inN );
  void setFromUint64( const Uint64 inN );

  void setSize( const Int32 howBig );

  inline Int32 getLast( void ) const
    {
    return last;
    }

  void truncateLast( const Int32 setTo )
    {
    if( setTo < 0 )
      throw "CharBuf.truncateLast < zero.";

    if( setTo > last )
      throw "CharBuf.truncateLast too big.";

    last = setTo;
    }

  inline void clear( void )
    {
    last = 0;
    }

  void copyToCharArray( ByteArray& copyTo );

  void copyToOpenCharArrayNoNull(
                  OpenCharArray& copyTo ) const;

  void copyToOpenCharArrayNull(
                  OpenCharArray& copyTo ) const;

  void copyFromOpenCharArrayNoNull(
                  const OpenCharArray& copyFrom );

  void copyFromOpenCharArrayNull(
                  const OpenCharArray& copyFrom );

  void appendChar( const char toSet );

  void appendCharPt( const char* pStr );

  void appendCharArray( const ByteArray& toAdd,
                        const Int32 howMany );

  void appendCharBuf( const CharBuf& charBuf );

  inline char getC( const Int32 where ) const
    {
    if( where >= last )
      throw "getC() past last.";

    return cArray.getC( where );
    }

  inline Uint8 getU8( const Int32 where ) const
    {
    if( where >= last )
      throw "getU8() past last.";

    return cArray.getU8( where );
    }

  inline void setC( const Int32 where,
                    const char toSet )
    {
    if( where >= last )
      throw "CharBuf.setC where past last.";

    cArray.setC( where, toSet );
    }


  inline void setU8( const Int32 where,
                     const Uint8 toSet )
    {
    if( where >= last )
      throw "CharBuf.setU8 where past last.";

    cArray.setU8( where, toSet );
    }


  void copy( const CharBuf& toCopy );

  Int32 findChar( const Int32 start,
                  const char toFind );

  void appendU8( const Uint32 toSet );

  void appendU16( const Uint32 toSet );

  void appendU32( const Uint32 toSet );

  void appendU64( const Uint64 toSet );

  Uint32 getU32( const Int32 where ) const;
  Uint64 getU64( const Int32 where ) const;

  Uint32 get24Bits( const Int32 where ) const;
  Uint32 get16Bits( const Int32 where ) const;

  void append24Bits( const Uint32 toSet );

  void testBasics( void );
  bool isEqual( const CharBuf& toCheck ) const;
  void reverse( void );
  void showHex( void ) const;
  void showAscii( void ) const;

  inline void fillBytes( const Uint8 toSet,
                         const Int32 howMany )
    {
    clear();
    for( Int32 count = 0; count < howMany; count++ )
      appendU8( toSet );

    }

  void setFromHexTo256( const CharBuf& hexBuf );

  inline void xorFrom( const CharBuf& fromBuf )
    {
    if( last != fromBuf.last )
      throw "CharBuf::xorFrom last != from.";

    const Int32 max = last;
    for( Int32 count = 0; count < max; count++ )
      {
      char fromByte = fromBuf.getC( count );
      char toSet = fromByte xor getC( count );
      cArray.setC( count, toSet );
      }
    }


  };
