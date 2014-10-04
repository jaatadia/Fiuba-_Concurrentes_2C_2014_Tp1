#!/bin/bash
#primero preparo las constantes para que ahora se ejecuten todos dentro de una misma carpeta.
cd comunicacion/src
sed -i.back 's#static const string MAIN_FOLDER=.*#static const string MAIN_FOLDER=".";#g' constantes.h
sed -i.back2 's#static const string DEBUG=.*#static const string DEBUG="";#g' constantes.h
sed -i.back2 's#static const string FOLDER_\([^=]*\)=.*#static const string FOLDER_\1="";#g' constantes.h
rm constantes.h.back2
#Compilo comunicacion.
cd ../Debug
make clean
make all

#esto seguro se puede hacer en un bucle pero nah. no me acuerdo como se hace.
cd ../..
cd cajero_p/Debug
make clean
make all
cd ../..
cd calesita_p/Debug
make clean
make all
cd ../..
cd generador_p/Debug
make clean
make all
cd ../..
cd logger_p/Debug
make clean
make all
cd ../..
cd ninio_p/Debug
make clean
make all
cd ../..
cd maestro/Debug
make clean
make all
#Ahora copio todos los ejecutables al directorio nuevo
cd ../..
rm -r Release
mkdir Release
cp ./cajero_p/Debug/cajero_p Release
cp ./calesita_p/Debug/calesita_p Release
cp ./generador_p/Debug/generador_p Release
cp ./logger_p/Debug/logger_p Release
cp ./maestro/Debug/maestro Release
cp ./ninio_p/Debug/ninio_p Release

#Restauro las constantes de comunicacion que modifique antes.
rm ./comunicacion/src/constantes.h
cp ./comunicacion/src/constantes.h.back ./comunicacion/src/constantes.h
rm ./comunicacion/src/constantes.h.back


