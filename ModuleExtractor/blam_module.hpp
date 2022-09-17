#pragma once

#include <cstdint>

#define EXPECT_SIZE(name, size) static_assert(sizeof(name) == (size), "Unexpected " #name " size")

const int BlamModuleHeaderMagic = 'dhom';
const int LatestBlamModuleVersion = 0x17;

struct BlamModuleHeader
{
	int magic; // 'dhom'
	int version; // 0x1B
	int unknown8;	// 8 byte id
	int unknownC;	// 8 byte id 2nd part
	int numFiles;	// offset 0x10
	int unknown14;	// Manifest Count
	int unknown18;	// Resource Index
	int fileNamesSize;	// offset 0x1c
	int numResources;	// offset 0x20
	int numCompressedBlocks;	// offset 0x24
	uint64_t unknown28;
	//uint64_t checksum;
};
EXPECT_SIZE(BlamModuleHeader, 0x30);

struct BlamModuleFile
{
	int nameOffset;
	int parentFileIndex; // used with resources to point back to the parent tag, -1 = none
	int unknown8;
	int unknownC;
	int compressedBlockCount; // if 0, then define a block using totalCompressedSize and totalUncompressedSize
	int firstCompressedBlockIndex;
	uint64_t compressedOffset; // relative to the start of the compressed data area in the module
	uint32_t totalCompressedSize; // if 0, then the file is empty (?)
	uint32_t totalUncompressedSize; // if 0, then the file is empty (?)
	uint8_t unknown28;
	uint8_t unknown29;
	uint8_t unknown2A;
	uint8_t unknown2B;
	int unknown2C;
	int unknown30;
	int unknown34;
	uint64_t unknown38;
	int groupTag; // -1 if not a tag
	uint32_t uncompressedHeaderSize;
	uint32_t uncompressedTagDataSize;
	uint32_t uncompressedResourceDataSize;
	int16_t unknown50;
	int16_t unknown52;
	int unknown54;
};
EXPECT_SIZE(BlamModuleFile, 0x58);

struct BlamModuleCompressedBlock
{
	//uint64_t checksum; // MurmurHash3_128 of uncompressed data (only the lower 64 bits are used)
	uint32_t compressedOffset; // relative to the file's compressedOffset
	uint32_t compressedSize;
	uint32_t uncompressedOffset; // offset in the result buffer to put the data
	uint32_t uncompressedSize;
	bool compressed;
	//uint64_t padding1C;
	//uint32_t padding;
	//uint16_t padding2;
	//uint8_t padding3;
};
EXPECT_SIZE(BlamModuleCompressedBlock, 0x14);
