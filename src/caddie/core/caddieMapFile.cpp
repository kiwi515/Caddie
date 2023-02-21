#include "caddieMapFile.h"

#include "caddieRuntime.h"
#include "caddieSTL.h"

#include <egg/core.h>
#include <string.h>

namespace caddie {

MapFile::MapFile() : mType(LINK_NONE), mMapBinary(NULL), mIsUnpacked(false) {}

MapFile::~MapFile() { Close(); }

/**
 * @brief Open and parse map file from DVD
 * @param type Linkage (Static or dynamic)
 */
void MapFile::LoadFromDVD(const char* path, LinkType type) {
    CADDIE_ASSERT(path != NULL);
    CADDIE_ASSERT(type != LINK_NONE);

    // Close existing map file
    if (mMapBinary != NULL) {
        Close();
    }

    // Load file from disc
    mMapBinary = static_cast<char*>(EGG::DvdRipper::loadToMainRAM(
        path, NULL, NULL, EGG::DvdRipper::ALLOC_DIR_TOP, 0, NULL, NULL));

    CADDIE_WARN_EX(mMapBinary == NULL, "Map file (%s) could not be opened!",
                   path);

    if (mMapBinary != NULL) {
        mType = type;
        Unpack();
    }
}

/**
 * @brief Close map file and free resources
 */
void MapFile::Close() {
    CADDIE_WARN(mMapBinary == NULL, "[MapFile::Close] Nothing is open");

    TLinkList<Symbol>::Iterator it = mSymbols.Begin();
    for (; it != mSymbols.End(); it++) {
        TLinkList<Symbol>::Iterator next = it++;
        mSymbols.Remove(next);
        delete &*next;
    }

    delete mMapBinary;
    mMapBinary = NULL;

    mIsUnpacked = false;
}

/**
 * @brief Query text section symbol name by address
 */
const MapFile::Symbol* MapFile::QueryTextSymbol(const void* addr) {
    if (mMapBinary == NULL || !mIsUnpacked) {
        return NULL;
    }

    TLinkList<Symbol>::Iterator it = mSymbols.Begin();
    for (; it != mSymbols.End(); it++) {
        // Resolve symbol address
        const void* symbAddr = (it->type == LINK_STATIC)
                                   ? it->addr
                                   : AddToPtr(GetTextStart(), it->offset);

        if (PtrDistance(symbAddr, addr) < it->size) {
            return &*it;
        }
    }

    return NULL;
}

/**
 * @brief Unpack loaded map file
 */
void MapFile::Unpack() {
    if (mIsUnpacked || mMapBinary == NULL) {
        return;
    }

    // Skip map file header (2 lines)
    char* map = mMapBinary;
    for (int i = 0; i < 2; i++) {
        map = cstl::strchr(map, '\n') + 1;
    }

    // Parse lines
    for (char* next = map; (next = cstl::strchr(map, '\n')); map = next + 1) {
        Symbol* sym = new Symbol();

        // Location
        if (mType == LINK_STATIC) {
            sym->addr = reinterpret_cast<void*>(cstl::strtoul(map, &map, 16));
        } else {
            sym->offset = cstl::strtoul(map, &map, 16);
        }

        // Linkage
        sym->type = mType;

        // Size
        sym->size = cstl::strtoul(map, &map, 16);

        // Trim whitespace from name
        while (*map == ' ') {
            map++;
        }
        sym->name = map;

        // Terminate symbol string
        *next = '\0';
        // Remove carriage return
        if (*(next - 1) == '\r') {
            *(next - 1) = '\0';
        }

        mSymbols.Append(sym);
    }

    mIsUnpacked = true;
}

} // namespace caddie
