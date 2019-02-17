#ifndef CAMERASCREEN_H
#define CAMERASCREEN_H

#include <QWidget>
#include "screen.h"
#ifdef Q_OS_SYMBIAN
    #include "camera/xqcamera.h"
    #include "camera/xqviewfinderwidget.h"
#endif
#include <QAction>
#include <QByteArray>
#include <QImage>

namespace Ui {
    class CameraScreen;
}

class CameraScreen : public Screen
{
    Q_OBJECT

public:
    explicit CameraScreen(MainWindow* window);
    ~CameraScreen();

protected:
    virtual void showHandler();

private:
    Ui::CameraScreen *ui;
#ifdef Q_OS_SYMBIAN
    XQCamera *camera;
    XQViewFinderWidget *viewfinder;
#endif
    QAction *captureAction;
    QAction *backAction;

    void stopCamera();

private slots:
    void goBackToBabyScreen();
    void onShowCameraScreen();
    virtual void captureComplete(QByteArray data);
};

#endif // CAMERASCREEN_H
