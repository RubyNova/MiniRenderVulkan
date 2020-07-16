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

inline int android_read(void* cookie, char* buf, int size) {
        return AAsset_read((AAsset*)cookie, buf, size);
}

inline int android_write(void* cookie, const char* buf, int size) {
        return EACCES; // can't provide write access to the apk
}

inline fpos_t android_seek(void* cookie, fpos_t offset, int whence) {
        return AAsset_seek((AAsset*)cookie, offset, whence);
}

inline int android_close(void* cookie) {
        AAsset_close((AAsset*)cookie);
        return 0;
}

inline FILE* android_fopen(android_app* androidAppCtx, const char* fname, const char* mode) {
        if(mode[0] == 'w') return NULL;

        AAsset* asset = AAssetManager_open(androidAppCtx->activity->assetManager, fname, 0);
        if(!asset) return NULL;

        return funopen(asset, android_read, android_write, android_seek, android_close);
}


#endif //!FILELOADINGSERVICE_H