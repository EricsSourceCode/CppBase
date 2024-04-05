// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericssourcecode.github.io/
// For guides and information.




#include "URLFileDctLine.h"



URLFileDctLine::URLFileDctLine( void )
{
valueArray = new URLFile[
             Casting::i32ToU64( arraySize )];

}



URLFileDctLine::URLFileDctLine(
                    const URLFileDctLine& in )
{
valueArray = new URLFile[
             Casting::i32ToU64( arraySize )];

if( in.testForCopy )
  return;

throw "URLFileDctLine copy constructor.";
}



URLFileDctLine::~URLFileDctLine( void )
{
delete[] valueArray;
}



#include "../CppMem/MemoryWarnTop.h"



void URLFileDctLine::clear()
{
const Int32 last = arraySize;
for( Int32 count = 0; count < last; count++ )
  valueArray[count].clear();

}


void URLFileDctLine::resizeArrays(
                           const Int32 toAdd )
{
if( arrayLast > arraySize )
  throw
     "URLFileDctLine::resizeArrays arrayLast";

const Int32 newSize = arraySize + toAdd;

URLFile* newValueArray;
newValueArray = new URLFile[
             Casting::i32ToU64( newSize )];

const Int32 max = arrayLast;
for( Int32 count = 0; count < max; count++ )
  newValueArray[count].copy( valueArray[count] );

arraySize = newSize;
delete[] valueArray;
valueArray = newValueArray;
}



==== What next?

Int32 URLFileDctLine::getIndexOfUrl(
                   const Uint16Buf& url ) const
{
if( arrayLast < 1 )
  return -1;

const Int32 max = arrayLast;
for( Int32 count = 0; count < max; count++ )
  {
  if( valueArray[count].urlIsEqual( url ))
    return count;

  }

return -1;
}



/*
  public void setValue( StrA key, URLFile value )
    {
    // This sets the URLFile to the new value whether
    // it's already there or not.
    int index = getIndexOfKey( key );
    if( index >= 0 )
      {
      valueArray[index] = value;
      }
    else
      {
      // There are 64,000 of these arrays, so don't
      // add too much for each array.
      if( arrayLast >= valueArray.length )
        resizeArrays( 4 );

      // mApp.showStatusAsync( key );
      keyArray[arrayLast] = key;
      valueArray[arrayLast] = value;
      arrayLast++;
      }
    }



  public URLFile getValue( StrA key )
    {
    int index = getIndexOfKey( key );
    if( index < 0 )
      return null;

    return valueArray[index];
    }



  public boolean keyExists( StrA key )
    {
    int index = getIndexOfKey( key );
    if( index < 0 )
      return false;

    return true;
    }




  public StrA makeKeysValuesStrA()
    {
    if( arrayLast < 1 )
      return StrA.Empty;

    StrABld sBld = new StrABld( 1024 * 8 );

    for( int count = 0; count < arrayLast; count++ )
      {
      StrA line = valueArray[count].toStrA();
      sBld.appendStrA( line );
      sBld.appendChar( '\n' );
      }

    return sBld.toStrA();
    }



  public StrA makeFilesStrA()
    {
    if( arrayLast < 1 )
      return StrA.Empty;

    StrABld sBld = new StrABld( 1024 * 8 );

    for( int count = 0; count < arrayLast; count++ )
      {
      StrA line = valueArray[count].getFileName();
      sBld.appendStrA( line );
      sBld.appendChar( '\n' );
      }

    return sBld.toStrA();
    }



  }
*/


#include "../CppMem/MemoryWarnBottom.h"
