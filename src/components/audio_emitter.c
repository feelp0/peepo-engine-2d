#include "components.h"

void audio_emitter_new(component* comp, const char* path, int loops, audio_extension audio_ext){
    audio_emitter* a = (audio_emitter*)malloc(sizeof(audio_emitter));
    a->loops = loops;
    a->path = path;
    a->__is_playing = false;
    a->audio_ext = audio_ext;

    switch (audio_ext)
    {
    case WAV:
        a->audio_wav = Mix_LoadWAV(path);
        break;
    case MP3:
        a->audio_mp3 = Mix_LoadMUS(path);
        break;
    default:
        break;
    }

    comp->update = audio_update;
    comp->type = AUDIO_EMITTER_T;
    comp->data = a;
}

void audio_destroy(component* comp){
    audio_emitter* a = (audio_emitter*)comp->data;
    Mix_FreeChunk(a->audio_wav);
    Mix_FreeMusic(a->audio_mp3);
    free(a);
}

void audio_update(component* comp){
    audio_emitter* a = (audio_emitter*)comp->data;
    int p = Mix_PlayingMusic();
    a->__is_playing = p == 1 ? true : false;
    if(!a->__is_playing){
        switch (a->audio_ext)
        {
            case WAV:
                Mix_PlayChannel(-1, a->audio_wav, a->loops);
                a->__is_playing = true;
                break;
            case MP3:
                Mix_PlayMusic(a->audio_mp3, a->loops);
                break;
            default:
                break;
        }
    }
}
