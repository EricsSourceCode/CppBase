// Copyright Eric Chauvin 2024.




// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericssourcecode.github.io/
// For guides and information.


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/CharBuf.h"



class Configure
  {
  private:
  bool testForCopy = false;
//  CharBuf dataDir;
//  CharBuf urlIndexName;
//  CharBuf urlFilesDir;

  public:
  Configure( void )
    {
    }

  Configure( const Configure& in )
    {
    if( in.testForCopy )
      return;

    throw "Configure copy constructor.";
    }

  ~Configure( void )
    {
    }


  static const char* getDataDir( void )
    {
    return "/AINewsData/";
    }

  static const char* getUrlFilesDir( void )
    {
    return "/AINewsData/UrlFiles/";
    }

  static const char* getUrlIndexName( void )
    {
    return "/AINewsData/UrlDictionary.txt";
    }

  };
