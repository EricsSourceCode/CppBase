// Copyright Eric Chauvin 2022 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
#include "../CppMem/ByteArray.h"
#include "RangeC.h"
#include "StIO.h"
#include "CharBuf.h"



class CircleBuf
  {
  private:
  bool testForCopy = false;
  ByteArray cArray;
  Int32 first = 0;
  Int32 last = 0;

  public:
  CircleBuf( void )
    {
    setSize( 16 );
    }

  CircleBuf( const CircleBuf& in )
    {
    if( in.testForCopy )
      return;

    throw "CircleBuf copy constructor called.";
    }


  ~CircleBuf( void )
    {
    }


  Int32 getSize( void ) const
    {
    return cArray.getSize();
    }

  void setSize( const Int32 howBig )
    {
    first = 0;
    last = 0;
    cArray.setSize( howBig );
    }


  inline bool isEmpty( void ) const
    {
    if( first == last )
      return true;

    return false;
    }


  char getChar( void )
    {
    // Call isEmpty() before getting something.
    if( first == last )
      throw "CircleBuf.getChar() is empty.";

    char result = cArray.getC( first );
    first++;
    if( first >= cArray.getSize())
      first = 0;

    return result;
    }


  Uint8 getU8( void )
    {
    // Call isEmpty() before getting something.
    if( first == last )
      {
      throw "CircleBuf.getU8() is empty.";
      }

    Uint8 result = cArray.getU8( first );
    first++;
    if( first >= cArray.getSize())
      first = 0;

    return result;
    }


  void addChar( const char toAdd )
    {
    cArray.setC( last, toAdd );
    last++;
    if( last >= cArray.getSize())
      last = 0;

    if( last == first )
      throw "CircleBuf overflowed.";

    }


  void addU8( const Uint8 toAdd )
    {
    cArray.setU8( last, toAdd );
    last++;
    if( last >= cArray.getSize())
      last = 0;

    if( last == first )
      throw "CircleBuf.addU8() overflowed.";

    }


  void appendToCharBuf( CharBuf& toGet,
                      const Int32 howMany )
    {
    for( Int32 count = 0; count < howMany;
                                     count++ )
      {
      if( isEmpty())
        break;

      toGet.appendU8( getU8());
      }
    }


  void addCharBuf( const CharBuf& toAdd )
    {
    const Int32 lastIn = toAdd.getLast();
    for( Int32 count = 0; count < lastIn;
                                      count++ )
      {
      addU8( toAdd.getU8( count ));
      }
    }



  Int32 getHowMany( void )
    {
    if( last == first )
      return 0;

    if( last > first )
      return last - first;

    // last is less than first.
    Int32 result = last + getSize();
    result -= first;
    return result;
    }


  };
