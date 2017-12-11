#include "stdafx.h"
#include "CacheBlock.h"
#include <iostream>


CacheBlock::CacheBlock() //default constructor
{
	cacheTag = 0;
	lru = 0;
	validBit = false; //default state is invalid
}


CacheBlock::~CacheBlock()
{
}

unsigned int CacheBlock::Read() //this version of read method used when searching for matching tag
{
	if (validBit)
		return cacheTag;
	else
		return 0; //a zero returned denotes invalid data
}

unsigned int CacheBlock::Read(int& blockLRU) //this version of read method used when searching for the lru block
{
	if (validBit)
	{
		blockLRU = lru; //used to find lru block when servicing a miss
		return cacheTag;
	}
	else
		return 0;
}

void CacheBlock::Write(unsigned int cacheTagIn, int cyclesIn)
{
	validBit = true;
	cacheTag = cacheTagIn;
	lru = cyclesIn;
}
