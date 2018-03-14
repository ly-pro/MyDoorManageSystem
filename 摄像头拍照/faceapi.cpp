#include "stdafx.h"

const char *cid = "FButrxH28fWTDJNwvE2bN5hP5R1h4Nek1rFMXRFPPrWK";
MPChar id;

MPChar ctom(const char * s)
{
	char *cAPPID = new char[strlen(s) + 1];
	strcpy_s(cAPPID, strlen(s) + 1, s);
	MPChar m = static_cast<MPChar>(cAPPID);
	return m;
}

bool printerr(const char * msg, MRESULT code)
{
	if (code != MOK) {
		printf("%s失败,错误代码%d", msg, code);
		return 0;
	}
	return 1;
}
inline AFR_FSDK_FACEINPUT getfaceinput(MRECT rec, AFD_FSDK_OrientCode orc) {
	AFR_FSDK_FACEINPUT fin;
	fin.rcFace = rec;
	fin.lOrient = orc;
	return fin;
}
LPAFD_FSDK_FACERES getfacesrecsbybmp24data(byte* data, int width, int height) {
	ASVLOFFSCREEN offInput1 = getimgbybmpdata(data, width, height);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(offInput1);
	return faces;
}
AFR_FSDK_FACEMODEL getfacemodbyfile(const char * picpath, int n) {//获取图片中的第n-1个脸
	AFR_FSDK_FACEMODEL mod;
	ASVLOFFSCREEN offInput1 = getimgbyfile(picpath);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(offInput1);
	if (!faces || faces->nFace == 0) {
		mod.lFeatureSize = 0;
		mod.pbFeature = nullptr;
		return mod;
	}
	MRECT rec = faces->rcFace[n];
	AFD_FSDK_OrientCode orc = faces->lfaceOrient[n];
	AFR_FSDK_FACEINPUT fin = getfaceinput(rec, orc);
	mod = FR::getfacemod(offInput1, fin);
	freeimg(offInput1);
	AFR_FSDK_FACEMODEL m1;
	m1.pbFeature = new MByte[mod.lFeatureSize];
	m1.lFeatureSize = mod.lFeatureSize;
	memcpy(m1.pbFeature, mod.pbFeature, mod.lFeatureSize);
	//dump(mod.pbFeature, mod.lFeatureSize, "2");
	return m1;
}
AFR_FSDK_FACEMODEL * getfacemodpbyfile(const char * picpath, int n) {//获取图片中的第n-1个脸
	AFR_FSDK_FACEMODEL mod;
	ASVLOFFSCREEN offInput1 = getimgbyfile(picpath);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(offInput1);
	if (!faces || faces->nFace == 0) {
		return nullptr;
	}
	MRECT rec = faces->rcFace[n];
	AFD_FSDK_OrientCode orc = faces->lfaceOrient[n];
	AFR_FSDK_FACEINPUT fin = getfaceinput(rec, orc);
	mod = FR::getfacemod(offInput1, fin);
	freeimg(offInput1);
	AFR_FSDK_FACEMODEL *m1 = new AFR_FSDK_FACEMODEL;
	m1->pbFeature = new MByte[mod.lFeatureSize];
	m1->lFeatureSize = mod.lFeatureSize;
	memcpy(m1->pbFeature, mod.pbFeature, mod.lFeatureSize);
	return m1;
}
AFR_FSDK_FACEMODEL getfacemodbybmpdata(byte * data, int width, int height, int n) {//获取图片中的第n-1个脸
	AFR_FSDK_FACEMODEL mod;
	ASVLOFFSCREEN offInput1 = getimgbybmpdata(data, width, height);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(offInput1);
	if (!faces) {
		mod.lFeatureSize = 0;
		mod.pbFeature = nullptr;
		return mod;
	}
	MRECT rec = faces->rcFace[n];
	AFD_FSDK_OrientCode orc = faces->lfaceOrient[n];
	AFR_FSDK_FACEINPUT fin = getfaceinput(rec, orc);
	mod = FR::getfacemod(offInput1, fin);
	AFR_FSDK_FACEMODEL m1;
	m1.pbFeature = new MByte[mod.lFeatureSize];
	m1.lFeatureSize = mod.lFeatureSize;
	memcpy(m1.pbFeature, mod.pbFeature, mod.lFeatureSize);
	//freeimg(offInput1);
	//dump(mod.pbFeature, mod.lFeatureSize, "2");
	return m1;
}
int getagebyfile(const char * picpath, int n) {
	ASAE_FSDK_AGERESULT ages;
	ASVLOFFSCREEN AgeImageInfo = getimgbyfile(picpath);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(AgeImageInfo);
	MRECT *rec = faces->rcFace;
	AFD_FSDK_OrientCode *orc = faces->lfaceOrient;
	ASAE_FSDK_AGEFACEINPUT AgeFaceInput;
	AgeFaceInput.lFaceNumber = faces->nFace;
	AgeFaceInput.pFaceRectArray = faces->rcFace;
	AgeFaceInput.pFaceOrientArray = faces->lfaceOrient;
	ages = FA::getage(AgeImageInfo, AgeFaceInput);
	freeimg(AgeImageInfo);
	return ages.pAgeResultArray[n];
}
int getagebybmpdata(byte * data, int width, int height, int n) {
	ASAE_FSDK_AGERESULT ages;
	ASVLOFFSCREEN AgeImageInfo = getimgbybmpdata(data, width, height);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(AgeImageInfo);
	if (!faces)return 0;
	MRECT *rec = faces->rcFace;
	AFD_FSDK_OrientCode *orc = faces->lfaceOrient;
	ASAE_FSDK_AGEFACEINPUT AgeFaceInput;
	AgeFaceInput.lFaceNumber = faces->nFace;
	AgeFaceInput.pFaceRectArray = faces->rcFace;
	AgeFaceInput.pFaceOrientArray = faces->lfaceOrient;
	ages = FA::getage(AgeImageInfo, AgeFaceInput);
	//freeimg(AgeImageInfo);
	return ages.pAgeResultArray[n];
}
int getgenderbyfile(const char * picpath, int n) {
	ASGE_FSDK_GENDERRESULT gs;
	ASVLOFFSCREEN GenderImageInfo = getimgbyfile(picpath);
	LPAFD_FSDK_FACERES faces = FD::getfacerecs(GenderImageInfo);
	MRECT *rec = faces->rcFace;
	AFD_FSDK_OrientCode *orc = faces->lfaceOrient;
	ASGE_FSDK_GENDERFACEINPUT GenderFaceInput;
	GenderFaceInput.lFaceNumber = faces->nFace;
	GenderFaceInput.pFaceRectArray = faces->rcFace;
	GenderFaceInput.pFaceOrientArray = faces->lfaceOrient;
	gs = FG::getgenders(GenderImageInfo, GenderFaceInput);
	//freeimg(GenderImageInfo);
	return gs.pGenderResultArray[n];
}
AFR_FSDK_FACEMODEL * getfacemodfromfile(const char * modfile) {//直接读取脸部模型文件
	FILE *fp = nullptr;
	if (errno_t e = fopen_s(&fp, modfile, "rb") != 0) {
		printf("读取模型文件文件失败:%d\n", e);
		return nullptr;
	}
	fseek(fp, 0, SEEK_END);
	unsigned long len = ftell(fp);  //这就是长度了.
	fseek(fp, 0, SEEK_SET);
	AFR_FSDK_FACEMODEL *m = new AFR_FSDK_FACEMODEL;
	m->lFeatureSize = len;
	m->pbFeature = new MByte[len];
	fread(m->pbFeature, sizeof(MByte), len, fp);
	return m;
}
int deletefacemodel(AFR_FSDK_FACEMODEL & m) {
	//if (!m)return 0;
	delete[] m.pbFeature;
	//delete m;
	return 1;
}
int deletefacemodel(AFR_FSDK_FACEMODEL * m) {
	if (!m)return 0;
	delete[] m->pbFeature;
	delete m;
	return 1;
}
bool initfaceengine() {
	id = ctom(cid);
	FR::init();
	FD::init();
	FT::init();
	FA::init();
	FG::init();
	return 1;
}
bool cleanupfaceengine() {
	delete id;
	FR::cleanup();
	FD::cleanup();
	FT::cleanup();
	FA::cleanup();
	FG::cleanup();
	return 1;
}
namespace FR {
	MRESULT nRet = MERR_UNKNOWN;
	MHandle hEngine = nullptr;
	MInt32 nScale = 16;
	MInt32 nMaxFace = 10;
	MByte *pWorkMem = nullptr;
	bool init() {/* 初始化引擎和变量 */
		pWorkMem = (MByte *)malloc(WORKBUF_SIZE);
		const char *ckey = "3Rj6v85BvMntMqkcA3HjuzhjxFxhVBenYpuffmu1dgx8";
		MPChar key = ctom(ckey);
		nRet = AFR_FSDK_InitialEngine(id, key, pWorkMem, WORKBUF_SIZE, &hEngine);
		printerr("初始化", nRet);

		delete key;
		return 1;
	}
	AFR_FSDK_FACEMODEL getfacemod(ASVLOFFSCREEN offInput1, AFR_FSDK_FACEINPUT faceInput) {
		AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };
		nRet = AFR_FSDK_ExtractFRFeature(hEngine, &offInput1, &faceInput, &LocalFaceModels);
		printerr("获取人脸模型", nRet);
		return LocalFaceModels;
	}
	MFloat compare(AFR_FSDK_FACEMODEL & faceModels1, AFR_FSDK_FACEMODEL & faceModels2) {
		MFloat  fSimilScore = 0.0f;
		nRet = AFR_FSDK_FacePairMatching(hEngine, &faceModels1, &faceModels2, &fSimilScore);
		printerr("识别", nRet);
		return fSimilScore;
	}
	bool cleanup() {
		nRet = AFR_FSDK_UninitialEngine(hEngine);
		printerr("释放", nRet);
		free(pWorkMem);
		return 1;
	}
}
namespace FD {
	MRESULT nRet = MERR_UNKNOWN;
	MHandle hEngine = nullptr;
	MInt32 nScale = 16;
	MInt32 nMaxFace = 10;
	MByte *pWorkMem = nullptr;
	bool init() {
		pWorkMem = (MByte *)malloc(WORKBUF_SIZE);
		const char *ckey = "3Rj6v85BvMntMqkcA3HjuzhFJev26e6zh7BmbSx9ae7s";
		MPChar key = ctom(ckey);
		nRet = AFD_FSDK_InitialFaceEngine(id, key, pWorkMem, WORKBUF_SIZE, &hEngine, AFD_FSDK_OPF_0_HIGHER_EXT, nScale, nMaxFace);
		printerr("初始化", nRet);

		delete key;
		return 1;
	}
	LPAFD_FSDK_FACERES getfacerecs(ASVLOFFSCREEN offInput) {
		LPAFD_FSDK_FACERES	FaceRes = nullptr;
		nRet = AFD_FSDK_StillImageFaceDetection(hEngine, &offInput, &FaceRes);
		printerr("人脸检测", nRet);
		return FaceRes;
	}

