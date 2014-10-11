#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- PARAMETROS-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#parametros generales
PARAMETROS = g++ -Wall -g
PROYECTO = concu_calesita
RELEASE = ./$(PROYECTO)
PROCESOS = ninio calesita administrador cajero generador logger maestro_p

#parametros para construccion de la libreria
LIBRERIA = comunicacionlib
PATH_LIBRERIA = ./comunicacion/src

#parametros para la compilacion del proceso niño
PATH_NINIO = ./ninio_p/src
OBJETOS_NINIO = Boleteria.o Calesita.o DineroInsuficienteException.o
NINIO_SOURCE = ninio_p.cpp
NINIO_EXE = ninio_p

#parametros para la compilacion del proceso calesita
PATH_CALESITA = ./calesita_p/src
OBJETOS_CALESITA = Entrada.o Interrupter.o
CALESITA_SOURCE = calesita_p.cpp
CALESITA_EXE = calesita_p

#parametros para la compilacion del proceso administrador
PATH_ADMIN = ./administrador_p/src
OBJETOS_ADMIN = 
ADMIN_SOURCE = administrador_p.cpp
ADMIN_EXE = administrador_p

#parametros para la compilacion del proceso cajero
PATH_CAJERO = ./cajero_p/src
OBJETOS_CAJERO = Expendio.o
CAJERO_SOURCE = cajero_p.cpp
CAJERO_EXE = cajero_p

#parametros para la compilacion del proceso generador
PATH_GENERADOR = ./generador_p/src
OBJETOS_GENERADOR = 
GENERADOR_SOURCE = generador_p.cpp
GENERADOR_EXE = generador_p

#parametros para la compilacion del proceso logger
PATH_LOG = ./logger_p/src
OBJETOS_LOG = LoggerListener.o
LOG_SOURCE = logger_p.cpp
LOG_EXE = logger_p

#parametros para la compilacion del proceso maestro
PATH_MAESTRO = ./maestro/src
OBJETOS_MAESTRO = 
MAESTRO_SOURCE = maestro.cpp
MAESTRO_EXE = maestro_p

all: $(PROYECTO)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Armado de la biblioteca-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


$(LIBRERIA): $(PATH_LIBRERIA)
	@echo
	#---------Generando libreria----------
	mkdir -p $(RELEASE)/include
	rm -f -r ./tmp
	mkdir -p ./tmp
	cp -r $(PATH_LIBRERIA) ./tmp
	@echo
	#1.compilando archivos
	var=`find ./tmp -name *.cpp`; for i in $$var;do $(PARAMETROS) -c $$i -o $${i%.*}.o; rm $$i;done
	@echo
	#2.incluyendo los archivos en la libreria	
	var=`find ./tmp -name *.o`; for i in $$var;do ar -crs $(RELEASE)/include/lib$(LIBRERIA).a $$i ; rm $$i;done
	cp -r ./tmp/* $(RELEASE)/include
	@echo
	#3.eliminando archivos temporales
	rm -f -r ./tmp


#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Compilacion de proyectos-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#////////////////////////NINIO////////////////////
ninio: $(LIBRERIA)
	@echo
	#-----------compilando ninio-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_NINIO); do $(PARAMETROS) -c $(PATH_NINIO)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable ninio
	$(PARAMETROS) $(OBJETOS_NINIO) $(PATH_NINIO)/$(NINIO_SOURCE) -o $(RELEASE)/$(NINIO_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_NINIO)


#////////////////////////CALESITA////////////////////


calesita: $(LIBRERIA)
	@echo
	#-----------compilando calesita-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_CALESITA); do $(PARAMETROS) -c $(PATH_CALESITA)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable calesita
	$(PARAMETROS) $(OBJETOS_CALESITA) $(PATH_CALESITA)/$(CALESITA_SOURCE) -o $(RELEASE)/$(CALESITA_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_CALESITA)



#////////////////////////ADMINISTRADOR////////////////////


administrador: $(LIBRERIA)
	@echo
	#-----------compilando admin-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_ADMIN); do $(PARAMETROS) -c $(PATH_ADMIN)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable admin
	$(PARAMETROS) $(OBJETOS_ADMIN) $(PATH_ADMIN)/$(ADMIN_SOURCE) -o $(RELEASE)/$(ADMIN_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_ADMIN)



#////////////////////////CAJERO////////////////////

cajero: $(LIBRERIA)
	@echo
	#-----------compilando cajero-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_CAJERO); do $(PARAMETROS) -c $(PATH_CAJERO)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable cajero
	$(PARAMETROS) $(OBJETOS_CAJERO) $(PATH_CAJERO)/$(CAJERO_SOURCE) -o $(RELEASE)/$(CAJERO_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_CAJERO)

#////////////////////////GENERADOR////////////////////

generador: $(LIBRERIA)
	@echo
	#-----------compilando generador-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_GENERADOR); do $(PARAMETROS) -c $(PATH_GENERADOR)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable generador
	$(PARAMETROS) $(OBJETOS_GENERADOR) $(PATH_GENERADOR)/$(GENERADOR_SOURCE) -o $(RELEASE)/$(GENERADOR_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_GENERADOR)

#////////////////////////LOG////////////////////

logger: $(LIBRERIA)
	@echo
	#-----------compilando logger-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_LOG); do $(PARAMETROS) -c $(PATH_LOG)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable logger
	$(PARAMETROS) $(OBJETOS_LOG) $(PATH_LOG)/$(LOG_SOURCE) -o $(RELEASE)/$(LOG_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_LOG)

#////////////////////////MAESTRO////////////////////

maestro_p: $(LIBRERIA)
	#-----------compilando maestro-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_MAESTRO); do $(PARAMETROS) -c $(PATH_MAESTRO)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable maestro
	$(PARAMETROS) $(OBJETOS_MAESTRO) $(PATH_MAESTRO)/$(MAESTRO_SOURCE) -o $(RELEASE)/$(MAESTRO_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm -f $(OBJETOS_MAESTRO)


#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Otros Comandos -------------------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

clean:
	rm -f -r $(RELEASE) *.o

$(PROYECTO): $(LIBRERIA) $(PROCESOS)
	
