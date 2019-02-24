
#include "stdafx.h"
#include <stdio.h>
//#include <string.h>

HINSTANCE hInst;
HBITMAP hero[5],bg[6],mons[3],boss[3],over,keng,shi,jin,bang,fire,bss;
HDC		hdc,mdc,bufdc,hDC;
HWND	hWnd;
DWORD	tPre,tNow;
int		dir,dim,x,y;
int		x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin=1200,num=0,num1=0,num2=0,num3=0,num4=0,num5=0;
int spacecount=0,bosscount=0,kaichangcount=0,jincount=0,paicount=0;
int yemian=1;
int i=0;
int ren=1,guai=1,bos=1,sixiang=0,guaizusu=0,juli=0,pai=0;
int guaizu[40]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int g=3,vx=5,vy=30;
int xshi=700,yshi=0;
int sshi=0;
char s1[12]="距离:",s2[6]="";
char *kaichang="为了拯救公主，英雄踏上了死亡之旅……";
FILE *fp;
char str[80];
char jinb1[12]="金币:",jinb2[6]="";
char strpai[100][20]={""};
int intpai[100]={0};
int num5zu[14]={0,0,1,1,2,2,3,3,4,4,5,5,6};

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
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
				guai=guaizu[guaizusu%40];//怪出现时间
				if (guaizusu%40 == 0)
				{
					x1=1024;
				}
				MyPaint(hdc);
			}
			else if (tNow-tPre >= 100 && guai==1)
				MyPaint(hdc);
			if (yemian == 1 && pai==1)//输出排行榜
			{
				fp=fopen("排行榜.txt","r");
				if (fp==NULL)
				{
					SetTextColor(hdc,RGB(255,0,0)); //设置文字颜色
					SetBkColor(hdc,RGB(0,255,0)); //设置文本背景色
					SetBkMode (hdc,TRANSPARENT);//设备背景色模式为透明与不透明 TRANSPARENT和OPAQUE
					HFONT hfont;
					LOGFONT font;
					ZeroMemory(&font, sizeof(LOGFONT));
					font.lfHeight = 50;
					font.lfQuality = PROOF_QUALITY;
					sprintf(font.lfFaceName, TEXT("微软雅黑"));
					hfont = CreateFontIndirect(&font);
					SelectObject(hdc, hfont);
					TextOut(hdc, 800, 0, "无信息" ,7);
				}
				else
				{
					TextOut(hdc, 800, 0, "距离   金币" ,12);
					while (!feof(fp))
					{
						fgets(str,80,fp);//juli=atoi(str);itoa(juli, str, 10);
						SetTextColor(hdc,RGB(255,0,0)); //设置文字颜色
						SetBkColor(hdc,RGB(0,255,0)); //设置文本背景色
						SetBkMode (hdc,TRANSPARENT);//设备背景色模式为透明与不透明 TRANSPARENT和OPAQUE
						HFONT hfont;
						LOGFONT font;
						ZeroMemory(&font, sizeof(LOGFONT));
						font.lfHeight = 50;
						font.lfQuality = PROOF_QUALITY;
						sprintf(font.lfFaceName, TEXT("微软雅黑"));
						hfont = CreateFontIndirect(&font);
						SelectObject(hdc, hfont);
						if(!feof(fp))//避免最后一行多次输出
							TextOut(hdc, 800, 50+paicount*50, str ,strlen(str));
						paicount++;
					}
					paicount=0;
					fclose(fp);
				}
			}
			if (yemian==0 )//输出距离、金币
			{
				SetTextColor(hdc,RGB(0,255,0)); //设置文字颜色
				SetBkMode (hdc,TRANSPARENT);//设备背景色模式为透明与不透明 TRANSPARENT和OPAQUE
				HFONT hfont;
				LOGFONT font;
				ZeroMemory(&font, sizeof(LOGFONT));
				font.lfHeight = 50;
				font.lfQuality = PROOF_QUALITY;
				sprintf(font.lfFaceName, TEXT("微软雅黑"));
				hfont = CreateFontIndirect(&font);
				SelectObject(hdc, hfont);
				TextOut(hdc,1000, 100, " " ,0);
			}
			if (yemian==2 || yemian==4 || yemian==5 && pai==0)//输出距离、金币
			{
				SetTextColor(hdc,RGB(0,0,255)); //设置文字颜色
				SetBkColor(hdc,RGB(0,255,0)); //设置文本背景色
				SetBkMode (hdc,TRANSPARENT);//设备背景色模式为透明与不透明 TRANSPARENT和OPAQUE
				HFONT hfont;
				LOGFONT font;
				ZeroMemory(&font, sizeof(LOGFONT));
				font.lfHeight = 50;
				font.lfQuality = PROOF_QUALITY;
				wsprintf(font.lfFaceName, TEXT("微软雅黑"));
				hfont = CreateFontIndirect(&font);
				SelectObject(hdc, hfont);
				itoa(juli, s2, 10);
				s1[5]='\0';
				strcat(s1,s2);
				TextOut(hdc, 850, 0, s1 ,strlen(s1));
				itoa(jincount, jinb2, 10);
				jinb1[5]='\0';
				strcat(jinb1,jinb2);
				TextOut(hdc, 850, 50, jinb1 ,strlen(jinb1));
			}
		}
    }

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "DeathRoad" ,WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
	bg[0] = (HBITMAP)LoadImage(NULL,"bg0.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[1] = (HBITMAP)LoadImage(NULL,"bg1.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[2] = (HBITMAP)LoadImage(NULL,"bg2.bmp",IMAGE_BITMAP,1024,544,LR_LOADFROMFILE);
	bg[3] = (HBITMAP)LoadImage(NULL,"bg3.bmp",IMAGE_BITMAP,1024,728,LR_LOADFROMFILE);
	bg[4] = (HBITMAP)LoadImage(NULL,"bg4.bmp",IMAGE_BITMAP,1024,608,LR_LOADFROMFILE);
	bg[5] = (HBITMAP)LoadImage(NULL,"bg5.bmp",IMAGE_BITMAP,1024,576,LR_LOADFROMFILE);
	over = (HBITMAP)LoadImage(NULL,"over.bmp",IMAGE_BITMAP,1024,1088,LR_LOADFROMFILE);
	keng = (HBITMAP)LoadImage(NULL,"keng.bmp",IMAGE_BITMAP,120,200,LR_LOADFROMFILE);
	shi = (HBITMAP)LoadImage(NULL,"stone.bmp",IMAGE_BITMAP,143,200,LR_LOADFROMFILE);
	//fire = (HBITMAP)LoadImage(NULL,"fire.bmp",IMAGE_BITMAP,1458,308,LR_LOADFROMFILE);
	fire = (HBITMAP)LoadImage(NULL,"fire.bmp",IMAGE_BITMAP,729,154,LR_LOADFROMFILE);
	jin = (HBITMAP)LoadImage(NULL,"jinbi.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);
	bang = (HBITMAP)LoadImage(NULL,"bang.bmp",IMAGE_BITMAP,188,90,LR_LOADFROMFILE);
	bss = (HBITMAP)LoadImage(NULL,"bss.bmp",IMAGE_BITMAP,400,400,LR_LOADFROMFILE);
	
	MyPaint(hdc);

	return TRUE;
}

void MyPaint(HDC hdc)
{
	int w=137,h=101;	

	if (yemian==1)//开始页
	{
		SelectObject(bufdc,bg[1]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		SelectObject(bufdc,bang);//排行榜
		BitBlt(mdc,50,242,188,90,bufdc,0,0,SRCCOPY);	
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
	}
	if (yemian==0)//对白页
	{
		SelectObject(bufdc,bg[2]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		tPre = GetTickCount(); 
 	}

	if (yemian == 6)//boss页
	{
		//	
		if (((x>x3-90) || (x>x4-40-num5zu[num5]*18 && x<x4+50 && y>200)) && bos==1&&(dir==1||dir==3))
		{
			ren=0;
		}
		if (((x>x3-90) || (x>x4+40-num5zu[num5]*18 && x<x4+100 && y>200)) && bos==1&&(dir==0||dir==2))
		{
			ren=0;
		}

		if (bosscount == 5)
		{
			bos=0;
		}

		SelectObject(bufdc,bg[2]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);

		SelectObject(bufdc,bss);
		BitBlt(mdc,300,0,400,200,bufdc,0,200,SRCAND);
		BitBlt(mdc,300,0,400,200,bufdc,0,0,SRCPAINT);

		SelectObject(bufdc,bg[3]);//树
		BitBlt(mdc,0,150,1024,364,bufdc,0,364,SRCAND);
		BitBlt(mdc,0,150,1024,364,bufdc,0,0,SRCPAINT);

		if (bos == 1)
		{		
			SelectObject(bufdc,boss[0]);//boss
	    	BitBlt(mdc,x3,170,387,241,bufdc,num4*387,241,SRCAND);
	    	BitBlt(mdc,x3,170,387,241,bufdc,num4*387,0,SRCPAINT);
	    	BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);

            if (x3 == 600)
            {
				if(x4>530)x4=530;				
				SelectObject(bufdc,fire);//喷火
				BitBlt(mdc,x4,247,121,77,bufdc,num5zu[num5]*121,77,SRCAND);
				BitBlt(mdc,x4,247,121,77,bufdc,num5zu[num5]*121,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
            }
			
			num4++;
			if (num4==4)
			{
				num4=0;
			}	
			num5++;
			if (num5zu[num5]==6)
			{
				num5=0;
			}	
		}

		tPre = GetTickCount(); 
		
// 活人特有
		if (ren==1)
		{
			if (dir<2)
			{
				SelectObject(bufdc,hero[dir]);//人
				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[dir+1]);//出招
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
			
			x4-=10;
			if (x4 < -400)
			{
				x4=530;
			}
			num++;
			if(num == 8)
				num = 0;
		}
// 死人特有
		else
		{
			if (num2<6)
			{
				SelectObject(bufdc,hero[2]);//死人
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

			num2++;
		}
	}

	if (yemian==2)
	{
		SelectObject(bufdc,bg[2]);//背景
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
	}

	if (yemian==4)
	{
		SelectObject(bufdc,bg[4]);//背景
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
	}

	if (yemian==5)
	{
		SelectObject(bufdc,bg[5]);//背景
		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
	}

	if (yemian==2 || yemian==4 || yemian==5)//游戏页
	{
		if (juli >= 200)
		{
			yemian=6;
		}
		if(x>x1-110 && x<x1+80 && y>270 && guai==1)
		{
			ren=0;
		}
		//坑
		if(x>xkeng-100 && x<xkeng+50 && y>279)
		{
			x=xkeng-20;
			vy+=g;
			y+=vy;
			ren=0;
		}
		//坠物
		if (x>xshi-100 && x<xshi+50 && yshi>200 && y>279)
		{
			ren=0;
			sshi=2;
			if(yshi<290) yshi=280;
		}
		//金币
		if (x>xjin-150 && x<xjin+50 && y<250)
		{
			jincount++;
			xjin=1400;
		}

//共有
// 		SelectObject(bufdc,bg[2]);//背景
// 		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
// 		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);

		SelectObject(bufdc,bg[3]);//树
		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,364,SRCAND);
		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,364,SRCAND);
		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,0,SRCPAINT);
		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,0,SRCPAINT);
		if (guai==1)
		{
			SelectObject(bufdc,mons[dim]);//怪
			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,157,SRCAND);
			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,0,SRCPAINT);
		}	
		else if(dim == 2)
		{
			SelectObject(bufdc,mons[2]);//死怪
			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,175,SRCAND);
			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,0,SRCPAINT);
			num3++;
			if (num3==5)
			{
				dim=0;
				num3=0;
			}
		}
		SelectObject(bufdc,keng);//坑
		BitBlt(mdc,xkeng,372,120,200,bufdc,0,0,SRCCOPY);
		SelectObject(bufdc,jin);//金币
		BitBlt(mdc,xjin,200,20,20,bufdc,0,0,SRCCOPY);
		if (sshi==1)//坠物空中
		{
			SelectObject(bufdc,shi);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			yshi+=50;
			if (yshi>300)
				yshi=300;
		}
		if (sshi==2)//坠物落地
		{
			SelectObject(bufdc,shi);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
		}
		tPre = GetTickCount(); 
		
// 活人特有
		if (ren==1)
		{
			if (dir<2)
			{
				SelectObject(bufdc,hero[dir]);//人
				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
			}
			else
			{
				SelectObject(bufdc,hero[dir+1]);//出招
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
//坠物
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

			x1 -= 15;//怪	
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
// 				if(xkeng < 0)
// 					xkeng = 1024;

				xjin -=10;
				if(xjin < 0)
					xjin = 1200;
				break;
			case 0:
				x0 += 2;		
				if(x0 > 1024)
					x0 = 0;
				
				x2 += 10;juli-=1;		
				if(x2 > 1024)
					x2 = 0;

				xkeng += 10;		
// 				if(xkeng > 1024)
// 					xkeng = 0;

				xjin+=10;
				break;
			}
			
			num++;
			if(num == 8)
				num = 0;
			num1++;
			if(num1 == 7)
				num1 = 0;
		}
// 死人特有
		else
		{
			if (num2<6)
			{
				SelectObject(bufdc,hero[2]);//死人
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
			SelectObject(bufdc,over);//开始
			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
			//SelectObject(bufdc,paihangbang);//排行榜
			//BitBlt(mdc,x,200,125,37,bufdc,0,0,SRCCOPY);
			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);

			num2++;
		}
	}
	
	if (yemian==3)
	{
		SelectObject(bufdc,bg[0]);
		BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCCOPY);		
		BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
	}

