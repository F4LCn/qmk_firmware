// Copyright 2021-2024 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "custom_keys.h"
#include "keycodes.h"

static inline bool process_custom_shift_ralt_keys(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    static uint16_t registered_keycode = KC_NO;

    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    if ((mods & MOD_MASK_ALT) != 0      // ALT is held
        && (mods & MOD_MASK_CTRL) != 0  // and CTRL is held
        && (mods & MOD_MASK_SHIFT) != 0 // and SHIFT is held
#if CUSTOM_SHIFT_RALT_KEYS_NEGMODS != 0
        && (mods & (CUSTOM_SHIFT_RALT_KEYS_NEGMODS)) == 0
#endif
    ) {
        for (int i = 0; i < NUM_CUSTOM_RALT_KEYS; ++i) {
            if (keycode == custom_ralt_keys[i].keycode) {
                registered_keycode = custom_ralt_keys[i].shift_ralt_keycode;

                if (IS_QK_MODS(registered_keycode) && // Should key be shifted?
                    (QK_MODS_GET_MODS(registered_keycode) & MOD_MASK_SHIFT) != 0) {
                    // If not, cancel ralt mods, press the key, and restore mods.
                    del_weak_mods(MOD_MASK_RALT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_RALT);
#endif // NO_ACTION_ONESHOT
                    unregister_mods(MOD_MASK_RALT);
                } else {
                    // If not, cancel ralt and shift mods, press the key, and restore mods.
                    del_weak_mods(MOD_MASK_SHIFT_RALT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_SHIFT_RALT);
#endif // NO_ACTION_ONESHOT
                    unregister_mods(MOD_MASK_SHIFT_RALT);
                }
                register_code16(registered_keycode);
                set_mods(mods);
                return false;
            }
        }
    }

    return true; // Continue with default handling.
}

static inline bool process_custom_ralt_keys(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    static uint16_t registered_keycode = KC_NO;

    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    if ((mods & MOD_MASK_ALT) != 0     // RALT is held
        && (mods & MOD_MASK_CTRL) != 0 // and CTRL is held
#if CUSTOM_RALT_KEYS_NEGMODS != 0
        && (mods & (CUSTOM_RALT_KEYS_NEGMODS)) == 0
#endif
    ) {
        for (int i = 0; i < NUM_CUSTOM_RALT_KEYS; ++i) {
            if (keycode == custom_ralt_keys[i].keycode) {
                registered_keycode = custom_ralt_keys[i].ralt_keycode;
                if (IS_QK_MODS(registered_keycode) && // Should key be ralted?
                    (QK_MODS_GET_MODS(registered_keycode) & MOD_MASK_RALT) != 0) {
                    register_code16(registered_keycode); // If so, press directly.
                } else {
                    // If not, cancel ralt mods, press the key, and restore mods.
                    del_weak_mods(MOD_MASK_RALT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_RALT);
#endif // NO_ACTION_ONESHOT
                    unregister_mods(MOD_MASK_RALT);
                    register_code16(registered_keycode);
                    set_mods(mods);
                }
                return false;
            }
        }
    }

    return true; // Continue with default handling.
}

static inline bool process_custom_shift_keys(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    static uint16_t registered_keycode = KC_NO;

    // If a custom shift key is registered, then this event is either
    // releasing it or manipulating another key at the same time. Either way,
    // we release the currently registered key.
    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    if ((mods & MOD_MASK_SHIFT) != 0 // Shift is held.
#if CUSTOM_SHIFT_KEYS_NEGMODS != 0
                                     // Nothing in CUSTOM_SHIFT_KEYS_NEGMODS is held.
        && (mods & (CUSTOM_SHIFT_KEYS_NEGMODS)) == 0
#endif // CUSTOM_SHIFT_KEYS_NEGMODS != 0
    ) {
        // Search for a custom shift key whose keycode is `keycode`.
        for (int i = 0; i < NUM_CUSTOM_SHIFT_KEYS; ++i) {
            if (keycode == custom_shift_keys[i].keycode) {
                registered_keycode = custom_shift_keys[i].shifted_keycode;
                if (IS_QK_MODS(registered_keycode) && // Should key be shifted?
                    (QK_MODS_GET_MODS(registered_keycode) & MOD_LSFT) != 0) {
                    register_code16(registered_keycode); // If so, press directly.
                } else {
                    // If not, cancel shift mods, press the key, and restore mods.
                    del_weak_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_SHIFT);
#endif // NO_ACTION_ONESHOT
                    unregister_mods(MOD_MASK_SHIFT);
                    register_code16(registered_keycode);
                    set_mods(mods);
                }
                return false;
            }
        }
    }

    return true; // Continue with default handling.
}

bool process_custom_keys(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) { // Press event.
        const uint8_t saved_mods = get_mods();

#ifndef NO_ACTION_ONESHOT
        const uint8_t mods = saved_mods | get_weak_mods() | get_oneshot_mods();
#else
        const uint8_t mods = saved_mods | get_weak_mods();
#endif // NO_ACTION_ONESHOT

        // Continue default handling if this is a tap-hold key being held.
        if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) && record->tap.count == 0) {
            return true;
        }

#ifdef CUSTOM_RALT_KEYS_ENABLE
        if (!process_custom_ralt_keys(keycode, record, mods)) {
            return false;
        }
        if (!process_custom_shift_ralt_keys(keycode, record, mods)) {
            return false;
        }
#endif

#ifdef CUSTOM_SHIFT_KEYS_ENABLE
        if (!process_custom_shift_keys(keycode, record, mods)) {
            return false;
        }
#endif
    }

    return true;
}
