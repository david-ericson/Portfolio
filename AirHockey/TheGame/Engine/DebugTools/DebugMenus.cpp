#include <DebugTools\DebugMenus.h>
#include <QtGui\QVBoxLayout>
#include <QtGui\qcheckbox.h>
#include <QtGui\qlabel.h>
#include <QtGui\qpushbutton.h>
#include <QtGui\qmainwindow.h>
#include <QtGui\qtabwidget.h>
#include <DebugTools\ButtonInfo.h>
#include <DebugTools\DebugMemory.h>
#include <Windows.h>
#include <cstdio>


QList<DebugMenus::Slider*> sliders;
QList<DebugMenus::SlideVec3*> vecSliders;
QList<DebugMenus::Checkbox*> checkboxes;
QList<DebugMenus::Label*> labels;
QList<ButtonInfo*> buttons;
QList<DebugMenus::LeTab*> tabLayouts;
QMainWindow* mainWindow;
QWidget* mainWidget;
QVBoxLayout* centralLayout;
QHBoxLayout* mainLayout;
QTabWidget* tabs;

void DebugMenus::Slider::update()
{
	if(value != nullptr)
	{
		*value = slider->value();
	}
}

void DebugMenus::SlideVec3::update()
{
	for(uint i=0; i<3;i++)
	{
		float slideValue = slider[i]->value();
		switch (i)
		{
		case 0:
			value->x = slideValue;
			break;
		case 1:
			value->y = slideValue;
			break;
		case 2:
			value->z = slideValue;
			break;
		}
	}
}

void DebugMenus::Checkbox::update()
{
	if(value != nullptr)
	{
		*value = box->isChecked();
	}
}

void DebugMenus::Label::update()
{
	char buf[50];
	char floatValue[50];
	strcpy_s(buf, priorText);
	sprintf_s(floatValue, "%f", *value);
	strcat_s(buf, floatValue);
	label->setText(buf);
}

void DebugMenus::initialize(QWidget* windowWidget)
{
	mainWindow = new QMainWindow();
	mainLayout = new QHBoxLayout();
	centralLayout = new QVBoxLayout();
	mainWidget = new QWidget();

	mainLayout->addWidget(tabs = new QTabWidget);
	tabs->setMaximumHeight(300);

	mainWidget->setLayout(centralLayout);
	mainWindow->setCentralWidget(mainWidget);
	windowWidget->setMinimumHeight(600);
	centralLayout->addLayout(mainLayout);
	centralLayout->addWidget(windowWidget);
	mainWindow->show();
	mainWindow->resize(1000, 800);
	tabs->setVisible(false);
	mainWindow->showFullScreen();
}

void DebugMenus::slide(char* text, float min, float max, int granuality, float startValue,  char* tabName, float* tracking)
{
	DebugSlider* slider = new DebugSlider(min, max, true, granuality);
	QLabel* label = new QLabel(text);
	label->setMaximumHeight(50.0f);
	slider->setMaximumHeight(100);
	slider->setValue(startValue);
	addWidgetsToTab(tabName, label, slider);
	DebugMenus::Slider* addedSlider = new DebugMenus::Slider;
	addedSlider->slider = slider;
	addedSlider->label = text;
	addedSlider->value = tracking;
	sliders.push_back(addedSlider);
}

void DebugMenus::slideVec3(char* text, float min, float max, int granuality, float startValue, char* tabName, glm::vec3* tracking)
{
	startValue;

	DebugSlider* slider1 = new DebugSlider(min, max, true, granuality);
	DebugSlider* slider2 = new DebugSlider(min, max, true, granuality);
	DebugSlider* slider3 = new DebugSlider(min, max, true, granuality);
	QLabel* label = new QLabel(text);
	label->setMaximumHeight(50.0f);
	slider1->setMaximumHeight(100);
	slider2->setMaximumHeight(100);
	slider3->setMaximumHeight(100);
	slider1->setValue(tracking->x);
	slider2->setValue(tracking->y);
	slider3->setValue(tracking->z);
	addWidgetsToTab(tabName, label, slider1, slider2, slider3);
	DebugMenus::SlideVec3* addedSlider = new DebugMenus::SlideVec3;
	addedSlider->slider[0] = slider1;
	addedSlider->slider[1] = slider2;
	addedSlider->slider[2] = slider3;
	addedSlider->label = text;
	addedSlider->value = tracking;
	vecSliders.push_back(addedSlider);
}

void DebugMenus::checkbox(bool* tracking, char* text, char* tabName)
{
	QCheckBox* box = new QCheckBox(text);
	bool startChecked = (tracking != nullptr)? *tracking:false;
	box->setChecked(startChecked);
	DebugMenus::Checkbox* checkbox = new DebugMenus::Checkbox;
	checkbox->box = box;
	checkbox->value = tracking;
	
	checkboxes.push_back(checkbox);

	addWidgetsToTab(tabName, box);
}

