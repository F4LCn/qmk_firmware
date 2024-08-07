// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t keycode;
    uint16_t shifted_keycode;
} custom_shift_key_t;

typedef struct {
    uint16_t keycode;
    uint16_t ralt_keycode;
    uint16_t shift_ralt_keycode;
} custom_ralt_key_t;

/** Table of custom shift keys. */
extern const custom_shift_key_t custom_shift_keys[];
extern const custom_ralt_key_t  custom_ralt_keys[];
/** Number of entries in the `custom_shift_keys` table. */
extern uint8_t NUM_CUSTOM_SHIFT_KEYS;
extern uint8_t NUM_CUSTOM_RALT_KEYS;

bool process_custom_keys(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif
