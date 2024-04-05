// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#include "URLFileDct.h"
#include "../CppBase/StIO.h"
#include "../CppBase/FileIO.h"
#include "../CppBase/UTF8Str.h"
#include "../CppBase/Casting.h"
#include "../CryptoBase/Sha256.h"



URLFileDct::URLFileDct( void )
{
lineArray = new URLFileDctLine[
             Casting::i32ToU64( keySize )];
}



URLFileDct::URLFileDct( const URLFileDct& in )
{
if( in.testForCopy )
  return;

lineArray = new URLFileDctLine[
             Casting::i32ToU64( keySize )];

throw "URLFileDct copy constructor.";
}



URLFileDct::~URLFileDct( void )
{
delete[] lineArray;
}



#include "../CppMem/MemoryWarnTop.h"



void URLFileDct::clear( void )
{
for( int count = 0; count < keySize; count++ )
  lineArray[count].clear();

}




Int32 URLFileDct::getIndex( Uint16Buf& url )
{
const Int32 lastUrl = url.getLast();
if( lastUrl == 0 )
  return 0;

CharBuf toHash;
url.toCharBuf( toHash );

CharBuf hash;

Sha256 sha256;
sha256.makeHash( hash, toHash );

Int32 index = hash.getU8( 0 );
index <<= 8;
index |= hash.getU8( 1 );
index = index & keySize;
if( index >= keySize )
  index = keySize - 1;

return index;
}





/*
  public void setValue( StrA key, URLFile value )
    {
    try
    {
    if( key == null )
      return;

    key = key.toLowerCase();
    if( key.length() < 1 )
      return;

    // mApp.showStatusAsync( "Setting value: " + key );

    int index = getIndex( key );
    if( lineArray[index] == null )
      lineArray[index] = new URLFileDictionaryLine( mApp );

    lineArray[index].setValue( key, value );
    }
    catch( Exception e )
      {
      mApp.showStatusAsync( "Exception in setValue()." );
      mApp.showStatusAsync( e.getMessage() );
      }
    }



  public URLFile getValue( StrA key )
    {
    if( key == null )
      return null;

    key = key.toLowerCase();
    if( key.length() < 1 )
      return null;

    int index = getIndex( key );
    if( lineArray[index] == null )
      return null;

    return lineArray[index].getValue( key );
    }



  public StrA makeKeysValuesStrA()
    {
    try
    {
    StrABld sBld = new StrABld( 1024 * 64 );

    for( int count = 0; count < keySize; count++ )
      {
      if( lineArray[count] == null )
        continue;

      StrA lines = lineArray[count].
                                 makeKeysValuesStrA();

      if( lines.length() == 0 )
        continue;

      // mApp.showStatusAsync( "At " + count +
      //                " length: " + lines.length() );


      sBld.appendStrA( lines );
      }

    return sBld.toStrA();
    }
    catch( Exception e )
      {
      mApp.showStatusAsync( "Exception in URLFileDictionary.makeKeysValuesStrA():\n" );
      mApp.showStatusAsync( e.getMessage() );
      return StrA.Empty;
      }
    }



  public boolean keyExists( StrA key )
    {
    if( key == null )
      return false;

    key = key.trim().toLowerCase();
    if( key.length() < 1 )
      return false;

    int index = getIndex( key );
    if( lineArray[index] == null )
      return false;

    return lineArray[index].keyExists( key );
    }



  public void saveToFile()
    {
    StrA fileS = makeKeysValuesStrA();
    FileUtility.writeStrAToFile( mApp,
                                 fileName,
                                 fileS,
                                 false,
                                 true );
    }
*/



void URLFileDct::readFromFile( void )
{
StIO::putS( "Reading from URL index file." );

clear();

CharBuf charBuf;
FileIO::readAll( Configure::getUrlIndexName(),
                 charBuf );

UTF8Str utf8Str;
Uint16Buf fileBuf;

utf8Str.charBufToU16Buf( charBuf, fileBuf );

const Int32 last = fileBuf.getLast();

Uint16Buf lineBuf;
Int32 where = 0;
Int32 howMany = 0;

// There are a lot less lines than there
// are bytes here.

for( Int32 count = 0; count < last; count++ )
  {
  where = fileBuf.getField( lineBuf,
                              where, '\n' );

  if( where < 0 )
    {
    StIO::printF( "\n\nLinks: " );
    StIO::printFD( howMany );
    StIO::putLF();
    return;
    }

  where++;

  URLFile urlFile;
  urlFile.setFromU16Buf( lineBuf );

  Uint16Buf url;
  urlFile.getUrl( url );
  Int32 index = getIndex( url );


  if( howMany < 200 )
    {
    StIO::putLF();
    Uint16Buf showLinkText;
    urlFile.getLinkText( showLinkText );
    showLinkText.showAscii();

    url.showAscii();
    StIO::printF( "URL index is: " );
    StIO::printFD( index );
    StIO::putLF();
    }

  howMany++;
  }
}


#include "../CppMem/MemoryWarnBottom.h"
