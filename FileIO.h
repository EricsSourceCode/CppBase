// Copyright Eric Chauvin 2022 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#pragma once


#include "BasicTypes.h"
#include "CharBuf.h"


// See std::filesystem for some other options.


class FileIO
  {
  private:

  public:
  static bool exists( const char* fileName );
  static bool writeAll( const char* fileName,
                        const CharBuf& cBuf );

  static bool readAll( const char* fileName,
                       CharBuf& cBuf );

  static bool copy( const char* fromName,
                    const char* toName );

  };