	bool cleanup() {
		nRet = AFD_FSDK_UninitialFaceEngine(hEngine);
		printerr("释放", nRet);
		free(pWorkMem);
		return 1;
	}
}
namespace FT {
	bool init() {
		MPChar key = ctom("3Rj6v85BvMntMqkcA3Hjuzh89FeuJgH2NeXFRBvDWbxM");
		return 1;
	}
	bool cleanup() {
		return 1;
	}
}
namespace FA {
	MHandle						AgeEngine = nullptr;
	ASVLOFFSCREEN				AgeImageInfo = { 0 };
	ASAE_FSDK_AGEFACEINPUT		AgeFaceInput;
	ASAE_FSDK_AGERESULT			AgeResult;
	MByte *						pWorkMem = nullptr;
	bool init() {
		MInt32 res = MOK;
		AgeFaceInput.lFaceNumber = 0;
		AgeFaceInput.pFaceRectArray = new MRECT[MAXIMUM_FACE_NUMBER];
		if (0 == AgeFaceInput.pFaceRectArray)
			return printerr("内存不足", MERR_NO_MEMORY);
		//return MERR_NO_MEMORY;
		AgeFaceInput.pFaceOrientArray = new MInt32[MAXIMUM_FACE_NUMBER];
		if (0 == AgeFaceInput.pFaceOrientArray)
			return printerr("内存不足", MERR_NO_MEMORY);
		//return MERR_NO_MEMORY;

		pWorkMem = new MByte[WORKBUF_SIZE];
		MPChar key = ctom("3Rj6v85BvMntMqkcA3HjuzhzH4V6RNYWkJj1qnzersC9");
		res = ASAE_FSDK_InitAgeEngine(id, key, pWorkMem, WORKBUF_SIZE, &AgeEngine);
		delete key;
		return printerr("年龄检测模块初始化", res);
	}
	ASAE_FSDK_AGERESULT getage(ASVLOFFSCREEN AgeImageInfo, ASAE_FSDK_AGEFACEINPUT AgeFaceInput) {
		MRESULT res;
		res = ASAE_FSDK_AgeEstimation_StaticImage(AgeEngine, &AgeImageInfo, &AgeFaceInput, &AgeResult);
		printerr("检测年龄", res);
		return AgeResult;
	}
	bool cleanup() {
		MRESULT r = ASAE_FSDK_UninitAgeEngine(AgeEngine);
		printerr("释放年龄检测模块", r);
		free(AgeFaceInput.pFaceRectArray);
		free(AgeFaceInput.pFaceOrientArray);
		free(pWorkMem);
		return 1;
	}
}
namespace FG {
	MHandle							GenderEngine = nullptr;
	ASVLOFFSCREEN					GenderImageInfo = { 0 };
	ASGE_FSDK_GENDERFACEINPUT		GenderFaceInput;
	ASGE_FSDK_GENDERRESULT			GenderResult;
	MByte *							pWorkMem = nullptr;
	MInt32 res = MOK;
	bool init() {
		GenderFaceInput.lFaceNumber = 0;
		GenderFaceInput.pFaceRectArray = new MRECT[MAXIMUM_FACE_NUMBER];
		if (0 == GenderFaceInput.pFaceRectArray)
			return printerr("内存不足", MERR_NO_MEMORY);
		//return MERR_NO_MEMORY;
		GenderFaceInput.pFaceOrientArray = new MInt32[MAXIMUM_FACE_NUMBER];
		if (0 == GenderFaceInput.pFaceOrientArray)
			return printerr("内存不足", MERR_NO_MEMORY);
		//return MERR_NO_MEMORY;

		pWorkMem = new MByte[WORKBUF_SIZE];
		MPChar key = ctom("3Rj6v85BvMntMqkcA3Hjuzi7STkGrbMceudUyav8wu8E");
		res = ASGE_FSDK_InitGenderEngine(id, key, pWorkMem, WORKBUF_SIZE, &GenderEngine);
		delete key;
		return printerr("性别检测模块初始化", res);
	}
	ASGE_FSDK_GENDERRESULT getgenders(ASVLOFFSCREEN GenderImageInfo, ASGE_FSDK_GENDERFACEINPUT GenderFaceInput) {
		res = ASGE_FSDK_GenderEstimation_StaticImage(GenderEngine, &GenderImageInfo, &GenderFaceInput, &GenderResult);
		return GenderResult;
		printerr("检测性别", res);
	}
	bool cleanup() {
		MRESULT r = ASGE_FSDK_UninitGenderEngine(GenderEngine);
		printerr("释放年龄检测模块", r);
		free(GenderFaceInput.pFaceRectArray);
		free(GenderFaceInput.pFaceOrientArray);
		free(pWorkMem);
		return 1;
	}
}
