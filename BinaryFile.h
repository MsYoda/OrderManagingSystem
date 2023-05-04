#pragma once
#include <fstream>
#include <QString>

using namespace std;
template <typename T>
class BinaryFile
{
    QString fileName; // Имя файла
    fstream binaryIOStream; // поток ввода-вывода
public:
    BinaryFile(QString filename = ""); // Конструктор

    void SetFileName(QString fname); // Установить имя файла

    void OpenForReading(); // Открыть для чтения
    void OpenForWriting(); // Открыть для записи

    T ReadObj(); // Прочитать объект
    void WriteObj(T* obj); // Записать объект

    void Close(); // Закрыть файл
    bool IsEndOfFile(); // Проверка на конец файла
    bool IsOpen(); // Открыт ли файл
};


