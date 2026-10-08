# de10-lvgl-test




CC = gcc

CFLAGS = -std=gnu99 -O2 -I/home/root -I/home/root/lvgl -I/home/root/lv_drivers

LIBS = -lm -lpthread

LVGL_SRC = $(shell find /home/root/lvgl/src -name '*.c')

DRIVER_SRC = /home/root/lv_drivers/display/fbdev.c \
             /home/root/lv_drivers/indev/evdev.c

all: lvgl_test

lvgl_test: main.c
	$(CC) $(CFLAGS) -o $@ main.c $(DRIVER_SRC) $(LVGL_SRC) $(LIBS)

clean:
	rm -f lvgl_test

.PHONY: all clean
