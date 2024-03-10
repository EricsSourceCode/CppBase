// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "Uint16Buf.h"
#include "StIO.h"
#include "Casting.h"
#include "ByteHex.h"



void Uint16Buf::setSize( const Int32 howBig )
{
last = 0;
cArray.setSize( howBig );
}


void Uint16Buf::increaseSize( const Int32 howMuch )
{
cArray.increaseSize( howMuch );
}



void Uint16Buf::copy( const Uint16Buf& toCopy )
{
last = toCopy.last;

cArray.copy( toCopy.cArray, last,
                   toCopy.cArray.getSize() );
}



void Uint16Buf::appendU16( const Uint16 toSet )
{
if( (last + 1) >= cArray.getSize() )
  increaseSize( 1024 * 64 );

cArray.setVal( last, toSet );
last++;
}


/*

void Uint16Buf::appendCharBuf( const CharBuf& charBuf )
{
const Int32 howMany = charBuf.getLast();

if( (last + howMany + 2) >= cArray.getSize() )
  increaseSize( howMany + (1024 * 16) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray.setC( last, charBuf.getC( count ));
  last++;
  }
}
*/






/*
void CharBuf::showHex( void ) const
{
const Int32 max = getLast();
for( Int32 count = 0; count < max; count++ )
  {
  Uint8 oneByte = getU8( count );
  char leftC = ByteHex::getLeftChar( oneByte );
  StIO::putChar( leftC );
  char rightC = ByteHex::getRightChar( oneByte );
  StIO::putChar( rightC );
  StIO::putChar( ' ' );
  }

StIO::putLF();
}
*/



void Uint16Buf::appendCharBuf(
                   const CharBuf& charBuf )
{
const Int32 howMany = charBuf.getLast();

if( (last + howMany + 2) >= cArray.getSize() )
  increaseSize( howMany + (1024 * 16) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray.setVal( last, charBuf.getU8( count ));
  last++;
  }
}
