/*

   Name:
   DRV_ALSA.C

   Description:
   Mikmod driver for output on ALSA

   Portability:  AlsaWare land.

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <alsa/asoundlib.h>
#include "mikmod.h"

#define DEFAULT_FRAGSIZE 2048

static snd_pcm_t* pcm;
static signed char *audiobuffer;
int alsa_div;

static BOOL Alsa_IsThere(void)
{
	return TRUE;
}

static int fragsize = DEFAULT_FRAGSIZE;

static BOOL Alsa_Init(void)
{
    int play_precision, play_stereo, play_rate;

    play_precision = (md_mode & DMODE_16BITS) ? 16 : 8;
    play_stereo = (md_mode & DMODE_STEREO) ? 1 : 0;
    play_rate = md_mixfreq;

    alsa_div = (play_stereo + 1) * (play_precision / 8);

    snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if(pcm == NULL) {
	    return 0;
    }

    snd_pcm_hw_params_t* params;
    snd_pcm_hw_params_malloc(&params);

    snd_pcm_hw_params_any(pcm, params);
    snd_pcm_hw_params_set_access(pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm, params, play_precision == 16 ? SND_PCM_FORMAT_S16 : SND_PCM_FORMAT_S8);
    snd_pcm_hw_params_set_channels(pcm, params, play_stereo + 1);
    snd_pcm_hw_params_set_rate(pcm, params, play_rate, 0);

    snd_pcm_hw_params(pcm, params);

    audiobuffer = (signed char *) malloc(fragsize);

    if (!VC_Init()) {
	return 0;
    }

    if (audiobuffer == NULL) {
	VC_Exit();
	return 0;
    }
    return 1;
}


static void Alsa_Exit(void)
{
    free(audiobuffer);
    VC_Exit();
}


static void Alsa_Update(void)
{
    VC_WriteBytes(audiobuffer, fragsize);
    snd_pcm_writei(pcm, audiobuffer, fragsize / alsa_div);
}


DRIVER drv_alsa =
{
    NULL,
    "ALSA",
    "ALAS Driver v1.0 - by Nishi",
    Alsa_IsThere,
    VC_SampleLoad,
    VC_SampleUnload,
    Alsa_Init,
    Alsa_Exit,
    VC_PlayStart,
    VC_PlayStop,
    Alsa_Update,
    VC_VoiceSetVolume,
    VC_VoiceSetFrequency,
    VC_VoiceSetPanning,
    VC_VoicePlay,
    MD_BlankFunction,
    MD_BlankFunction,
    MD_BlankFunction
};
