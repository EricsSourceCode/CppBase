// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericinarizona.github.io/
// For guides and information.


/*
UTF-8 (UCS Transformation Format -8)
UCS: Universal Character Set

http://en.wikipedia.org/wiki/Unicode
http://en.wikipedia.org/wiki/UTF-8
http://en.wikipedia.org/wiki/Wide_character
http://en.wikipedia.org/wiki/UTF-16
http://en.wikipedia.org/wiki/
                    Basic_Multilingual_Plane
http://en.wikipedia.org/wiki/
                    Universal_Character_Set
*/


#pragma once



#include "BasicTypes.h"
#include "CharBuf.h"
#include "Uint16Buf.h"


class UTF8Str
  {
  private:
  bool testForCopy = false;

  public:
  UTF8Str( void )
    {
    }

  UTF8Str( const UTF8Str& in )
    {
    if( in.testForCopy )
      return;

    throw "UTF8Str copy constructor.";
    }

  ~UTF8Str( void )
    {
    }

  static void u16BufToCharBuf(
                        const Uint16Buf& inBuf,
                        CharBuf& outBuf );

  void charBufToU16Buf( const CharBuf& inBuf,
                        Uint16Buf& outBuf );

  };
