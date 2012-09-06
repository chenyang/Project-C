mymain:



	gcc -c ./source/MODULE_GLOBALE.c -o ./static_lib/MODULE_GLOBALE.o
	gcc -c ./source/MODULE_FICHIER.c -o ./static_lib/MODULE_FICHIER.o
	#gcc -c ./source/MODULE_ANTL.c -o ./static_lib/MODULE_ANTL.o
	gcc -c ./source/MODULE_ARBRE.c -o ./static_lib/MODULE_ARBRE.o
	gcc -c ./source/MODULE_DIJKSTRA.c -o ./static_lib/MODULE_DIJKSTRA.o
	gcc -c ./source/MODULE_APPENDICE.c -o ./static_lib/MODULE_APPENDICE.o

	ar cr ./static_lib/libMODULE_GLOBALE.a ./static_lib/MODULE_GLOBALE.o
	ar cr ./static_lib/libMODULE_FICHIER.a ./static_lib/MODULE_FICHIER.o
	#ar cr ./static_lib/libMODULE_ANTL.a ./static_lib/MODULE_ANTL.o
	ar cr ./static_lib/libMODULE_ARBRE.a ./static_lib/MODULE_ARBRE.o
	ar cr ./static_lib/libMODULE_DIJKSTRA.a ./static_lib/MODULE_DIJKSTRA.o
	ar cr ./static_lib/libMODULE_APPENDICE.a ./static_lib/MODULE_APPENDICE.o
	rm -f ./static_lib/*.o
	



	gcc -o main main.c -L./static_lib/ -lMODULE_FICHIER -lMODULE_GLOBALE -lMODULE_ARBRE -lMODULE_DIJKSTRA -lMODULE_APPENDICE -lm 
