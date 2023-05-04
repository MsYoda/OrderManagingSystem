#pragma once
#include "File.h"

template <typename T>
class TextFile :
    public File
{
public:
    TextFile(QString filename = "");

    void SetFileName(QString fname);

    void OpenForReading();
    void OpenForWriting();

    T ReadObj();
    void WriteObj(T& obj);

    void Close();
    bool IsEndOfFile();
};