// 	if (yemian==4)//游戏页
// 	{
// 		if (juli >= 200)
// 		{
// 			yemian=6;
// 		}
// 		if(x>x1-110 && x<x1+80 && y>270 && guai==1)
// 		{
// 			ren=0;
// 		}
// 		//坑
// 		if(x>xkeng-100 && x<xkeng+50 && y>279)
// 		{
// 			x=xkeng-20;
// 			vy+=g;
// 			y+=vy;
// 			ren=0;
// 		}
// 		//坠物
// 		if (x>xshi-100 && x<xshi+50 && yshi>200 && y>279)
// 		{
// 			ren=0;
// 			sshi=2;
// 			if(yshi<290) yshi=280;
// 		}
// 		//金币
// 		if (x>xjin-150 && x<xjin+50 && y<250)
// 		{
// 			jincount++;
// 			xjin=1400;
// 		}
// 
// //共有
// 		SelectObject(bufdc,bg[4]);//背景
// 		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
// 		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
// 
// 		SelectObject(bufdc,bg[3]);//树
// 		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,364,SRCAND);
// 		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,364,SRCAND);
// 		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,0,SRCPAINT);
// 		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,0,SRCPAINT);
// 		if (guai==1)
// 		{
// 			SelectObject(bufdc,mons[dim]);//怪
// 			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,157,SRCAND);
// 			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,0,SRCPAINT);
// 		}	
// 		else if(dim == 2)
// 		{
// 			SelectObject(bufdc,mons[2]);//死怪
// 			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,175,SRCAND);
// 			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,0,SRCPAINT);
// 			num3++;
// 			if (num3==5)
// 			{
// 				dim=0;
// 				num3=0;
// 			}
// 		}
// 		SelectObject(bufdc,keng);//坑
// 		BitBlt(mdc,xkeng,372,120,200,bufdc,0,0,SRCCOPY);
// 		SelectObject(bufdc,jin);//金币
// 		BitBlt(mdc,xjin,200,20,20,bufdc,0,0,SRCCOPY);
// 		if (sshi==1)//坠物空中
// 		{
// 			SelectObject(bufdc,shi);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			yshi+=50;
// 			if (yshi>300)
// 				yshi=300;
// 		}
// 		if (sshi==2)//坠物落地
// 		{
// 			SelectObject(bufdc,shi);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 		}
// 		tPre = GetTickCount(); 
// 		
// // 活人特有
// 		if (ren==1)
// 		{
// 			if (dir<2)
// 			{
// 				SelectObject(bufdc,hero[dir]);//人
// 				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
// 				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			else
// 			{
// 				SelectObject(bufdc,hero[dir+1]);//出招   
// 				BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,112,SRCAND);
// 			    BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 				num2++;
// 				if (num2==6)
// 				{
// 					dir=sixiang;
// 					num2=0;
// 				}
// 			}
// //坠物
// 			if (x>600 && x<700 && sshi==0)
// 			{
// 				sshi=1;
// 			}
// 			if (sshi==1 && yshi==300)
// 			{
// 				sshi=2;
// 			}
// 			if (sshi==2)
// 			{
// 				if(dir==0)
// 					xshi+=10;
// 				if (dir==1)
// 					xshi-=10;
// 			}
// 			if (xshi<-200 || xshi>1224)
// 			{
// 				sshi=0;
// 				xshi=700;
// 				yshi=0;
// 			}
// 
// 			x1 -= 15;//怪	
// 			if(x1<-120)
// 				x1 = 1024;
// 
// 			switch (dir)
// 			{
// 			case 1:
// 				x0 -= 2;		
// 				if(x0 < 0)
// 					x0 = 1024;
// 				
// 				x2 -= 10;
// 				juli+=1;	
// 				if(x2 < 0)
// 					x2 = 1024;
// 
// 				xkeng -= 10;		
// // 				if(xkeng < 0)
// // 					xkeng = 1024;
// 
// 				xjin -=10;
// 				if(xjin < 0)
// 					xjin = 1200;
// 				break;
// 			case 0:
// 				x0 += 2;		
// 				if(x0 > 1024)
// 					x0 = 0;
// 				
// 				x2 += 10;juli-=1;		
// 				if(x2 > 1024)
// 					x2 = 0;
// 
// 				xkeng += 10;		
// // 				if(xkeng > 1024)
// // 					xkeng = 0;
// 
// 				xjin+=10;
// 				break;
// 			}
// 			
// 			num++;
// 			if(num == 8)
// 				num = 0;
// 			num1++;
// 			if(num1 == 7)
// 				num1 = 0;
// 		}
// // 死人特有
// 		else
// 		{
// 			if (num2<6)
// 			{
// 				SelectObject(bufdc,hero[2]);//死人
// 				BitBlt(mdc,x,y,145,122,bufdc,num2*145,122,SRCAND);
// 				BitBlt(mdc,x,y,145,122,bufdc,num2*145,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			else
// 			{
// 				SelectObject(bufdc,hero[2]);
// 				BitBlt(mdc,x,y,145,122,bufdc,5*145,122,SRCAND);
// 				BitBlt(mdc,x,y,145,122,bufdc,5*145,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			SelectObject(bufdc,over);//开始
// 			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
// 			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 
// 			num2++;
// 		}
// 	}
// 
// 	if (yemian==5)//游戏页
// 	{
// 		if (juli >= 200)
// 		{
// 			yemian=6;
// 		}
// 		if(x>x1-110 && x<x1+80 && y>270 && guai==1)
// 		{
// 			ren=0;
// 		}
// 		//坑
// 		if(x>xkeng-100 && x<xkeng+50 && y>279)
// 		{
// 			x=xkeng-20;
// 			vy+=g;
// 			y+=vy;
// 			ren=0;
// 		}
// 		//坠物
// 		if (x>xshi-100 && x<xshi+50 && yshi>200 && y>279)
// 		{
// 			ren=0;
// 			sshi=2;
// 			if(yshi<290) yshi=280;
// 		}
// 		//金币
// 		if (x>xjin-150 && x<xjin+50 && y<250)
// 		{
// 			jincount++;
// 			xjin=1400;
// 		}
// 
// //共有
// 		SelectObject(bufdc,bg[5]);//背景
// 		BitBlt(mdc,0,0,x0,544,bufdc,1024-x0,0,SRCCOPY);
// 		BitBlt(mdc,x0,0,1024-x0,544,bufdc,0,0,SRCCOPY);
// 
// 		SelectObject(bufdc,bg[3]);//树
// 		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,364,SRCAND);
// 		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,364,SRCAND);
// 		BitBlt(mdc,0,150,x2,364,bufdc,1024-x2,0,SRCPAINT);
// 		BitBlt(mdc,x2,150,1024-x2,364,bufdc,0,0,SRCPAINT);
// 		if (guai==1)
// 		{
// 			SelectObject(bufdc,mons[dim]);//怪
// 			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,157,SRCAND);
// 			BitBlt(mdc,x1,230,121,157,bufdc,num1*121,0,SRCPAINT);
// 		}	
// 		else if(dim == 2)
// 		{
// 			SelectObject(bufdc,mons[2]);//死怪
// 			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,175,SRCAND);
// 			BitBlt(mdc,x1,230,175,175,bufdc,num3*175,0,SRCPAINT);
// 			num3++;
// 			if (num3==5)
// 			{
// 				dim=0;
// 				num3=0;
// 			}
// 		}
// 		SelectObject(bufdc,keng);//坑
// 		BitBlt(mdc,xkeng,372,120,200,bufdc,0,0,SRCCOPY);
// 		SelectObject(bufdc,jin);//金币
// 		BitBlt(mdc,xjin,200,20,20,bufdc,0,0,SRCCOPY);
// 		if (sshi==1)//坠物空中
// 		{
// 			SelectObject(bufdc,shi);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			yshi+=50;
// 			if (yshi>300)
// 				yshi=300;
// 		}
// 		if (sshi==2)//坠物落地
// 		{
// 			SelectObject(bufdc,shi);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,100,SRCAND);
// 			BitBlt(mdc,xshi,yshi,143,100,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 		}
// 		tPre = GetTickCount(); 
// 		
// // 活人特有
// 		if (ren==1)
// 		{
// 			if (dir<2)
// 			{
// 				SelectObject(bufdc,hero[dir]);//人
// 				BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
// 				BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			else
// 			{
// 				SelectObject(bufdc,hero[dir+1]);//出招
// 				BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,112,SRCAND);
// 			    BitBlt(mdc,x,y-10,182,112,bufdc,num2*182,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 				num2++;
// 				if (num2==6)
// 				{
// 					dir=sixiang;
// 					num2=0;
// 				}
// 			}
// //坠物
// 			if (x>600 && x<700 && sshi==0)
// 			{
// 				sshi=1;
// 			}
// 			if (sshi==1 && yshi==300)
// 			{
// 				sshi=2;
// 			}
// 			if (sshi==2)
// 			{
// 				if(dir==0)
// 					xshi+=10;
// 				if (dir==1)
// 					xshi-=10;
// 			}
// 			if (xshi<-200 || xshi>1224)
// 			{
// 				sshi=0;
// 				xshi=700;
// 				yshi=0;
// 			}
// 
// 			x1 -= 15;//怪	
// 			if(x1<-120)
// 				x1 = 1024;
// 
// 			switch (dir)
// 			{
// 			case 1:
// 				x0 -= 2;		
// 				if(x0 < 0)
// 					x0 = 1024;
// 				
// 				x2 -= 10;
// 				juli+=1;	
// 				if(x2 < 0)
// 					x2 = 1024;
// 
// 				xkeng -= 10;		
// // 				if(xkeng < 0)
// // 					xkeng = 1024;
// 
// 				xjin -=10;
// 				if(xjin < 0)
// 					xjin = 1200;
// 				break;
// 			case 0:
// 				x0 += 2;		
// 				if(x0 > 1024)
// 					x0 = 0;
// 				
// 				x2 += 10;juli-=1;		
// 				if(x2 > 1024)
// 					x2 = 0;
// 
// 				xkeng += 10;		
// // 				if(xkeng > 1024)
// // 					xkeng = 0;
// 
// 				xjin+=10;
// 				break;
// 			}
// 			
// 			num++;
// 			if(num == 8)
// 				num = 0;
// 			num1++;
// 			if(num1 == 7)
// 				num1 = 0;
// 		}
// // 死人特有
// 		else
// 		{
// 			if (num2<6)
// 			{
// 				SelectObject(bufdc,hero[2]);//死人
// 				BitBlt(mdc,x,y,145,122,bufdc,num2*145,122,SRCAND);
// 				BitBlt(mdc,x,y,145,122,bufdc,num2*145,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			else
// 			{
// 				SelectObject(bufdc,hero[2]);
// 				BitBlt(mdc,x,y,145,122,bufdc,5*145,122,SRCAND);
// 				BitBlt(mdc,x,y,145,122,bufdc,5*145,0,SRCPAINT);
// 				BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 			}
// 			SelectObject(bufdc,over);//开始
// 			BitBlt(mdc,0,0,1024,544,bufdc,0,544,SRCAND);
// 			BitBlt(mdc,0,0,1024,544,bufdc,0,0,SRCPAINT);
// 			BitBlt(hdc,0,0,1024,544,mdc,0,0,SRCCOPY);
// 
// 			num2++;
// 		}
// 	}

	if (yemian==0 && kaichangcount<37)//对白
	{
		SetTextColor(hdc,RGB(255,255,255)); //设置文字颜色
		SetBkMode (hdc,TRANSPARENT);//设备背景色模式为透明与不透明 TRANSPARENT和OPAQUE
		HFONT hfont;
		LOGFONT font;
		ZeroMemory(&font, sizeof(LOGFONT));
		font.lfHeight = 50;
		font.lfQuality = PROOF_QUALITY;
		sprintf(font.lfFaceName, TEXT("微软雅黑"));
		hfont = CreateFontIndirect(&font);
		SelectObject(hdc, hfont);
		TextOut(hdc, 100, 100, kaichang ,kaichangcount);
		kaichangcount+=1;

		if(kaichangcount==37)
		{
			yemian=2;
			kaichangcount=0;
		}
	}
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		switch (yemian)
		{
		case 1:
			if(WORD LOWORD(lParam)>300 && WORD LOWORD(lParam)<488 && WORD HIWORD(lParam)>240 && WORD HIWORD(lParam)<330)//开始
			{
				yemian=3;
				//pai=0;
				x0=1024,x1=1024,x2=1024,x3=1024,x4=1000,xkeng=2024,xjin=1200,num=0,num1=0,num2=0,num3=0,num4=0;
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
			}
			else if(WORD LOWORD(lParam)>50 && WORD LOWORD(lParam)<240 && WORD HIWORD(lParam)>242 && WORD HIWORD(lParam)<332)//排行
				pai=1;
			break;
		case 6:
			if(ren==0 && WORD LOWORD(lParam)>0 && WORD LOWORD(lParam)<1024 && WORD HIWORD(lParam)>0 && WORD HIWORD(lParam)<544)//开始
			{
				yemian = 1;
			}
		case 2:
			if(ren==0 && WORD LOWORD(lParam)>0 && WORD LOWORD(lParam)<1024 && WORD HIWORD(lParam)>0 && WORD HIWORD(lParam)<544)//开始
			{
				yemian = 1;
				if (pai==0)
				{
					fp=fopen("排行榜.txt","at");
					itoa(juli, str, 10);
					itoa(jincount, jinb2, 10);
					int j=strlen(str);
					for (i=0;i<8-j;i++)
					{
						strcat(str," ");
					}
					strcat(str,jinb2);
					strcat(str,"\n");
					fputs(str,fp);
					fclose(fp);
					
					fp=fopen("排行榜.txt","r");
					i=0;
					while (!feof(fp))
					{
						fgets(strpai[i],80,fp);
						intpai[i]=atoi(strpai[i]);
						i++;
					}
					fclose(fp);
					
					int l=i;
					int k;
					char temp[20]="";
					for (i=i-1;i>0;i--)
					{
						for (int j=i;j>0;j--)
						{
							if (intpai[j]>intpai[j-1])
							{
								k=intpai[j];
								intpai[j-1]=intpai[j];
								intpai[j]=k;
								strcpy(temp,strpai[j]); strcpy(strpai[j],strpai[j-1]); strcpy(strpai[j-1],temp);
							}
						}
					}
					
					fp=fopen("排行榜.txt","w");
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
			}				
			else if(WORD LOWORD(lParam)>60 && WORD LOWORD(lParam)<380 && WORD HIWORD(lParam)>260 && WORD HIWORD(lParam)<440)		
				yemian=4;
			else if(WORD LOWORD(lParam)>420 && WORD LOWORD(lParam)<740 && WORD HIWORD(lParam)>40 && WORD HIWORD(lParam)<220)
				yemian=5;
			break;

		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:          
			PostQuitMessage( 0 );
			break;
		case VK_LEFT:
			if (yemian==2 || yemian==4 || yemian==5 || yemian==6 && ren==1)
			{
				switch(dir)
				{
				case 0:
					x -= 20;juli-=2;
					break;
				case 1:
					x -= 20;juli-=2;
					break;
				}
				if(x < 0)
					x = 0;
				dir = 0;
			}
			break;
			
		case VK_RIGHT:
			if (yemian==2 || yemian==4 || yemian==5 || yemian==6 && ren==1)
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
			break;
				
		case VK_SPACE:
			if (yemian==2 || yemian==4 || yemian==5 || yemian==6 && spacecount==0 && ren==1)
			{
				spacecount=1;

				switch (dir)
				{
				case 0:
					for (i=0;i<10;i++)
					{
						x -= vx;x1+=10;		
						y -= vy;								
						vy -= g;
						Sleep(20);
						MyPaint(hdc);
						if(x < 0)
					       x = 0;
					}
					
					for (i=0;i<10;i++)
					{
						x -= vx;x1+=10;								
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

		case 'X':
			if (yemian==2 || yemian==4 || yemian==5 || yemian==6 && ren==1)
			{
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
				}

				if(bos==1 && x>400)
				{
					bosscount++;
				}
			}
			break;
		}
		break;
			
	case WM_KEYUP:			    
		switch (wParam) 
		{
		case VK_SPACE:
			if (spacecount==1)
			{
				spacecount=0;
			}
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
		ReleaseDC(hWnd,hdc);
			
		PostQuitMessage(0);
		break;
	default:						
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}