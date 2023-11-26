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
5. Create a new empty project in your IDE.
6. Right-click your project, add a new C++ file, and name it "main."

## Project Properties:
7. Right-click your project, go to properties:
    a. Change configuration to Release and Platform to x64.
8. Under C/C++ -> General, include additional directories:
    a. Additional Include Directories:
        - Find vcpkg installation directory.
        - Add three directories: include, leptonica, and tesseract.

## Linker Configuration:
9. Go to Linker -> General:
    a. Additional Library Directories:
        - Find vcpkg installation directory, and add the lib folder.

10. Go to Linker -> Input:
    a. Additional Dependencies:
        - Add the necessary libraries, e.g., `tesseract53.lib`, `leptonica-1.83.1.lib`, and others.

11. Apply changes and go back to `main.cpp`.

## Testing Tesseract:
12. Change configuration to Release and x64.
13. Paste and run the test code in `main.cpp`.
    - If you encounter DLL errors, save the project and relaunch your IDE.

