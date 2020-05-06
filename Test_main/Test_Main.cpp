#include "Packet/Packet.h"
#include <iostream>

using namespace Server;

int main()
{
	cPacket packet;

	packet.Pack(5);
	packet.Pack("asdqwe");


	int n = 0;
	char str[250];



	packet.UnPack(n);
	packet.UnPack(str);


	std::cout << str << std::endl;
	   
}