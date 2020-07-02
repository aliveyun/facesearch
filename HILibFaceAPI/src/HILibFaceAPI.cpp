#include "HILibFaceAPI.h"
#include "facedetectcnn.h"
// https://github.com/ShiqiYu/libfacedetection
//#define _ENABLE_AVX2 //Please enable it if X64 CPU //AVX2 某些电脑支支持avx

//#if defined(USE_FACE_EXTRACT)
#include <memory>
#include <vector>
#include "SeetaWrap.h"
#include <io.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define VERIFY_RETURN(conn, ret) \
    if(!conn) return ret;

seeta::ModelSetting::Device device;
std::string strModelPath;
int nDeviceIndex = 0;

bool CheckModulePath(const std::string strModulePath)
{
	auto code = _access(strModulePath.c_str(), 0);
	return (-1 == _access(strModulePath.c_str(), 0)) ? false : true;
}
HI_FACE_API int face_api_init(const HiFaceSdkPara& paraSdk)
{

	device = (seeta::ModelSetting::Device)paraSdk.nModel;
	nDeviceIndex = paraSdk.nDeviceIndex;
	strModelPath = paraSdk.strModulePath;
	VERIFY_RETURN(CheckModulePath(strModelPath), HI_FACE_UNKNOWN);
	if (strModelPath.back() != '\\')
		strModelPath.push_back('\\');
	return HI_FACE_SUCCESS;
}

HI_FACE_API intptr_t face_api_creat_extract()
{
	SeetaWrap * p =  new SeetaWrap(strModelPath, device, nDeviceIndex);
	return (intptr_t)p;
}
HI_FACE_API int face_api_extract_feature(intptr_t pInstance, float* pFeature, unsigned char* rgb_image_data, int width, int height, int x, int y, int w, int h)
{

	/*SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);*/
	SeetaWrap* pFaceObject = (SeetaWrap*)(pInstance);
	if (!pFaceObject->ExtractFeature(pFeature ,rgb_image_data,  width,  height,  x,  y,  w,  h))
		return HI_FACE_UNKNOWN;
	return HI_FACE_SUCCESS;
}
HI_FACE_API int face_api_extract_feature2(intptr_t pInstance, const char* file, float* pFeature)
{
	SeetaWrap* pFaceObject = (SeetaWrap*)(pInstance);
	if (!pFaceObject->ExtractFeature(file, pFeature))
		return HI_FACE_UNKNOWN;
	return HI_FACE_SUCCESS;

}
HI_FACE_API int face_api_compare_feature(intptr_t pInstance, const float* pFeatureFst, const float* pFeatureSec, float& nSimility)
{

	//VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
	SeetaWrap* pFaceObject = (SeetaWrap*)(pInstance);
	return pFaceObject->CompareWithFeature(pFeatureFst, pFeatureSec, nSimility);
	
}
HI_FACE_API void* face_api_get_region(const void* packet, int width, int height, int x, int y, int w, int h)
{
	cv::Mat img(cv::Size(width, height), CV_8UC3, (unsigned char*)packet, 3 * width);
	cv::Rect area(x, y, w, h);
	cv::Mat img_region = img(area);
	imwrite("D://pic/11111.jpg", img_region);
	return img_region.data;
}
HI_FACE_API void face_api_destroy(intptr_t pInstance)
{
	
	SeetaWrap* pFaceObject = (SeetaWrap*)(pInstance);
	if (pFaceObject != nullptr)
	{
		delete pFaceObject;
		pFaceObject = nullptr;
	}
}
//#endif
HI_FACE_API int* face_api_detect(intptr_t pInstance, unsigned char* result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
	unsigned char* rgb_image_data, int width, int height, int step) //input image, it must be RGB (three-channel) image!
{
	if (0!=pInstance)
	{
		SeetaWrap* pFaceObject = (SeetaWrap*)(pInstance);
		return pFaceObject->Detect(result_buffer, rgb_image_data, width, height, step);
	} 
	return facedetect_cnn(result_buffer, rgb_image_data, width, height, step);
}
