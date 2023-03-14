#ifndef NW4R_UT_NAND_FILE_STREAM_H
#define NW4R_UT_NAND_FILE_STREAM_H
#include "ut_FileStream.h"
#include <revolution/NAND.h>
#include <types_nw4r.h>

namespace nw4r {
namespace ut {

class NandFileStream : public FileStream {
public:
    /**
     * NAND callbacks need a reference to the NW4R stream. This structure is
     * used to up-cast the NANDCommandBlock given to the async callback.
     *
     * This structure's NANDCommandBlock is always used in calls to async NAND
     * functions, so it is always a safe assumption that the up-cast is correct.
     *
     * NANDCommandBlock does contain user data however, so they could have just
     * used that field.
     */
    struct AsyncContext {
        NANDCommandBlock block; // at 0x0
        NANDFileInfo info;      // at 0xB8
        NandFileStream* stream; // at 0x144
    };

public:
    NW4R_UT_RTTI_DECL(NandFileStream);

    static void NandAsyncCallback_(s32 result, NANDCommandBlock* block);

    NandFileStream(const char* path, u32 access);
    NandFileStream(const NANDFileInfo* info, u32 access, bool close);
    virtual ~NandFileStream(); // at 0xC

    virtual void Close();                  // at 0x10
    virtual s32 Read(void* dst, u32 size); // at 0x14
    virtual bool ReadAsync(void* dst, u32 size, AsyncCallback callback,
                           void* arg);             // at 0x18
    virtual void Write(const void* src, u32 size); // at 0x1C
    virtual bool WriteAsync(const void* src, u32 size, AsyncCallback callback,
                            void* arg);        // at 0x20
    virtual bool IsBusy() const;               // at 0x24
    virtual bool CanAsync() const;             // at 0x28
    virtual bool CanRead() const;              // at 0x2C
    virtual bool CanWrite() const;             // at 0x30
    virtual u32 GetOffsetAlign() const;        // at 0x34
    virtual u32 GetSizeAlign() const;          // at 0x38
    virtual u32 GetBufferAlign() const;        // at 0x3C
    virtual u32 GetSize() const;               // at 0x40
    virtual void Seek(s32 offset, u32 origin); // at 0x44
    virtual bool CanSeek() const;              // at 0x50
    virtual bool CanCancel() const;            // at 0x54
    virtual u32 Tell() const;                  // at 0x58

    bool Open(const char* path, u32 access);
    bool Open(const NANDFileInfo* info, u32 access, bool close)
        __attribute__((never_inline));

private:
    void Initialize_();

private:
    FilePosition mFilePosition; // at 0x14
    AsyncContext mAsyncContext; // at 0x1C
    bool mCanRead;              // at 0x164
    bool mCanWrite;             // at 0x165
    bool mIsBusy;               // at 0x166
    bool mOwnsOpenNandFile;     // at 0x167
    bool mCloseNandWithStream;  // at 0x168
};

} // namespace ut
} // namespace nw4r

#endif
