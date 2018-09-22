#!/bin/bash


function build()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed


g++ -std=c++0x -fexceptions -fnon-call-exceptions -fno-pie -fno-stack-protector -Wno-pointer-arith -Wno-attributes -Winvalid-pch -fPIC -g -D_DEBUG    -I../../../app-core/appseed/netnode_dynamic_source_script -I../../../app/thirdparty/appseed -I. -I.. -I../.. -I../core -I../../nodeapp/linux -I../../nodeapp/linux/include -I../../../app -I../../../app/include -I../../.. -I../../../app/appseed -I../../../app/appseed/core -I../../../app/appseed/base -I../../../app/appseed/axis -I../../../app/appseed/aura -I../../../app/axis  -I/netnodenet/net/netseed/include -I"%CA2_ROOT%time/dynamic_source/library/include" -c "%CA2_ROOT%time/dynamic_source%ITEM_NAME%.cpp" -o "%CA2_ROOT%time/intermediate/%PLATFORM%/%CONFIGURATION_NAME%/netnode_dynamic_source_script%ITEM_NAME%/%ITEM_TITLE%.o" &> "%CA2_ROOT%time/dynamic_source%ITEM_NAME%-compile-log.txt"

g++ -shared -L"%CA2_ROOT%stage/x86/"  "%CA2_ROOT%time/intermediate/app-core/netnode_dynamic_source_script/framework.o"  "%CA2_ROOT%time/intermediate/%PLATFORM%/%CONFIGURATION_NAME%/netnode_dynamic_source_script%ITEM_NAME%/%ITEM_TITLE%.o" -o "%TARGET_PATH%.so" -Wl,-rpath,\\$ORIGIN -Wl,-E -ldl -lpthread -laura -laxiscrypto -laxisopenssl -laxiszlib -laxisfreeimage -laxisfreetype -laxispixman -laxiscairo -laxis -lbase -lcore -lprogramming -lX11 -lXmu -lnetnode -lnetnodelibrary -lapp_core_alarm -Wl,-z,defs &> "%CA2_ROOT%time/dynamic_source%ITEM_NAME%-link-log.txt"


}


build
