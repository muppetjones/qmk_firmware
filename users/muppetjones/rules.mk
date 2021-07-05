# Reduce firmware size
# 	https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
# also requires in config.h
#	NO_ACTION_MACRO
#	NO_ACTION_FUNCTION
EXTRAFLAGS += -flto

SRC += muppetjones.c

# Add only if certain features are enabled
ifdef CAPSWORD_ENABLE
	SRC += ./features/casemodes.c
endif

ifdef TAP_LAYER_ENABLE
	SRC += ./features/dancelayers.c
endif
