#pragma once
class CacheBlock
{
public:
	CacheBlock();
	~CacheBlock();

	unsigned int Read(int&); //returns the cache tag and sets the blockLRU in Cache
	unsigned int Read(); //just returns the cache tag

	void Write(unsigned int, int); //writes the cache tag and lru to the block, and sets valid bit to true

private:
	unsigned int cacheTag;
	int lru;
	bool validBit;
};