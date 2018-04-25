/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#if defined(_WIN32)
#include <direct.h>
#else
//#include "sysstat.h"
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <typeinfo>
#include <vector>
#include <sstream>
#include <iostream>

#include <string.h>

#include <processing/common/commonMethods.hpp>

#include <system/PMDTimeInfo.hpp>

#ifndef INT16_MAX
#define INT16_MAX 32767
#endif

#define char_CAST( param ) reinterpret_cast<char *> ( param )

inline int  pmd_mkdir (const char *dirName)
{
#if defined(_WIN32)
    return _mkdir (dirName);
#else
    return mkdir (dirName, 0777);
#endif
}

// fopen
#if defined(_WIN32)

#define pmd_fopen( file, filename, mode ) \
fopen_s( &file, filename, mode );
#else

#define pmd_fopen( file, filename, mode ) \
file = fopen ( filename, mode )
#endif

template <typename T>
std::string pmd_numberToString (T Number)
{
    std::stringstream ss;

    if ( (typeid (T) != typeid (char)) && (typeid (T) != typeid (uint8_t)))
    {
        ss << Number;
    }
    else
    {
        ss << static_cast<uint32_t> (Number);
    }

    return ss.str();
}


template<typename T> void pmd_saveImage (const std::string &fileName, const uint32_t height, const uint32_t width, T *data)
{
    FILE *pFile;

    T min = data[0];
    T max = data[0];
    uint32_t numPixel = height * width;

    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        if (data[idx] < min)
        {
            if (data[idx] < min)
            {
                min = data[idx];
            }

            if (data[idx] > max)
            {
                max = data[idx];
            }
        }
    }

    pmd_fopen (pFile, fileName.c_str(), "wb");
    std::string strImgWidth = pmd_numberToString (width);
    std::string strImgHeight = pmd_numberToString (height);
    std::string header = "P6\n" + strImgWidth + " " + strImgHeight + "\n255\n";
    fclose (pFile);

    pmd_fopen (pFile, fileName.c_str(), "ab");
    fwrite (header.c_str(), sizeof (char), header.size(), pFile);

    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        if (data[idx] > max)
        {
            uint8_t pixel[3];
            float value;
            value = ( (float) data[idx] - (float) min) / (float) max;
            pixel[0] = 255 * static_cast<uint8_t> (pmd_round (value));
            pixel[1] = 255 * static_cast<uint8_t> (pmd_round (value));
            pixel[2] = 255 * static_cast<uint8_t> (pmd_round (value));
            fwrite (pixel, sizeof (uint8_t), 3, pFile);
        }
    }
    fclose (pFile);
}

template<typename T> bool pmd_saveArrayToStream (std::ofstream &stream, size_t size, T *data)
{
    if (!stream.good())
    {
        return false;
    }
    auto byteSize = sizeof (T) * size;
    auto bytePtr = reinterpret_cast<const char *> (data);
    stream.write (bytePtr, byteSize);
    return stream.good();
}

template<typename T> bool pmd_saveArrayToFile (const std::string &fullfileName, size_t size, const T *data, std::ios_base::openmode mode = std::ofstream::out | std::ofstream::binary | std::ofstream::trunc)
{
    std::ofstream stream (fullfileName, mode);
    return pmd_saveArrayToStream (stream, size, data);
}


