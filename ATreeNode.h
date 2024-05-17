// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppMem/Int32Array.h"


// This uses characters 0 through 127.
// Chars below 32 (space) are for markers.
// Need an end of string marker.  So zero.



class ATreeNode
  {
  private:
  bool testForCopy = false;
  Int32Array indexAr;
  const Int32 maxArray = 127;

  public:
  ATreeNode( void )
    {
    indexAr.setSize( maxArray );
    }

  ATreeNode( const ATreeNode& in )
    {
    if( in.testForCopy )
      return;

    throw "ATreeNode copy constructor.";
    }

  ~ATreeNode( void )
    {
    }


  void clear( void )
    {
    indexAr.clearTo( -1 );
    }

/*
  void addChar( const char c )
    {
    Int32 where = indexOfChar( c );

    }
*/

  };
