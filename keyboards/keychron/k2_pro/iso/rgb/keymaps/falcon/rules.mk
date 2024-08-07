CUSTOM_KEYS_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_KEYS_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_SHIFT_KEYS_ENABLE -DCUSTOM_RALT_KEYS_ENABLE
	SRC += keyboards/keychron/falcon/features/custom_keys.c
endif

LTO_ENABLE = yes
VIA_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes
CONSOLE_ENABLE = yes
