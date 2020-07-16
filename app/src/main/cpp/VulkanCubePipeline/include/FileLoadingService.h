#ifndef FILELOADINGSERVICE_H
#define FILELOADINGSERVICE_H

#include <stdio.h>

#include <fstream>
#include <vector>
#include <cstdint>
#include <android_native_app_glue.h>

class FileLoadingService {
public:
    static std::vector<char> readFile(android_app* androidAppCtx, const std::string& filename) {

        AAsset* file = AAssetManager_open(androidAppCtx->activity->assetManager,
                                              filename.c_str(), AASSET_MODE_BUFFER);

        size_t fileLength = AAsset_getLength(file);
        char* fileContent = new char[fileLength];
        AAsset_read(file, fileContent, fileLength);

        AAsset_close(file);

        return std::vector<char>(fileContent, fileContent + fileLength);
    }

};


#endif //!FILELOADINGSERVICE_H