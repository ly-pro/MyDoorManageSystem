#pragma once

// TODO: 在此处引用程序需要的其他标头
#include<Windows.h>
#include "header\amcomdef.h"
#include "header\ammem.h"
#include "header\arcsoft_fsdk_age_estimation.h"
#include "header\arcsoft_fsdk_face_detection.h"
#include "header\arcsoft_fsdk_face_recognition.h"
#include "header\arcsoft_fsdk_face_tracking.h"
#include "header\arcsoft_fsdk_gender_estimation.h"
#include "header\asvloffscreen.h"
#include "header\merror.h"
#include "MyForm.h"
#include "MainForm.h"
#include "LoginForm.h"
#include "CPersonInfo.h"
#include "mytool.h"
#include "ConfigManager.h"
#include "FormsManager.h"
#include "pictool.h"
#include "faceapi.h"
#include "CDeviceInfo.h"
#include "MyClient.h"

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"Comdlg32.lib")
#pragma comment(lib,"lib/libarcsoft_fsdk_age_estimation.lib")
#pragma comment(lib,"lib/libarcsoft_fsdk_face_detection.lib")
#pragma comment(lib,"lib/libarcsoft_fsdk_face_recognition.lib")
#pragma comment(lib,"lib/libarcsoft_fsdk_face_tracking.lib")
#pragma comment(lib,"lib/libarcsoft_fsdk_gender_estimation.lib")

#define ADMIN 0
#define HUZHU 1
#define CHANGZHU 2
#define FANGKE 3
#define MAXIMUM_FACE_NUMBER 10
#define WORKBUF_SIZE (40*1024*1024)
