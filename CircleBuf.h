// Copyright Eric Chauvin 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
#include "../CppMem/ByteArray.h"
#include "RangeC.h"
#include "StIO.h"



class CircleBuf
  {
  private:
  bool testForCopy = false;
  ByteArray cArray;
  Int32 first = 0;
  Int32 last = 0;

  public:
  inline CircleBuf( void )
    {
    setSize( 16 );
    }

  inline CircleBuf( const CircleBuf& in )
    {
    if( in.testForCopy )
      return;

    throw "CircleBuf copy constructor called.";
    }


  inline ~CircleBuf( void )
    {
    }


  inline Int32 getSize( void ) const
    {
    return cArray.getSize();
    }

  inline void setSize( const Int32 howBig )
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


  inline char getChar( void )
    {
    // Call isEmpty() before getting something.
    if( first == last )
      {
      StIO::putS( "CircleBuf is empty exception." );
      throw "CircleBuf is empty.";
      }

    char result = cArray.getC( first );
    first++;
    if( first >= cArray.getSize())
      first = 0;

    return result;
    }


  inline Uint8 getU8( void )
    {
    // Call isEmpty() before getting something.
    if( first == last )
      {
      StIO::putS( "CircleBuf is empty exception." );
      throw "CircleBuf is empty.";
      }

    Uint8 result = cArray.getU8( first );
    first++;
    if( first >= cArray.getSize())
      first = 0;

    return result;
    }


  inline void addChar( const char toAdd )
    {
    cArray.setC( last, toAdd );
    last++;
    if( last >= cArray.getSize())
      last = 0;

    if( last == first )
      {
      StIO::putS( "CircleBuf overflowed." );
      throw "CircleBuf overflowed.";
      }
    }


  inline void addU8( const Uint8 toAdd )
    {
    cArray.setU8( last, toAdd );
    last++;
    if( last >= cArray.getSize())
      last = 0;

    if( last == first )
      {
      StIO::putS( "CircleBuf overflowed." );
      throw "CircleBuf overflowed.";
      }
    }



  };
