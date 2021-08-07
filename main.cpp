//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// A simple test case that will draw a triangle in ES.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/main.cpp#2 $ 
// 
// Last check-in:  $DateTime: 2008/02/26 16:36:56 $ 
// Last edited by: $Author: juanli $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

#pragma comment( lib, "libEGL.lib" )
#pragma comment( lib, "libGLESv2.lib" )

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include "ArgDefines.h"
#include "Scene.h"
#include "Misc.h"
#include "Uniform.h"
#include <tchar.h>


// 一些常量定义

#define MAINWINDOW_WIDTH    400      // 主窗口宽度

#define MAINWINDOW_HEIGHT   200      // 主窗口高度

#define TEXTBOX_WIDTH       100      // 文本框宽度

#define TEXTBOX_HEIGHT      20       // 文本框高度

#define TEXTBOX_MAXLENGTH   1024 // 文本框中文本的最大长度

TCHAR _TextBoxClass[] = _T("MySimpleTextBox"); // 文本框的类名

TCHAR _String[TEXTBOX_MAXLENGTH + 1] = _T("");     // 文本

int    _StringPosition = ::_tcslen(_String);        // 光标插入点所在的位置


#define IDM_OPT1     301     
#define IDM_OPT2     302  


HINSTANCE _HInstance;                              // 应用程序句柄

TCHAR _Title[] = _T("简单文本框");                 // 定义窗口的标题


TCHAR _WindowClass[] = _T("MySimpleTextBoxApp");// 主窗口类名

ATOM _RegisterClass();                             // 注册主窗口类

HWND _CreateWindow(int nCmdShow);                  // 创建主窗口

LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);   // 主窗口消息处理函数

ATOM _RegisterTextBoxClass();                      // 注册文本框的类

HWND _CreateTextBoxWindow(HWND hParentWnd);        // 创建文本框

LRESULT CALLBACK _TextBoxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 文本框窗口消息处理函数

void _DrawText(HDC hDC);                           // 绘制文本

void _SetCaretPos(HWND hWnd);                      // 设置光标位置

void _UpdateWindow(HWND hWnd);                     // 更新窗口


// Globals
bool  g_keys[256];               // Array Used For The Keyboard Routine
bool  g_active = TRUE;             // Window Active Flag Set To TRUE By Default

Scene g_scene;


LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


void CreateTabMenu();//创建菜单     

//=================================================================================================================================
///
/// Funtion to redirect stdin/stdout to a console window.
///
/// \return void
//=================================================================================================================================
MatrixTransformData *matrixTDPoint = new MatrixTransformData(1.0, 0.0);
void RedirectIOToConsole()
{
	BOOL bResult;

	// Could try attaching to the current console but there might not
	// be one and the output format is somewhat ugly.
	//AttachConsole(ATTACH_PARENT_PROCESS);

	// allocate a console for this app
	bResult = AllocConsole();

	if (bResult)
	{
		int hConHandle;
		HANDLE StdHandle;
		FILE *fp;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;

		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		// redirect unbuffered STDOUT to the console
		StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle((intptr_t)StdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);

		// redirect unbuffered STDIN to the console
		StdHandle = GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle((intptr_t)StdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);
	}
}

//=================================================================================================================================
///
/// Funtion to resize the ES window.
///
/// \param nWidth the width of the new window.
/// \param nHeight the height of the new window.
///
/// \return void
//=================================================================================================================================
void ResizeScene(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
}

//=================================================================================================================================
///
/// Funtion draw the simple ES scene.
///
/// \return void
//=================================================================================================================================
int DrawScene()
{
	g_scene.drawFrame();

	return TRUE;
}

