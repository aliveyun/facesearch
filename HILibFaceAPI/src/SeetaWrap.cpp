#include "SeetaWrap.h"
#include <seeta/QualityAssessor.h>
#include "HILibFaceAPI.h"
#include "seeta/QualityOfPoseEx.h"
#include "seeta/Struct.h"
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
#include "seeta/QualityOfPoseEx.h"
#include "seeta/Struct.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

SeetaWrap::SeetaWrap(const std::string& strModelPath, seeta::ModelSetting::Device device, int nDeviceIndex)
    : m_strModelPath(strModelPath)
    //, FD_model(strModelPath + "face_detector.csta", device, nDeviceIndex)
    //, PD_model(strModelPath + "face_landmarker_pts5.csta", device, nDeviceIndex)
    //, FR_model(strModelPath + "face_recognizer.csta", seeta::ModelSetting::CPU, nDeviceIndex)
    ///*, engine(FD_model, PD_model, FR_model, 2, 16)*/
    //, m_faceRecog(FR_model)
{
    //FR_model.set_id(0);

	seeta::ModelSetting fd_model;
	fd_model.append(strModelPath + "face_detector.csta");
	fd_model.set_device(seeta::ModelSetting::CPU);
	fd_model.set_id(0);
	m_fd = new seeta::FaceDetector(fd_model);
	m_fd->set(seeta::FaceDetector::PROPERTY_MIN_FACE_SIZE, 100);

	m_tracker = new seeta::FaceTracker(fd_model, 544, 960);
	m_tracker->SetMinFaceSize(100); //set(seeta::FaceTracker::PROPERTY_MIN_FACE_SIZE, 100);

	seeta::ModelSetting pd_model;
	pd_model.append(strModelPath + "face_landmarker_pts5.csta");
	pd_model.set_device(seeta::ModelSetting::CPU);
	pd_model.set_id(0);
	m_pd = new seeta::FaceLandmarker(pd_model);


	seeta::ModelSetting spoof_model;
	spoof_model.append(strModelPath + "fas_first.csta");
	spoof_model.append(strModelPath + "fas_second.csta");
	spoof_model.set_device(seeta::ModelSetting::CPU);
	spoof_model.set_id(0);
	m_spoof = new seeta::FaceAntiSpoofing(spoof_model);
	m_spoof->SetThreshold(0.30, 0.80);

	seeta::ModelSetting fr_model;
	fr_model.append(strModelPath + "face_recognizer.csta");
	fr_model.set_device(seeta::ModelSetting::CPU);
	fr_model.set_id(0);
	m_fr = new seeta::FaceRecognizer(fr_model);



	///////////////////////////////
	seeta::ModelSetting setting68;
	setting68.set_id(0);
	setting68.set_device(SEETA_DEVICE_CPU);
	setting68.append(strModelPath + "face_landmarker_pts68.csta");
	m_pd68 = new seeta::FaceLandmarker(setting68);

	seeta::ModelSetting posemodel;
	posemodel.set_device(SEETA_DEVICE_CPU);
	posemodel.set_id(0);
	posemodel.append(strModelPath + "pose_estimation.csta");
	m_poseex = new seeta::QualityOfPoseEx(posemodel);
	m_poseex->set(seeta::QualityOfPoseEx::YAW_LOW_THRESHOLD, 20);
	m_poseex->set(seeta::QualityOfPoseEx::YAW_HIGH_THRESHOLD, 10);
	m_poseex->set(seeta::QualityOfPoseEx::PITCH_LOW_THRESHOLD, 20);
	m_poseex->set(seeta::QualityOfPoseEx::PITCH_HIGH_THRESHOLD, 10);

	seeta::ModelSetting lbnmodel;
	lbnmodel.set_device(SEETA_DEVICE_CPU);
	lbnmodel.set_id(0);
	lbnmodel.append(strModelPath + "quality_lbn.csta");
	m_lbn = new seeta::QualityOfLBN(lbnmodel);
	m_lbn->set(seeta::QualityOfLBN::PROPERTY_BLUR_THRESH, 0.80);

	m_qa = new seeta::QualityAssessor();
	m_qa->add_rule(seeta::INTEGRITY);
	m_qa->add_rule(seeta::RESOLUTION);
	m_qa->add_rule(seeta::BRIGHTNESS);
	m_qa->add_rule(seeta::CLARITY);
	m_qa->add_rule(seeta::POSE_EX, m_poseex, true);



}


SeetaWrap::~SeetaWrap()
{
    
}

