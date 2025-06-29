/*

   Name:
   DRV_MA.C

   Description:
   Mikmod driver for output on miniaudio

   Portability:  Probably everywhere

 */
#include <stdlib.h>
#include <string.h>
#include "stb_ds.h"
#include "miniaudio.h"
#include "mikmod.h"

#define DEFAULT_FRAGSIZE 2048

typedef struct buffer {
	unsigned char* buffer;
	int remain;
	int shift;
} buffer_t;

static ma_device device;
static buffer_t* queue = NULL;
static int madrv_div;

static BOOL MA_IsThere(void)
{
	return TRUE; /* TODO */
}

static void data(ma_device* device, void* out, const void* input, ma_uint32 frame){
	int wanted = frame * madrv_div;
	int shift = 0;
	while(wanted > 0 && arrlen(queue) > 0){
		int canget = wanted > queue[0].remain ? queue[0].remain : wanted;

		memcpy((unsigned char*)out + shift, queue[0].buffer + queue[0].shift, canget);
		if(!(md_mode & DMODE_16BITS)){
			int i;
			unsigned char* u8 = (unsigned char*)out + shift;
			signed char* s8 = (signed char*)out + shift;
			/* s8 -> u8 */
			for(i = 0; i < canget; i++){
				u8[i] = (int)s8[i] + 128;
			}
		}

		shift += canget;
		wanted -= canget;
		queue[0].remain -= canget;
		queue[0].shift += canget;
		if(queue[0].remain == 0){
			free(queue[0].buffer);
			arrdel(queue, 0);
		}
	}
	(void)input;
}

static int fragsize = DEFAULT_FRAGSIZE;

static BOOL MA_Init(void)
{
    int play_precision, play_stereo, play_rate;
    ma_device_config config;

    play_precision = (md_mode & DMODE_16BITS) ? 16 : 8;
    play_stereo = (md_mode & DMODE_STEREO) ? 2 : 1;
    play_rate = md_mixfreq;

    madrv_div = play_stereo * (play_precision / 8);

    config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = play_precision == 16 ? ma_format_s16 : ma_format_u8;
    config.playback.channels = play_stereo;
    config.sampleRate = play_rate;
    config.dataCallback = data;

    if(ma_device_init(NULL, &config, &device) != MA_SUCCESS){
	    return 0;
    }

    if (!VC_Init()) {
	ma_device_uninit(&device);
	return 0;
    }

    ma_device_start(&device);
    return 1;
}


static void MA_Exit(void)
{
    ma_device_stop(&device);
    ma_device_uninit(&device);
    VC_Exit();
}


static void MA_Update(void)
{
    buffer_t buf;
    buf.buffer = malloc(fragsize);
    buf.remain = fragsize;
    buf.shift = 0;
    VC_WriteBytes(buf.buffer, fragsize);
    arrput(queue, buf);
}


DRIVER drv_ma =
{
    NULL,
    "Miniaudio",
    "Miniaudio Driver v1.0 - by Nishi",
    MA_IsThere,
    VC_SampleLoad,
    VC_SampleUnload,
    MA_Init,
    MA_Exit,
    VC_PlayStart,
    VC_PlayStop,
    MA_Update,
    VC_VoiceSetVolume,
    VC_VoiceSetFrequency,
    VC_VoiceSetPanning,
    VC_VoicePlay,
    MD_BlankFunction,
    MD_BlankFunction,
    MD_BlankFunction
};