//=================================================================================================================================
///
/// Funtion to create the EGL window.
///
/// \param hWnd the parent window HWND.
/// \param hInstance the class instance.
///
/// \return 1 = pass; 0 = fail.
//=================================================================================================================================
int CreateEGLContext(HWND hWnd, HINSTANCE hInstance)
{
	EGLint attribList[MAX_EGL_ATTRIBUTES];
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;

	/// Build up the attribute list
	BuildAttribList(attribList);

	// Get Display
	g_egl.dsp = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (g_egl.dsp == EGL_NO_DISPLAY)
	{
		assert(0 && "eglGetDisplay failed");
		return FALSE;
	}

	// Initialize EGL
	if (!eglInitialize(g_egl.dsp, &majorVersion, &minorVersion))
	{
		assert(0 && "eglInitialize failed");
		return FALSE;
	}

	// Get configs
	if (!eglGetConfigs(g_egl.dsp, NULL, 0, &numConfigs))
	{
		assert(0 && "eglGetConfigs failed");
		return FALSE;
	}

	// Choose config
	if (!eglChooseConfig(g_egl.dsp, attribList, &g_egl.cfg, 1, &numConfigs))
	{
		assert(0 && "eglChooseConfig failed");
		return FALSE;
	}

	// Create a surface
	g_egl.surf = eglCreateWindowSurface(g_egl.dsp, g_egl.cfg, NativeWindowType(hWnd), NULL);
	if (g_egl.surf == EGL_NO_SURFACE)
	{
		assert(0 && "eglCreateWindowSurface failed");
		return FALSE;
	}

	// Create a GL context
	EGLint ctxAttribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	g_egl.cxt = eglCreateContext(g_egl.dsp, g_egl.cfg, EGL_NO_CONTEXT, ctxAttribList);
	if (g_egl.cxt == EGL_NO_CONTEXT)
	{
		assert(0 && "eglCreateContext failed");
		return FALSE;
	}

	// Make the context current
	if (!eglMakeCurrent(g_egl.dsp, g_egl.surf, g_egl.surf, g_egl.cxt))
	{
		assert(0 && "eglMakeCurrent failed");
		return FALSE;
	}
	return TRUE;
}

//=================================================================================================================================
///
/// Funtion to create Window.
///
/// \param width the width of the window.
/// \param height the height of the window.
///
/// \return 0=fail; 1=pass
//=================================================================================================================================
HMENU hRoot;
int CreateWind(int width, int height)
{
	WNDCLASS             wc;                  // Windows Class Structure
	HWND hWnd;
	HINSTANCE hInstance;

	hInstance = GetModuleHandle(NULL);             // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = WNDPROC(WndProc);                  // WndProc Handles Messages
	wc.cbClsExtra = 0;                                   // No Extra Window Data
	wc.cbWndExtra = 0;                                   // No Extra Window Data
	wc.hInstance = hInstance;                           // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);       // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // Load The Arrow Pointer
	wc.hbrBackground = NULL;                                // No Background Required For GL
	wc.lpszMenuName = NULL;                                // We Don't Want A Menu
	wc.lpszClassName = "OpenGL";                            // Set The Class Name

	if (!RegisterClass(&wc))                            // Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hWnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,       // Extended Style For The Window
		"OpenGL",                                 // Class Name
		"Triangle ES App",                        // Window Title
		WS_OVERLAPPEDWINDOW |                     // Defined Window Style
		WS_CLIPSIBLINGS |                         // Required Window Style
		WS_CLIPCHILDREN,                          // Required Window Style
		0, 0,                                     // Window Position
		width,                                    // Window Width
		height,                                   // Window Height
		NULL,                                     // No Parent Window
		hRoot,                                     // No Menu
		hInstance,                                // Instance
		NULL)))                                // Dont Pass Anything To WM_CREATE
	{
		return 0;
	}

	/*Uniform *uniform = (Uniform*)malloc(sizeof(Uniform));
	uniform->m_name = "abc";
	SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)(LONG_PTR)uniform);*/

	if (CreateEGLContext(hWnd, hInstance) == false)
	{
		MessageBox(NULL, "Failed to create a context.", "ERROR", MB_OK | MB_ICONSTOP);
		exit(0);
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);  // Slightly Higher Priority
	SetFocus(hWnd);             // Sets Keyboard Focus To The Window

	ResizeScene(width, height);

	return TRUE;
}
void  operate(WPARAM wParam)
{
	
	if (wParam == 'a')
	{
		g_scene.matrixTDPoint->angleChange += 5;
		/*Uniform uniform = g_scene.m_uniforms;
		std::vector<UniformData*> uniformDatas = uniform.getUniformDataList();
		for (int i = 0; i < uniformDatas.size(); i++)
		{
			UniformData* uniformDataPoint = uniformDatas.at(i);
			char* name = uniformDataPoint->m_name;
			std::cout << name << std::endl;
			printf("%s", name);
		}*/
	}
	else if (wParam == 'b')
	{
		g_scene.matrixTDPoint->scaleValue += 0.3;
	}
	else if (wParam == 'c')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosX += 0.01;
	}
	else if (wParam == 'd')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosX -= 0.01;
	}
	else if (wParam == 'e')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosY += 0.01;
	}
	else if (wParam == 'f')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosY -= 0.01;
	}
	else if (wParam == 'g')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosZ += 0.01;
	}
	else if (wParam == 'h')
	{
		((MatrixTransformData*)matrixTDPoint)->lightPosZ -= 0.01;
	}
	else if (wParam == 'i')
	{
		g_scene.matrixTDPoint->angleChange -= 5;
	}
}

