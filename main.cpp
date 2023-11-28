#include <baseapi.h>
#include <allheaders.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>


using namespace std;

void fixRows()
{
    string line1;
    string line2;
    int count1 = 0;
    int count2 = 0;
    int i;

    ifstream inText("output.csv");

    getline(inText, line1);
    inText.ignore();
    getline(inText, line2);

    // count "," occurrence
    for (i = 0; i < line1.size(); ++i)
    {
        if (line1[i] == ';')
        {
            ++count1;
        }
    }
    for (i = 0; i < line2.size(); ++i)
    {
        if (line2[i] == ';')
        {
            ++count2;
        }
    }

    // close file
    inText.close();

    // check
    if (count2 > count1)
    {
        ofstream newText("output2.csv");
        ifstream oldText("output.csv");
        newText << "; ";

        // append file 1 to file 2
        string line;
        while (getline(oldText, line))
        {
            newText << line << endl;
        }
        
        // close files
        oldText.close();
        newText.close();

        // re-open to clear
        ifstream newText1("output2.csv");
        ofstream oldText1("output.csv");

        // write file 2 to file 1
        while (getline(newText1, line))
        {
            oldText1 << line << endl;
        }

        // close files
        oldText1.close();
        newText1.close();

        // delete 2nd file
        remove("output2.csv");
    }   
}

/*
function()
{
    --do something :D
}
*/

int main()
{
    // vars
    char* outText;
    ofstream outputFile;
    string imgfile;
    char* nextData = NULL;

    // Open the output file
    outputFile.open("output.csv");

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // ask for image path
    cout << "Enter Image File Path: ";
    getline(cin, imgfile);

    // remove first/last quotes
    if (imgfile[0] == '\"')
    {
        imgfile.erase(0, 1);
    }
    if (imgfile[imgfile.size() - 1] == '\"')
    {
        imgfile.erase(imgfile.size() - 1, 1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead(imgfile.c_str());
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();

    // tokenize tesseract "string"
    char* wordToken = strtok_s(outText, " ", &nextData);
    while (wordToken != nullptr)
    {
        if (strchr(wordToken, '|') == nullptr)
        {
            if (strchr(wordToken, '\n') != nullptr)
            {
                outputFile << wordToken;
            }
            else
            {
                outputFile << wordToken;
                outputFile << "; ";
            }
        }
        wordToken = strtok_s(nullptr, " ", &nextData);
    }

    // Closing the file
    outputFile.close();

    // fix if there is an empty header
    fixRows();

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return 0;
}
