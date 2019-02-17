#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include <QAction>
#include "screen.h"

namespace Ui {
    class OptionsScreen;
}

class MainWindow;

class OptionsScreen : public Screen
{
    Q_OBJECT

public:
    explicit OptionsScreen(MainWindow* window);
    ~OptionsScreen();

protected:
    void showHandler();

private:
    Ui::OptionsScreen *ui;
    QAction* actionSave;

private slots:
    void onShowOptionsScreen();
};

#endif // OPTIONSSCREEN_H