//=================================================================================================================================
///
/// Callback function for this simple ES app.
///
/// \param hWnd handle For this window.
/// \param uMsg message for this window.
/// \param wParam additional message info.
/// \param lParam additional message info.
///
/// \return void
//=================================================================================================================================
LRESULT CALLBACK WndProc(HWND      hWnd,
	UINT      uMsg,
	WPARAM    wParam,
	LPARAM    lParam)
{
	static HWND hTextBoxWnd;
	switch (uMsg)      // Check For Windows Messages
	{
	case WM_CREATE: {

						//_RegisterTextBoxClass();    // 注册文本框的类

						//hTextBoxWnd = _CreateTextBoxWindow(hWnd); // 创建文本框

	} break;
	case WM_ACTIVATE:
	{
						::SetFocus(hTextBoxWnd);
						if (!HIWORD(wParam))     // Check Minimization State
						{
							g_active = TRUE;
						}
						else
						{
							g_active = FALSE;
						}
						return 0;
	}

	case WM_SYSCOMMAND:
	{
						  if ((wParam == SC_SCREENSAVE) ||
							  (wParam == SC_MONITORPOWER))
						  {
							  return 0;
						  }
						  break;
	}

	case WM_CLOSE:
	{
					 PostQuitMessage(0);
					 return 0;
	}

	case WM_KEYDOWN:
	{
					   g_keys[wParam] = TRUE;
					   return 0;
	}

	case WM_KEYUP:
	{
					 g_keys[wParam] = FALSE;
					 return 0;
	}

	case WM_SIZE:
	{
					ResizeScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
					return 0;
	}
	case WM_CHAR:
	{
					operate(wParam);

	}

	case WM_COMMAND:
	{
					   // 取出资源Id值     
					   // 并判断用户选择了哪个菜单项     
					   switch (LOWORD(wParam))
					   {
					   case 301:
						   MessageBox(hWnd, "灰机来了。", "提示", MB_OK);
						   break;
					   case 302:
						   MessageBox(hWnd, "让炮弹飞。", "提示", MB_OK);
						   break;
					   case 40001:
						   MessageBox(hWnd, "山炮欲来风满楼。", "提示", MB_OK);
						   break;
					   default:
						   break;
					   }
	}

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=================================================================================================================================
///
/// WinMain function for this simple ES app.
///
/// \param hInstance instance.
/// \param hPrevInstance previous instance.
/// \param lpCmdLine command line parameters.
/// \param nCmdShow window show state.
///
/// \return void
//=================================================================================================================================




#define BM 19778		// 位图的标志

#define PATH "d:\\test.bmp"  //打开的文件路径 


//判断是否是位图,在0-1字节 
int IsBitMap(FILE *fp)
{
	unsigned short s;
	fread(&s, 1, 2, fp);
	if (s == BM)
		return 1;
	else
		return 0;
}

//获得图片的宽度,在18-21字节 
long getWidth(FILE *fp)
{
	long width;
	fseek(fp, 18, SEEK_SET);
	fread(&width, 1, 4, fp);
	return width;
}

//获得图片的高度 ，在22-25字节 
long getHeight(FILE *fp)
{
	long height;
	fseek(fp, 22, SEEK_SET);
	fread(&height, 1, 4, fp);
	return height;
}

//获得每个像素的位数,在28-29字节 
unsigned short getBit(FILE *fp)
{
	unsigned short bit;
	fseek(fp, 28, SEEK_SET);
	fread(&bit, 1, 2, fp);
	return bit;
}

//获得数据的起始位置
unsigned int getOffSet(FILE *fp)
{
	unsigned int OffSet;
	fseek(fp, 10L, SEEK_SET);
	fread(&OffSet, 1, 4, fp);
	return OffSet;
}

//获得图像的数据
void getData(FILE* fp, unsigned char *r, unsigned char *g, unsigned char *b)
{
	FILE* fpr;
	FILE* fpg;
	FILE* fpb;

	int i, j = 0;
	int stride;
	unsigned char* pix = NULL;
	long height, width;
	height = getHeight(fp);
	width = getWidth(fp);

	fseek(fp, getOffSet(fp), SEEK_SET);	//找到位图的数据区 

	stride = (24 * width + 31) / 8;	//对齐,计算一个width有多少个8位 
	stride = stride / 4 * 4;		//取四的倍数 r,g,b,alph 

	//写入数组 
	pix = (unsigned char *)malloc(stride);
	for (j = 0; j<height; j++)
	{
		fread(pix, 1, stride, fp);
		for (i = 0; i<width; i++)
		{
			*(r + (height - 1 - j) + i) = pix[i * 3 + 2];
			*(g + (height - 1 - j) + i) = pix[i * 3 + 1];
			*(b + (height - 1 - j) + i) = pix[i * 3];
		}
	}

	//写入文件 
	fpr = fopen("d:\\bmpr.txt", "w+");
	fpg = fopen("d:\\bmpg.txt", "w+");
	fpb = fopen("d:\\bmpb.txt", "w+");

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width - 1; j++)
		{
			fprintf(fpr, "%4d", *(r + i + j));
			fprintf(fpg, "%4d", *(g + i + j));
			fprintf(fpb, "%4d", *(b + i + j));
		}
		fprintf(fpr, "%4d", *(r + i + j));
		fprintf(fpg, "%4d", *(g + i + j));
		fprintf(fpb, "%4d", *(b + i + j));
	}

	fclose(fpr);
	fclose(fpg);
	fclose(fpb);

}


