/* ////////////////////////////////////////////////////////////

File Name: fsmacosxwrappercpp.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "fssimplewindow.h"

extern "C" void FsOpenWindowC(int x0,int y0,int wid,int hei,int useDoubleBuffer,int useMultiSampleBuffer,int fullScreen,const char windowName[]);
extern "C" void FsGetWindowSizeC(int *wid,int *hei);
extern "C" void FsGetWindowPositionC(int *wid,int *hei);
extern "C" void FsMaximizeWindowC(void);
extern "C" void FsPollDeviceC(void);
extern "C" void FsPushOnPaintEventC(void);
extern "C" void FsSleepC(int ms);
extern "C" int FsPassedTimeC(void);
extern "C" long long int FsSubSecondTimerC(void);
extern "C" void FsMouseC(int *lb,int *mb,int *rb,int *mx,int *my);
extern "C" int FsGetMouseEventC(int *lb,int *mb,int *rb,int *mx,int *my);
extern "C" void FsSwapBufferC(void);
extern "C" int FsInkeyC(void);
extern "C" int FsInkeyCharC(void);
extern "C" int FsKeyStateC(int fsKeyCode);
extern "C" void FsChangeToProgramDirC(void);
extern "C" int FsCheckExposureC(void);
extern "C" void FsPushKeyC(int fsKeyCode);
extern "C" void FsEnableIMEC(void);
extern "C" void FsDisableIMEC(void);


static int doubleBuffer=1;
static int windowOpen=0;

void FsOpenWindow(const FsOpenWindowOption &opt)
{
	if(0!=windowOpen)
	{
		printf("Error! Window is already open.\n");
		exit(1);
	}

	const int useDoubleBuffer=(int)opt.useDoubleBuffer;
	const int useMultiSampleBuffer=(int)opt.useMultiSampleBuffer;
	const int fullScreen=(FsOpenWindowOption::FULLSCREEN==opt.sizeOpt ? 1 : 0);

	if(NULL==opt.windowTitle)
	{
		FsOpenWindowC(opt.x0,opt.y0,opt.wid,opt.hei,useDoubleBuffer,useMultiSampleBuffer,fullScreen,"Main Window");
	}
	else
	{
		FsOpenWindowC(opt.x0,opt.y0,opt.wid,opt.hei,useDoubleBuffer,useMultiSampleBuffer,fullScreen,opt.windowTitle);
	}

	FsPassedTimeC();  // Resetting the timer.
	doubleBuffer=useDoubleBuffer;
	windowOpen=1;

	if(NULL!=fsAfterWindowCreationCallBack)
	{
		(*fsAfterWindowCreationCallBack)(fsAfterWindowCreationCallBackParam);
	}
}

int FsCheckWindowOpen(void)
{
	return windowOpen;
}

void FsPushOnPaintEvent(void)
{
	FsPushOnPaintEventC();
}

void FsCloseWindow(void)
{
}

void FsGetWindowSize(int &wid,int &hei)
{
	FsGetWindowSizeC(&wid,&hei);
}

void FsGetWindowPosition(int &x0,int &y0)
{
	FsGetWindowPositionC(&x0,&y0);
}

void FsSetWindowTitle(const char windowTitle[])
{
	printf("Sorry. %s not supported on this platform yet\n",__FUNCTION__);
}

void FsMaximizeWindow(void)
{
	FsMaximizeWindowC();
}
void FsUnmaximizeWindow(void)
{
}
void FsMakeFullScreen(void)
{
}

void FsPollDevice(void)
{
	FsPollDeviceC();
}

void FsSleep(int ms)
{
	FsSleepC(ms);
}

long long int FsPassedTime(void)
{
	static long long int lastTick;
	long long int tick;

	static int first=1;
	if(1==first)
	{
		lastTick=FsSubSecondTimer();
		first=0;
	}

	tick=FsSubSecondTimer();
	long long passed=tick-lastTick;
	lastTick=tick;

	return passed;
}

long long int FsSubSecondTimer(void)
{
	return FsSubSecondTimerC();
}

void FsGetMouseState(int &lb,int &mb,int &rb,int &mx,int &my)
{
	FsMouseC(&lb,&mb,&rb,&mx,&my);
}

int FsGetMouseEvent(int &lb,int &mb,int &rb,int &mx,int &my)
{
	return FsGetMouseEventC(&lb,&mb,&rb,&mx,&my);
}

void FsSwapBuffers(void)
{
	if(0==doubleBuffer)
	{
		printf("Error! FsSwapBufferes called in a single-buffered application.\n");
		exit(1);
	}

	FsSwapBufferC();
}

int FsInkey(void)
{
	return FsInkeyC();
}

int FsInkeyChar(void)
{
	return FsInkeyCharC();
}

void FsPushKey(int fskeyCode)
{
	FsPushKeyC(fskeyCode);
}

int FsGetKeyState(int fsKeyCode)
{
	return FsKeyStateC(fsKeyCode);
}

int FsCheckWindowExposure(void)
{
	return FsCheckExposureC();
}

void FsChangeToProgramDir(void)
{
	FsChangeToProgramDirC();
}

extern "C" void FsOnPaintCallBackCpp(void)
{
	if(NULL!=fsOnPaintCallback)
	{
		(*fsOnPaintCallback)(fsOnPaintCallbackParam);
	}
}


int FsGetNumCurrentTouch(void)
{
	return 0;
}

const FsVec2i *FsGetCurrentTouch(void)
{
	return nullptr;
}

////////////////////////////////////////////////////////////

int FsEnableIME(void)
{
	FsEnableIMEC();
	return 1;
}

void FsDisableIME(void)
{
	FsDisableIMEC();
}

////////////////////////////////////////////////////////////

int FsIsNativeTextInputAvailable(void)
{
	return 0;
}

int FsOpenNativeTextInput(int x1,int y1,int wid,int hei)
{
	return 0;
}

void FsCloseNativeTextInput(void)
{
}

void FsSetNativeTextInputText(const wchar_t [])
{
}

int FsGetNativeTextInputTextLength(void)
{
	return 0;
}

void FsGetNativeTextInputText(wchar_t str[],int bufLen)
{
	if(0<bufLen)
	{
		str[0]=0;
	}
}

int FsGetNativeTextInputEvent(void)
{
	return FSNATIVETEXTEVENT_NONE;
}
/* ////////////////////////////////////////////////////////////

File Name: fssimplewindowcommon.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */







