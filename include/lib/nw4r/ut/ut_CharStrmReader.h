#ifndef NW4R_UT_CHAR_STRM_READER_H
#define NW4R_UT_CHAR_STRM_READER_H
#include <types_nw4r.h>

namespace nw4r {
namespace ut {

class CharStrmReader {
public:
    typedef u16 (CharStrmReader::*ReaderFunc)();

    CharStrmReader(ReaderFunc ReaderFunc)
        : mCharStrm(NULL), mReaderFunc(ReaderFunc) {}
    ~CharStrmReader() {}

    u16 ReadNextCharUTF8();
    u16 ReadNextCharUTF16();
    u16 ReadNextCharCP1252();
    u16 ReadNextCharSJIS();

    template <typename T> T GetChar(int offset) const {
        const T* strm = reinterpret_cast<const T*>(mCharStrm);
        return strm[offset];
    }

    template <typename T> void StepStrm(int offset) {
        mCharStrm += offset * sizeof(T);
    }

    u16 Next() { return (this->*mReaderFunc)(); }

    void Set(const char* charStrm) { mCharStrm = charStrm; }
    void Set(const wchar_t* charStrm) {
        mCharStrm = reinterpret_cast<const char*>(charStrm);
    }

private:
    const char* mCharStrm;  // at 0x0
    ReaderFunc mReaderFunc; // at 0x4
};

} // namespace ut
} // namespace nw4r

#endif