int* SeetaWrap::Detect(unsigned char* result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
	unsigned char* rgb_image_data, int width, int height, int step)
{

	cv::Mat mat(cv::Size(width, height), CV_8UC3, (unsigned char*)rgb_image_data, 3 * width);

	SeetaImageData img;
	img.width = mat.cols;
	img.height = mat.rows;
	img.channels = mat.channels();
	img.data = mat.data;
	auto face_array = m_fd->detect(img);
	int* pCount = (int*)result_buffer;
	pCount[0] = face_array.size;
	for (int i=0 ;i< face_array.size;i++)
	{
		short* p = ((short*)(result_buffer + 4)) + 142 * size_t(i);
		SeetaRect& face = face_array.data[i].pos;
		p[0] = face.x;
		p[1] = face.y;
		p[2] = face.width;
		p[3] = face.height;

	}

	return pCount;
}
bool SeetaWrap::ExtractFeature(float* pFeature, unsigned char* rgb_image_data, int width, int height, int x, int y, int w, int h)
{
    try
	{
		if (w<1||h<1)
		{
			return false;
		}
		cv::Mat mat(cv::Size(width, height), CV_8UC3, (unsigned char*)rgb_image_data, 3 * width);

		SeetaImageData img;
		img.width = mat.cols;
		img.height = mat.rows;
		img.channels = mat.channels();
		img.data = mat.data;
		
		SeetaPointF points[5];

		SeetaRect face;
		face.height = w;
		face.width = h;
		face.x = x;
		face.y = y;
	
		m_pd->mark(img, face, points);
		m_qa->feed(img, face, points, 5);
		auto result1 = m_qa->query(seeta::BRIGHTNESS);
		auto result2 = m_qa->query(seeta::RESOLUTION);
		auto result3 = m_qa->query(seeta::CLARITY);
		auto result4 = m_qa->query(seeta::INTEGRITY);
		//auto result5 = m_qa->query(seeta::POSE);
		auto result = m_qa->query(seeta::POSE_EX);

		/*if (result.level == 0 || result1.level == 0 || result2.level == 0 || result3.level == 0 || result4.level == 0)
		{
			return 2;
		}*/

		seeta::ImageData cropface = m_fr->CropFaceV2(img, points);

		//cv::Mat imgmat(cropface.height, cropface.width, CV_8UC(cropface.channels), cropface.data);
		//cv::imwrite("D:\\189.jpg", imgmat);
        return m_fr->ExtractCroppedFace(cropface, pFeature);
    }
    catch (const std::exception& e) {}
    return false;
}
bool SeetaWrap::ExtractFeature(const char* file, float* pFeature)
{
	cv::Mat mat = cv::imread(/*"d:\\pic/4.jpg"*/file); ;
	if (mat.data == NULL)
	{
		return HI_FACE_UNKNOWN;
	}
	SeetaImageData img;
	img.width = mat.cols;
	img.height = mat.rows;
	img.channels = mat.channels();
	img.data = mat.data;
	// m_fr->ExtractCroppedFace(img, features);
	auto face_array = m_fd->detect(img);

	if (face_array.size <= 0)
	{
		return -2;
	}
	else if (face_array.size > 1)
	{
		return 1;
	}

	SeetaRect& face = face_array.data[0].pos;
	SeetaPointF points[5];

	m_pd->mark(img, face, points);

	m_qa->feed(img, face, points, 5);
	auto result1 = m_qa->query(seeta::BRIGHTNESS);
	auto result2 = m_qa->query(seeta::RESOLUTION);
	auto result3 = m_qa->query(seeta::CLARITY);
	auto result4 = m_qa->query(seeta::INTEGRITY);
	//auto result5 = m_qa->query(seeta::POSE);
	auto result = m_qa->query(seeta::POSE_EX);

	if (result.level == 0 || result1.level == 0 || result2.level == 0 || result3.level == 0 || result4.level == 0)
	{
		return 2;
	}

	/*
	SeetaPointF points68[68];
	memset( points68, 0, sizeof( SeetaPointF ) * 68 );

	m_pd68->mark(img, face,points68);
	int light, blur, noise;
	light = blur = noise = -1;

	m_lbn->Detect( img, points68, &light, &blur, &noise );
	*/
	//std::cout << "light:" << light << ", blur:" << blur << ", noise:" << noise << std::endl;

	seeta::ImageData cropface = m_fr->CropFaceV2(img, points);
	cv::Mat imgmat(cropface.height, cropface.width, CV_8UC(cropface.channels), cropface.data);

	m_fr->ExtractCroppedFace(cropface, pFeature);

	cv::imwrite("D:\\189.jpg", imgmat);


	return false;
}
void SeetaWrap::GetFeatureSize(int& nSize)
{
    nSize = m_fr->GetExtractFeatureSize();
}

//int SeetaWrap::Compare1v1(const seeta::ImageData& imgFst, const seeta::ImageData& imgSec, float& nSimilarity)
//{
//    std::vector<SeetaFaceInfo> vecFstDetectFaces = engine.DetectFaces(imgFst);
//    if (vecFstDetectFaces.empty())return kFaceResultInvalidInput;
//    std::vector<SeetaFaceInfo> vecSecDetectFaces = engine.DetectFaces(imgSec);
//    if (vecSecDetectFaces.empty())return kFaceResultInvalidInput;
//    try
//    {
//        nSimilarity = engine.Compare(imgFst, vecFstDetectFaces.front(), imgSec, vecSecDetectFaces.front());
//    }
//    catch (const std::exception& e) {}
//
//    return kFaceResultInvalidOk;
//}

int SeetaWrap::CompareWithFeature(const float* pFeatureFst, const float* pFeatureSec, float& nSimility)
{
    if (nullptr == pFeatureFst || nullptr == pFeatureSec)return kFaceResultInvalidInput;
    try
    {
        nSimility =m_fr->CalculateSimilarity(pFeatureFst, pFeatureSec);
    }
    catch (const std::exception& e) {}
    return HI_FACE_SUCCESS;
}