FsOpenWindowOption::FsOpenWindowOption()
{
	x0=16;
	y0=16;
	wid=800;
	hei=600;

	windowTitle="Main Window";

	useDoubleBuffer=false;
	useMultiSampleBuffer=false;

	sizeOpt=NORMAL_WINDOW;
}

void FsOpenWindow(int x0,int y0,int wid,int hei,int useDoubleBuffer)
{
	FsOpenWindow(x0,y0,wid,hei,useDoubleBuffer,NULL);
}

void FsOpenWindow(int x0,int y0,int wid,int hei,int useDoubleBuffer,const char windowName[])
{
	FsOpenWindowOption opt;
	opt.x0=x0;
	opt.y0=y0;
	opt.wid=wid;
	opt.hei=hei;
	opt.windowTitle=windowName;
	opt.useDoubleBuffer=(bool)useDoubleBuffer;
	FsOpenWindow(opt);
}

void FsClearEventQueue(void)
{
	auto intervalFunc=fsIntervalCallBack;
	auto intervalParam=fsIntervalCallBackParameter;
	FsRegisterIntervalCallBack(NULL,NULL);

	for(;;)
	{
		int checkAgain=0;

		FsPollDevice();

		int lb,mb,rb,mx,my;
		while(FSMOUSEEVENT_NONE!=FsGetMouseEvent(lb,mb,rb,mx,my) ||
		      FSKEY_NULL!=FsInkey() ||
		      0!=FsInkeyChar() ||
		      0!=FsCheckWindowExposure())
		{
			checkAgain=1;
		}

		if(0!=lb || 0!=rb || 0!=mb)
		{
			checkAgain=1;
		}

		if(0!=FsCheckKeyHeldDown())
		{
			checkAgain=1;
		}

		if(0==checkAgain)
		{
			break;
		}

		FsSleep(50);
	}

	FsRegisterIntervalCallBack(intervalFunc,intervalParam);
}

int FsCheckKeyHeldDown(void)
{
	int keyCode;
	for(keyCode=FSKEY_NULL+1; keyCode<FSKEY_NUM_KEYCODE; keyCode++)
	{
		if(0!=FsGetKeyState(keyCode))
		{
			return 1;
		}
	}
	return 0;
}


