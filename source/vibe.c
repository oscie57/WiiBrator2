#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;


int main(int argc, char **argv) {

	VIDEO_Init();
	
	WPAD_Init();
	PAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	printf("\x1b[2;0H");


	printf("\tWiiBrator v2.2\n");
	printf("\t(c)2022 oscie57, MethodOrMadness\n\n");
	printf("\tDISCLAIMER: To avoid injury or aggravation of pre-existing conditions,\n\tthe vibrating remote should not be used on swollen or inflamed areas\n\tor skin lacerations. No medical claims are warranted or implied by\n\tthe use of this software. Excessive use of your vibrating remote\n\twill wear out the motor.\n\n\n");
	printf("\tSupported controllers: Wii Remote, GameCube\n\n");
	printf("\tPress A to turn on/off rumble\n");
	printf("\tPress B to enable/disable pulse mode\n\n");
	printf("\tPress Home/Start when you're done\n\n\n");
	printf("\tPULSE COMING SOON!\n\n\n\n");
	printf("\thttps://github.com/oscie57/WiiBrator2");

	bool rumbling = false;
	bool grumbling = false;

	// Add pulse later
	//bool pulse = false;

	while(1) {

		PAD_ScanPads();
		WPAD_ScanPads();
		

		u32 pressed = WPAD_ButtonsDown(0);
		u32 gpressed = PAD_ButtonsDown(0);

		if ( gpressed & PAD_BUTTON_START ) {
			exit(0);
		};
		if ( gpressed & PAD_BUTTON_A ) {
			printf("GC A");
			if ( grumbling ) {
				PAD_ControlMotor(0, 0);
				grumbling = false;
			} else {
				PAD_ControlMotor(0, 1);
				grumbling = true;
			}
		};
		if ( gpressed & PAD_BUTTON_B ) {
			// Add pulse later
		};

		if ( pressed & WPAD_BUTTON_HOME ) {
			exit(0);
		};
		if ( pressed & WPAD_BUTTON_A ) {

			if (rumbling) {
				WPAD_Rumble(0, 0);
				rumbling = false;
			} else {
				WPAD_Rumble(0, 1);
				rumbling = true;
			}
		};
		if ( pressed & WPAD_BUTTON_B) {
			// Add pulse later
		};

		VIDEO_WaitVSync();
	}

	return 0;
}
