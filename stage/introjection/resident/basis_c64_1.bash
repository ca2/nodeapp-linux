#!/bin/bash


function compile()
{
	
	cd %CA2_ROOT%nodeapp/seed/metaseed


g++ -std=c++0x -fexceptions -fnon-call-exceptions -fno-pie -fno-stack-protector -Wno-pointer-arith -Wno-attributes -Winvalid-pch -fPIC -std=c++14  -g -D_DEBUG    -I../../../app-core/appseed/netnode_dynamic_source_library -I../../../app/thirdparty/appseed -I. -I.. -I../.. -I../core -I../../nodeapp/linux -I../../nodeapp/linux/include -I../../../app -I../../../app/include -I../../.. -I../../../app/appseed -I../../../app/appseed/core -I../../../app/appseed/base -I../../../app/appseed/axis -I../../../app/appseed/aura -I../../../app/axis  -I/netnodenet/net/netseed/include -c "%SOURCE%" -o "%CA2_ROOT%time/intermediate/%PLATFORM%/%CONFIGURATION_NAME%/xmpp_resident/%ITEM_NAME%.o"


}


compile
