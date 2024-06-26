// Copyright Eric Chauvin 2024



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
#include "RangeC.h"
#include "CharBuf.h"
#include "../CppMem/Uint16Array.h"



class Uint16Buf
  {
  private:
  bool testForCopy = false;
  Uint16Array cArray;
  Int32 last = 0;

  void increaseSize( Int32 howMuch );

  public:
  Uint16Buf( void )
    {
    setSize( 1 );
    }

  Uint16Buf( const Uint16Buf& in )
    {
    if( in.testForCopy )
      return;

    throw "Uint16Buf copy constructor.";
    }

  ~Uint16Buf( void )
    {
    }

  void setSize( const Int32 howBig );

  inline Int32 getLast( void ) const
    {
    return last;
    }

  void truncateLast( const Int32 setTo )
    {
    if( setTo < 0 )
      throw "Uint16Buf.truncateLast < zero.";

    if( setTo > last )
      throw "Uint16Buf.truncateLast too big.";

    last = setTo;
    }

  inline void clear( void )
    {
    last = 0;
    }


  void appendU16( const Uint16 toSet );

  inline Uint16 getVal( const Int32 where ) const
    {
    if( where >= last )
      throw "Uint16Buf.getVal() past last.";

    return cArray.getVal( where );
    }


  inline void setVal( const Int32 where,
                      const Uint16 toSet )
    {
    if( where >= last )
      throw "Uint16Buf.setVal where past last.";

    cArray.setVal( where, toSet );
    }

  void copy( const Uint16Buf& toCopy );

  void appendU16Buf( const Uint16Buf& u16Buf );
  void appendCharBuf( const CharBuf& cBuf );
  Int32 getField( Uint16Buf& toGet,
                  const Int32 startAt,
                  const Uint16 delimit ) const;
  Int32 getFieldC( CharBuf& toGet,
                  const Int32 startAt,
                  const Uint16 delimit ) const;
  void showAscii( void ) const;
  void toCharBuf( CharBuf& toGet ) const;
  bool isEqual( const Uint16Buf& toCheck ) const;

  static inline Uint16 toLower(
                       const Uint16 fromVal )
    {
    if( !((fromVal >= 'A') &&
                          (fromVal <= 'Z')) )
      return fromVal;

    // 'A' is 65 and 'a' is 97.
    // A lower case letter is 32 plus the
    // upper case letter.  So that is the
    // fifth bit.
    const Uint16 fifth = 'a' - 'A';
    return fromVal + fifth;
    // Or xor that fifth bit.
    // return fromChar xor fifth;
    }

  bool searchMatches(
                 const Int32 position,
                 const Uint16Buf& toFind ) const;

  Int32 findText( const Uint16Buf& toFind,
                  const Int32 startAt ) const;

  void setFromCharPoint( const char* pStr );

  };
