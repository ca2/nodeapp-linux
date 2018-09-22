#pragma once


#include "app-core/appseed/multimedia/multimedia/multimedia.h"
#include <alsa/asoundlib.h>
// Ubuntu libasound2-dev


#if defined(_AUDIO_ALSA_LIBRARY)
   #define CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_IMPORT
#endif


#include "audio_alsa_translation.h"


#include "audio_alsa_snd_pcm.h"


#include "audio_alsa_wave_out.h"
#include "audio_alsa_wave_in.h"


#include "audio_alsa_factory_exchange.h"
