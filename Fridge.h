#pragma once
#include "HouseTech.h"

class Fridge :
	public HouseTech
{
	float cameraVolume; // объеём камеры
	float noiseLevel;   // уровень шума
	const static QString TYPENAME;  // Имя типа - "Холодильник"

	 // Функтор для работы фильтра
	class FridgeFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};
	FridgeFilterComparator comparator; // Объект фильтра
	QString& GenerateDescription(QString& str); // Сгенерировать описание
public:
	Fridge(); // Конструктор

	void SetCameraVolume(float vol); // Установить объём камеры
	void SetNoiseLevel(float lvl);  // Установить уровень шума

	float GetCameraVolume();    // Узнать объём камеры
	float GetNoiseLevel();  // Узнать уровень шума

	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	QString GenerateDescription() override; // Сгенерировать полное описание
	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override;

	bool operator==(Fridge& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, Fridge& obj);
	friend fstream& operator<<(fstream& out, Fridge& obj);
};

