#include <QtGui\qwidget>
#include <FastDelegate.h>

class QPushButton;

#pragma once
struct ButtonInfo : public QObject
	{
		Q_OBJECT
	public:
		QPushButton* button;
		char* tab;
		fastdelegate::FastDelegate0<>delegate;
		private slots:
			void buttonClicked();
	};

