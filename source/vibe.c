#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;


int main(int argc, char **argv) {

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
	printf("\x1b[2;0H");


	printf("   WiiBrator v2.0\n");
	printf("   (c)2022 oscie57, MethodOrMadness\n\n\n");
	printf("   DISCLAIMER: To avoid injury or aggravation of pre-existing conditions,\n   the vibrating Wii remote should not be used on swollen or inflamed\n   areas or skin lacerations. No medical claims are warranted or implied by\n   the use of this software. Exessive use of your vibrating Wii remote\n   will wear out the motor. Make sure your Wii remote is fully charged to\n   avoid disappointment. If the Wii remote gets unduly hot then stop and\n   allow it to cool down before restarting.\n\n\n");
	printf("   Press A to turn on/off rumble\n");
	printf("   Press B to enable/disable pulse mode\n\n");
	printf("   Press Home when you're done\n\n\n");
	printf("   PULSE COMING SOON!\n\n\n\n");
	printf("   https://github.com/oscie57/WiiBrator2");

	bool rumbling = false;

	// Add pulse later
	//bool pulse = false;

	while(1) {

		WPAD_ScanPads();

		u32 pressed = WPAD_ButtonsDown(0);

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
