#pragma once
#include <string>
#include <vector>


#ifdef FACE_SDK_LIBRARY_EXPORT
#ifdef _WIN32
#define FACE_SDK_LIBRARY extern "C" __declspec(dllexport)
#else
#define FACE_SDK_LIBRARY extern "C" __attribute__((visibility("default")))
#endif
#else
#define FACE_SDK_LIBRARY extern "C"
#endif


enum FaceResult
{
    kFaceResultOk,
    kFaceResultInvalidModelPath,
    kFaceResultInvalidInstance,
    kFaceResultInvalidInput,
    kFaceResultExtractFailed

};

struct FaceSdkPara
{
    std::string strModulePath = "model/";
    int nModel = 0;    // 0:Ä¬ÈÏ, 1:CPU, 2:GPU
    int nDeviceIndex = 0;   // GPUË÷Òý
    int nMinFaceSize = 80;
};

struct FaceInfo
{
    int x;
    int y;
    int width;
    int height;
};

struct ImageData
{
    int width;
    int height;
    int channels;
    unsigned char* data;
};

/*
*
* @brief:       init the face sdk
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    paraSdk, para of face sdk
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult InitFaceSdk(const FaceSdkPara& paraSdk);

/*
*
* @brief:       create an instance
* @author:      wite_chen
* @create:      20120-01-09
* @para[out]:   pInstance, instance of face sdk
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult CreateInstance(void* &pInstance);

/*
*
* @brief:       detect faces of one picture
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    pInstance, instance of face sdk
* @para[in]:    dataImg, picture's info
* @para[out]    vecFaces, faces of detection
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult Detect(void* pInstance, const ImageData& dataImg, std::vector<FaceInfo>& vecFaces);

/*
*
* @brief:       get size of feature
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    pInstance, instance of face sdk
* @para[out]    nSize, the size of feature
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult GetFeatureSize(void* pInstance, int& nSize);

/*
*
* @brief:       extract feature of one picture
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    pInstance, instance of face sdk
* @para[in]:    dataImg, picture's info
* @para[out]    pFeature, the feature of picture
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult ExtractFeature(void* pInstance, const ImageData& dataImg, float* pFeature);

/*
*
* @brief:       calculate similarity of two person with image
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    pInstance, instance of face sdk
* @para[in]:    imgFst, first person
* @para[in]:    imgSec, second person
* @para[out]    nSimilarity, similarity of two person
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult Compare1v1(void* pInstance, const ImageData& imgFst, const ImageData& imgSec, float& nSimilarity);

/*
*
* @brief:       calculate similarity of two person with feature
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:    pInstance, instance of face sdk
* @para[in]:    imgFst, first person
* @para[in]:    imgSec, second person
* @para[out]    nSimilarity, similarity of two person
* @return:      FaceResult, result of invoking
*
*/
FACE_SDK_LIBRARY FaceResult CompareWithFeature(void* pInstance, const float* pFeatureFst, const float* pFeatureSec, float& nSimility);

/*
*
* @brief:       destroy an instance
* @author:      wite_chen
* @create:      20120-01-09
* @para[in]:   pInstance, instance of face sdk
* @return:      void
*
*/
FACE_SDK_LIBRARY void DestroyInstance(void* &pInstance);