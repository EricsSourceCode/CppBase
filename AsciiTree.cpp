// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#include "AsciiTree.h"
#include "../CppBase/StIO.h"



void AsciiTree::showChars( void ) const
{
// Space is at 32.
// ! is at 33.
// Lower case a is at 97.
// Upper case A is at 65.

for( Int32 count = 33; count < 127; count++ )
  {
  StIO::printFD( count );
  StIO::printF( ") " );
  char toShow = count & 0x7F;
  StIO::putChar( toShow );
  StIO::putLF();
  }
}



void AsciiTree::setSize( const Int32 howBig )
{
if( howBig == arraySize )
  return;

arraySize = howBig;
delete[] nodes;
nodes = new ATreeNode[
                 Casting::i32ToU64( arraySize )];
}


/*
void AsciiTree::addChar( const char c )
{
lastNode is what?

// Int32 where = indexOfChar( c );
}
*/



