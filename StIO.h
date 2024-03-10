// Copyright Eric Chauvin 2022 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
#include "CharBuf.h"



class StIO
  {
  private:

  public:
  static void printFStack( void );
  static void printF( const char* toWrite );
  // putS adds a newline to the end.
  static void putS( const char* toWrite );
  static void printFD( const Int64 x );
  static void printFUD( const Uint64 d );
  static void printFX( const Uint32 x );
  static void putChar( const int c );
  static void putLF( void );

  static void putWChar( const Uint16 c );
  static void putCharBuf( const CharBuf& charBuf );

  // bool checkKey( void );

  };
