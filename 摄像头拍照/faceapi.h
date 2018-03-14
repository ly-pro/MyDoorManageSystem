#pragma once

MPChar ctom(const char* s);
bool printerr(const char *msg, MRESULT code);
namespace FR {
	bool init();/* 初始化引擎和变量 */
	AFR_FSDK_FACEMODEL getfacemod(ASVLOFFSCREEN offInput1, AFR_FSDK_FACEINPUT faceInput);
	MFloat compare(AFR_FSDK_FACEMODEL &faceModels1, AFR_FSDK_FACEMODEL &faceModels2);
	bool cleanup();
}
namespace FD {
	bool init();
	LPAFD_FSDK_FACERES getfacerecs(ASVLOFFSCREEN offInput);
	bool cleanup();
}
namespace FT {
	bool init();
	bool cleanup();
}
namespace FA {
	bool init();
	ASAE_FSDK_AGERESULT getage(ASVLOFFSCREEN AgeImageInfo, ASAE_FSDK_AGEFACEINPUT AgeFaceInput);
	bool cleanup();
}
namespace FG {
	bool init();
	ASGE_FSDK_GENDERRESULT getgenders(ASVLOFFSCREEN GenderImageInfo, ASGE_FSDK_GENDERFACEINPUT GenderFaceInput);
	bool cleanup();
}
inline AFR_FSDK_FACEINPUT getfaceinput(MRECT rec, AFD_FSDK_OrientCode orc);
AFR_FSDK_FACEMODEL getfacemodbyfile(const char* picpath, int n);
AFR_FSDK_FACEMODEL* getfacemodpbyfile(const char* picpath, int n);
AFR_FSDK_FACEMODEL getfacemodbybmpdata(byte *data, int width, int height, int n);

int getagebyfile(const char* picpath, int n);
int getagebybmpdata(byte *data, int width, int height, int n);
int getgenderbyfile(const char* picpath, int n);
AFR_FSDK_FACEMODEL* getfacemodfromfile(const char* modfile);
LPAFD_FSDK_FACERES getfacesrecsbybmp24data(byte* data, int width, int height);
int deletefacemodel(AFR_FSDK_FACEMODEL &m);
int deletefacemodel(AFR_FSDK_FACEMODEL *m);
bool initfaceengine();
bool cleanupfaceengine();