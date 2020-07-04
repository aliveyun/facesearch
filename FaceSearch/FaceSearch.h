#pragma once

#include <QtWidgets/QWidget>
#include "ui_FaceSearch.h"


typedef struct face_item_t
{
	QString  File;
    QString  SaveFile;
    QString  FileName;
	intptr_t handle;
    intptr_t pThis;
    intptr_t faceObject;
	float* feature;
    float similarity;
    unsigned char* pBuffer;
} FACE_ITEM;

class FaceSearch : public QWidget
{
    Q_OBJECT

public:
    FaceSearch(QWidget *parent = Q_NULLPTR);

    void getOneFileFace(QString file);


    float* getFeature() {
		return _feature;
	};
signals:
    void signal_count();
public slots:
    void btnChooseFace();
    void btnChooseFile();
    void btnChooseSave();
    void btnStart();
    void btnStop();
    void count();
private:
    Ui::FaceSearchClass ui;
    QString  mFile;
    //intptr_t _faceObject;
    intptr_t _handle;
    float* _feature;
    int _count=0;
};
