gcc \
    -I/usr/local/Cellar/glib/2.56.1/include/glib-2.0 \
    -L/usr/local/Cellar/glib \
    -lglib-2.0 -lgd main.c -o image-similar && ./image-similar test/chrome_48.png test/chrome_32.png

