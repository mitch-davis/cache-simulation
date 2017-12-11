#pragma once
#include "CacheBlock.h"
class Cache
{
public:
	Cache();
	Cache(int blockSizeIn, int cacheSizeIn);
	~Cache();

	bool Get(int, int); //services the memory request, returning true on a hit and false on a miss

private:
	int blockSize; 
	int cacheSize;
	int numBlocks;
	CacheBlock * sRAM; //points to array of cache blocks after initialization
};