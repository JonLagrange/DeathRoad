//15
#include "stdafx.h"
#include "resource.h"
#include <stdio.h>

#include <windows.h>
#include <mmsystem.h>//PlaySound //mciSendCommand
#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "user32.lib")

#include < vfw.h >//MCIWndPlay
#pragma comment(lib,"vfw32.lib")

#include <digitalv.h>//MCI_DGV_SETAUDIO_PARMS

HINSTANCE hInst;
HBITMAP hero[5],bg[6],mons[3],boss[3],over,keng,shi,jin,bang,fire,bss,win,light;
HDC		hdc,mdc,bufdc,hDC;
HWND	hWnd;
DWORD	tPre,tNow;
int		dir,dim,x,y;
int		x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin1=1200,xjin2=1250,xjin3=1300,num=0,num1=0,num2=0,num3=0,num4=0,num5=0;
int spacecount=0,bosscount=0,kaichangcount=0,jincount=0,paicount=0;
int yemian=1;
int i=0;
int ren=1,guai=1,bos=1,bos2=1,sixiang=0,guaizusu=0,juli=0,pai=0;
int guaizu[40]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int lightnums[30]={0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
int lnum=0;
int weizhi=0;
int g=3,vx=5,vy=30;
int xshi=700,yshi=0;
int sshi=0;
char s1[18]="����:",s2[4]="";
char *kaichang="Ϊ�����ȹ�����Ӣ��̤��������֮�á���";
char *second="Ӣ��ɱ���˶�����Ȼ������ȴ��֪���١���";
char *third="��һ����գ��������������";
char bossxue[15]="BOSSѪ����";
FILE *fp;
char str[80];
char jinb1[8]="���:",jinb2[3]="";
char strpai[1000][40]={""},strpaijin[3]="";
int intpai[1000]={0},intpaijin[1000]={0};
int num5zu[18]={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8};
int music=0;
int dialogpai=0,dialogguan=0,dialogxing=0;
char name[20]=" ";
int guan=1;
int z=0;
int yinliang=400;
int yin;
int jing=0;
TCHAR cmd[256];

UINT deviceID;
MCI_OPEN_PARMS mciopen; 

HINSTANCE hInstance;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		else 
		{
			tNow = GetTickCount();

			 if(tNow-tPre >= 100 && guai==0)
			{
				guaizusu++;
				guai=guaizu[guaizusu%40];//�ֳ���ʱ��
				if (guaizusu%40 == 0)
				{
					x1=1024;
				}
				MyPaint(hdc);
			}
			else if (tNow-tPre >= 100 && guai==1)
				MyPaint(hdc);
			if (yemian == 1 && pai==1)//������а�
			{
				fp=fopen("���а�.txt","r");
				if (fp==NULL)
				{
					SetTextColor(hdc,RGB(255,0,0)); //����������ɫ
					SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
					HFONT hfont;
					LOGFONT font;
					ZeroMemory(&font, sizeof(LOGFONT));
					font.lfHeight = 50;
					font.lfQuality = PROOF_QUALITY;
					sprintf(font.lfFaceName, TEXT("΢���ź�"));
					hfont = CreateFontIndirect(&font);
					SelectObject(hdc, hfont);
					TextOut(hdc, 800, 0, "����Ϣ" ,7);
				}
				else
				{
					TextOut(hdc, 660, 0, "����   ���  ����" ,18);
					while (!feof(fp))
					{
						fgets(str,80,fp);
						SetTextColor(hdc,RGB(255,0,0)); //����������ɫ
						SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
						HFONT hfont;
						LOGFONT font;
						ZeroMemory(&font, sizeof(LOGFONT));
						font.lfHeight = 50;
						font.lfQuality = PROOF_QUALITY;
						sprintf(font.lfFaceName, TEXT("΢���ź�"));
						hfont = CreateFontIndirect(&font);
						SelectObject(hdc, hfont);
						if(!feof(fp))//�������һ�ж�����
							TextOut(hdc, 660, 50+paicount*50, str ,strlen(str));
						paicount++;
					}
					paicount=0;
					fclose(fp);
				}
			}
			
			if (yemian==0 && kaichangcount<37)//�԰�
			{
				TextOut(hdc, 100, 100, kaichang ,kaichangcount);
			}
			
			if (yemian==8 && kaichangcount<40)//�԰�
			{
				TextOut(hdc, 100, 100, second ,kaichangcount);
			}
			
			if (yemian==7 && kaichangcount<33)//�԰�
			{
				TextOut(hdc, 100, 100, third ,kaichangcount);
			}
			
			if ((yemian==2 || yemian==4 || yemian==5) && pai==0)//������롢���
			{
				TextOut(hdc, 800, 50, jinb1 ,strlen(jinb1));
			}
		}
    }
	return msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // �ṹ��WNDCLASSEX�Ĵ�С
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ���崰����ʽ  CS_HREDRAW������ˮƽ����Ŀ�ȱ仯ʱ�ػ���������.CS_VREDRAW �����ڴ�ֱ����Ŀ�ȱ仯ʱ�ػ���������.
	wcex.lpfnWndProc	= (WNDPROC)WndProc; //�ص�����
	wcex.cbClsExtra		= 0; // ����������ֽ�����ͨ��Ϊ0
	wcex.cbWndExtra		= 0; // ����ʵ�������ֽ�����ͨ��Ϊ0
	wcex.hInstance		= hInstance;//���̾��
	wcex.hIcon			= LoadIcon(hInstance,(LPCTSTR)(IDI_DEATHROAD));//����ͼ��
	wcex.hCursor		= NULL;
	wcex.hCursor		=  LoadCursorFromFile(_T("AppStarting.cur"));//���
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); //����
	wcex.lpszMenuName	= (LPCSTR)IDC_DEATHROAD;//�˵�
	wcex.lpszClassName	= "DeathRoad";//��������
	wcex.hIconSm		= LoadIcon(hInstance,(LPCTSTR)IDI_SMALL); //����Сͼ��

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("DeathRoad", "����֮��" ,WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, 0, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	
	MoveWindow(hWnd,0,0,1024,544,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc,1024,544);
	SelectObject(mdc,bmp);

	x = 50;
	y = 280;
	dir = 1;
	dim = 0;

	hero[0] = (HBITMAP)LoadImage(NULL,"runl.bmp",IMAGE_BITMAP,1096,202,LR_LOADFROMFILE);
	hero[1] = (HBITMAP)LoadImage(NULL,"runr.bmp",IMAGE_BITMAP,1096,202,LR_LOADFROMFILE);
	hero[2] = (HBITMAP)LoadImage(NULL,"die.bmp",IMAGE_BITMAP,870,244,LR_LOADFROMFILE);
	hero[3] = (HBITMAP)LoadImage(NULL,"kill.bmp",IMAGE_BITMAP,1456,224,LR_LOADFROMFILE);
	hero[4] = (HBITMAP)LoadImage(NULL,"kilr.bmp",IMAGE_BITMAP,1456,224,LR_LOADFROMFILE);	
	mons[0] = (HBITMAP)LoadImage(NULL,"mons.bmp",IMAGE_BITMAP,847,314,LR_LOADFROMFILE);
	mons[1] = (HBITMAP)LoadImage(NULL,"mons1.bmp",IMAGE_BITMAP,847,314,LR_LOADFROMFILE);
	mons[2] = (HBITMAP)LoadImage(NULL,"mdies.bmp",IMAGE_BITMAP,875,350,LR_LOADFROMFILE);
	boss[0] = (HBITMAP)LoadImage(NULL,"boss.bmp",IMAGE_BITMAP,2322,482,LR_LOADFROMFILE);
	boss[1] = (HBITMAP)LoadImage(NULL,"boss2.bmp",IMAGE_BITMAP,2328,614,LR_LOADFROMFILE);
	bg[0] = (HBITMAP)LoadImage(NULL,"bg0.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[1] = (HBITMAP)LoadImage(NULL,"bg1.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[2] = (HBITMAP)LoadImage(NULL,"bg2.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[3] = (HBITMAP)LoadImage(NULL,"bg3.bmp",IMAGE_BITMAP,1024,728,LR_LOADFROMFILE);
	bg[4] = (HBITMAP)LoadImage(NULL,"bg4.bmp",IMAGE_BITMAP,1024,608,LR_LOADFROMFILE);
	bg[5] = (HBITMAP)LoadImage(NULL,"bg5.bmp",IMAGE_BITMAP,1024,576,LR_LOADFROMFILE);
	over = (HBITMAP)LoadImage(NULL,"over.bmp",IMAGE_BITMAP,1024,1088,LR_LOADFROMFILE);
	keng = (HBITMAP)LoadImage(NULL,"keng.bmp",IMAGE_BITMAP,120,200,LR_LOADFROMFILE);
	shi = (HBITMAP)LoadImage(NULL,"stone.bmp",IMAGE_BITMAP,143,200,LR_LOADFROMFILE);
	fire = (HBITMAP)LoadImage(NULL,"fire.bmp",IMAGE_BITMAP,1458,308,LR_LOADFROMFILE);
	light= (HBITMAP)LoadImage(NULL,"light.bmp",IMAGE_BITMAP,1520,612,LR_LOADFROMFILE);
	jin = (HBITMAP)LoadImage(NULL,"gold.bmp",IMAGE_BITMAP,150,200,LR_LOADFROMFILE);
	bang = (HBITMAP)LoadImage(NULL,"bang.bmp",IMAGE_BITMAP,188,90,LR_LOADFROMFILE);
	bss = (HBITMAP)LoadImage(NULL,"bss.bmp",IMAGE_BITMAP,400,400,LR_LOADFROMFILE);
	win = (HBITMAP)LoadImage(NULL,"win.bmp",IMAGE_BITMAP,1024,1088,LR_LOADFROMFILE);
	
	MyPaint(hdc);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG: 
		if (dialogpai==1)
		{
			fp=fopen("���а�.txt","r");
			if (fp==NULL)
			{
				return 0;
			}
			else
			{
				char paistr[10000]="";
				while (!feof(fp))
				{
					fgets(str,80,fp);
					if(!feof(fp))
					{
						strcat(paistr,str);
						paistr[strlen(paistr)-1]='\0';
						strcat(paistr,"\r\n");
					}
				}
				SetDlgItemText(hWnd,IDC_EDIT1, paistr);
			} 
			fclose(fp);
			dialogpai=0;
		}

		if (dialogguan==1)
		{
			fp=fopen("����.txt","r");
			if (fp==NULL)
			{
				return 0;
			}
			else
			{
				char paistr[1000]="";
				while (!feof(fp))
				{
					fgets(str,80,fp);
					if(!feof(fp))
					{
						strcat(paistr,str);
						paistr[strlen(paistr)-1]='\0';
						strcat(paistr,"\r\n");
					}
				}
				SetDlgItemText(hWnd,IDC_EDIT4, paistr);
			} 
			fclose(fp);
			dialogguan=0;
		}

		if (dialogxing==1)
		{
			strcat(s1,"\r\n");
			strcat(s1,jinb1);
			SetDlgItemText(hWnd,IDC_EDIT2, s1);
			dialogxing=0;
		}
		
		return TRUE;//��Ϣ�Ѵ�������Ҫ�ٵ����������ڲ��Ի�����Ϣ������
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hWnd,IDC_EDIT3, name,17);
			EndDialog(hWnd,1);
			SetCursorPos(400,200);//���ù��λ��
			mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//����
			mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//����
			return true;
			break;
		case IDCANCEL:
			EndDialog(hWnd,1);
			return true;
		}
	}
	return false;//����δ���������Ϣ�������ڲ�����Ϣ������
}
//////////////////////////////////////////////////////////////////////////
void MyPaint(HDC hdc)
{
	if (yemian==1 && music==0)
	{
		mciSendString("close boss.mp3 ", NULL, 0, 0);
		mciSendString("open 1.mp3 " , NULL, 0, 0); 
		mciSendString("play 1.mp3 repeat", NULL, 0, 0);
		wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
		mciSendString (cmd,NULL,0,0);//mp3;
		music=1;
	}
	int w=137,h=101;	

	if (yemian==1)//��ʼҳ
	{
		SelectObject(bufdc,bg[1]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		SelectObject(bufdc,bang);//���а�
		BitBlt(mdc,50,242,188,90,bufdc,0,0,SRCCOPY);	
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
	}
	if (yemian==0)//�԰�ҳ
	{
		SelectObject(bufdc,bg[2]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
	}
	
	if (yemian==7)//�԰�ҳ
	{
		SelectObject(bufdc,bg[4]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
	}
	
	if (yemian==8)//�԰�ҳ
	{
		SelectObject(bufdc,bg[5]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
	}

	if (yemian == 6 || yemian==9 || yemian==10)//bossҳ
	{	
		if (yemian ==6 && ((x>x3+5) || (x>x4+60-num5zu[num5]*18 && x<x4+100 && y>200)) && bos==1&&(dir==0||dir==2))
		{
			ren=0;
			//PlaySound(NULL,NULL,NULL);//ֹͣ����
			mciSendString("close boss.mp3 ", NULL, 0, 0);
		}
		if (yemian ==6 && ((x>x3-95) || (x>x4-40-num5zu[num5]*10 && x<x4+100 && y>200)) && bos==1&&(dir==1||dir==3))
		{
			ren=0;
			mciSendString("close boss.mp3 ", NULL, 0, 0);
		}
		if ((yemian ==9 || yemian==10) && ( (x>x3-30) || (x>x4 && x<x4+120) ) && bos==1&&(dir==0||dir==2))
		{
			ren=0;
			mciSendString("close boss.mp3 ", NULL, 0, 0);
		}
		if ((yemian ==9 || yemian==10) && ( (x>x3-130) || (x>x4-65 && x<x4+60) ) && bos==1&&(dir==1||dir==3))
		{
			ren=0;
			mciSendString("close boss.mp3 ", NULL, 0, 0);
		}
		if (bosscount == 5)
		{
			bos=0;
			//yemian=3;

			
			mciSendString("close boss.mp3 ", NULL, 0, 0);
			mciSendString("open 2.mp3 " , NULL, 0, 0); 
			mciSendString("play 2.mp3  repeat", NULL, 0, 0);
			wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
			mciSendString (cmd,NULL,0,0);//mp3;
			if (guan==3)
			{
			}
			else
				guan=2;

			x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin1=1200,xjin2=1250,xjin3=1300,num=0,num1=0,num2=0,num3=0,num4=0;
			//x=50;
			//y=280;
			vx=5,vy=30,g=3;
			dir = 1;
			ren=1;
			guai=1;
			sshi=0;
			xshi=700;
			yshi=0;
			kaichangcount=0;
			pai=0;
			bosscount=6;
			//bos=1;
			music=0;
			name[0]='\0';
		}
		
		if (bosscount == 13)
		{
			bos=0;
			//yemian=3;
			mciSendString("close boss.mp3 ", NULL, 0, 0);
			mciSendString("open 2.mp3 " , NULL, 0, 0); 
			mciSendString("play 2.mp3  repeat", NULL, 0, 0);
			wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
			mciSendString (cmd,NULL,0,0);//mp3;

			guan=3;
			
			x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin1=1200,xjin2=1250,xjin3=1300,num=0,num1=0,num2=0,num3=0,num4=0;
			//x=50;
			//y=280;
			vx=5,vy=30,g=3;
			dir = 1;
			ren=1;
			guai=1;
			sshi=0;
			xshi=700;
			yshi=0;
			kaichangcount=0;
			pai=0;
			bosscount=14;
			//bos=1;
			music=0;
			name[0]='\0';	
		}
		
		if (bosscount == 23)
		{
			bos=0;
		}

		if (yemian==6)
		{
			SelectObject(bufdc,bg[2]);//����
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}
		if (yemian==9)
		{
			SelectObject(bufdc,bg[5]);//����
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}
		if (yemian==10)
		{
			SelectObject(bufdc,bg[4]);//����
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}

		SelectObject(bufdc,bss);
		BitBlt(mdc,300,0,400,200,bufdc,0,200,SRCAND);
		BitBlt(mdc,300,0,400,200,bufdc,0,0,SRCPAINT);

		SelectObject(bufdc,bg[3]);//��
		BitBlt(mdc,0,150,1024,364,bufdc,0,364,SRCAND);
		BitBlt(mdc,0,150,1024,364,bufdc,0,0,SRCPAINT);

		if ((yemian ==6 || yemian==10) && bos == 1)
		{		
			SelectObject(bufdc,boss[0]);//boss
	    	BitBlt(mdc,x3,170,387,241,bufdc,num4*387,241,SRCAND);
	    	BitBlt(mdc,x3,170,387,241,bufdc,num4*387,0,SRCPAINT);
	    	BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);

            if (yemian==6 && x3 == 600)
            {
				if(x4 > 410)  x4=410;				
				SelectObject(bufdc,fire);//���
				BitBlt(mdc,x4,210,243,154,bufdc,num5zu[num5]*243,154,SRCAND);
				BitBlt(mdc,x4,210,243,154,bufdc,num5zu[num5]*243,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
            }
			
			if (yemian==10 && x3 == 600)
            {
				//if(x4 > 410)  x4=410;				
				SelectObject(bufdc,light);//����
				BitBlt(mdc,x4,120,190,306,bufdc,num5zu[num5]*190,306,SRCAND);
				BitBlt(mdc,x4,120,190,306,bufdc,num5zu[num5]*190,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
				
				if (lightnums[lnum]==2)
				{
					lnum=0;
					weizhi++;
					if(weizhi==1)
						x4=800;
					if(weizhi==2)
						x4=500;
					else if(weizhi==3)
						x4=250;
					else if(weizhi==4)
					{
						weizhi=0;
						x4=-50;
					}
				}
				else if (lightnums[lnum]==1)
					x4=1500;
				lnum++;
            }
			num4++;
			if (num4==4)
			{
				num4=0;
			}	
			num5++;
			if (num5zu[num5]>=4)
			{
				num5=0;
			}	
		}

		if (yemian == 9 && bos == 1)
		{		
			SelectObject(bufdc,boss[1]);//boss
			BitBlt(mdc,x3,100,291,307,bufdc,num*291,307,SRCAND);
			BitBlt(mdc,x3,100,291,307,bufdc,num*291,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			
            if (x3 == 600)
            {
				//if(x4 > 410)  x4=410;				
				SelectObject(bufdc,light);//����
				BitBlt(mdc,x4,120,190,306,bufdc,num5zu[num5]*190,306,SRCAND);
				BitBlt(mdc,x4,120,190,306,bufdc,num5zu[num5]*190,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);

				if (lightnums[lnum]==2)
				{
					lnum=0;
					weizhi++;
					if(weizhi==1)
						x4=800;
					if(weizhi==2)
						x4=500;
					else if(weizhi==3)
						x4=250;
					else if(weizhi==4)
					{
						weizhi=0;
						x4=-50;
					}
				}
				else if (lightnums[lnum]==1)
					x4=1500;
				lnum++;
            }
			
			num++;
			if (num==8)
			{
				num=0;
			}	
			num5+=2;
			if (num5zu[num5]==8)
			{
				num5=0;
			}
		}


		if (bos == 0 && ren==1)
		{		
			SelectObject(bufdc,win);//win
			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}

		tPre = GetTickCount(); 
		
// ��������
		if (ren==1)
		{
			if (dir<2)
			{
				SelectObject(bufdc,hero[dir]);//��
				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[dir+1]);//����
				BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,112,SRCAND);
			    BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
				num2++;
				if (num2==6)
				{
					dir=sixiang;
					num2=0;
				}
			}

			x3-=10;
			if (x3 < 600)
			{
				x3=600;
			}
			
			if (yemian==6)
			{
				x4-=10;
				if (x4 < -400)
				{
					x4=530;
				}
			}
			num++;
			if(num == 8)
				num = 0;
		}
// ��������
		else
		{
			if (num2<6)
			{
				SelectObject(bufdc,hero[2]);//����
				BitBlt(mdc,x,y,145,122,bufdc,num2*145,122,SRCAND);
				BitBlt(mdc,x,y,145,122,bufdc,num2*145,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[2]);
				BitBlt(mdc,x,y,145,122,bufdc,5*145,122,SRCAND);
				BitBlt(mdc,x,y,145,122,bufdc,5*145,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			SelectObject(bufdc,over);//over
			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			
			if (num2==0)
			{
				mciSendString("close ����.mp3 " , NULL, 0, 0);
				mciSendString("open ����.mp3 " , NULL, 0, 0); 
				mciSendString("play ����.mp3", NULL, 0, 0);
				wsprintf(cmd, "setaudio ����.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);//mp3;
			}
			if (num2==6)
			{
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),NULL,Main_Proc); 
			}
			num2++;
		}
	}

	if (yemian==2)
	{
		SelectObject(bufdc,bg[2]);//����
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
	}

	if (yemian==4)
	{
		SelectObject(bufdc,bg[4]);//����
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
		if (juli<=451)
		{
			juli=451;
		}
	}

	if (yemian==5)
	{
		SelectObject(bufdc,bg[5]);//����
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
		if (juli<=201)
		{
			juli=201;
		}
	}

	if (yemian==2 || yemian==4 || yemian==5)//��Ϸҳ
	{
		if (ren==1 && juli == 200)
		{
			yemian=6;
			mciSendString("close 03.mp3 ", NULL, 0, 0);
			mciSendString("open boss.mp3 " , NULL, 0, 0); 
			mciSendString("play boss.mp3 repeat", NULL, 0, 0);//�����Կɵ������ţ�ͬplaysound
			wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
			mciSendString (cmd,NULL,0,0);//mp3;
		}
		if (ren==1 && juli == 450)
		{
			yemian=9;
			mciSendString("close 04.mp3 ", NULL, 0, 0);
			mciSendString("open boss.mp3 " , NULL, 0, 0); 
			mciSendString("play boss.mp3 repeat", NULL, 0, 0);
			wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
			mciSendString (cmd,NULL,0,0);//mp3;
		}
		if (ren==1&&juli == 700)
		{
			yemian=10;
			mciSendString("close 05.mp3 ", NULL, 0, 0);
			mciSendString("open boss.mp3 " , NULL, 0, 0); 
			mciSendString("play boss.mp3 repeat", NULL, 0, 0);
			wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
			mciSendString (cmd,NULL,0,0);//mp3;
		}
		if(x>x1-110 && x<x1+80 && y>270 && guai==1)
		{
			ren=0;
			mciSendString("close 03.mp3", NULL, 0, 0);
			mciSendString("close 04.mp3", NULL, 0, 0);
			mciSendString("close 05.mp3", NULL, 0, 0);
		}
		//��
		if(x>xkeng-100 && x<xkeng+50 && y>279)
		{
			x=xkeng-20;
			vy+=g;
			y+=vy;
			ren=0;
			mciSendString("close 03.mp3", NULL, 0, 0);
			mciSendString("close 04.mp3", NULL, 0, 0);
			mciSendString("close 05.mp3", NULL, 0, 0);
		}
		//׹��
		if (x>xshi-100 && x<xshi+50 && yshi>200 && y>279)
		{
			ren=0;
			mciSendString("close 03.mp3", NULL, 0, 0);
			mciSendString("close 04.mp3", NULL, 0, 0);
			mciSendString("close 05.mp3", NULL, 0, 0);
			sshi=2;
			if(yshi<290) yshi=280;
		}
		//���
		if (x>xjin1-80 && x<xjin1+50 && y<250)
		{
			jincount++;
			xjin1=1400;
		}
		
		if (x>xjin2-80 && x<xjin2+50 && y<250)
		{
			jincount++;
			xjin2=1450;
		}
		
		if (x>xjin3-80 && x<xjin3+50 && y<250)
		{
			jincount++;
			xjin3=1500;
		}


//����
		SelectObject(bufdc,bg[3]);//��
		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,364,SRCAND);
		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,364,SRCAND);
		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,0,SRCPAINT);
		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,0,SRCPAINT);
		if (guai==1)
		{
			SelectObject(bufdc,mons[dim]);//��
			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,157,SRCAND);
			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,0,SRCPAINT);
		}	
		else if(dim == 2)
		{
			SelectObject(bufdc,mons[2]);//����
			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,175,SRCAND);
			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,0,SRCPAINT);
			num3++;
			if (num3==5)
			{
				dim=0;
				num3=0;
			}
		}
		SelectObject(bufdc,keng);//��
		BitBlt(mdc,xkeng,372,120,200,bufdc,0,0,SRCCOPY);
		SelectObject(bufdc,jin);//���
		BitBlt(mdc,xjin1,200,150,100,bufdc,0,100,SRCAND);
		BitBlt(mdc,xjin1,200,150,100,bufdc,0,0,SRCPAINT);
		BitBlt(mdc,xjin2,200,150,100,bufdc,0,100,SRCAND);
		BitBlt(mdc,xjin2,200,150,100,bufdc,0,0,SRCPAINT);
		BitBlt(mdc,xjin3,200,150,100,bufdc,0,100,SRCAND);
	    BitBlt(mdc,xjin3,200,150,100,bufdc,0,0,SRCPAINT);

		if (sshi==1)//׹�����
		{
			SelectObject(bufdc,shi);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			yshi+=50;
			if (yshi>300)
				yshi=300;
		}
		if (sshi==2)//׹�����
		{
			SelectObject(bufdc,shi);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}
		tPre = GetTickCount(); 
		
