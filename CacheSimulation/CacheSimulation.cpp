// CacheSimulation.cpp
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Cache.h"
#include "CacheBlock.h"
using namespace std;

void CacheSimUnop(); //run a simulation of cache with unoptimized memory accesses
void CacheSimOp(); //run a simulation of cache with optimized memory accesses

int main()
{
	CacheSimUnop();

	CacheSimOp();

	system("pause"); //prevent console from immediately closing
	return 0;
}

void CacheSimUnop()
{
	int cycle = 0; //current "clock" cycle
	float exTime = 0; //execution time
	bool isHit = false; //result of Get()

	Cache L1(64, 16384); //64 byte blocks, 16Kb memory
	Cache L2(64, 2097152); //64 byte blocks, 2Mb memory
	Cache L3(64, 8388608); //64 byte blocks, 8Mb memory

	FILE *infile;
	infile = fopen("unop.bin", "rb"); //open unoptimized binary file
	int nAddress; //will hold the incloming address

	while (!feof(infile))
	{
		cycle++;

		fread(&nAddress, sizeof(int), 1, infile); //read in 32-bit address

		isHit = L1.Get(nAddress, cycle);
		if (isHit)
		{
			exTime += 1.1f; //L1 access time
		}
		else
		{
			isHit = L2.Get(nAddress, cycle);
			if (isHit)
			{
				exTime += 7.9f; //L2 access time
			}
			else
			{
				isHit = L3.Get(nAddress, cycle);
				if (isHit)
				{
					exTime += 24.9f;  //L3 access time
				}
				else
				{
					exTime += 73.7f; //main memory access time
				}
			}
		}
	}

	fclose(infile);
	printf("Unoptimized - Time to execute: %f", exTime);
}

void CacheSimOp()
{
	int cycle = 0;
	float exTime = 0;
	bool isHit = false;
	Cache L1(64, 16384); //64 byte blocks, 16Kb memory
	Cache L2(64, 2097152); //64 byte blocks, 2Mb memory
	Cache L3(64, 8388608); //64 byte blocks, 8Mb memory

	FILE *infile;
	infile = fopen("layout.bin", "rb"); //open optimized binary file
	int nAddress;

	while (!feof(infile))
	{
		cycle++;

		fread(&nAddress, sizeof(int), 1, infile); //read in 32-bit address

		isHit = L1.Get(nAddress, cycle);
		if (isHit)
		{
			exTime += 1.1f; //L1 access time
		}
		else
		{
			isHit = L2.Get(nAddress, cycle);
			if (isHit)
			{
				exTime += 7.9f; //L2 access time
			}
			else
			{
				isHit = L3.Get(nAddress, cycle);
				if (isHit)
				{
					exTime += 24.9f;  //L3 access time
				}
				else
				{
					exTime += 73.7f; //main memory access time
				}
			}
		}
	}

	fclose(infile);
	printf("\nOptimized - Time to execute: %f", exTime);
}
