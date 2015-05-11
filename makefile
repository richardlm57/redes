all: reserva_bol_ser reserva_bol_cli servicio
reserva_bol_ser: reserva_bol_ser.o 
	gcc -o reserva_bol_ser reserva_bol_ser.o
reserva_bol_ser.o: reserva_bol_ser.c reserva_bol_ser.h
	gcc -c reserva_bol_ser.c
reserva_bol_cli: reserva_bol_cli.o 
	gcc -o reserva_bol_cli reserva_bol_cli.o
reserva_bol_cli.o: reserva_bol_cli.c reserva_bol_cli.h
	gcc -c reserva_bol_cli.c
servicio: servicio.o
	gcc -o servicio servicio.o
servicio.o: servicio.c
	gcc -c servicio.c
clean:
	rm *.o