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
5. Open cloned project "CodeCrafters---Automated-Data-Extraction-with-OCR"
6. Right-click main.cpp, go to Property Pages:
    a. Change configuration to Release and Platform to x64.
7. Right-click main.cpp, go to Property Pages, under C/C++ -> General, include additional directories:
    a. Additional Include Directories:
        - Click the down arrow on the square to the right, click <Edit...>
        - Find vcpkg installation directory.
        - Add three directories: include, leptonica, and tesseract:
          c:\Users\myname\vcpkg\installed\x64-windows\include
          c:\Users\myname\vcpkg\installed\x64-windows\include\leptonica
          c:\Users\myname\vcpkg\installed\x64-windows\include\tesseract

## Linker Configuration:
8. Right-click "testing"(project name) select on Properties, go to Linker -> General:
    a. Additional Library Directories:
        - Click the down arrow on the square to the right, click <Edit...>
        - Find vcpkg installation directory, and add the lib folder:
           c:\Users\myname\vcpkg\installed\x64-windows\lib

9. Right-click "testing"(project name) select on Properties, go to Linker -> Input:
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

10. Apply changes and go back to `main.cpp`.
11. Change configuration to Release and x64.

