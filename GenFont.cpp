//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Implementation of the GenFont class.  This class takes font data generated by the AngelCode Bitmap Font Generator
// (http://www.angelcode.com/products/bmfont/) and converts it into a header file that can be read by the Font class.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/GenFont.cpp#1 $ 
// 
// Last check-in:  $DateTime: 2008/01/23 11:45:40 $ 
// Last edited by: $Author: dginsbur $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

#include "GenFont.h"
#include "ImageLoader.h"

#include <assert.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//=================================================================================================================================
///
/// SmartGrowMaxCharBufSize (private) - Creates the header file from the font data generated by AngelCode
///
/// \param fontImageFile - The tga file generated by AngelCode that contains the font image
/// \param fontDataFile - The .fnt file generated by AngleCode that contains the font data
/// \param outFontFile - The name of the header file you want to generate
/// \param fontNum - A number that gets appended to the structures in the header file (this allows you to easily have more than a 
/// single font in an application
///
/// \return bool - true if the function succeeds
//=================================================================================================================================
bool GenFont::CreateFontFile( char8* fontImageFile, char8* fontDataFile, char8* outFontFile, int32 fontNum )
{
   ifstream ifile( fontDataFile );
   char8 *buf = new char8[256];
   int32 lineHeight=0, numCharData=0;

   // Get the lineHeight
   while ( ifile.getline( buf, 256 ) )
   {
      string str = buf;
      size_t val;

      val = str.find( "char id=" );
      if ( val == 0 )
      {
         ++numCharData;
      }
      else
      {
         val = str.find( "lineHeight=" );
         if (val != 0xffffffff)
         {
            str = str.substr( val+11, 10 );
            istringstream strStream( str.c_str() );
            strStream >> lineHeight;
         }
      }
   }
   assert( lineHeight );
   assert( numCharData );
   ifile.close();
   ifile.clear();
   ifile.open( fontDataFile );

   // load image
   ImageLoader imgLoader;
   ImageObject *pImgObj;
   pImgObj = imgLoader.LoadImageFile( fontImageFile );

   if ( pImgObj != NULL )
   {
      if ( pImgObj->GetNumChannels() == 1 && pImgObj->GetBpp() == 8 )
      {
         ofstream ofile;
         ofile.open( outFontFile, ios_base::trunc );

         ofile << "// This file was generated with the GenFont class." << endl << endl << endl;
         ofile << "#ifndef _" << "FONT_" << fontNum << "_" << endl;
         ofile << "#define _" << "FONT_" << fontNum << "_" << endl;

         ofile << "// Data format is -- texWidth, texHeight, channels, bitsPerChannel, lineHeight, numCharData" << endl;

         ofile << "int fontHeader" << fontNum << "[] = { " << pImgObj->GetWidth() << ", " << pImgObj->GetHeight() << ", "
            << pImgObj->GetNumChannels() << ", " << pImgObj->GetBitsPerChannel() << ", " << lineHeight << ", "
            << numCharData << " };" << endl << endl;

         ofile << "// Format is: id, x, y, width, height, xoffset, yoffset, xadvance" << endl;
         ofile << "int charData" << fontNum << "[][8] = { " << endl;
         while ( ifile.getline( buf, 256 ) )
         {
            string str = buf;
            size_t val;

            val = str.find( "char id=" );
            if ( val == 0 )
            {
               string::size_type pos;
               while ( pos = str.find( "=" ) )
               {
                  if ( pos == 0xffffffff )
                  {
                     break;
                  }
                  str.replace( pos, 1, " " );
               }
               
               istringstream strStream( str.c_str() );
               int32 id, x, y, width, height, xoffset, yoffset, xadvance, page;

               strStream >> buf >> buf >> id >> buf >> x >> buf >> y >> buf >> width >> buf >> height >>
                      buf >> xoffset >> buf >> yoffset >> buf >> xadvance >> buf >> page;

               assert( page == 0 ); // Only support 1 page exports (make texture bigger or font smaller to fix this)

               ofile << "   { " << id << ", " << x << ", " << y << ", " << width << ", " << height << ", " << xoffset
                     << ", " << yoffset << ", " << xadvance << " }," << endl;
            }
         }
         ofile << "};" << endl << endl;

         // Output all the font image data
         ofile << "// This is the image data for the font texture" << endl;
         ofile << "unsigned char fontImageData" << fontNum << "[] = { ";
         for( uint32 i = 0; i < pImgObj->GetHeight(); ++i )
         {
            for ( uint32 j = 0; j < pImgObj->GetWidth(); ++j )
            {
               if ( (i*pImgObj->GetWidth()+j)%20 == 0 )
               {
                  ofile << endl << "   ";
               }
               ofile << int32(pImgObj->Pixel(j, i, 0)) << ", ";
            }
         }
         ofile << endl << "};" << endl << endl;

         ofile << "#endif // _" << "FONT_" << fontNum << "_" << endl << endl << endl;
         ofile.close();
      }
      else 
      {
         assert( 0 );
      }

      delete pImgObj;
   }
   else
   {
      // Font not found
      assert( 0 );
      return false;
   }
   delete [] buf;
   ifile.close();
   return true;
}