#!/bin/bash


function link()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed



g++ -shared -L"%CA2_ROOT%stage/x86/"  %OBJS% -o "%CA2_ROOT%stage/%PLATFORM%/libnetnodelibrary.so" -Wl,-rpath,$ORIGIN -Wl,-E -ldl -lpthread -l_ca2openssl -l_ca2zlib -l_ca2freeimage -l_ca2freetype -l_ca2c -lca2ca -lca2 -lcairo -lX11 -lXmu -lnetnode -Wl,-z,defs &> "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%-link-log.txt"


}


link
