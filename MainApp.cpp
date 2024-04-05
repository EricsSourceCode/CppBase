// Copyright Eric Chauvin, 2021 - 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "MainApp.h"

#include "../CppBase/StIO.h"
#include "../CppBase/FileIO.h"
// #include "../LinuxApi/SetStack.h"
#include "../CppBase/Casting.h"
#include "../CppBase/Threads.h"
#include "../WinApi/Signals.h"
// #include "../LinuxApi/Signals.h"
// #include "../CryptoBase/Sha256.h"
// #include "../CryptoBase/Base64.h"
// #include "../CryptoBase/AesGalois.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/RsaTest.h"
#include "../Network/ClientTls.h"
#include "../Network/Http.h"


// int MainApp::mainLoop( int argc, char* argv[] )
int MainApp::mainLoop( void )
{
Int32 delay = 200; // milliseconds.

try
{
BasicTypes::thingsAreRight();

StIO::putLF();
StIO::putS( "AI News." );
StIO::putS( "Programming by Eric Chauvin." );
StIO::printF( "Version date: " );
StIO::putS( getVersionStr() );
StIO::putLF();

// For Linux:
// Int32 stackSize = SetStack::getSize();
// Str showS( stackSize );
// mainIO.appendChars( "Stack size: " );
// mainIO.appendStr( showS );
// mainIO.appendChars( "\n\n" );

Signals::setupControlCSignal();
Signals::setupFpeSignal();
Signals::setupIllegalOpSignal();
Signals::setupBadMemSignal();

StIO::putS( "Initializing." );

quadRes.init( sPrimes );
multInv.init( sPrimes );
// findFacQr.init( intMath, sPrimes );
crtMath.init( intMath,
              sPrimes );
garnerCrt.setUpConstants( sPrimes, intMath );


// StIO::putS( "Starting RSA test." );
// RsaTest rsaTest;
// rsaTest.test( rsa, mod, sPrimes, intMath,
//              findFacSm, //findFacQr,
//              multInv, // quadRes,
//              crtMath, garnerCrt );


urlFileDct.readFromFile();

// Http http;
// http.getWebPage();


StIO::putS( "End of main app." );

Threads::sleep( delay );

return 0;
}
catch( const char* in )
  {
  StIO::putS( "Exception in main loop." );
  StIO::putS( in );
  StIO::putLF();

  Threads::sleep( delay );
  return 1;
  }

catch( ... )
  {
  const char* in = "An unknown exception"
                   " happened in the main loop.\n";

  StIO::putS( in );

  Threads::sleep( delay );
  return 1;
  }
}
