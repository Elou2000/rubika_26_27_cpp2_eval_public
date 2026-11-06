#include "LRUCache.h"

LRUCache::LRUCache(int capacity) 
{
	cacheCapacity = capacity;
}

std::string LRUCache::get(int key)
{
	auto found = cacheMapIterator.find(key);
	if (found == cacheMapIterator.end())
	{
		return std::string();
	}

	cacheList.splice(cacheList.begin(), cacheList, found->second);
	return found->second->second;

	// This version is the one before the 0(1) refractor
	
	//if (cacheMap.empty())
	//	return std::string();
	//
	//if (cacheMap.find(key) == cacheMap.end())
	//	return std::string();
	//
	//
	//for (auto it = cacheList.begin(); it != cacheList.end(); ++it)
	//{
	//	if (it->first == key)
	//	{
	//		std::string value = it->second;
	//		cacheList.erase(it);
	//		cacheList.push_front({ key, value });
	//		return value;
	//	}
	//}
	//
	//return std::string();
}

void LRUCache::put(int key, std::string value)
{
	if (cacheCapacity <= 0)
		return;

	auto found = cacheMapIterator.find(key);
	if (found != cacheMapIterator.end())
	{
		found->second->second = value;
		cacheList.splice(cacheList.begin(), cacheList, found->second);
		return;
	}

	if (cacheList.size() == cacheCapacity)
	{
		cacheMapIterator.erase(cacheList.back().first);
		cacheList.pop_back();
	}

	cacheList.push_front({ key, value });
	cacheMapIterator[key] = cacheList.begin();

	// This version is the one before the 0(1) refractor
	//
	//if (cacheMap.find(key) != cacheMap.end())
	//{
	//	for (auto it = cacheList.begin(); it != cacheList.end(); ++it)
	//	{
	//		if (it->first == key)
	//		{
	//			cacheList.erase(it);
	//			break;
	//		}
	//	}
	//}
	//else if ((int)cacheList.size() == cacheCapacity)
	//{
	//	cacheMap.erase(cacheList.back().first);
	//	cacheList.pop_back();
	//}
	//
	//cacheList.push_front({ key, value });
	//cacheMap[key] = value;
}


