// Copyright Eric Chauvin 2022 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "FileIO.h"
#include "StIO.h"
#include "Casting.h"
#include "../CppMem/OpenCharArray.h"


// Put these standard files last so that macros
// get defined as late as possible.

#include <iostream>
#include <fstream>



bool FileIO::writeAll( const CharBuf& fileName,
                       const CharBuf& cBuf )
{
try
{
const Int32 howMany = cBuf.getLast();

OpenCharArray writeAr;
cBuf.copyToOpenCharArrayNoNull( writeAr );

OpenCharArray fileAr;
fileName.copyToOpenCharArrayNull( fileAr );

std::ofstream outFile( fileAr.cArray,
                       std::ofstream::binary );

outFile.write( writeAr.cArray,
               howMany );

// good() returns true if none of the error
// bits get set.
// End of file flag?

// outFile.good();

outFile.close();

// Any OpenCharArray goes out of scope.
return true;
}
catch( ... )
  {
  const char* errorS = "FileIO writeCharBuf"
                " exception.";

  StIO::putS( errorS );
  return false;
  }
}



bool FileIO::readAll( const CharBuf& fileName,
                      CharBuf& cBuf )
{
try
{

OpenCharArray fileAr;
fileName.copyToOpenCharArrayNull( fileAr );

std::ifstream inFile( fileAr.cArray,
                      std::ifstream::binary );

inFile.seekg( 0, inFile.end );
Int64 howMany = inFile.tellg();
// Error returns -1.
if( howMany < 0 )
  {
  StIO::putS( "FileIO.readAll() returned < 0." );
  return false;
  }

// Don't read files that are this big in to RAM.
if( howMany > 1000000000LL )
  {
  StIO::putS( "FileIO returned > 1000000000." );
  return false;
  }

inFile.seekg( 0 );

OpenCharArray readAr;
readAr.setSize( Casting::i64ToI32( howMany ));

inFile.read( readAr.cArray, howMany );

// setSize sets last to zero also.
cBuf.setSize( Casting::i64ToI32( howMany + 1024 ));
for( Int32 count = 0; count < howMany; count++ )
  cBuf.appendChar( readAr.getC( count ));

inFile.close();
return true;

}
catch( ... )
  {
  const char* errorS = "FileIO readAll"
                " exception.";

  StIO::putS( errorS );
  return false;
  }
}



bool FileIO::exists( const CharBuf& fileName )
{
try
{
OpenCharArray fileAr;
fileName.copyToOpenCharArrayNull( fileAr );

std::ifstream inFile( fileAr.cArray,
                      std::ifstream::binary );

return inFile.good();

}
catch( ... )
  {
  const char* errorS = "FileIO exists"
                " exception.";

  StIO::putS( errorS );
  return false;
  }
}


bool FileIO::copy( const CharBuf& fromName,
                   const CharBuf& toName )
{
CharBuf cBuf;
if( !readAll( fromName, cBuf ))
  return false;

return writeAll( toName, cBuf );
}
