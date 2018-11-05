#!/bin/bash


function build()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed


g++ -std=c++0x -fPIC -fexceptions -fnon-call-exceptions -fno-pie -fno-stack-protector -Wno-pointer-arith -Wno-attributes -Winvalid-pch  -g -D_DEBUG  -DMEMDLEAK  -I../../../app/thirdparty/appseed -I. -I.. -I../.. -I../ca2 -I../../nodeapp/linux -I../../nodeapp/linux/include -I../../.. -I../../../app/appseed -I../../../app/appseed/ca -I../../../app/appseed/ca2 -I../../../app/thirdparty/include  -c /ca2/app-core/appseed/netnode_dynamic_source_script/ds_script.cpp -o "%CA2_ROOT%time/intermediate/%PLATFORM%/netnode_dynamic_source_script%ITEM_NAME%/%ITEM_TITLE%.o" 

g++ -shared -L"/ca2/stage/x86/"  "%CA2_ROOT%time/intermediate/%PLATFORM%/netnode_dynamic_source_script/framework.o" "%CA2_ROOT%time/intermediate/%PLATFORM%/netnode_dynamic_source_script/netnode_dynamic_source_script.o" "%CA2_ROOT%time/intermediate/%PLATFORM%/netnode_dynamic_source_script%ITEM_NAME%/%ITEM_TITLE%.o" -o "%TARGET_PATH%.so" -Wl,-rpath,\\$ORIGIN -Wl,-E -ldl -lpthread -l_ca2openssl -l_ca2zlib -l_ca2freeimage -l_ca2freetype -l_ca2c -lca2ca -lca2 -lcairo -lX11 -lXmu -Wl,-z,defs 


}


build
