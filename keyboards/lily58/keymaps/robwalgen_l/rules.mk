# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight. 

# Bootloader selection
BOOTLOADER = atmel-dfu

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
# EXTRAFLAGS += -flto
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE  = no


# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./burst.c \
        ./navi_logo.c \
        ./gui_state.c \
        ./fast_random.c \
        ./layer_frame.c \
        ./ring.c \
        ./boot.c \
        ./draw_helper.c \


EXTRAKEY_ENABLE = yes		# added by me
POINTING_DEVICE_ENABLE = yes 	# added by me
QUANTUM_LIB_SRC += i2c_master.c		# added by me
SRC += drivers/sensors/pimoroni_trackball.c	# added by me