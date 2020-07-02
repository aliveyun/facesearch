#ifndef _HI_FACE_API_H
#define _HI_FACE_API_H
#include <stdint.h>
#include <string>
#ifdef WIN32
#ifdef HI_FACE_EXPORTS
#define HI_FACE_API extern "C"  __declspec(dllexport) 
#else 
#define HI_FACE_API extern "C"  __declspec(dllimport) 
#endif
#else
#define HI_FACE_API
#endif

#ifdef WIN32
#pragma warning(disable:4005 4099 4251 4508 4101 4700 4244 4267 4200 4312 4010 4091 4616 4311 4018 4482 4305 4129 4065 4805 4114 4060 4819 4996 )
#endif

#define HI_FACE_SUCCESS             1
#define HI_FACE_UNKNOWN             0




#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif


struct HiFaceSdkPara
{
	std::string strModulePath = "D:\\Open\\HI\\Release\\x64\\model\\";
	int nModel = 0;    // 0:Ä¬ÈÏ, 1:CPU, 2:GPU
	int nDeviceIndex = 0;   // GPUË÷Òý
	int nMinFaceSize = 80;
};
struct HiImageData
{
	int width;
	int height;
	int channels;
	unsigned char* data;
};
//#if defined(USE_FACE_EXTRACT)
HI_FACE_API int face_api_init(const HiFaceSdkPara& paraSdk);
HI_FACE_API intptr_t face_api_creat_extract();

HI_FACE_API int face_api_extract_feature(intptr_t pInstance,  float* pFeature, unsigned char* rgb_image_data, int width, int height, int x, int y, int w, int h);
HI_FACE_API int face_api_extract_feature2(intptr_t pInstance, const char* file, float* pFeature);
HI_FACE_API int face_api_compare_feature(intptr_t pInstance, const float* pFeatureFst, const float* pFeatureSec, float& nSimility);
HI_FACE_API void * face_api_get_region(const void* packet, int width, int height,int x, int y,int w,int h);

HI_FACE_API void face_api_destroy(intptr_t pInstance);
//#endif
HI_FACE_API int* face_api_detect(intptr_t pInstance,  unsigned char* result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
	unsigned char* rgb_image_data, int width, int height, int step); //input image, it must be RGB (three-channel) image!
#endif
