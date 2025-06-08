#include "sound.h"
#include <SDL.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define PI 3.14159265f

typedef struct {
    float frequency;
    float phase;
    float phase_increment;
} BeepContext;

typedef struct {
    int frequency;
    int duration_ms;
} BeepArgs;

static void audio_callback(void *userdata, Uint8 *stream, int len) {
    BeepContext *ctx = (BeepContext *)userdata;

    for (int i = 0; i < len; ++i) {
        float sample = sinf(ctx->phase * 2.0f * PI);
        stream[i] = (Uint8)((sample * 127.5f) + 127.5f);

        ctx->phase += ctx->phase_increment;
        if (ctx->phase >= 1.0f)
            ctx->phase -= 1.0f;
    }
}

static void* beep_thread(void* arg) {
    BeepArgs *args = (BeepArgs*)arg;

    if (args->frequency < 20 || args->frequency > 20000) {
        free(arg);
        return NULL;
    }

    SDL_InitSubSystem(SDL_INIT_AUDIO);

    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;
    BeepContext ctx = {
        .frequency = (float)args->frequency,
        .phase = 0.0f,
        .phase_increment = (float)args->frequency / SAMPLE_RATE
    };

    SDL_zero(want);
    want.freq = SAMPLE_RATE;
    want.format = AUDIO_U8;
    want.channels = 1;
    want.samples = 512;
    want.callback = audio_callback;
    want.userdata = &ctx;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (dev == 0) {
        SDL_Log("Audio error: %s\n", SDL_GetError());
        free(arg);
        return NULL;
    }

    SDL_PauseAudioDevice(dev, 0);
    SDL_Delay(args->duration_ms);
    SDL_PauseAudioDevice(dev, 1);
    SDL_CloseAudioDevice(dev);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);

    free(arg);
    return NULL;
}

void Beep(int frequency, int duration_ms) {
    BeepArgs *args = malloc(sizeof(BeepArgs));
    args->frequency = frequency;
    args->duration_ms = duration_ms;

    pthread_t tid;
    pthread_create(&tid, NULL, beep_thread, args);
    pthread_detach(tid);  // So we don't need to join later
}
