#include "camerascreen.h"
#include "ui_camerascreen.h"
#include "mainwindow.h"
#include <QSize>
#include <QMessageBox>
#include "eventbus.h"

CameraScreen::CameraScreen(MainWindow* window) :
    Screen(window),
    ui(new Ui::CameraScreen)
{
    ui->setupUi(this);

    captureAction=new QAction(tr("Capture"), this);
    captureAction->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(captureAction);
    backAction=new QAction(tr("Back"), this);
    backAction->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(backAction);

    connect(backAction, SIGNAL(triggered()), this, SLOT(goBackToBabyScreen()));
    connect(EventBus::getInstance(), SIGNAL(showCameraScreen()), this, SLOT(onShowCameraScreen()));

#ifdef Q_OS_SYMBIAN
    viewfinder=new XQViewFinderWidget(this);
    camera=new XQCamera(this);
    camera->setCaptureSize(QSize(320,240));
    viewfinder->setCamera(*camera);
    ui->viewfinderHolderLayout->addWidget(viewfinder);
    viewfinder->setViewfinderSize(QSize(320, 240));

    connect(camera, SIGNAL(cameraReady()), viewfinder, SLOT(start()));
    connect(camera, SIGNAL(captureCompleted(QByteArray)), this, SLOT(captureComplete(QByteArray)));
    connect(camera, SIGNAL(captureCompleted(QImage*)), this, SLOT(captureComplete(QImage*)));
    connect(viewfinder, SIGNAL(viewFinderFrameReady()), this, SLOT(frameReady()));
    connect(captureAction, SIGNAL(triggered()), camera, SLOT(capture()));
#endif
}

CameraScreen::~CameraScreen()
{
    delete ui;
}

void CameraScreen::showHandler()
{
#ifdef Q_OS_SYMBIAN
    camera->open(0);
#endif
}

void CameraScreen::stopCamera()
{
#ifdef Q_OS_SYMBIAN
    camera->close();
    viewfinder->stop();
#endif
}

void CameraScreen::goBackToBabyScreen()
{
    stopCamera();
    EventBus::getInstance()->fireBabyPhotoAborted();
}


void CameraScreen::captureComplete(QByteArray data)
{
    EventBus::getInstance()->fireBabyPhotoCaptured(data);
#ifdef Q_OS_SYMBIAN
    camera->releaseImageBuffer();
#endif
    stopCamera();
}

void CameraScreen::onShowCameraScreen()
{
    show();
}
