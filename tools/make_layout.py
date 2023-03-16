from caddie_py.layout.fnl1_block import FNL1Block
from caddie_py.stream.file_stream import *
from caddie_py.stream.stream_base import Endian


def main():
    strm = FileStream(Endian.Big)
    strm.open("test_fnl1.bin", OpenMode.Write, DataMode.Binary)

    blk = FNL1Block()
    blk.add_font("/WS2_rodin2.brfnt")
    blk.add_font("/WS2_rodin4.brfnt")
    blk.write(strm)

    strm.close()


main()
