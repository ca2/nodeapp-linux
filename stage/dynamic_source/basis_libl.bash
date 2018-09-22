#!/bin/bash


function link()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed



g++ -shared -L"%CA2_ROOT%stage/x86/"  %OBJS% -o "%CA2_ROOT%stage/%PLATFORM%/libnetnodelibrary.so" -Wl,-rpath,\\$ORIGIN -Wl,-E -ldl -lpthread -lbase -lbaseopenssl -lbasezlib -lbasefreeimage -lbasefreetype -lbasepixman -lbasecairo -lboot -lcore -lX11 -lXmu -lnetnode -Wl,-z,defs &> "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%-link-log.txt"


}


link