// ��������
		if (ren==1)
		{
			if (dir<2)
			{
				SelectObject(bufdc,hero[dir]);//��
				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[dir+1]);//����
				BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,112,SRCAND);
			    BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
				num2++;
				if (num2==6)
				{
					dir=sixiang;
					num2=0;
				}
			}
//׹��
			if (x>600 && x<700 && sshi==0)
			{
				sshi=1;
			}
			if (sshi==1 && yshi==300)
			{
				sshi=2;
			}
			if (sshi==2)
			{
				if(dir==0)
					xshi+=10;
				if (dir==1)
					xshi-=10;
			}
			if (xshi<-200 || xshi>1224)
			{
				sshi=0;
				xshi=700;
				yshi=0;
			}

			x1 -= 15;//��	
			if(x1<-120)
				x1 = 1024;

			switch (dir)
			{
			case 1:
				x0 -= 2;		
				if(x0 < 0)
					x0 = 1024;
				
				x2 -= 10;
				juli+=1;	
				if(x2 < 0)
					x2 = 1024;

				xkeng -= 10;

				xjin1 -=10;
				if(xjin1 < -100)
					xjin1 = 1200;
				
				xjin2 -=10;
				if(xjin2 < -100)
					xjin2 = 1300;
				
				xjin3 -=10;
				if(xjin3 < -100)
					xjin3 =1450;

				break;
			case 0:
				x0 += 2;		
				if(x0 > 1024)
					x0 = 0;
				
				x2 += 10;juli-=1;		
				if(x2 > 1024)
					x2 = 0;

				xkeng += 10;

				xjin1+=10;
				xjin2+=10;
				xjin3+=10;

				break;
			}
			
			num++;
			if(num == 8)
				num = 0;
			num1++;
			if(num1 == 7)
				num1 = 0;
		}
