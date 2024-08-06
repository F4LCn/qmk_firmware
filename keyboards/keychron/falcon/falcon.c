#include "config.h"
#ifdef CUSTOM_SHIFT_KEYS_ENABLE
#    include "features/custom_keys.h"
#endif // CUSTOM_SHIFT_KEYS_ENABLE

#ifdef CUSTOM_SHIFT_KEYS_ENABLE
// clang-format off
const custom_shift_key_t custom_shift_keys[] = {
    {KC_CIRC, KC_1},
    {KC_AT, KC_2},
    {KC_HASH, KC_3},
    {KC_DLR, KC_4},
    {KC_PERC, KC_5},
    {KC_DQT, KC_6},
    {KC_QUOT, KC_7},
    {KC_ASTR, KC_8},
    {KC_LPRN, KC_9},
    {KC_RPRN, KC_0},

    {KC_DOT, KC_EXLM},
    {KC_COMM, KC_AMPR},

    {KC_LABK, KC_RABK},

    {C(A(KC_CIRC)), KC_RPRN},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
#endif

#ifdef CUSTOM_RALT_KEYS_ENABLE
const custom_ralt_key_t custom_ralt_keys[] = {
    {KC_CIRC, KC_LPRN, KC_RPRN},
    {KC_AT, KC_LBRC, KC_RBRC},
    {KC_HASH, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE},
};
uint8_t NUM_CUSTOM_RALT_KEYS = sizeof(custom_ralt_keys) / sizeof(custom_ralt_key_t);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef CUSTOM_RALT_KEYS_ENABLE
    if (!process_custom_shift_ralt_keys(keycode, record)) {
        return false;
    }
    if (!process_custom_ralt_keys(keycode, record)) {
        return false;
    }
#endif

#ifdef CUSTOM_SHIFT_KEYS_ENABLE
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
#endif

    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_OFF);
}

void caps_word_set_user(bool active) {
    if (active) {
        rgb_matrix_sethsv_noeeprom(HSV_GOLD);
    } else {
        rgb_matrix_sethsv_noeeprom(HSV_OFF);
    }
}
