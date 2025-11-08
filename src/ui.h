#ifndef UI_H
#define UI_H

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QObject>
#include "ddcutil.h"

int uiopen(int argc, char* argv[], DDCA_Display_Handle dh);

#endif // UI_H

