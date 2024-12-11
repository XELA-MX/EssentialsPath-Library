#pragma once

#define _WIN32_WINNT 0x0600
#define NTDDI_VERSION 0x06000000

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#include <initguid.h>
#include <knownfolders.h>
#else
#include <cstdlib>
#include <pwd.h>
#include <unistd.h>
#endif

enum class FolderType {
    DOCUMENTS,
    DOWNLOADS,
    DESKTOP,
    PICTURES,
    MUSIC,
    VIDEOS
};

template<typename T>
inline constexpr bool always_false = false;

template<typename ReturnType = std::filesystem::path>
ReturnType getFolderPath(FolderType folderType) {
    std::filesystem::path result;

#ifdef _WIN32 // Windows
    std::unordered_map<FolderType, const KNOWNFOLDERID*> folderMap = {
        {FolderType::DOCUMENTS, &FOLDERID_Documents},
        {FolderType::DOWNLOADS, &FOLDERID_Downloads},
        {FolderType::DESKTOP, &FOLDERID_Desktop},
        {FolderType::PICTURES, &FOLDERID_Pictures},
        {FolderType::MUSIC, &FOLDERID_Music},
        {FolderType::VIDEOS, &FOLDERID_Videos}
    };

    auto it = folderMap.find(folderType);
    if (it == folderMap.end()) {
        throw std::invalid_argument("Invalid folder type");
    }

    PWSTR path = nullptr;
    HRESULT hr = SHGetKnownFolderPath(*(it->second), 0, nullptr, &path);

    if (SUCCEEDED(hr)) {
        result = path;
        CoTaskMemFree(path);
    } else {
        throw std::runtime_error("Failed to get folder path");
    }
#else // Linux and macOS
    std::unordered_map<FolderType, std::string> folderMap = {
        {FolderType::DOCUMENTS, "Documents"},
        {FolderType::DOWNLOADS, "Downloads"},
        {FolderType::DESKTOP, "Desktop"},
        {FolderType::PICTURES, "Pictures"},
        {FolderType::MUSIC, "Music"},
        {FolderType::VIDEOS, "Videos"}
    };

    auto it = folderMap.find(folderType);
    if (it == folderMap.end()) {
        throw std::invalid_argument("Invalid folder type");
    }

    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        homeDir = getpwuid(getuid())->pw_dir;
    }

    result = std::filesystem::path(homeDir) / it->second;

    if (!std::filesystem::exists(result)) {
        throw std::runtime_error("Folder does not exist: " + result.string());
    }
#endif

    if constexpr (std::is_same_v<ReturnType, std::filesystem::path>) {
        return result;
    } else if constexpr (std::is_same_v<ReturnType, std::string>) {
        return result.string();
    } else if constexpr (std::is_same_v<ReturnType, const char*>) {
        static std::string str = result.string();
        return str.c_str();
    } else {
        static_assert(always_false<ReturnType>, "Unsupported return type");
    }
}
