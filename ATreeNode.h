// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppMem/Int32Array.h"




class ATreeNode
  {
  private:
  bool testForCopy = false;
  Int32Array indexAr;
  const Int32 maxArray = 127 - 32;

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

  inline Int32 indexOfChar( const char c ) const
    {
    RangeC::test2( c, 32, 126,
             "ATreeNode.indexOfChar range." );

    // So a space is at zero.
    return c - 32;
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
