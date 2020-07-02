#include "FaceSearch.h"
#include <QFileInfo>
#include <QUrl>
#include <qdebug.h>
#include <QtWidgets/QFileDialog>
#include <QtCore/qstring.h>
#include <QtCore/QBuffer>
#include <QtCore/QVariant>
#include <QtCore/qdir.h>
#include <QtCore/QDirIterator>
#include "thread_pool.h"
#include "../HILibFaceAPI/include/HILibFaceAPI.h"
#include "../HIFfReadAPI/include/HIFfReadAPI.h"

#include <iostream>
#include <chrono>
#include <sstream>
#include<windows.h>
#include "yh_global.h"
#include <QIntValidator>
#include <QDoubleValidator>


#define DETECT_BUFFER_SIZE 0x20000
thread_pool g_threadpool;
FaceSearch::FaceSearch(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.btn_choose_face, SIGNAL(clicked()), this, SLOT(btnChooseFace()));
	connect(ui.btn_choose_file, SIGNAL(clicked()), this, SLOT(btnChooseFile()));
	connect(ui.btn_choose_save, SIGNAL(clicked()), this, SLOT(btnChooseSave()));
	connect(ui.btnstart, SIGNAL(clicked()), this, SLOT(btnStart()));
	connect(ui.btnstop, SIGNAL(clicked()), this, SLOT(btnStop()));

	connect(this, SIGNAL(signal_count()), this, SLOT(count()));

	/*QDoubleValidator* vfdthreshold = new QDoubleValidator(0.0, 1.0, 2);
	vfdthreshold->setRange(0.0, 1.0);
	ui.lineEdit_Similarity->setValidator(vfdthreshold);*/

	/*QDoubleValidator* antValidator = new QDoubleValidator;
	antValidator->setRange(0.0, 1.0);
	ui.lineEdit_Similarity->setValidator(antValidator);*/

	//QRegExp rx("[0-9\.]+$");

	//限制-180，180，并限定小数点后4位
	//QRegExp rx("^+?(1|1?[0-7]?\\d(\\.\\d{1,2})?)$");
	//QRegExp rx("^(?:\\.\\d{1,2})?$|(^\\t?$)");

	/*QRegExp rx("^?(1|[0-1]?\\d(\\.\\d{1,2})?)$");*/

	QRegExp rx("^(?:0|1|0.(?!0+$)[0-9]+)$");
	QRegExpValidator* validator = new QRegExpValidator(rx, this);
	ui.lineEdit_Similarity->setValidator(validator);




	g_threadpool.init_thread_size(10);
	HiFaceSdkPara para;
	int b = face_api_init(para);
	ffmpg_api_init();
	
	_feature= new float[1024];
	memset(_feature, 0, 1024 * sizeof(float));

	AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);



}

void FaceSearch::btnChooseFace()
{
	QFileInfo  fileInfo;
	mFile = QFileDialog::getOpenFileName();
	QImage image(mFile);
	ui.label_ico->setPixmap(QPixmap::fromImage(image));


	intptr_t faceObject = face_api_creat_extract();
	QString file = QDir::toNativeSeparators(mFile);
	face_api_extract_feature2(faceObject, UToGString(file).c_str(), _feature);
	face_api_destroy(faceObject);
	
	//float pFeature[1024] = { 0 };

	//face_api_extract_feature2(_faceObject, "D:\\pic\\crop_3_98.jpg", pFeature);

	////face_api_extract_feature2(_faceObject, QDir::toNativeSeparators(mFile).toLocal8Bit().data(), pFeature);

	//float nSimilarity = 0l;
	//face_api_compare_feature(_faceObject, pFeature, _feature, nSimilarity);
	//printf("1111\n");


}
void FaceSearch::btnChooseFile()
{
	//文件夹路径
	QString  srcDirPath = QFileDialog::getExistingDirectory(
		this, "choose src Directory",
		"/");

	if (srcDirPath.isEmpty())
	{
		return;
	}
	else
	{
		qDebug() << "srcDirPath=" << srcDirPath;
		srcDirPath += "/";
	}
	ui.lineEdit->setText(srcDirPath);
}
void FaceSearch::btnChooseSave()
{
	QString  srcDirPath = QFileDialog::getExistingDirectory(
		this, "choose src Directory",
		"/");

	if (srcDirPath.isEmpty())
	{
		return;
	}
	else
	{
		qDebug() << "srcDirPath=" << srcDirPath;
		srcDirPath += "/";
	}
	ui.lineEdit_save->setText(srcDirPath);
}

