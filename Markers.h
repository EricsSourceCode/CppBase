// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "BasicTypes.h"
// #include "RangeC.h"



class Markers
  {
  private:
  // bool testForCopy = false;

  public:
  // Marker symbols go from 0x2700 to 0x27BF.
  // These are the Dingbat characters in the
  // Unicode Basic Multilingual Plane.

  static const Uint16 First = 0x2700;
  static const Uint16 Last = 0x27BF;


  inline static bool isMarker( Uint16 testC )
    {
    if( (testC >= First) && (testC <= Last))
      return true;

    return false;
    }

  };
