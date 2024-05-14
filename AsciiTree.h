// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/Casting.h"
#include "../CppBase/RangeC.h"
#include "ATreeNode.h"




class AsciiTree
  {
  private:
  bool testForCopy = false;
  ATreeNode* nodes;
  Int32 arraySize = 1;
  // Int32 lastNode = 0;

  public:
  AsciiTree( void )
    {
    arraySize = 1;
    nodes = new ATreeNode[
                  Casting::i32ToU64( arraySize )];
    }


  AsciiTree( const AsciiTree& in )
    {
    arraySize = 1;
    nodes = new ATreeNode[
                  Casting::i32ToU64( arraySize )];

    if( in.testForCopy )
      return;

    throw "AsciiTree copy constructor.";
    }


  ~AsciiTree( void )
    {
    delete[] nodes;
    }

  void showChars( void ) const;
  void setSize( const Int32 howBig );

  };