static const char *const keyCodeToStr[]=
{
	"NULL",
	"SPACE",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"ESC",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"PRINTSCRN",
	"CAPSLOCK",
	"SCROLLLOCK",
	"PAUSEBREAK",
	"BS",
	"TAB",
	"ENTER",
	"SHIFT",
	"CTRL",
	"ALT",
	"INS",
	"DEL",
	"HOME",
	"END",
	"PAGEUP",
	"PAGEDOWN",
	"UP",
	"DOWN",
	"LEFT",
	"RIGHT",
	"NUMLOCK",
	"TILDA",
	"MINUS",
	"PLUS",
	"LBRACKET",
	"RBRACKET",
	"BACKSLASH",
	"SEMICOLON",
	"SINGLEQUOTE",
	"COMMA",
	"DOT",
	"SLASH",
	"TEN0",
	"TEN1",
	"TEN2",
	"TEN3",
	"TEN4",
	"TEN5",
	"TEN6",
	"TEN7",
	"TEN8",
	"TEN9",
	"TENDOT",
	"TENSLASH",
	"TENSTAR",
	"TENMINUS",
	"TENPLUS",
	"TENENTER",
	"WHEELUP",
	"WHEELDOWN"
};

const char *FsKeyCodeToString(int keyCode)
{
	if(0<=keyCode && keyCode<FSKEY_NUM_KEYCODE)
	{
		return keyCodeToStr[keyCode];
	}
	return "(Undefined keycode)";
}

int FsStringToKeyCode(const char str[])
{
	if(nullptr==str)
	{
		return FSKEY_NULL;
	}

	char upper[256];
	for(int i=0; i<255 && 0!=str[i]; ++i)
	{
		upper[i  ]=str[i];
		upper[i+1]=0;
		if('a'<=upper[i] && upper[i]<='z')
		{
			upper[i]=upper[i]+'A'-'a';
		}
	}
	for(int i=0; i<FSKEY_NUM_KEYCODE; ++i)
	{
		if(0==strcmp(upper,keyCodeToStr[i]))
		{
			return i;
		}
	}
	return FSKEY_NULL;
}


void *fsCloseWindowCallBackParam=NULL;
bool (*fsCloseWindowCallBack)(void *param)=NULL;

void *fsOpenGLContextCreationCallBackParam=NULL;
bool (*fsOpenGLContextCreationCallBack)(void *param)=NULL;

void *fsAfterWindowCreationCallBackParam=NULL;
void (*fsAfterWindowCreationCallBack)(void *param)=NULL;

void *fsSwapBuffersHookParam=NULL;
bool (*fsSwapBuffersHook)(void *param)=NULL;

void *fsOnPaintCallbackParam=NULL;
void (*fsOnPaintCallback)(void *param)=NULL;

void *fsOnResizeCallBackParam=NULL;
void (*fsOnResizeCallBack)(void *param,int wid,int hei)=NULL;

void (*fsIntervalCallBack)(void *)=NULL;
void *fsIntervalCallBackParameter=NULL;

void (*fsPollDeviceHook)(void *)=NULL;
void *fsPollDeviceHookParam=NULL;

void FsRegisterCloseWindowCallBack(bool (*callback)(void *),void *param)
{
	fsCloseWindowCallBack=callback;
	fsCloseWindowCallBackParam=param;
}

void FsRegisterBeforeOpenGLContextCreationCallBack(bool (*callback)(void *),void *param)
{
	fsOpenGLContextCreationCallBack=callback;
	fsOpenGLContextCreationCallBackParam=param;
}

void FsRegisterAfterWindowCreationCallBack(void (*callback)(void *),void *param)
{
	fsAfterWindowCreationCallBackParam=param;
	fsAfterWindowCreationCallBack=callback;
}

void FsRegisterSwapBuffersCallBack(bool (*callback)(void *),void *param)
{
	fsSwapBuffersHookParam=param;
	fsSwapBuffersHook=callback;
}

void FsRegisterOnPaintCallBack(void (*callback)(void *),void *param)
{
	fsOnPaintCallbackParam=param;
	fsOnPaintCallback=callback;
}

void FsRegisterWindowResizeCallBack(void (*callback)(void *,int wid,int hei),void *param)
{
	fsOnResizeCallBackParam=param;
	fsOnResizeCallBack=callback;
}

void FsRegisterIntervalCallBack(void (*callback)(void *),void *param)
{
	fsIntervalCallBack=callback;
	fsIntervalCallBackParameter=param;
}

void FsRegisterPollDeviceCallBack(void (*callback)(void *),void *param)
{
	fsPollDeviceHook=callback;
	fsPollDeviceHookParam=param;
}

