#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <unordered_map>

#define BUFFER_SIZE 1024
namespace smartDescriptor {

    enum FieldFlags : int {
        CIVILITY = 0,
        LASTNAME = 1,
        FIRSTNAME = 2,
        LASTNAME_FIRSTNAME = 3,
        BIRTHDAY = 4,
        LINE2 = 5,
        LINE3 = 6,
        STREET = 7,
        ZIPCODE = 8,
        CITY = 9,
        COUNTRY = 10,
        ZIPCODE_CITY = 11,
        PHONE = 12,
        PHONE_FIX = 13,
        PHONE_MOB = 14,
        EMAIL = 15
    };

    const std::unordered_map<FieldFlags, std::string> field{
            {LASTNAME,           "lastname"},
            {FIRSTNAME,          "firstname"},
            {LASTNAME_FIRSTNAME, "lastname_firstname"},
            {BIRTHDAY,           "birthday"},
            {LINE2,              "line2"},
            {LINE3,              "line3"},
            {STREET,             "street"},
            {ZIPCODE,            "zipcode"},
            {CITY,               "city"},
            {COUNTRY,            "country"},
            {ZIPCODE_CITY,       "zipcode_city"},
            {PHONE,              "phone"},
            {PHONE_FIX,          "phone_fix"},
            {PHONE_MOB,          "phone_mob"}
    };

    enum Compressed : int {
        GZ = 0,
        LZMA = 1,
        LZ = 2,
        XZ = 3,
        Z = 4,
        BZ2 = 5,
        NO_COMPRESSED = 6
    };
    const std::unordered_map<std::string, Compressed> compressedFile{
            {"GZ",   GZ},
            {"XZ",   XZ},
            {"LZ",   LZ},
            {"LZMA", LZMA},
            {"Z",    Z},
            {"BZ2",  BZ2}
    };

    enum Archive : int {
        ZIP = 0,
        TAR = 1,
        NO_ARCHIVE = 2
    };

    const std::unordered_map<std::string, Archive> archiveFile{
            {"ZIP", ZIP},
            {"TAR", TAR}
    };

    enum Extension : int {
        CSV = 0,
        TXT = 1,
        NO_EXTENSION = 2
    };

    const std::unordered_map<std::string, Extension> extensionFile{
            {"CSV", CSV},
            {"TXT", TXT}
    };

    enum Encoding {
        None,                // Unknown or binary
        ANSI,                // 0-255
        ASCII,                // 0-127
        UTF8_BOM,            // UTF8 with BOM
        UTF8_NOBOM,            // UTF8 without BOM
        UTF16_LE_BOM,        // UTF16 LE with BOM
        UTF16_LE_NOBOM,        // UTF16 LE without BOM
        UTF16_BE_BOM,        // UTF16-BE with BOM
        UTF16_BE_NOBOM,        // UTF16-BE without BOM
        ISO_8859_1,         // ISO_8859_1
        ISO_8859_15         // ISO_8859_15
    };

    inline const std::string &pathFile(std::string const &envVariable) {
        try {
            const static std::string path = std::getenv(envVariable.c_str());
            return path;
        }
        catch (std::exception &e) {
            std::cerr << envVariable + " not found " << std::endl;
            throw e;
        }
    }
}
#endif