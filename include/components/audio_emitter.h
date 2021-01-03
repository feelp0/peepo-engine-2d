#ifndef AUDIO_EMITTER_H
#define AUDIO_EMITTER_H
#include "SDL_mixer.h"

enum audio_extension{
    WAV,
    MP3,
}; typedef enum audio_extension audio_extension;

struct audio_emitter{
    Mix_Chunk* audio_wav;
    Mix_Music* audio_mp3;
    const char* path;
    int loops;
    audio_extension audio_ext;
    boolean __is_playing;
}; typedef struct audio_emitter audio_emitter;

void audio_emitter_new(component* comp, const char* path, int loops, audio_extension audio_ext);
void audio_destroy(component* comp);
void audio_update(component* comp);

#endif