template<typename T> bool pmd_saveArray (const std::string &fileName, size_t size, T *data)
{
    return pmd_saveArrayToFile (fileName, size, data, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
}


template<typename T> bool pmd_saveArrayAdd (const std::string &fileName, size_t size, T *data)
{
    return pmd_saveArrayToFile (fileName, size, data, std::ofstream::out | std::ofstream::binary | std::ofstream::app);
}


template<typename T> bool pmd_saveArraySingle (const std::string &fileName, T data)
{
    std::ofstream fileEntry;
    fileEntry.open (fileName);

    if (!fileEntry.is_open())
    {
        return false;
    }

    auto byteSize = sizeof (T);
    auto bytePtr = reinterpret_cast<const char *> (&data);

    fileEntry.write (bytePtr, byteSize);
    return fileEntry.good();
}

//added by zhudm, start
//extern std::string calibrationSaveDir;
template<typename T> bool sunny_saveArray (const std::string &fileName, size_t size, T *data)
{
    std::string dirTree = "/data/sunny/hand/Process_Calib";
    std::string fullName = dirTree + "/" + fileName + ".bin";
    return pmd_saveArrayToFile (fullName, size, data);
}

//added by zhudm, end

template<typename T> bool pmd_saveVector (const std::string &fileName, std::vector<T> &data)
{
    return pmd_saveArray (fileName, data.size(), data.data());
}

inline size_t getStreamSize (std::istream &stream)
{
    std::streampos failure (-1);
    auto curpos = stream.tellg();
    if (curpos == failure)
    {
        return 0;
    }
    stream.seekg (0, stream.beg);
    auto startpos = stream.tellg();
    stream.seekg (0, stream.end);
    auto endpos = stream.tellg();
    stream.seekg (curpos, stream.beg);
    if (startpos == failure || endpos == failure)
    {
        return 0;
    }
    return static_cast<size_t> (endpos - startpos);
}

inline size_t getFileSize (const std::string &filename)
{
    std::ifstream file (filename);
    if (file.good())
    {
        return getStreamSize (file);
    }
    return 0;
}

template<typename T> bool pmd_loadVector (const std::string &filename, std::vector<T> &data)
{
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return false;
    }
    auto size = getStreamSize (file);
    if (!file.good() || size == 0)
    {
        return false;
    }
    auto elements = size;
    if (size != 1)
    {
        elements = size / sizeof (T);
    }
    data.resize (elements);
    //reset size if size is not a multiple of sizeof(T)
    size = elements * sizeof (T);
    auto byteptr = reinterpret_cast<char *> (data.data());
    file.read (byteptr, size);
    if (!file)
    {
        return false;
    }
    return true;
}

template<typename T> bool pmd_loadFile (const std::string &filename, std::vector<T> &data)
{
    auto result = pmd_loadVector (filename, data);

    for (uint32_t i = 0; i < data.size(); ++i)
    {
        if (pmd_isNaNOrInfinity (static_cast<float> (data[i])))
        {
            data[i] = T {};
        }
    }

    return result;
}

template<typename T> size_t pmd_loadArray (const std::string &filename, T **data)
{
    *data = nullptr;
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return 0;
    }
    auto byteSize = getStreamSize (file);
    if (!file.good() || byteSize == 0)
    {
        return 0;
    }
    auto elements = byteSize;
    if (byteSize != 1)
    {
        elements = byteSize / sizeof (T);
    }
    //reset byteSize if size is not a multiple of sizeof(T)
    byteSize = elements * sizeof (T);
    if (typeid (T) != typeid (char))
    {
        *data = reinterpret_cast<T *> (malloc (byteSize));
        if (*data)
        {
            memset (*data, 0, byteSize);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *data = reinterpret_cast<T *> (malloc (byteSize + 1));
        if (*data)
        {
            memset (*data, 0, byteSize + 1);
        }
        else
        {
            return 0;
        }
    }
    auto byteptr = reinterpret_cast<char *> (*data);
    file.read (byteptr, byteSize);
    if (!file)
    {
        return 0;
    }
    return elements;
}

template<typename T> bool pmd_loadScalar (std::string filename, T *data)
{
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return false;
    }
    auto size = getStreamSize (file);
    if (!file.good() || size != sizeof (T))
    {
        return false;
    }
    auto byteptr = reinterpret_cast<char *> (data);
    file.read (byteptr, size);
    if (!file)
    {
        return false;
    }
    return true;
}

/** \brief returns parent directory of the given path
 *
 * \param path a relative or absolute file or directory path
 * \return the parent part of the given path. if the path
 * contains no parent part "./" is returned
 *
 */
inline std::string pmd_getDirectory (const std::string &path)
{
#if defined(_WIN32)
    const char pasep = '\\';
#else
    const char pasep = '/';
#endif

    auto pos = path.find_last_of (pasep);

    if (pos != 0 && pos == path.size() - 1)
    {
        pos = path.find_last_of (pasep, pos - 1);
    }

    if (pos != std::string::npos)
    {
        return path.substr (0, pos + 1);
    }

    return std::string (".") + pasep;
}

/**
 * Loads a binary file into a vector
 * Throws const char* if loading the file failed
 *
 * @param filepath file
 *
 * @return vector with binary data
 */
std::vector<uint8_t> loadData (const std::string &file);
