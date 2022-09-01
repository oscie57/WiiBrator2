#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	// Initialise the video system
	VIDEO_Init();

	// This function initialises the attached controllers
	WPAD_Init();

	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);

	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);

	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();


	// The console understands VT terminal escape codes
	// This positions the cursor on row 2, column 0
	// we can use variables for this with format codes too
	// e.g. printf ("\x1b[%d;%dH", row, column );
	printf("\x1b[2;0H");


	printf("   WiiBrator v2.0\n");
	printf("   (c)2022 oscie57 - oscie.net\n\n\n");
	printf("   DISCLAIMER: To avoid injury or aggravation of pre-existing conditions,\n   the vibrating Wii remote should not be used on swollen or inflamed\n   areas or skin lacerations. No medical claims are warranted or implied by\n   the use of this software. Exessive use of your vibrating Wii remote\n   will wear out the motor. Make sure your Wii remote is fully charged to\n   avoid disappointment. If the Wii remote gets unduly hot then stop and\n   allow it to cool down before restarting.\n\n\n");
	printf("   Press A to turn on/off rumble\n");
	printf("   Press B to enable/disable pulse mode\n\n");
	printf("   Press Home when you're done");

	bool rumbling = false;

	// Add pulse later
	//bool pulse = false;

	printf("\n\n\n\n   PULSE COMING SOON!   ");

	while(1) {

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
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
