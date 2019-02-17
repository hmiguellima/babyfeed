#ifndef BUSYDIALOG_H
#define BUSYDIALOG_H

#include <QProgressDialog>

class BusyDialog : public QProgressDialog
{
    Q_OBJECT
public:
    BusyDialog();
};

#endif // BUSYDIALOG_H
