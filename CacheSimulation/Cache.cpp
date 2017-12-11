#include "stdafx.h"
#include "Cache.h"
#include <iostream>
#include "CacheBlock.h"
#include <fstream>

Cache::Cache() //default constructor
{
	blockSize = 64;
	cacheSize = 16384;
	numBlocks = 256;
	sRAM = new CacheBlock[numBlocks];
	
}

Cache::Cache(int blockSizeIn, int cacheSizeIn) //parameter constructor
{
	blockSize = blockSizeIn;
	cacheSize = cacheSizeIn;
	numBlocks = cacheSizeIn / blockSizeIn;
	sRAM = new CacheBlock[numBlocks];
}

Cache::~Cache()
{
}

bool Cache::Get(int address, int cycles) 
{
	int shiftAmt; //the amount of bits to shift right in the address
	unsigned int currentTag; //the tag extracted from incoming address
	int currentLRU = cycles; //will hold the lowest LRU in cache after comparing cache blocks at time of function call
	int blockLRU = 0; //holds the lru of the most recently read block
	int blockIndex = 0; //will hold the index of the block containing lowest LRU

	shiftAmt = log2(blockSize) + log2(numBlocks); //shift amount is block offset bits + block index bits (assuming direct mapped, block index = set index)
	currentTag = address >> shiftAmt; //shift address right by shift amount to obtain tag

	for (int i = 0; i < numBlocks; i++)  //check each block for the cache tag
	{
		if (sRAM[i].Read() == currentTag) //if tag matches, update LRU in the block and return true
		{
			sRAM[i].Write(currentTag, cycles);
			return true;
		}
	}

	//this block only executes if a miss occurs... will find a block to evict and writes the missing data into the cache
	//usually would be done after data is found in a higher level cache, but done now for simplicity and since doesnt affect final results
	for (int i = 0; i < numBlocks; i++) 
	{
		sRAM[i].Read(blockLRU); //get next lru from block
		if (sRAM[i].Read() == 0) //if block data is invalid, it can be victimized and rewritten with the new data
		{
			blockIndex = i; //mark this block as the one to be replaced
			break; //no need to keep searching after finding a block to evict
		}
		if (blockLRU < currentLRU) //if next lru is lower than previous, set that as the new lru
		{
			currentLRU = blockLRU;
			blockIndex = i; //mark the block which has the lru for writing without searching the entire cache again
		}
	}

	sRAM[blockIndex].Write(currentTag, cycles); //write the data to lru cache block

	return false;
}