void DebugMenus::label(char* text, float* value, char* tabName)
{
	char buf[50];
	char floatValue[10];
	strcpy_s(buf, text);
	sprintf_s(floatValue, "%f", *value);
	strcat_s(buf, floatValue);
	QLabel* label = new QLabel(buf);
	label->setMaximumHeight(50);
	DebugMenus::Label* myLabel = new DebugMenus::Label;
	myLabel->label = label;
	myLabel->priorText = text;
	myLabel->value = value;
	addWidgetsToTab(tabName, label);
	labels.push_back(myLabel);
}

void DebugMenus::button(char* text, fastdelegate::FastDelegate0<> callback, char* tabName)
{
	ButtonInfo* button = new ButtonInfo();
	button->button = new QPushButton(text);
	QObject::connect(button->button, SIGNAL(clicked()), button, SLOT(buttonClicked()));
	button->delegate = callback;
	buttons.push_back(button);
	addWidgetsToTab(tabName, button->button);
}

void DebugMenus::makeSliderVisible(char* text, bool visible)
{
	for(int i=0; i<sliders.size(); i++)
	{
		if(sliders[i]->label == text)
		{
			sliders[i]->slider->setVisible(visible);
		}
	}
}

float DebugMenus::getValueOfSliderWithLabel(char* label)
{
	float value = 0;
	for(int i=0; i<sliders.size(); i++)
	{
		if(sliders[i]->label == label)
		{
			value = sliders[i]->slider->value();
		}
	}
	return value;
}

bool DebugMenus::getIsCheckedOfCheckboxWithLabel(char* label)
{
	bool value = true;
	for(int i=0; i<checkboxes.size(); i++)
	{
		if(checkboxes[i]->box->text() == label)
		{
			value = checkboxes[i]->box->isChecked();
		}
	}
	return value;
}

void DebugMenus::update()
{
	for(int i = 0; i<sliders.size();i++)
	{
		sliders[i]->update();
	}

	for(int i = 0; i<checkboxes.size();i++)
	{
		checkboxes[i]->update();
	}

	for(int i=0; i<labels.size();i++)
	{
		labels[i]->update();
	}
	for(int i=0; i<vecSliders.size();i++)
	{
		vecSliders[i]->update();
	}

	if(GetAsyncKeyState(VK_ESCAPE))
	{
		mainWindow->close();
	}
}

void DebugMenus::addTab(char* tabName)
{
	QWidget* widg = new QWidget();
	tabs->addTab(widg,tabName);
	LeTab* tab = new LeTab;
	QVBoxLayout* layout = new QVBoxLayout();
	widg->setLayout(layout);
	tab->masterLayout = layout;
	tab->label = tabName;
	tab->widg = widg;
	tabLayouts.push_back(tab);
	addRowToTab(tabName);
}

void DebugMenus::addRowToTab(char* tabName)
{
	bool found = false;
	for(int i=0; i<tabLayouts.size() && !found; i++)
	{
		if(*tabLayouts[i]->label == *tabName)
		{
			QHBoxLayout* newLayout = new QHBoxLayout();
			tabLayouts[i]->masterLayout->addLayout(newLayout);
			tabLayouts[i]->currentLayout.push_back(newLayout);
		}
	}
}

void DebugMenus::addWidgetsToTab(char* searchLabel, QWidget* widg1, QWidget* widg2, QWidget* widg3, QWidget* widg4)
{
	bool found = false;
	for(int i=0; i<tabLayouts.size() && !found; i++)
	{
		if(*searchLabel == *tabLayouts[i]->label)
		{
			found = true;
			int index = tabLayouts[i]->currentLayout.size()-1;
			tabLayouts[i]->currentLayout[index]->addWidget(widg1);
			if(widg2)
			{
				tabLayouts[i]->currentLayout[index]->addWidget(widg2);
			}
			if(widg3)
			{
				tabLayouts[i]->currentLayout[index]->addWidget(widg3);
			}
			if(widg4)
			{
				tabLayouts[i]->currentLayout[index]->addWidget(widg4);
			}
		}
	}
}

QHBoxLayout* DebugMenus::getLayout()
{
	return mainLayout;
}

void DebugMenus::shutdown()
{
	delete mainLayout;
	delete centralLayout;
	delete mainWidget;
	delete mainWindow;
	for(int i=0; i<tabLayouts.size(); i)
	{
		delete tabLayouts[i];
		tabLayouts.erase(tabLayouts.begin()+i);
	}
	for(int i = 0; i<sliders.size();i)
	{
		delete sliders[i];
		sliders.erase(sliders.begin()+i);

	}

	for(int i = 0; i<checkboxes.size();i)
	{
		delete checkboxes[i];
		checkboxes.erase(checkboxes.begin()+i);
	}

	for(int i=0; i<labels.size();i)
	{
		delete labels[i];
		labels.erase(labels.begin()+i);
	}

	for(int i=0; i<buttons.size();i)
	{
		delete buttons[i];
		buttons.erase(buttons.begin()+i);
	}
}
