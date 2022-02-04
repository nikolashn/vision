# See LICENSE for copyright/license information

include config.mk

all:
	${CC} -o vision src/main.c ${CFLAGS}

clean:
	rm -f vision

install: all
	mkdir -p ${DESTDIR}${PPATH}/bin
	cp -f vision ${DESTDIR}${PPATH}/bin
	chmod 755 ${DESTDIR}${PPATH}/bin/vision

uninstall:
	rm -f ${DESTDIR}${PPATH}/bin/vision

.PHONY: all clean install uninstall