// ��������
		else
		{
			if (num2<6)
			{
				SelectObject(bufdc,hero[2]);//����
				BitBlt(mdc,x,y,145,122,bufdc,num2*145,122,SRCAND);
				BitBlt(mdc,x,y,145,122,bufdc,num2*145,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[2]);
				BitBlt(mdc,x,y,145,122,bufdc,5*145,122,SRCAND);
				BitBlt(mdc,x,y,145,122,bufdc,5*145,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			SelectObject(bufdc,over);//����
			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			if (num2==0)
			{
				mciSendString("close ����.mp3 " , NULL, 0, 0); 
				mciSendString("open ����.mp3 " , NULL, 0, 0); 
				mciSendString("play ����.mp3", NULL, 0, 0);
				wsprintf(cmd, "setaudio ����.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);//mp3;
			}
			if (num2==6)
			{
				dialogxing=1;
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),NULL,Main_Proc); 
			}
			num2++;
		}
	}
	
	if (yemian==3)
	{
		SelectObject(bufdc,bg[0]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
	}

	if (yemian==0 && kaichangcount<38)//�԰�
	{
		SetTextColor(hdc,RGB(255,255,255)); //����������ɫ
		SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		sprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		TextOut(hdc, 100, 100, kaichang ,kaichangcount);
		kaichangcount+=1;
		
		if(kaichangcount==38)
		{
			yemian=2;
			kaichangcount=0;
		}
	}
	
	if (yemian==8 && kaichangcount<40)//�԰�
	{
		SetTextColor(hdc,RGB(255,255,255)); //����������ɫ
		SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		sprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		TextOut(hdc, 100, 100, second ,kaichangcount);
		kaichangcount+=1;
		
		if(kaichangcount==40)
		{
			yemian=5;
			kaichangcount=0;
		}
	}
	
	if (yemian==7 && kaichangcount<33)//�԰�
	{
		SetTextColor(hdc,RGB(255,255,255)); //����������ɫ
		SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		sprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		TextOut(hdc, 100, 100, third ,kaichangcount);
		kaichangcount+=1;


		if(kaichangcount==33)
		{
			yemian=4;
			kaichangcount=0;
		}
	}
	
	if ((yemian==2 || yemian==4 || yemian==5) && pai==0)//������롢���
	{
		SetTextColor(hdc,RGB(0,0,255)); //����������ɫ
		SetBkMode (hdc,TRANSPARENT);//�豸����ɫģʽΪ͸���벻͸�� TRANSPARENT��OPAQUE
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		wsprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		itoa(juli, s2, 10);
		s1[5]='\0';
		strcat(s1,s2);
		TextOut(hdc, 800, 0, s1 ,strlen(s1));
		itoa(jincount, jinb2, 10);
		jinb1[5]='\0';
		strcat(jinb1,jinb2);
		TextOut(hdc, 800, 50, jinb1 ,strlen(jinb1));
	}
	if (yemian==6)//���bossѪ��
	{
		SetTextColor(hdc,RGB(0,0,255)); 
		SetBkMode (hdc,TRANSPARENT);
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		wsprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		if(5-bosscount>0)
			itoa(5-bosscount, s2, 10);
		else
			itoa(0, s2, 10);
		bossxue[10]='\0';
		strcat(bossxue,s2);
		TextOut(hdc, 730, 0, bossxue ,strlen(bossxue));
	}
	if (yemian==9)//���bossѪ��
	{
		SetTextColor(hdc,RGB(0,0,255)); 
		SetBkMode (hdc,TRANSPARENT);
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		wsprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		if(13-bosscount>0)
			itoa(13-bosscount, s2, 10);
		else
			itoa(0, s2, 10);
		bossxue[10]='\0';
		strcat(bossxue,s2);
		TextOut(hdc, 730, 0, bossxue ,strlen(bossxue));
	}
	if (yemian==10)//���bossѪ��
	{
		SetTextColor(hdc,RGB(0,0,255)); 
		SetBkMode (hdc,TRANSPARENT);
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		wsprintf(font.lfFaceName, TEXT("΢���ź�"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		if(23-bosscount>0)
			itoa(23-bosscount, s2, 10);
		else
			itoa(0, s2, 10);
		bossxue[10]='\0';
		strcat(bossxue,s2);
		TextOut(hdc, 730, 0, bossxue ,strlen(bossxue));
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
						 WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		if (IDYES==MessageBox(hWnd,"ȷ��Ҫ�˳���","��ʾ",MB_YESNO))
		{
			PostQuitMessage( 0 );
		}
		break;
	case WM_COMMAND:
		{// �ж��û�ѡ�����ĸ��˵���  
			switch(LOWORD(wParam))  
			{  
			case IDM_PAI:  
				fp=fopen("���а�.txt","r");
				if (fp==NULL)
				{
					return 0;
				}
				else
				{
					char paistr[10000]="";
					while (!feof(fp))
					{
						fgets(str,80,fp);
						if(!feof(fp))
							strcat(paistr,str);
					}
					SetCursorPos(400,200);//���ù��λ��
					dialogpai=1;
					DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),
						      NULL,Main_Proc);
					
					mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//����
					mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//����
				} 
				fclose(fp);
				break;  
			case IDM_ABOUT: 
				dialogguan=1;
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG3),NULL,Main_Proc);
				break;

			case ID_MENUITEM32773:				
				if(yinliang<1000)
				{
					if (jing==1)
					{
						jing=0;
						DeleteMenu(GetMenu(hWnd), ID_MENUITEM32775+1, 0);// {ɾ���ò˵�}
						InsertMenu(GetMenu(hWnd), 5,MF_BYPOSITION | MF_POPUP,ID_MENUITEM32775, TEXT("����"));
						DrawMenuBar(hWnd); //{�ػ�˵�}
					}
					yinliang+=100;
					wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
				}
				break;
			case ID_MENUITEM32774:
				if(yinliang>0)
				{
					if (jing==1)
					{
						jing=0;
						DeleteMenu(GetMenu(hWnd), ID_MENUITEM32775+1, 0);// {ɾ���ò˵�}
						InsertMenu(GetMenu(hWnd), 5,MF_BYPOSITION | MF_POPUP,ID_MENUITEM32775, TEXT("����"));
						DrawMenuBar(hWnd); //{�ػ�˵�}
					}
					yinliang-=100;
					wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
				}
				break;
			case ID_MENUITEM32775:
				jing=1;
				yin=yinliang;
				yinliang=0;
				wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				
				DeleteMenu(GetMenu(hWnd), ID_MENUITEM32775, 0);// {ɾ���ò˵�}
				InsertMenu(GetMenu(hWnd), 5,MF_BYPOSITION | MF_POPUP,ID_MENUITEM32775+1, TEXT("ȡ������"));
				DrawMenuBar(hWnd); //{�ػ�˵�}
				break;
			case ID_MENUITEM32775+1:
				jing=0;
				yinliang=yin;
				wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				DeleteMenu(GetMenu(hWnd), ID_MENUITEM32775+1, 0);// {ɾ���ò˵�}
				InsertMenu(GetMenu(hWnd), 5,MF_BYPOSITION | MF_POPUP,ID_MENUITEM32775, TEXT("����"));
				DrawMenuBar(hWnd); //{�ػ�˵�}
				break;
			default:  
				break;
			}  
        }  
		break;
	case WM_LBUTTONDOWN:
		switch (yemian)
		{
		case 1:
			if(WORD LOWORD(lParam) >300 && WORD LOWORD(lParam)<488 && WORD HIWORD(lParam)>240 && WORD HIWORD(lParam)<330)//��ʼ
			{
				mciSendString("close 1.mp3 ", NULL, 0, 0);
				mciSendString("open 2.mp3 " , NULL, 0, 0); 
				mciSendString("play 2.mp3  repeat", NULL, 0, 0);
				wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);//mp3;

				yemian=3;
				x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin1=1200,xjin2=1250,xjin3=1300,num=0,num1=0,num2=0,num3=0,num4=0;
				x=50;
				y=280;
				vx=5,vy=30,g=3;
				dir = 1;
				ren=1;
				guai=1;
				sshi=0;
				xshi=700;
				yshi=0;
				juli=0;
				yemian=3;
				kaichangcount=0;
			    jincount=0;
				pai=0;
				bosscount=0;bos=1;
				music=0;
				name[0]='\0';
			}
			else if(WORD LOWORD(lParam)>50 && WORD LOWORD(lParam)<240 && WORD HIWORD(lParam)>242 && WORD HIWORD(lParam)<332)//����
			{
				pai=1;
				dialogpai=1;
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),NULL,Main_Proc);
			}
			break;
		case 6:
		case 2:
		case 4:
		case 5:
		case 9:
		case 10:
			if((ren==0||bos==0) && WORD LOWORD(lParam)>0 && WORD LOWORD(lParam)<1024 && WORD HIWORD(lParam)>0 && WORD HIWORD(lParam)<544)//��ʼ
			{
				if (ren==0)
				{
					yemian = 1;
				}
				if (bos==0)
				{
					yemian = 3;
				}
				if (pai==0)
				{
					fp=fopen("���а�.txt","at");
					itoa(juli, str, 10);
					itoa(jincount, jinb2, 10);
					int j=strlen(str);
					for (i=0;i<8-j;i++)
					{
						strcat(str," ");
					}
					strcat(str,jinb2);
					j=strlen(jinb2);
					for (i=0;i<8-j;i++)
					{
						strcat(str," ");
					}
					strcat(str,name);
					strcat(str,"\n");
					fputs(str,fp);
					fclose(fp);
					
					fp=fopen("���а�.txt","r");
					i=0;
					while (!feof(fp))
					{
						fgets(strpai[i],80,fp);
						intpai[i]=atoi(strpai[i]);
						strncpy(strpaijin,strpai[i]+8,2);
						intpaijin[i]=atoi(strpaijin);
						i++;
					}
					fclose(fp);
					
					int l=i;
					int m,n;
					char temp[20]="";
					for (i=i-1;i>0;i--)
					{
						for (int j=i;j>0;j--)
						{
							if (intpai[j]>intpai[j-1])
							{
								m=intpai[j];n=intpaijin[j];
								intpai[j-1]=intpai[j];intpaijin[j-1]=intpaijin[j];
								intpai[j]=m;intpaijin[j]=n;
								strcpy(temp,strpai[j]); strcpy(strpai[j],strpai[j-1]); strcpy(strpai[j-1],temp);
							}
							else if (intpai[j]==intpai[j-1])
							{
								if (intpaijin[j]>intpaijin[j-1])
								{
									m=intpai[j];n=intpaijin[j];
									intpai[j-1]=intpai[j];intpaijin[j-1]=intpaijin[j];
									intpai[j]=m;intpaijin[j]=n;
									strcpy(temp,strpai[j]); strcpy(strpai[j],strpai[j-1]); strcpy(strpai[j-1],temp);
								}
							}
						}
					}
					
					fp=fopen("���а�.txt","w");
					for (i=0;i<l;i++)
					{
						fputs(strpai[i],fp);
					}
					fclose(fp);
				}
		}
			break;
		case 3:
			if(WORD LOWORD(lParam)>60 && WORD LOWORD(lParam)<380 && WORD HIWORD(lParam)>40 && WORD HIWORD(lParam)<220)
			{
				yemian=0;
				mciSendString("close 2.mp3 ", NULL, 0, 0);
				mciSendString("open 03.mp3 " , NULL, 0, 0); 
				mciSendString("play 03.mp3  repeat", NULL, 0, 0);
				wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				juli=0;
			}				
			else if(WORD LOWORD(lParam)>60 && WORD LOWORD(lParam)<380 && WORD HIWORD(lParam)>260 && WORD HIWORD(lParam)<440)		
			{
				if(guan<3)
					MessageBox(hWnd,"����ͨ��ǰ��Ĺؿ���","��ʾ",MB_OK);
				else
				{
					yemian=7;
					bosscount=14;
					mciSendString("close 2.mp3 ", NULL, 0, 0);
					mciSendString("open 05.mp3 " , NULL, 0, 0); 
					mciSendString("play 05.mp3  repeat", NULL, 0, 0);
					wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					juli=451;
				}
			}
			else if(WORD LOWORD(lParam)>420 && WORD LOWORD(lParam)<740 && WORD HIWORD(lParam)>40 && WORD HIWORD(lParam)<220)
			{
				if (guan==1)
					MessageBox(hWnd,"����ͨ��ǰ��Ĺؿ���","��ʾ",MB_OK);
				else
				{
					yemian=8;
					bosscount=6;
					mciSendString("close 2.mp3 ", NULL, 0, 0);
					mciSendString("open 04.mp3 " , NULL, 0, 0); 
					mciSendString("play 04.mp3  repeat", NULL, 0, 0);
					wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
					mciSendString (cmd,NULL,0,0);
					juli=201;
				}
			}
			bos=1;
			x=50;
			y=280;
			break;
		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			if (IDYES==MessageBox(hWnd,"ȷ��Ҫ�˳���","��ʾ",MB_YESNO))
			{
				PostQuitMessage( 0 );
			}
			break;
		case VK_LEFT:
			if ( (yemian==2 || yemian==4 || yemian==5 || yemian==6 || yemian==9 || yemian==10) && ren==1)
			{
				switch(dir)
				{
				case 0:
					x -= 20;
					break;
				case 1:
					x -= 20;
					break;
				}
				if(x < 0)
					x = 0;
				dir = 0;
			}
			if ( (yemian==2 || yemian==4 || yemian==5) && ren==1)
				juli-=2;
			break;
			
		case VK_RIGHT:
			if ( (yemian==2 || yemian==4 || yemian==5 || yemian==6 || yemian==9 || yemian==10) && ren==1)
			{
				switch(dir)
				{
				case 0:
					x += 20;juli+=2;
					break;
				case 1:
					x += 20;juli+=2;
					break;
				}
				if(x > 870)
					x = 870;
				dir = 1;
			}
			if ( (yemian==2 || yemian==4 || yemian==5) && ren==1)
				juli+=2;
			break;
				
		case VK_SPACE:
			if ( (yemian==2 || yemian==4 || yemian==5 || yemian==6 || yemian==9 || yemian==10)&& spacecount==0 && ren==1)
			{
				spacecount=1;

				switch (dir)
				{
				case 0:
					for (i=0;i<10;i++)
					{
						x -= vx;x1+=6;		
						y -= vy;								
						vy -= g;
						Sleep(20);
						MyPaint(hdc);
						if(x < 0)
					       x = 0;
					}
					
					for (i=0;i<10;i++)
					{
						x -= vx;x1+=6;								
						vy += g;		
						y += vy;
						Sleep(20);
						MyPaint(hdc);
						if(x < 0)
				           x = 0;
					}
					break;

				case 1:
					for (i=0;i<10;i++)
					{
						x += vx;x1+=5;		
						y -= vy;								
						vy -= g;
						Sleep(20);
						MyPaint(hdc);
						if(x > 870)
					       x = 870;
					}
					
					for (i=0;i<10;i++)
					{
						x += vx;x1+=5;								
						vy += g;		
						y += vy;
						Sleep(20);
						MyPaint(hdc);
						if(x > 870)
					       x = 870;
					}
					break;
				}

			}	
			break;

		case 'Z':
			z=1;
			break;
		case VK_UP:
			if(z==1 && yinliang<1000)
			{
				yinliang+=100;
				wsprintf(cmd, "setaudio 1.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
			}
			break;
		case VK_DOWN:
			if(z==1 && yinliang>0)
			{
				yinliang-=100;
				wsprintf(cmd, "setaudio *.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 2.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 03.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 04.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio 05.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
				wsprintf(cmd, "setaudio boss.mp3 volume to %i",yinliang);
				mciSendString (cmd,NULL,0,0);
			}
			break;

		case 'X':
			if ( (yemian==2 || yemian==4 || yemian==5 || yemian==6 || yemian==9 || yemian==10) && ren==1)
			{	
				mciSendString("close 3.mp3 " , NULL, 0, 0);
				mciSendString("open 3.mp3 " , NULL, 0, 0); 
				mciSendString("play 3.mp3", NULL, 0, 0);			
// 				HWND MyPlayer = MCIWndCreate(NULL,GetModuleHandle(NULL), WS_POPUP, "3.mp3");
// 				MCIWndPlay(MyPlayer); 
// 				MCIWndSetVolume(MyPlayer,yinliang);

				switch(dir)
				{
				case 0:
					sixiang=dir;
				    dir=2;
					break;
				case 1:
					sixiang=dir;
				    dir=3;
					break;
				}

				if(guai==1 && x>x1-200 && x<x1+200)
				{
					dim=2;
					guai=0;
					
					HWND MyPlayer = MCIWndCreate(NULL,GetModuleHandle(NULL), WS_POPUP, "4.mp3");
					MCIWndPlay(MyPlayer); 
					MCIWndSetVolume(MyPlayer,yinliang);
				}

				if((yemian==6 || yemian==9 || yemian==10) && bos==1 && x>400)
				{
					bosscount++;
					if (bosscount==5||bosscount==13||bosscount==23)
					{
						HWND MyPlayer = MCIWndCreate(NULL,GetModuleHandle(NULL), WS_POPUP, "5.mp3");
						MCIWndPlay(MyPlayer); //������ ���ص�����
						MCIWndSetVolume(MyPlayer,yinliang); //�������������Ϊ1000,mp3
					}
				}
			}
			break;
		}
		break;
			
	case WM_KEYUP:			    
		switch (wParam) 
		{
		case VK_SPACE:
			spacecount=0;
			break;
		case 'Z':
			z=0;
			break;
		}
		break;
	
	case WM_DESTROY:			    
		int i;
		
		DeleteDC(mdc);
		DeleteDC(bufdc);
		for(i=0;i<5;i++)
			DeleteObject(hero[i]);
		for(i=0;i<6;i++)
			DeleteObject(bg[i]);
		for(i=0;i<3;i++)
			DeleteObject(mons[i]);
		for(i=0;i<3;i++)
			DeleteObject(boss[i]);
		DeleteObject(over);
		DeleteObject(keng);
		DeleteObject(shi);
		DeleteObject(jin);
		DeleteObject(bang);
		DeleteObject(fire);
		DeleteObject(win);
		ReleaseDC(hWnd,hdc);
			
		PostQuitMessage(0);
		break;
	default:						
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}