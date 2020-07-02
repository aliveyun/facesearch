#pragma once
#include <string>
#include <seeta/Struct.h>
//#include <seeta/FaceEngine.h>
#include <seeta/FaceRecognizer.h>
#include "seeta/FaceLandmarker.h"
#include "seeta/FaceDetector.h"
#include "seeta/FaceAntiSpoofing.h"
#include "seeta/Common/Struct.h"
#include "seeta/CTrackingFaceInfo.h"
#include "seeta/FaceTracker.h"
#include "seeta/FaceRecognizer.h"
#include "seeta/QualityAssessor.h"
#include "seeta/QualityOfPoseEx.h"
#include "seeta/QualityOfLBN.h"
class SeetaWrap
{
    static const int kFaceResultInvalidOk = 0;
    static const int kFaceResultInvalidInput = 3;
public:
    SeetaWrap(const std::string& strModelPath, seeta::ModelSetting::Device device, int nDeviceIndex);
    ~SeetaWrap();


public:
    //void Detect(const seeta::ImageData& dataFst, std::vector<SeetaFaceInfo>& vecFaces);
    int* Detect(unsigned char* result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
        unsigned char* rgb_image_data, int width, int height, int step);

    bool ExtractFeature(float* pFeature ,unsigned char* rgb_image_data, int width, int height, int x, int y, int w, int h);
    bool ExtractFeature(const char* file, float* pFeature);
    void GetFeatureSize(int& nSize);
    //int Compare1v1(const seeta::ImageData& dataFst, const seeta::ImageData& dataSec, float& nSimility);
    int CompareWithFeature(const float* pFeatureFst, const float* pFeatureSec, float& nSimility);

public:
    SeetaWrap() = delete;

private:
    std::string m_strModelPath;
    // face handles
    //seeta::ModelSetting FD_model;
    //seeta::ModelSetting PD_model;
    //seeta::ModelSetting FR_model;
    //seeta::FaceRecognizer m_faceRecog;
    //seeta::FaceEngine engine;

	seeta::FaceDetector* m_fd;
	seeta::FaceLandmarker* m_pd;
	seeta::FaceLandmarker* m_pd68;
	seeta::FaceAntiSpoofing* m_spoof;
	seeta::FaceRecognizer* m_fr;
	seeta::FaceTracker* m_tracker;
	seeta::QualityAssessor* m_qa;
	seeta::QualityOfLBN* m_lbn;
	seeta::QualityOfPoseEx* m_poseex;


};