int mainddd()
{
	long width, height;
	FILE *fp = fopen(PATH, "r");
	unsigned char *r, *g, *b;
	int i, j;
	r = (unsigned char *)malloc(4000);
	b = (unsigned char *)malloc(4000);
	g = (unsigned char *)malloc(4000);

	if (IsBitMap(fp))
		printf("该文件是位图!\n");
	else
	{
		printf("该文件不是位图!\n");
		fclose(fp);
		return 0;
	}

	printf("width=%ld\nheight=%ld\n", getWidth(fp), getHeight(fp));

	printf("该图像是%d位图\n", getBit(fp));

	printf("OffSet=%d\n", getOffSet(fp));

	getData(fp, r, g, b);

	return 1;
}







int WINAPI WinMain(HINSTANCE  hInstance,
	HINSTANCE  hPrevInstance,
	LPSTR      lpCmdLine,
	int        nCmdShow)
{



	long width, height;
	FILE *fp = fopen(PATH, "r");
	unsigned char *r, *g, *b;
	int i, j;
	r = (unsigned char *)malloc(4000);
	b = (unsigned char *)malloc(4000);
	g = (unsigned char *)malloc(4000);

	if (IsBitMap(fp))
		printf("该文件是位图!\n");
	else
	{
		printf("该文件不是位图!\n");
		fclose(fp);
		return 0;
	}

	printf("width=%ld\nheight=%ld\n", getWidth(fp), getHeight(fp));

	printf("该图像是%d位图\n", getBit(fp));

	printf("OffSet=%d\n", getOffSet(fp));

	getData(fp, r, g, b);

	return 1;



	MSG  msg;
	BOOL done = FALSE;

	// redirect stdin/stdout to a console window
	RedirectIOToConsole();

	_HInstance = hInstance;


	CreateTabMenu();
	MainFuncInit();
	//width right
	//height bottom
	matrixTDPoint->windowWidth = 940;
	matrixTDPoint->windowHeight = 900;
	matrixTDPoint->lightPosX = 0.0;
	matrixTDPoint->lightPosY = 0.0;
	matrixTDPoint->lightPosZ = 0.2;
	if (!CreateWind(matrixTDPoint->windowWidth, matrixTDPoint->windowHeight))
	{
		return 0;
	}
	//glClearColor(0.0, 0.5, 0.5, 1.0);
	g_scene.loadData("../../data/uniforms.txt");
	g_scene.matrixTDPoint = matrixTDPoint;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  // Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if ((g_active && !DrawScene()) || g_keys[VK_ESCAPE])
			{
				done = TRUE;  // ESC or DrawGLScene Signalled A Quit
			}
			else
			{
				eglSwapBuffers(g_egl.dsp, g_egl.surf);
			}
		}
	}

	eglDestroyContext(g_egl.dsp, g_egl.cxt);
	eglDestroySurface(g_egl.dsp, g_egl.surf);
	eglTerminate(g_egl.dsp);
	g_scene.freeResources();
	return 0;
}


