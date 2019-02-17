#include "view.h"
#include <QTimer>
#include <QString>
#include "../BabyFeedApp.hpp"
#include <bb/cascades/controls/page.h>
#include <screen/screen.h>
#include <bb/cascades/application.h>
#include <bb/cascades/core/window.h>

using namespace bb::cascades;

View::View(BabyFeedApp* dView, QObject* parent) : QObject(parent),
    _dView(dView), _mainItem(0)
{
}

BabyFeedApp* View::view()
{
    return _dView;
}

void View::notifyActive()
{
	QString name=viewName();
	QObject* newItem;

    newItem=view()->rootObject()->findChild<QObject*>(name);
    if (newItem!=_mainItem) {
    	_mainItem=newItem;
    	handleActivation();
    }
}

void write_bitmap_header(int nbytes, QByteArray& ba, const int size[])
{
	char header[54];

	/* Set standard bitmap header */
	header[0] = 'B';
	header[1] = 'M';
	header[2] = nbytes & 0xff;
	header[3] = (nbytes >> 8) & 0xff;
	header[4] = (nbytes >> 16) & 0xff;
	header[5] = (nbytes >> 24) & 0xff;
	header[6] = 0;
	header[7] = 0;
	header[8] = 0;
	header[9] = 0;
	header[10] = 54;
	header[11] = 0;
	header[12] = 0;
	header[13] = 0;
	header[14] = 40;
	header[15] = 0;
	header[16] = 0;
	header[17] = 0;
	header[18] = size[0] & 0xff;
	header[19] = (size[0] >> 8) & 0xff;
	header[20] = (size[0] >> 16) & 0xff;
	header[21] = (size[0] >> 24) & 0xff;
	header[22] = -size[1] & 0xff;
	header[23] = (-size[1] >> 8) & 0xff;
	header[24] = (-size[1] >> 16) & 0xff;
	header[25] = (-size[1] >> 24) & 0xff;
	header[26] = 1;
	header[27] = 0;
	header[28] = 32;
	header[29] = 0;
	header[30] = 0;
	header[31] = 0;
	header[32] = 0;
	header[33] = 0;
	header[34] = 0; /* image size*/
	header[35] = 0;
	header[36] = 0;
	header[37] = 0;
	header[38] = 0x9;
	header[39] = 0x88;
	header[40] = 0;
	header[41] = 0;
	header[42] = 0x9l;
	header[43] = 0x88;
	header[44] = 0;
	header[45] = 0;
	header[46] = 0;
	header[47] = 0;
	header[48] = 0;
	header[49] = 0;
	header[50] = 0;
	header[51] = 0;
	header[52] = 0;
	header[53] = 0;

	ba.append(header, sizeof(header));
}

void View::grabViewJpeg(QString fileName) {
	screen_pixmap_t screen_pix;
	screen_buffer_t screenshot_buf;
	char *screenshot_ptr = NULL;
	int screenshot_stride = 0;

	int usage, format;
	int size[2];

	screen_context_t context;
	screen_create_context(&context, 0);

	screen_create_pixmap(&screen_pix, context);

	usage = SCREEN_USAGE_READ | SCREEN_USAGE_NATIVE;
	screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_USAGE, &usage);

	format = SCREEN_FORMAT_RGBA8888;
	screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_FORMAT, &format);

	size[0] = 768;
	size[1] = 1280;
	screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_BUFFER_SIZE, size);

	screen_create_pixmap_buffer(screen_pix);
	screen_get_pixmap_property_pv(screen_pix, SCREEN_PROPERTY_RENDER_BUFFERS,
		                              (void**)&screenshot_buf);
	screen_get_buffer_property_pv(screenshot_buf, SCREEN_PROPERTY_POINTER,
		                              (void**)&screenshot_ptr);
	screen_get_buffer_property_iv(screenshot_buf, SCREEN_PROPERTY_STRIDE,
		                              &screenshot_stride);

	screen_read_window(bb::cascades::Application::instance()->mainWindow()->handle(), screenshot_buf, 0, NULL ,0);

	QByteArray array;

	int nbytes = size[0] * size[1] * 4;
	write_bitmap_header(nbytes, array, size);

	for (int i = 0; i < size[1]; i++)
	{
		array.append(screenshot_ptr + i * screenshot_stride, size[0] * 4);
	}

	QImage image = QImage::fromData(array, "BMP");
	QFile outFile(fileName);
	outFile.open(QIODevice::WriteOnly);
	image.save(&outFile, "JPEG");

	screen_destroy_pixmap(screen_pix);
}

QObject * View::mainItem()
{
    return _mainItem;
}

void View::setTitle(QString title)
{
	QMetaObject::invokeMethod(_mainItem, "setTitle", Q_ARG(QVariant, QVariant(title)));
}
