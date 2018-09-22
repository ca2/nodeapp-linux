#!/bin/bash


function compile()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed


g++ -std=c++0x -fPIC -fexceptions -fnon-call-exceptions -fno-pie -fno-stack-protector -Wno-pointer-arith -Wno-attributes -Winvalid-pch  -g -D_DEBUG  -DMEMDLEAK  -I../../../app-core/appseed/netnode_dynamic_source_library -I../../../app/thirdparty/appseed -I. -I.. -I../.. -I../ca2 -I../../nodeapp/linux -I../../nodeapp/linux/include -I../../.. -I../../../app/appseed -I../../../app/appseed/ca -I../../../app/appseed/ca2 -I../../../app/thirdparty/include  -I/netnodenet/net/netseed/ds/ca2/include -c -I"%CA2_ROOT%time/dynamic_source/library/include" "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%.cpp" -o "%CA2_ROOT%time/intermediate/%PLATFORM%/netnode_dynamic_source_library/%ITEM_NAME%.o" &> "%CA2_ROOT%time/dynamic_source/%ITEM_NAME%-compile-log.txt"


}


compile
