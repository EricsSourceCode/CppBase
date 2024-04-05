// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericssourcecode.github.io/
// For guides and information.



#include "URLFile.h"


void URLFile::clear( void )
{
linkText.clear();
fileName.clear();
url.clear();
dateTime.clear();
anchorsPulled = false;
titleHtml.clear();
}



void URLFile::copy( const URLFile& toCopy )
{
linkText.copy( toCopy.linkText );
fileName.copy( toCopy.fileName );
url.copy( toCopy.url );
dateTime.copy( toCopy.dateTime );
anchorsPulled = toCopy.anchorsPulled;
titleHtml.copy( toCopy.titleHtml );
}



/*

  public URLFile( MainApp appToUse, StrA urlToUse )
    {
    mApp = appToUse;
    url = urlToUse.cleanUnicodeField().trim();
    fileName = makeNewFileName( url );
    dateTime = makeDateTime();
    }



  public URLFile( MainApp appToUse,
                  StrA titleToUse,
                  StrA urlToUse )
    {
    mApp = appToUse;
    url = urlToUse.cleanUnicodeField().trim();
    title = titleToUse.cleanUnicodeField();
    fileName = makeNewFileName( url );
    dateTime = makeDateTime();
    }


  private StrA makeNewFileName( StrA fromURL )
    {
    if( fromURL.length() == 0 )
      return StrA.Empty;

    LocalDateTime rightNow = LocalDateTime.now();
    int year = rightNow.getYear();

    int month = rightNow.getMonthValue();
    int day = rightNow.getDayOfMonth();

    // int getDayOfYear()
    // getDayOfWeek()

    int hour = rightNow.getHour();
    int minute = rightNow.getMinute();
    int second = rightNow.getSecond();
    int nano = rightNow.getNano();

    int index = url.GetCRC16();

    String fileName = "UFile_" +
           year + "_" +
           month + "_" +
           day + "_" +
           hour + "_" +
           minute + "_" +
           second + "_" +
           nano + "_" +
           index + ".txt";

    return new StrA( fileName );
    }



  private StrA makeDateTime()
    {
    LocalDateTime rightNow = LocalDateTime.now();
    int year = rightNow.getYear();
    int month = rightNow.getMonthValue();
    int day = rightNow.getDayOfMonth();
    int hour = rightNow.getHour();
    int minute = rightNow.getMinute();
    int second = rightNow.getSecond();
    int nano = rightNow.getNano();

    String result = "" +
           year + ";" +
           month + ";" +
           day + ";" +
           hour + ";" +
           minute + ";" +
           second + ";" +
           nano;

    return new StrA( result );
    }

*/


void URLFile::toU16Buf( Uint16Buf& outBuf )
{
outBuf.appendU16Buf( url );
outBuf.appendU16( MarkersAI::URLFileDelimit );
outBuf.appendU16Buf( linkText );
outBuf.appendU16( MarkersAI::URLFileDelimit );
outBuf.appendU16Buf( fileName );
outBuf.appendU16( MarkersAI::URLFileDelimit );
outBuf.appendU16Buf( dateTime );
outBuf.appendU16( MarkersAI::URLFileDelimit );

if( anchorsPulled )
  outBuf.appendU16( 't' & 0xFF );
else
  outBuf.appendU16( 'f' & 0xFF );

outBuf.appendU16( MarkersAI::URLFileDelimit );

outBuf.appendU16Buf( titleHtml );
outBuf.appendU16( MarkersAI::URLFileDelimit );
}



void URLFile::setFromU16Buf(
                     const Uint16Buf& u16Buf )
{
Int32 startAt = 0;

startAt = u16Buf.getField( url, startAt,
                 MarkersAI::URLFileDelimit );

if( startAt < 0 )
  return;

startAt++; // Go past the delimiter it found.

startAt = u16Buf.getField( linkText, startAt,
                 MarkersAI::URLFileDelimit );

if( startAt < 0 )
  return;

startAt++;

startAt = u16Buf.getField( fileName, startAt,
                 MarkersAI::URLFileDelimit );

if( startAt < 0 )
  return;

startAt++;

startAt = u16Buf.getField( dateTime, startAt,
                 MarkersAI::URLFileDelimit );

if( startAt < 0 )
  return;

startAt++;

Uint16Buf anchors;

startAt = u16Buf.getField( anchors, startAt,
                 MarkersAI::URLFileDelimit );

if( anchors.getLast() < 1 )
  {
  anchorsPulled = false;
  }
else
  {
  if( anchors.getVal( 0 ) == ('t' & 0xFF) )
    anchorsPulled = true;
  else
    anchorsPulled = false;

  }

startAt++;

u16Buf.getField( titleHtml, startAt,
                 MarkersAI::URLFileDelimit );
}