static QStringList addSubFolderImages(QString path)
{
	//判断路径是否存在
	QDir dir(path);
	if (!dir.exists())
	{
		return QStringList();
	}

	//获取所选文件类型过滤器
	QStringList filters;
	//文件过滤
	//filters << QString("*.jpeg") << QString("*.jpg") << QString("*.png") << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
	//定义迭代器并设置过滤器
	QDirIterator dir_iterator(path,
		filters,
		QDir::Files | QDir::NoSymLinks,
		QDirIterator::Subdirectories);
	QStringList string_list;
	while (dir_iterator.hasNext())
	{
		dir_iterator.next();
		QFileInfo file_info = dir_iterator.fileInfo();
		QString absolute_file_path = file_info.absoluteFilePath();
		//QString file_name = file_info.baseName();
		//absolute_file_path.append("@@");
		//absolute_file_path.append(file_name);

		string_list.append(absolute_file_path);
	}
	return string_list;
}
void FaceSearch::btnStart()
{
	QStringList list = addSubFolderImages(ui.lineEdit->text());
	QList<QString>::Iterator it = list.begin(), itend = list.end();
	int i = 0;
	for (; it != itend; it++, i++) {
		g_threadpool.add_task(&FaceSearch::getOneFileFace, this, *it);
	}
}
int64_t GetTimestamp()
{
	auto curr = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr.time_since_epoch());
	return ms.count();
}
static void v_packet_cb(intptr_t param, int streamid, const void* packet, size_t bytes, int w, int h, uint64_t time, int flags, int extra)
{
	FACE_ITEM* item = ( FACE_ITEM*)param;
	FaceSearch* pThis =(FaceSearch*) item->pThis;
	if (extra/*||!flags*/)
		return;
	int* pResults = NULL;
	int64_t start = GetTimestamp();
	pResults = face_api_detect(item->faceObject, item->pBuffer, (unsigned char*)packet, w, h, w * 3);
	qDebug() << "Detect Finished, it costs " << GetTimestamp() - start << " milli-seconds\n";
	for (int i = 0; i < (pResults ? *pResults : 0); i++) {
		short* p = ((short*)(pResults + 1)) + 142 * i;
		if ((p[3] > 80) && (p[4] > 80) && (abs(p[4]) > 75))
		{
			float pFeature[1024] = { 0 };
			face_api_extract_feature(item->faceObject, pFeature,(unsigned char*) packet, w, h, p[0], p[1], p[2], p[3]);

			float nSimilarity = 0l;
			face_api_compare_feature(item->faceObject, pFeature, pThis->getFeature(), nSimilarity);
			printf("nSimilarity=%.3f\n", nSimilarity);

			if (item->similarity < nSimilarity)
			{
				if (item->handle)
				{
					QString file(item->SaveFile);
					file.append(QString::number(time));
					file.append(".jpg");

					ffmpg_api_snap_shot(item->handle, file.toLocal8Bit().data());
				}
				emit pThis->signal_count();
				break;
			}

		}
	}
	/*int* pResults = NULL;

	int64_t start = GetTimestamp();
	pResults = face_api_detect(item->pBuffer, (unsigned char*)packet, w, h, w * 3);
	qDebug() << "Detect Finished, it costs " << GetTimestamp() - start << " milli-seconds\n";
	for (int i = 0; i < (pResults ? *pResults : 0); i++) {
		short* p = ((short*)(pResults + 1)) + 142 * i;
		if ((p[3] > 80) && (p[4] > 80) && (abs(p[4]) > 75))
		{

	
			if (p[3]<256)
			{
				int w1 = 256 - p[3] / 2;
				p[1] += w1;
				
			}
			if (p[4] < 256)
			{
				int h1 = 256 - p[4] / 2;
				p[2] += h1;
				
			}

			p[1] = p[1] + 256 > w ? w - 256 : p[1] ;
			p[2] = p[2] + 256 > h ? h - 256 : p[2] ;
			p[3] = 256;
			p[4] = 256;
			HiImageData imgSrc;
			imgSrc.width = p[3];
			imgSrc.height = p[4];
			//imgSrc.width =w;
			//imgSrc.height = h;
			imgSrc.channels = 3;

			start = GetTimestamp();
			imgSrc.data = (unsigned char*)face_api_get_region(packet, w, h, p[1], p[2], p[3], p[4]);
			//imgSrc.data = (unsigned char*)face_api_get_region(packet, w, h, 0, 0, w, h);;
			qDebug() << "face_api_extract_feature  00, it costs " << GetTimestamp() - start << " milli-seconds\n";
			
			float pFeature[1024] = { 0 };
			

			start = GetTimestamp();
			face_api_extract_feature(pThis->getExtractHandle(), imgSrc, pFeature);

			qDebug() << "face_api_extract_feature  0011, it costs " << GetTimestamp() - start << " milli-seconds\n";
			float nSimilarity = 0l;
			face_api_compare_feature(pThis->getExtractHandle(), pFeature, pThis->getFeature(), nSimilarity);
			printf("nSimilarity=%.3f\n", nSimilarity);
			qDebug() << "face_api_extract_feature  2222, it costs " << GetTimestamp() - start << " milli-seconds\n";
			//delete[]pFeature;
			if (0.90< nSimilarity)
			{
				if (item->handle)
				{
					QString file(item->SaveFile);
					file.append(QString::number(time));
					file.append(".jpg");
					
					ffmpg_api_snap_shot(item->handle, file.toLocal8Bit().data());
				}
				emit pThis->signal_count();
				break;
			}
		}
	}*/
}
static void e_onerror(intptr_t param, int code)
{
	FACE_ITEM* item = (FACE_ITEM*)param;
	FaceSearch* pThis = (FaceSearch*)item->pThis;

	ffmpg_api_close_stream(item->handle);
	delete[]item->pBuffer;
	face_api_destroy(item->faceObject);
	delete item;
}

void FaceSearch::getOneFileFace(QString file)
{
	FACE_ITEM* item = new FACE_ITEM();
	item->pThis =(intptr_t) this;
	item->feature = _feature;
	item->File = file;
	item->SaveFile = ui.lineEdit_save->text();
	item->pBuffer = new unsigned char[DETECT_BUFFER_SIZE];
	item->similarity = ui.lineEdit_Similarity->text().toFloat();
	item->faceObject = face_api_creat_extract();
	struct ffmpeg_handler_t h;
	memset(&h, 0, sizeof(struct ffmpeg_handler_t));
	h.onvideo = v_packet_cb;
	h.onerror = e_onerror;
	intptr_t handle = ffmpg_api_open_stream((char*)file.toStdString().c_str(), HI_PIXEL_FMT_RGB24, 0, 0, &h, (intptr_t)item);
	item->handle = handle;
	ffmpg_api_start_stream(handle);
	ffmpg_api_setreconnect(handle ,1,1);

}
void FaceSearch::btnStop()
{

}
void FaceSearch::count()
{
	_count++;
	ui.label_total->setText(QString::number(_count));
}