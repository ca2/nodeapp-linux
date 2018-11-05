#!/bin/bash


function link()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed



g++ -shared -L"%CA2_ROOT%stage/x86/"  %OBJS% -o "%CA2_ROOT%stage/x86/libnetnodelibrary.so" -Wl,-rpath,\\$ORIGIN -Wl,-E -ldl -lpthread -laura -laxiscrypto -laxisopenssl -laxiszlib -laxisfreeimage -laxisfreetype -laxispixman -laxiscairo -laxis -lbase -lcore -lprogramming -lX11 -lXmu -lnetnode -Wl,-z,defs &> "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%-link-log.txt"


}


link