void CreateTabMenu()
{
	hRoot = CreateMenu();
	if (!hRoot)
		return;
	HMENU pop1 = CreatePopupMenu();
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop1,
		"操作");
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop1,
		"操作2");
	// 一种方法是使用AppendMenu函数     
	AppendMenu(pop1,
		MF_STRING,
		IDM_OPT1,
		"飞机");

	AppendMenu(pop1,
		MF_STRING,
		IDM_OPT1,
		"迫击炮");

	// 另一种方法是使用InsertMenuItem函数     
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = "机关枪";
	mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	mif.fState = MFS_ENABLED;
	mif.fType = MIIM_STRING;
	mif.wID = IDM_OPT2;

	InsertMenuItem(pop1, IDM_OPT2, FALSE, &mif);

}

// 更新窗口
void _UpdateWindow(HWND hWnd)
{
	RECT rect;
	::GetClientRect(hWnd, &rect);
	::InvalidateRect(hWnd, &rect, TRUE);
	::UpdateWindow(hWnd);
}
// 绘制文本
void _DrawText(HDC hDC)
{
	int len = ::_tcslen(_String);
	::TextOut(hDC, 4, 2, _String, len);
}
// 设置光标位置
void _SetCaretPos(HWND hWnd)
{
	HDC hDC = ::GetDC(hWnd);
	SIZE size;
	::GetTextExtentPoint(hDC, _String, _StringPosition, &size);
	::SetCaretPos(4 + size.cx, 3);
	::ReleaseDC(hWnd, hDC);
}
// 文本框消息的处理过程

