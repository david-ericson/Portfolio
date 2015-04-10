#include <DebugTools\DebugSlider.h>
#include <Qt\qdebug.h>
#include <FastDelegate.h>
#include <ExportHeader.h>
#include <glm\glm.hpp>
#include <Qt\qcheckbox.h>
#include <Qt\qlabel.h>
#include <vector>
#include "DebugMemory.h"
using std::vector;

class QPushButton;

#pragma once
class DebugMenus
{
public:
	struct Slider
	{
		DebugSlider* slider;
		float* value;
		char* label;
		void update();
	};

	struct SlideVec3
	{
		DebugSlider* slider[3];
		glm::vec3* value;
		char* label;
		void update();

	};

	struct Checkbox
	{
		QCheckBox* box;
		bool* value;
		void update();
	};

	struct Label
	{
		QLabel* label;
		char* priorText;
		float* value;
		void update();
	};

	struct LeTab
	{
		char* label;
		QVBoxLayout* masterLayout;
		QList<QHBoxLayout*> currentLayout;
		QWidget* widg;
	};

	static void initialize(QWidget* widg);
	ENGINE_SHARED static void slide(char* text, float min, float max, int granuality, float startValue, char* tabName, float* tracking);
	ENGINE_SHARED static void slideVec3(char* text, float min, float max, int granuality, float startValue, char* tabName, glm::vec3* tracking);
	ENGINE_SHARED static void checkbox(bool* tracking, char* text, char* tabName);
	ENGINE_SHARED static void label(char* text, float* value, char* tabName);
	ENGINE_SHARED static void button(char* text, fastdelegate::FastDelegate0<> callback, char* tabName);
	ENGINE_SHARED static void makeSliderVisible(char* test, bool visible);
	ENGINE_SHARED static float getValueOfSliderWithLabel(char* label);
	ENGINE_SHARED static bool getIsCheckedOfCheckboxWithLabel(char* label);
	ENGINE_SHARED static void update();
	ENGINE_SHARED static void addTab(char* tabName);
	ENGINE_SHARED static void addRowToTab(char* tabName);
	ENGINE_SHARED static void addWidgetsToTab(char* searchLabel, QWidget* widg1, QWidget* widg2=nullptr, QWidget* widg3=nullptr, QWidget* widg4=nullptr);
	static QHBoxLayout* getLayout();
	ENGINE_SHARED static void shutdown();
	~DebugMenus();
};

