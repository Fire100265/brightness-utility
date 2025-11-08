#include "ui.h"
#include <QString>
#include <QTimer>
#include <QMenu>
#include <QAction>

int uiopen(int argc, char* argv[], DDCA_Display_Handle dh) {
    QApplication app(argc, argv);

    // --- Main window setup ---
    QWidget window;
    window.setWindowTitle("Brightness Utility");

    QSlider *slider = new QSlider(Qt::Horizontal);
    QLineEdit *textBox = new QLineEdit;
    slider->setRange(0, 100);

    // Initial brightness
    int current = get_brightness(dh);
    if (current < 0) current = 50;
    slider->setValue(current);
    textBox->setText(QString::number(current));

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(textBox);
    window.setLayout(layout);

    // --- System tray ---
    QSystemTrayIcon tray;
    QIcon icon(":/sun.svg"); // embedded resource
    tray.setIcon(icon);
    tray.setToolTip(QString("Brightness: %1%").arg(current));
    tray.show();

    // Tray menu
    QMenu trayMenu;
    QAction quitAction("Quit", &app);
    trayMenu.addAction(&quitAction);
    tray.setContextMenu(&trayMenu);

    QObject::connect(&quitAction, &QAction::triggered, [&]() {
        app.quit();
    });

    QObject::connect(&tray, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::Trigger) {
            window.show();
            window.raise();
            window.activateWindow();
        }
    });

    // --- Slider/TextBox connections ---
    QObject::connect(slider, &QSlider::valueChanged, [&](int value) {
        textBox->setText(QString::number(value));
        set_brightness(dh, value);
        tray.setToolTip(QString("Brightness: %1%").arg(value));
    });

    QObject::connect(textBox, &QLineEdit::textChanged, [&](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if(ok && value >= slider->minimum() && value <= slider->maximum()) {
            slider->setValue(value);
        }
    });

    // --- Auto-refresh brightness every second ---
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        int newVal = get_brightness(dh);
        if (newVal >= 0 && newVal != slider->value()) {
            slider->blockSignals(true);
            slider->setValue(newVal);
            textBox->setText(QString::number(newVal));
            tray.setToolTip(QString("Brightness: %1%").arg(newVal));
            slider->blockSignals(false);
        }
    });
    timer.start(1000); // every 1000 ms

    return app.exec();
}

