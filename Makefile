#
# Makefile:
# For command line to LED SPI interface app named spi_led_spit
#
#################################################################################
# Compile a piece of C code using the wiringPi library:
# sudo cc -o fun softPwm.c -I/usr/local/include -L/usr/local/lib -lwiringPi -lpthread
#################################################################################

TRANSFER=scp
REXEC=ssh
SSHFLAGS=-C # Compress data
REMOTE=pi@192.168.25.200:~/dev/projects/spi_work/
FILES=spi_led_spit.ct spi_server.jst Makefile.buildt cJSON.ct cJSON.ht

###############################################################################

SRC	=	spi_led_spit.c

OBJ	=	spi_led_spit.o

BINS	=	spi_led_spit

%.ht : %.h
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)

%.ct : %.c
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)

%.jst : %.js
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)
	
%.buildt : %.build
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)

all-done: $(FILES)
	$(REXEC) $(SSHFLAGS) pi@192.168.25.200 "cd ~/dev/projects/spi_work/ && make"
