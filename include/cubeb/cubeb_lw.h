/*
 * Copyright © 2012 Mozilla Foundation
 *
 * This program is made available under an ISC-style license.  See the
 * accompanying file LICENSE for details.
 */
#ifndef   CUBEB_LW_0bb9e89b_0f88_4402_a3ba_8360922df0bc
#define   CUBEB_LW_0bb9e89b_0f88_4402_a3ba_8360922df0bc

#include <cubeb/cubeb-stdint.h>
#include <cubeb/cubeb.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @mainpage

    @section intro Introduction

    This is the documentation for the <tt>libcubeb</tt> C API.
    <tt>libcubeb</tt> is a callback-based audio API library allowing the
    authoring of portable multiplatform audio playback.

    @section example Example code

    @code
    cubeb * app_ctx;
    cubeb_init(&app_ctx, "Example Application");

    cubeb_stream_params params;
    params.format = CUBEB_SAMPLE_S16NE;
    params.rate = 48000;
    params.channels = 2;

    unsigned int latency_ms = 250;

    cubeb_stream * stm;
    cubeb_stream_init(app_ctx, &stm, "Example Stream 1", params,
                      latency_ms, data_cb, state_cb, NULL);

    cubeb_stream_start(stm);
    for (;;) {
      cubeb_stream_get_position(stm, &ts);
      printf("time=%llu\n", ts);
      sleep(1);
    }
    cubeb_stream_stop(stm);

    cubeb_stream_destroy(stm);
    cubeb_destroy(app_ctx);
    @endcode

    @code
    long data_cb(cubeb_stream * stm, void * user, void * buffer, long nframes)
    {
      short * buf = buffer;
      for (i = 0; i < nframes; ++i) {
        for (c = 0; c < params.channels; ++c) {
          buf[i][c] = 0;
        }
      }
      return nframes;
    }
    @endcode

    @code
    void state_cb(cubeb_stream * stm, void * user, cubeb_state state)
    {
      printf("state=%d\n", state);
    }
    @endcode
*/


/** @file
    The <tt>libcubeb</tt> C API. */

typedef struct cubeb_lw cubeb_lw;               /**< Opaque handle referencing the application state. */
typedef struct cubeb_lw_stream cubeb_lw_stream; /**< Opaque handle referencing the stream state. */

/** Initialize an application context.  This will perform any library or
    application scoped initialization.
    @param context
    @param context_name
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_lw_init(cubeb_lw ** context, char const * context_name);

/** Destroy an application context.
    @param context */
void cubeb_lw_destroy(cubeb_lw * context);

/** Initialize a stream associated with the supplied application context.
    @param context
    @param stream
    @param stream_name
    @param stream_params
    @param latency Approximate stream latency in milliseconds.  Valid range is [1, 2000].
    @param data_callback Will be called to preroll data before playback is
                          started by cubeb_stream_start.
    @param state_callback
    @param user_ptr
    @retval CUBEB_OK
    @retval CUBEB_ERROR
    @retval CUBEB_ERROR_INVALID_FORMAT */
int cubeb_lw_stream_init(cubeb_lw * context, cubeb_lw_stream ** stream, char const * stream_name,
                         cubeb_stream_params stream_params, unsigned int latency,
                         cubeb_data_callback data_callback,
                         cubeb_state_callback state_callback,
                         void * user_ptr);

/** Destroy a stream.
    @param stream */
void cubeb_lw_stream_destroy(cubeb_lw_stream * stream);

/** Start playback.
    @param stream
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_lw_stream_start(cubeb_lw_stream * stream);

/** Stop playback.
    @param stream
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_lw_stream_stop(cubeb_lw_stream * stream);

/** Get the current stream playback position.
    @param stream
    @param position Playback position in frames.
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_lw_stream_get_position(cubeb_lw_stream * stream, uint64_t * position);

#ifdef __cplusplus
}
#endif

#endif /* CUBEB_LW_0bb9e89b_0f88_4402_a3ba_8360922df0bc */