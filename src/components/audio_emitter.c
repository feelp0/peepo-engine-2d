#include "components.h"

void audio_emitter_new(gameObject* go, const char* path, int loops, audio_extension audio_ext){

    component* comp = __component_new(go);

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

    comp->init = audio_init;
    comp->update = audio_update;
    comp->destroy = audio_destroy;
    comp->on_enable = audio_on_enable;
    comp->on_disable = audio_on_disable;
    comp->type = AUDIO_EMITTER_T;
    comp->data = a;
}

void audio_destroy(component* comp){
    audio_emitter* a = (audio_emitter*)comp->data;
    Mix_FreeChunk(a->audio_wav);
    Mix_FreeMusic(a->audio_mp3);
    free(a);
}

void audio_init(component* comp){
    
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

void audio_on_enable(component* comp){

}

void audio_on_disable(component* comp){

}
