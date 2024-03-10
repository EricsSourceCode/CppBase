// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericinarizona.github.io/
// For guides and information.



#include "UTF8Str.h"


void UTF8Str::u16BufToCharBuf(
                      const Uint16Buf& inBuf,
                      CharBuf& outBuf )
{
const Int32 last = inBuf.getLast();
outBuf.clear();

if( last == 0 )
  return;


// Bits
//  7   U+007F   0xxxxxxx
// 11   U+07FF   110xxxxx   10xxxxxx
// 16   U+FFFF   1110xxxx   10xxxxxx   10xxxxxx
// 21   U+1FFFFF   11110xxx   10xxxxxx
//            10xxxxxx   10xxxxxx
// 26   U+3FFFFFF   111110xx   10xxxxxx
//            10xxxxxx   10xxxxxx   10xxxxxx
// 31   U+7FFFFFFF   1111110x   10xxxxxx
//        10xxxxxx   10xxxxxx   10xxxxxx   10x

// try
// {

for( Int32 count = 0; count < last; count++ )
  {
  Uint16 letter = inBuf.getVal( count );
  if( letter <= 0x7F )
    {
    // Regular ASCII.
    outBuf.appendU8( letter & 0xFF );
    continue;
    }

  if( letter >= 0xD800 ) // High Surrogates
    break; // This should have been
           // cleaned out already.

  //  7   U+007F   0xxxxxxx
  // 11   U+07FF   110xxxxx   10xxxxxx
  // 16   U+FFFF   1110xxxx   10xxxxxx   10xxxxxx
  if( (letter > 0x7F) && (letter <= 0x7FF) )
    {
    Uint8 smallByte = letter & 0x3F;
    Uint8 bigByte = ((letter >> 6) & 0x1F);
    bigByte |= 0xC0; // Mark it as the
                     // beginning byte.
    smallByte |= 0x80; // Mark it as a
                       // continuing byte.
    outBuf.appendU8( bigByte );
    outBuf.appendU8( smallByte );
    }

  // 16   U+FFFF   1110xxxx   10xxxxxx   10xxxxxx
  if( letter > 0x7FF ) // && (letter < 0xD800) )
    {
    Uint8 byte3 = letter & 0x3F;
    Uint8 byte2 = ((letter >> 6) & 0x3F);
    Uint8 bigByte = ((letter >> 12) & 0x0F);

    bigByte |= 0xE0; // Mark it as the
                     // beginning byte.
    byte2 |= 0x80; // Mark it as a
                   // continuing byte.
    byte3 |= 0x80; // Mark it as a
                   // continuing byte.
    outBuf.appendU8( bigByte );
    outBuf.appendU8( byte2 );
    outBuf.appendU8( byte3 );
    }
  }

//    Array.Resize( ref Result, Where );
}




void UTF8Str::charBufToU16Buf(
                      const CharBuf& inBuf,
                      Uint16Buf& outBuf )
{
const Int32 last = inBuf.getLast();
outBuf.clear();

if( last == 0 )
  return;

// try
// {

for( Int32 count = 0; count < last; count++ )
  {
  Uint8 inByte = inBuf.getU8( count );
  if( (inByte & 0x80) == 0 )
    {
    // It's regular ASCII.
    outBuf.appendU16( inByte );
    continue;
    }

  if( (inByte & 0xC0) == 0x80 )
    {
    // It's a continuing byte that has
    // already been read below.
    // Or it's garbage.
    continue;
    }

  if( (inByte & 0xC0) == 0xC0 )
    {
    // It's a beginning byte.
    // A beginning byte is either 110xxxxx
    // or 1110xxxx.
    if( (inByte & 0xF0) == 0xE0 )
      {
      // Starts with 1110xxxx.
      // It's a 3-byte character.
      if( (count + 2) >= last )
        break; // Ignore the garbage.

      Uint16 bigByte = (inByte & 0x0F);
      Uint16 byte2 = inBuf.getU8( count + 1 )
                                      & 0x3F;

      Uint16 byte3 = inBuf.getU8( count + 2 )
                                      & 0x3F;

      Uint16 letter = (bigByte << 12) & 0xFFFF;
      letter |= byte2 << 6;
      letter |= byte3;
      if( letter< 0xD800 ) // High Surrogates
        outBuf.appendU16( letter );

      }

    if( (inByte & 0xE0) == 0xC0 )
      {
      // Starts with 110xxxxx.
      // It's a 2-byte character.
      if( (count + 1) >= last )
        continue; // Ignore the garbage.

      Uint16 bigByte = inByte & 0x1F;
      Uint16 byte2 =  inBuf.getU8( count + 1 )
                                       & 0x3F;

      Uint16 letter = (bigByte << 6) & 0xFFFF;
      letter |= byte2;

      if( letter < 0xD800 ) // High Surrogates
        outBuf.appendU16( letter );

      }

    // If it doesn't match the two above
    // it gets ignored.
    }
  }
}
