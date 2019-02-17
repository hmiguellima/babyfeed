#include "busydialog.h"
#include <QApplication>

BusyDialog::BusyDialog() : QProgressDialog(QApplication::tr("Please wait..."), "", 0, 0)
{
    setCancelButton(NULL);
    setAutoClose(false);
    setMinimumDuration(0);
    setWindowModality(Qt::WindowModal);
    show();
    QApplication::processEvents();
}
