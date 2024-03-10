// Copyright Eric Chauvin 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


// See https://ericinarizona.github.io/
// For guides and information.


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/CharBuf.h"



class Message
  {
  private:
  bool testForCopy = false;

  // And do like   new message1();

  // Message* message1;

  // Messages within messages within messages.

  // What about using Markers?
  // Like a language with markers?
  // Where the language expresses messages
  // within messages...

  public:
  inline Message( void )
    {
    }

  inline Message( const Message& in )
    {
    if( in.testForCopy )
      return;

    throw "Message copy constructor.";
    }

  inline ~Message( void )
    {
    }

  };
