#pragma once
#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 

//Source texture cua cac doi tuong
#define SIMON_TEXTURE_PATH "Simon.png"

#define WINDOW_CLASS_NAME	"Castle Vania"
#define MAIN_WINDOW_TITLE	"Castle Vania"
#define FULLSCREEN	false

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH		256
#define SCREEN_HEIGHT		224

#define MAX_FRAME_RATE		60
#define FRAME_RATE			30

#define FPS					60
#define MAX_TIME_PER_FRAME	1000 / FPS
