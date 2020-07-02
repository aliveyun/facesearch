#define FACE_SDK_LIBRARY_EXPORT
#include "FaceSdk.h"
#include <memory>
#include <vector>
#include "SeetaWrap.h"
#include <io.h>


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


FaceResult InitFaceSdk(const FaceSdkPara& paraSdk)
{
    device = (seeta::ModelSetting::Device)paraSdk.nModel;
    nDeviceIndex = paraSdk.nDeviceIndex;
    strModelPath = paraSdk.strModulePath;
    VERIFY_RETURN( CheckModulePath(strModelPath), kFaceResultInvalidModelPath);
    if (strModelPath.back() != '\\')
        strModelPath.push_back('\\');

    return kFaceResultOk;
}

FaceResult CreateInstance(void* &pInstance)
{
    if (nullptr == pInstance) 
    {
        pInstance = static_cast<void*>(new SeetaWrap(strModelPath, device, nDeviceIndex));
    }
    return kFaceResultOk;
}

FaceResult GetFeatureSize(void* pInstance, int& nSize)
{
    VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
    pFaceObject->GetFeatureSize(nSize);

    return kFaceResultOk;
}

//FaceResult Detect(void* pInstance, const ImageData& dataImg, std::vector<FaceInfo>& vecFaces)
//{
//    VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
//    std::vector<SeetaFaceInfo> vecDetectFaces;
//    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
//    seeta::ImageData img = { dataImg.data, dataImg.width, dataImg.height, dataImg.channels};
//    pFaceObject->Detect(img, vecDetectFaces);
//    for (const auto& iter : vecDetectFaces)
//    {
//        FaceInfo infoFace;
//        infoFace.height = iter.pos.height;
//        infoFace.width = iter.pos.width;
//        infoFace.x = iter.pos.x;
//        infoFace.y = iter.pos.y;
//        vecFaces.push_back(infoFace);
//    }
//
//    return kFaceResultOk;
//}

FaceResult ExtractFeature(void* pInstance, const ImageData& dataImg, float* pFeature)
{
    VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
    seeta::ImageData img = { dataImg.data, dataImg.width, dataImg.height, dataImg.channels };
    if (!pFaceObject->ExtractFeature(img, pFeature))
        return kFaceResultExtractFailed;

    return kFaceResultOk;
}

//FaceResult Compare1v1(void* pInstance, const ImageData& imgFst, const ImageData& imgSec, float& nSimilarity)
//{
//    VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
//    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
//    seeta::ImageData img1 = { imgFst.data, imgFst.width, imgFst.height, imgFst.channels };
//    seeta::ImageData img2 = { imgSec.data, imgSec.width, imgSec.height, imgSec.channels };
//    return (FaceResult)pFaceObject->Compare1v1(img1, img2, nSimilarity);
//}

FaceResult CompareWithFeature(void* pInstance, const float* pFeatureFst, const float* pFeatureSec, float& nSimility)
{
    VERIFY_RETURN(!(pInstance == nullptr), kFaceResultInvalidInstance);
    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
    return (FaceResult)pFaceObject->CompareWithFeature(pFeatureFst, pFeatureSec, nSimility);
}

void DestroyInstance(void* &pInstance)
{
    SeetaWrap* pFaceObject = static_cast<SeetaWrap*>(pInstance);
    if (pFaceObject != nullptr)
    {
        delete pFaceObject;
        pFaceObject = nullptr;
    }
}