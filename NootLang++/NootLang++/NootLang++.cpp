// NootLang++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#if WIN32
#include <windows.h>
#endif // WINDOWS

// Types
typedef unsigned char BYTE;

// Globals
static std::string output;
static std::vector<char> data;

void PrintOutput()
{
    if (output.empty())
        return;

    printf("%s\r\n", output.c_str());
    output.clear();
}

void IncDataTable(int amount)
{
    if (amount >= data.size())
    {
        for (int i = data.size(); i < amount; ++i)
            data.push_back(0);
    }
}

bool CheckString(const char* key, int index, const char* value)
{
    return !memcmp(key + index, value, strlen(value));
}

int main(int argc, const char* argv[])
{
    // Win32 Title
    #if WIN32
        SetConsoleTitle(_T("NootLang++"));
    #endif

    // Read File
    auto handle = fopen(argv[1], "rb");
    if (!handle)
    {
        printf("File Not found");
        // Pause if compiled for Win32
        #if WIN32
            system("pause");
        #endif
        return 0;
    }
    fseek(handle, 0, SEEK_END);
    int size = ftell(handle);
    fseek(handle, 0, SEEK_SET);
    char* instructions = (char*) malloc(size);
    fread(instructions, 1, size, handle);

    int index = 0;
    int dataPointer = 0;
    int ignoreAmount = 0;
    FILE* fs = nullptr;
    data.push_back(0);
    // Main Loop
    while (index < size)
    {
        if (instructions[index] == 'n' || instructions[index] == 'N')
        {
            if (CheckString(instructions, index, "nooT"))
            {
                ++dataPointer;
                if (dataPointer >= data.size())
                    data.push_back(0);
            }
            else if (CheckString(instructions, index, "Noot"))
            {
                --dataPointer;
            }
            else if (CheckString(instructions, index, "noOT"))
            {
                ++(data[dataPointer]);
            }
            else if (CheckString(instructions, index, "NOot"))
            {
                --(data[dataPointer]);
            }
            else if (CheckString(instructions, index, "noot"))
            {
                // subscirbe to redfox comms, give a shotout to simpleflips and check ichigo's hot furry mods.. And SuperSonic16!!!!
                output.append(&data[dataPointer], 1);
            }
            else if (CheckString(instructions, index, "NOOt"))
            {
                if (data.at(dataPointer) == 0)
                {
                    while (index <= size)
                    {
                        if (CheckString(instructions, index + 4, "nOOT"))
                        {
                            --ignoreAmount;
                            if (ignoreAmount <= 0)
                                break;
                        }
                        if (CheckString(instructions, index + 4, "NOOt"))
                        {
                            ++ignoreAmount;
                        }
                        index += 4;
                    }
                    ignoreAmount = 0;
                }
            }
            else if (CheckString(instructions, index, "nOOT"))
            {
                if (data.at(dataPointer) != 0)
                {
                    while (index > 0)
                    {
                        if (CheckString(instructions, index + 4, "NOOt"))
                        {
                            --ignoreAmount;
                            if (ignoreAmount <= 0)
                                break;
                        }
                        if (CheckString(instructions, index + 4, "nOOT"))
                        {
                            ++ignoreAmount;
                        }
                        index -= 4;
                    }
                    ignoreAmount = 0;
                }
            }
            else if (CheckString(instructions, index, "nOot"))
            {
                IncDataTable(dataPointer + 2);
                data[dataPointer] = data[dataPointer + 1] / data[dataPointer + 2];
            }
            else if (CheckString(instructions, index, "noOt"))
            {
                IncDataTable(dataPointer + 2);
                data[dataPointer] = data[dataPointer + 1] * data[dataPointer + 2];
            }
            else if (CheckString(instructions, index, "NooT"))
            {
                IncDataTable(dataPointer + 2);
                data[dataPointer] = data[dataPointer + 1] | data[dataPointer + 2];
            }
            else if (CheckString(instructions, index, "nOOt"))
            {
                IncDataTable(dataPointer + 2);
                data[dataPointer] = data[dataPointer + 1] & data[dataPointer + 2];
            }
            else if (CheckString(instructions, index, "NoOt"))
            {
                fread(&(data[dataPointer]), 1, 1, fs);
            }
            else if (CheckString(instructions, index, "NoOT"))
            {
                fwrite(&(data[dataPointer]), 1, 1, fs);
            }
            else if (CheckString(instructions, index, "NOoT"))
            {
                printf("      .___.\n");
                printf("     /     \\\n");
                printf("    | O _ O |\n");
                printf("    /  \\_/  \\ \n");
                printf("  .' /     \\ `.\n");
                printf(" / _|  noot |_ \\\n");
                printf("(_/ |  lang | \\_)\n");
                printf("    \\       /\n");
                printf("   __\\_>-<_/__\n");
                printf("   ~;/     \\;~\n");
                printf("\n");
                printf("why did I make this?\n");
                break;
            }
            else if (CheckString(instructions, index, "NOOT"))
            {
                if (fs == nullptr)
                {
                    int e = dataPointer + data[dataPointer];
                    std::string fn;
                    
                    for (; dataPointer < e; ++dataPointer)
                    {
                        fn.append(&data[dataPointer + 1], 1);
                    }

                    dataPointer = e;
                    fs = fopen(fn.c_str(), "r+b");
                    if (fs == nullptr)
                    {
                        fs = fopen(fn.c_str(), "wb");
                    }
                }
                else
                {
                    fclose(fs);
                    fs = nullptr;
                }
            }
            index += 4;
        }
        else
        {
            printf("fineE\n");
            index += 4;
        }
    }
    PrintOutput();
    // Pause if compiled for Win32
    #if WIN32
        system("pause");
    #endif
    delete instructions;
    return 0;
}

