#
# Makefile:
# For command line to LED SPI interface app named spi_led_spit
#
#################################################################################
# Compile a piece of C code using the wiringPi library:
# sudo cc -o fun softPwm.c -I/usr/local/include -L/usr/local/lib -lwiringPi -lpthread
#################################################################################

#DEBUG	= -g -O0
DEBUG	= -O3
CC	= cc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LIBS    = -lwiringPi

# Should not alter anything below this line
###############################################################################

SRC	=	socket_server.c

OBJ	=	socket_server.o

BINS	=	socket_server

# all:	
# 	@echo "    $(BINS)" | fmt
# 	@echo ""

socket_server:	socket_server.o
	@echo [link]
	$(CC) -o $@ socket_server.o $(LDFLAGS) $(LIBS) -lm -lpthread

.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) *~ spi_led_spit

tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

depend:
	makedepend -Y $(SRC)
