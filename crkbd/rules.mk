
# If you want to change the display of OLED, you need to change here
#SRC +=  ./lib/glcdfont.c \
#        ./lib/rgb_state_reader.c \
#        ./lib/layer_state_reader.c \
#        ./lib/logo_reader.c \
#        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

LTO_ENABLE = yes

RGBLIGHT_ENABLE    = no
RGB_MATRIX_ENABLE  = WS2812

MOUSEKEY_ENABLE    = yes
NKRO_ENABLE        = yes

OLED_DRIVER_ENABLE = yes


#WPM_ENABLE = yes
#get_current_wpm()

CONSOLE_ENABLE = yes

