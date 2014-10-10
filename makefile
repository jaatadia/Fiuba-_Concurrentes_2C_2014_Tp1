#parametros generales
PARAMETROS = g++ -Wall -g
PROYECTO = concu_calesita
RELEASE = ./$(PROYECTO)

#parametros para construccion de la libreria
LIBRERIA = comunicacion
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

all: $(PROYECTO)

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





ninio: $(LIBRERIA)
	@echo
	#-----------compilando ninio-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_NINIO); do $(PARAMETROS) -c $(PATH_NINIO)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable ninio
	$(PARAMETROS) $(OBJETOS_NINIO) $(PATH_NINIO)/$(NINIO_SOURCE) -o $(RELEASE)/$(NINIO_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm $(OBJETOS_NINIO)





calesita: $(LIBRERIA)
	@echo
	#-----------compilando calesita-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_CALESITA); do $(PARAMETROS) -c $(PATH_CALESITA)/$${i%.*}.cpp -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA);done 
	#2.creando ejecutable ninio
	$(PARAMETROS) $(OBJETOS_CALESITA) $(PATH_CALESITA)/$(CALESITA_SOURCE) -o $(RELEASE)/$(CALESITA_EXE) -I $(RELEASE)/include -L$(RELEASE)/include -l$(LIBRERIA)
	#3.eliminando archivos temporales
	rm $(OBJETOS_CALESITA)





clean:
	rm -f -r $(RELEASE) *.o


run:
	$(RELEASE)/$(CALESITA_EXE)&
	$(RELEASE)/$(NINIO_EXE)&
	$(RELEASE)/$(NINIO_EXE)&
	$(RELEASE)/$(NINIO_EXE)&



$(PROYECTO): $(LIBRERIA) ninio calesita
	
