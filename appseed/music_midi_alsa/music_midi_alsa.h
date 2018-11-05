#pragma once


#include "app-veriwell/appseed/multimedia/multimedia/multimedia.h"
#include "app/appseed/core/user/user/user.h"
#include "seqlib.h"



#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA_LIBRARY)
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA  CLASS_DECL_IMPORT
#endif



#include "music_midi_alsa_translation.h"

#include "music_midi_alsa_midi_out.h"

#include "music_midi_alsa_sequence.h"

#include "player/music_midi_alsa_player.h"

#include "music_midi_alsa_out.h"

#include "music_midi_alsa_file.h"

#include "music_midi_alsa_sequence_thread.h"

#include "music_midi_alsa_midi.h"

#include "music_midi_alsa_factory_exchange.h"