LRESULT CALLBACK _TextBoxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: {  // 绘制这里之所以加一对大括号，是为了让之下定义的变量局部化
					   static PAINTSTRUCT ps;

					   static RECT rect;

					   HDC hDC = ::BeginPaint(hWnd, &ps);  // 开始绘制操作


					   ::GetClientRect(hWnd, &rect);        // 获取客户区的尺寸

					   ::DrawEdge(hDC, &rect, EDGE_SUNKEN, BF_RECT);  // 绘制边框，EDGE_SUNKEN表示绘制样式为内嵌样式，BF_RECT表示绘制矩形边框

					   _DrawText(hDC);                      // 绘制文本

					   ::EndPaint(hWnd, &ps);               // 结束绘制操作

	} break;
	case WM_SETFOCUS: {    // 获得焦点

						  ::CreateCaret(hWnd, (HBITMAP)NULL, 1, TEXTBOX_HEIGHT - 5);     // 创建光标

						  _SetCaretPos(hWnd);                            // 设置光标位置

						  ::ShowCaret(hWnd);                   // 显示光标

	} break;
	case WM_KILLFOCUS: // 失去焦点
		::HideCaret(hWnd);                   // 隐藏光标

		::DestroyCaret();                    // 销毁光标

		break;
	case WM_SETCURSOR: {  // 设置光标形状
						   static HCURSOR hCursor = ::LoadCursor(NULL, IDC_IBEAM);

						   ::SetCursor(hCursor);

	} break;



	case WM_CHAR: {    // 字符消息

					  TCHAR code = (TCHAR)wParam;

					  int len = ::_tcslen(_String);

					  if (code < (TCHAR)' ' || len >= TEXTBOX_MAXLENGTH)

						  return 0;
					  ::MoveMemory(_String + _StringPosition + 1, _String + _StringPosition, (len - _StringPosition + 1) * sizeof(TCHAR));

					  _String[_StringPosition++] = code;
					  _UpdateWindow(hWnd);

					  _SetCaretPos(hWnd);
	} break;
	case WM_KEYDOWN: {  // 键按下消息
						 TCHAR code = (TCHAR)wParam;
						 switch (code)

						 {
						 case VK_LEFT: // 左光标键

							 if (_StringPosition > 0)

								 _StringPosition--;

							 break;
						 case VK_RIGHT:     // 右光标键

							 if (_StringPosition < (int)::_tcslen(_String))

								 _StringPosition++;

							 break;
						 case VK_HOME: // HOME 键

							 _StringPosition = 0;

							 break;
						 case VK_END:  // END 键

							 _StringPosition = ::_tcslen(_String);

							 break;

						 case VK_BACK: // 退格键

							 if (_StringPosition > 0)

							 {

								 ::MoveMemory(_String + _StringPosition - 1, _String + _StringPosition, (::_tcslen(_String) - _StringPosition + 1) * sizeof(TCHAR));

								 _StringPosition--;

								 _UpdateWindow(hWnd);

							 }

							 break;
						 case VK_DELETE: {  // 删除键

											 int len = ::_tcslen(_String);

											 if (_StringPosition < len)

											 {

												 ::MoveMemory(_String + _StringPosition, _String + _StringPosition + 1, (::_tcslen(_String) - _StringPosition + 1) * sizeof(TCHAR));

												 _UpdateWindow(hWnd);

											 }
						 } break;
						 }
						 _SetCaretPos(hWnd);
	} break;
	case WM_LBUTTONDOWN: {  // 鼠标单击，设置光标位置

							 int x = LOWORD(lParam);

							 HDC hDc = ::GetDC(hWnd);
							 int strLen = ::_tcslen(_String), strPos = 0;

							 SIZE size;
							 for (strPos = 0; strPos < strLen; strPos++)

							 {

								 ::GetTextExtentPoint(hDc, _String, strPos, &size);

								 if (size.cx + 4 >= x)

									 break;

							 }
							 _StringPosition = strPos;

							 ::GetTextExtentPoint(hDc, _String, strPos, &size);

							 ::SetCaretPos(size.cx + 4, 3);
							 ::ReleaseDC(hWnd, hDc);
	} break;
	default:
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	return (LRESULT)0;
}

// 注册文本框的类

ATOM _RegisterTextBoxClass()

{

	WNDCLASSEX wc;

	::ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);

	wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;   // 指定当窗口尺寸发生变化时重绘窗口，并且响应鼠标双击事件

	wc.hInstance = _HInstance;

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 指定窗口背景颜色为系统颜色“窗口背景”

	wc.lpszClassName = _TextBoxClass;                  // 指定要注册的窗口类名，创建窗口时要以此类名为标识符

	wc.lpfnWndProc = _TextBoxWndProc;               // 处理窗口消息的函数

	return ::RegisterClassEx(&wc);                     // 调用API函数注册文本框窗口

}

// 创建文本框

HWND _CreateTextBoxWindow(HWND hParentWnd)

{

	// 之下代码是为了让文本框显示在父窗口中央，而计算位置

	RECT parentWndRect;

	::GetClientRect(hParentWnd, &parentWndRect);  // 获取父窗口客户区的位置

	int left = (parentWndRect.right - TEXTBOX_WIDTH) / 2, top = (parentWndRect.bottom - TEXTBOX_HEIGHT) / 2;

	// 创建文本框

	HWND hWnd = ::CreateWindow(_TextBoxClass, NULL, WS_CHILDWINDOW | WS_VISIBLE,

		0, 0, TEXTBOX_WIDTH, TEXTBOX_HEIGHT,

		hParentWnd, NULL, _HInstance, NULL);

	return hWnd;
}