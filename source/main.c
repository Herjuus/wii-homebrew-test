#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static u32 *xfb;
static GXRModeObj *rmode;


void Initialise() {
  
	VIDEO_Init();
	WPAD_Init();
 
	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
 
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}


int main() {
 
	Initialise();
	
	printf("Hello World!\n");
	
	while(1) {
		WPAD_ScanPads();
                
		u16 buttonsDown = WPAD_ButtonsDown(0);
                
		if( buttonsDown & WPAD_BUTTON_B ) {
        	printf("Button B pressed\n");
		}

		if( buttonsDown & WPAD_BUTTON_A ) {
			printf("Button A pressed\n");
		}
                
		if( buttonsDown & WPAD_BUTTON_HOME ) {
			break;
		}
	}
	
	return 0;
}
