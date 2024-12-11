#pragma once

#include <string>
#include <windows.h>
#include <shlobj.h>
#include <unordered_map>

enum class FolderType {
    DOCUMENTS,
    DOWNLOADS,
    DESKTOP,
    PICTURES,
    MUSIC,
    VIDEOS
};

std::string getFolderPath(FolderType folderType) {
    std::unordered_map<FolderType, int> folderMap = {
        {FolderType::DOCUMENTS, CSIDL_MYDOCUMENTS},
        {FolderType::DOWNLOADS, CSIDL_PROFILE},
        {FolderType::DESKTOP, CSIDL_DESKTOP},
        {FolderType::PICTURES, CSIDL_MYPICTURES},
        {FolderType::MUSIC, CSIDL_MYMUSIC},
        {FolderType::VIDEOS, CSIDL_MYVIDEO}
    };

    auto it = folderMap.find(folderType);
    if (it == folderMap.end()) {
        return "";
    }

    wchar_t folder[MAX_PATH];
    HRESULT hr = SHGetFolderPathW(NULL, it->second, NULL, 0, folder);

    if (SUCCEEDED(hr)) {
        char str[MAX_PATH];
        size_t convertedChars = 0;
        wcstombs_s(&convertedChars, str, sizeof(str), folder, _TRUNCATE);
        return std::string(str);
    }

    return "";
}
