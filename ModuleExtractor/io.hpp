#pragma once

#include <fstream>
#include <filesystem>

void ReadData(std::ifstream& stream, int64_t size, uint8_t* out);

template<typename T>
void ReadStruct(std::ifstream& stream, T& out)
{
	ReadData(stream, sizeof(T), reinterpret_cast<uint8_t*>(&out));
}

template<typename T>
void ReadArray(std::ifstream& stream, size_t count, T out[])
{
	ReadData(stream, sizeof(T) * count, reinterpret_cast<uint8_t*>(out));
}

bool WriteData(const uint8_t* data, int64_t size, const std::filesystem::path& path);

template<typename T>
void WriteStruct(const T& value, const std::filesystem::path& path)
{
	WriteData(reinterpret_cast<const uint8_t*>(&value), sizeof(T), path);
}

template<typename T>
void WriteArray(const T values[], size_t count, const std::filesystem::path& path)
{
	WriteData(reinterpret_cast<const uint8_t*>(values), sizeof(T) * count, path);
}

std::filesystem::path SanitizeFileName(const std::filesystem::path& path);

std::filesystem::path MakeLongPath(const std::filesystem::path& path);

void CreateDirectories(const std::filesystem::path& path);