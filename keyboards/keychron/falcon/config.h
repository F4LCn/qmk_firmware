
#pragma once

#define FORCE_NKRO

#ifdef CUSTOM_KEYS_ENABLE
#    ifndef CUSTOM_SHIFT_KEYS_ENABLE
#        define CUSTOM_SHIFT_KEYS_ENABLE
#    endif
#    ifndef CUSTOM_RALT_KEYS_ENABLE
#        define CUSTOM_RALT_KEYS_ENABLE
#    endif
#endif

#define MOD_MASK_RALT (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_SHIFT_RALT (MOD_MASK_RALT | MOD_MASK_SHIFT)

// Don't apply custom shift keys with mods other than Shift.
#define CUSTOM_SHIFT_KEYS_NEGMODS (~MOD_MASK_SHIFT)
#define CUSTOM_RALT_KEYS_NEGMODS (~MOD_MASK_RALT)
#define CUSTOM_SHIFT_RALT_KEYS_NEGMODS (~MOD_MASK_SHIFT_RALT)

// enable caps word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 3000
