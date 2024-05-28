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


void Uint16Buf::appendU16Buf(
                   const Uint16Buf& u16Buf )
{
const Int32 howMany = u16Buf.getLast();

if( (last + howMany + 2) >= cArray.getSize() )
  increaseSize( howMany + (1024 * 16) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray.setVal( last, u16Buf.getVal( count ));
  last++;
  }
}



void Uint16Buf::appendCharBuf(
                   const CharBuf& cBuf )
{
const Int32 howMany = cBuf.getLast();

if( (last + howMany + 2) >= cArray.getSize() )
  increaseSize( howMany + (1024 * 16) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray.setVal( last, cBuf.getU8( count ));
  last++;
  }
}



Int32 Uint16Buf::getField( Uint16Buf& toGet,
                  const Int32 startAt,
                  const Uint16 delimit ) const
{
toGet.clear();
if( startAt < 0 )
  return -1;

const Int32 max = last;

if( startAt >= max )
  return -1;

for( Int32 count = startAt; count < max;
                                       count++ )
  {
  Uint16 val = cArray.getVal( count );
  if( val == delimit )
    return count;

  toGet.appendU16( val );
  }

return -1;
}



Int32 Uint16Buf::getFieldC( CharBuf& toGet,
                  const Int32 startAt,
                  const Uint16 delimit ) const
{
toGet.clear();
if( startAt < 0 )
  return -1;

const Int32 max = last;

if( startAt >= max )
  return -1;

for( Int32 count = startAt; count < max;
                                       count++ )
  {
  Uint16 val = cArray.getVal( count );
  if( val == delimit )
    return count;

  toGet.appendU8( val & 0x7F );
  }

return -1;
}



void Uint16Buf::showAscii( void ) const
{
const Int32 max = getLast();
for( Int32 count = 0; count < max; count++ )
  {
  Uint16 oneByte = getVal( count );
  if( oneByte == 10 ) // Line Feed.
    {
    StIO::putLF();
    continue;
    }

  if( (oneByte < 127) && (oneByte >= 32))
    {
    char showC = oneByte & 0x7F;
    StIO::putChar( showC );
    }
  }

StIO::putLF();
}



void Uint16Buf::toCharBuf( CharBuf& toGet ) const
{
const Int32 max = last;

for( Int32 count = 0; count < max; count++ )
  {
  Uint16 val = getVal( count );
  Uint8 highByte = (val >> 8) & 0xFF;
  Uint8 lowByte = val & 0xFF;
  toGet.appendU8( highByte );
  toGet.appendU8( lowByte );
  }
}




bool Uint16Buf::isEqual(
               const Uint16Buf& toCheck ) const
{
if( last != toCheck.last )
  return false;

const Int32 max = last;
for( Int32 count = 0; count < max; count++ )
  {
  if( cArray.getVal( count ) !=
               toCheck.cArray.getVal( count ) )
    return false;

  }

return true;
}




bool Uint16Buf::searchMatches(
                  const Int32 position,
                  const Uint16Buf& toFind ) const
{
const Int32 findLength = toFind.getLast();
if( findLength < 1 )
  return false;

if( (position + findLength - 1) >= last )
  return false;

for( Int32 count = 0; count < findLength;
                                     count++ )
  {
  Uint16 val = cArray.getVal(
                           position + count );
  val = toLower( val );

  if( val != toFind.getVal( count ) )
    return false;

  }

return true;
}



Int32 Uint16Buf::findText(
                    const Uint16Buf& toFind,
                    const Int32 startAt ) const
{
const Int32 max = last;

if( startAt >= max )
  return -1;

const Int32 toFindLen = toFind.getLast();
Uint16Buf toFindLow;
for( Int32 count = startAt; count < toFindLen;
                                       count++ )
  {
  toFindLow.appendU16( toLower(
                     toFind.getVal( count )) );
  }

for( Int32 count = startAt; count < max; count++ )
  {
  if( searchMatches( count, toFindLow ))
    return count;

  }

return -1;
}

#include "../CppMem/MemoryWarnTop.h"


void Uint16Buf::setFromCharPoint(
                         const char* pStr )
{
last = 0;
if( pStr == nullptr )
  return;

const char* sizePoint = pStr;

Int32 strSize = 0;

// Make it a reasonable loop count so it
// doesn't go forever if it never finds null.

bool foundNull = false;
for( Int32 count = 0; count < 5000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    {
    foundNull = true;
    break;
    }

  sizePoint++;
  strSize++;
  }

if( !foundNull )
  return;

const Int32 max = strSize;

setSize( max + 1 );

for( Int32 count = 0; count < max; count++ )
  {
  char c = *pStr;
  cArray.setVal( last, c & 0x7F  );
  last++;
  pStr++;
  }
}


#include "../CppMem/MemoryWarnBottom.h"
