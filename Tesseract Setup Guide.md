# Tesseract Setup Guide

## Prerequisites:
1. Install Git for your operating system from [here](https://git-scm.com/downloads).

## Installing vcpkg:
2. Install vcpkg by following the steps in this [guide](https://github.com/Microsoft/vcpkg#quick-start-windows):
    a. If you have Git installed, open your cmd and run: `git clone https://github.com/microsoft/vcpkg`
    b. After cloning, run: `.\vcpkg\bootstrap-vcpkg.bat`
    c. Install Tesseract with: `.\vcpkg\vcpkg install tesseract:x64-windows`
    d. Integrate vcpkg with: `.\vcpkg\vcpkg integrate install`

## Obtaining Tessdata:
3. Use Git to obtain tessdata (language data) with: `git clone https://github.com/tesseract-ocr/tessdata`

## Adding to Environmental Variables:
4. Add tessdata to your environmental variables:
    a. Search for "Environmental Variables" in Windows search, and open the system properties tab/advanced.
    b. In "User variables for ...(your computer name)," click "New."
    c. Add variable name: `TESSDATA_PREFIX`
    d. Variable value is the location where tessdata was downloaded (e.g., `C:\Users\yourname\tessdata`).
    e. Click OK and restart your computer.

## Project Setup:
5. Create a new empty project in your IDE name "testing".
6. Right-click your project "testing", add a new C++ file, and name it "main.cpp"

## Project Properties:
7. Right-click main.cpp, go to Property Pages:
    a. Change configuration to Release and Platform to x64.
8. Right-click main.cpp, go to Property Pages, under C/C++ -> General, include additional directories:
    a. Additional Include Directories:
        - Click the down arrow on the square to the right, click <Edit...>
        - Find vcpkg installation directory.
        - Add three directories: include, leptonica, and tesseract:
          c:\Users\myname\vcpkg\installed\x64-windows\include
          c:\Users\myname\vcpkg\installed\x64-windows\include\leptonica
          c:\Users\myname\vcpkg\installed\x64-windows\include\tesseract

## Linker Configuration:
9. Right-click "testing"(projecte name) selecte on Properties, go to Linker -> General:
    a. Additional Library Directories:
        - Click the down arrow on the square to the right, click <Edit...>
        - Find vcpkg installation directory, and add the lib folder:
           c:\Users\myname\vcpkg\installed\x64-windows\lib

11. Right-click "testing"(projecte name) selecte on Properties, go to Linker -> Input:
    a. Additional Dependencies:
       - Click the down arrow on the square to the right, click <Edit...>
    b. Add all of these:
tesseract53.lib      //or whatever version you installed
leptonica-1.83.1.lib      //or whatever version you installed
archive.lib
bz2.lib
charset.lib
gif.lib
iconv.lib
jpeg.lib
libcrypto.lib
libpng16.lib
libssl.lib
libwebpmux.lib
libxml2.lib
lz4.lib
lzma.lib
openjp2.lib
tiff.lib
turbojpeg.lib
libwebp.lib
libwebpdecoder.lib
libwebpdemux.lib
zlib.lib
zstd.lib

13. Apply changes and go back to `main.cpp`.

## Testing Tesseract:
12. Change configuration to Release and x64.
13. Paste and run the test code in `main.cpp`.
    - If you encounter DLL errors, save the project and relaunch your IDE.
   
#include <baseapi.h>
#include <allheaders.h>
#include <iostream>
using namespace std;

int main()
{
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead("C:/Users/blain/OneDrive/Desktop/201/l-pitt-city-dir-artical-web1.jpg");   //Change directory of image
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);     //This is first line of output

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return 0;
}
