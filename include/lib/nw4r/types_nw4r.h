/**
 * General types include + NW4R structure forward declarations
 */

#ifndef TYPES_NW4R_H
#define TYPES_NW4R_H
#include <types.h>

namespace nw4r {
namespace ut {
namespace detail {

class LinkListImpl;
class ResFontBase;
class RuntimeTypeInfo;

} // namespace detail

struct BinaryBlockHeader;
struct BinaryFileHeader;
class CharStrmReader;
struct CharWidths;
class Color;
class FileStream;
class Font;
struct FontCodeMap;
struct FontInformation;
struct FontTextureGlyph;
struct FontWidth;
struct Glyph;
class IOStream;
template <typename T, int Ofs> class LinkList;
class LinkListNode;
class List;
class NandFileStream;
class ResFont;
class RomFont;

} // namespace ut

namespace math {

class VEC2;
class VEC3;

} // namespace math
} // namespace nw4r

#endif
