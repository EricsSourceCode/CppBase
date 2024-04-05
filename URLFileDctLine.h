// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericssourcecode.github.io/
// For guides and information.



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/Uint16Buf.h"
#include "URLFile.h"



class URLFileDctLine
  {
  private:
  bool testForCopy = false;
  URLFile* valueArray;
  Int32 arraySize = 2;
  Int32 arrayLast = 0;
  void resizeArrays( const Int32 toAdd );

  public:
  URLFileDctLine( void );
  URLFileDctLine( const URLFileDctLine& in );
  ~URLFileDctLine( void );
  void clear();
  Int32 getIndexOfUrl(
                 const Uint16Buf& url ) const;

  };
