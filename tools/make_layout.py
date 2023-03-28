from caddie_py.layout.fnl1_block import FNL1Block
from caddie_py.layout.lyt1_block import LYT1Block
from caddie_py.stream.file_stream import *
from caddie_py.stream.stream_base import Endian

def test_lyt1():
    strm = FileStream(Endian.Big)
    strm.open("test_lyt1.bin", OpenMode.Write, DataMode.Binary)

    blk = LYT1Block(res={
        "centered" : True,
        "size" : {"width" : 640.0, "height" : 480.0}   
    })
    blk.write(strm)
    
    strm.close()

def test_fnl1():
    strm = FileStream(Endian.Big)
    strm.open("test_fnl1.bin", OpenMode.Write, DataMode.Binary)

    blk = FNL1Block()
    blk.add_font("/WS2_rodin2.brfnt")
    blk.add_font("/WS2_rodin4.brfnt")
    blk.write(strm)

    strm.close()

def main():
    test_lyt1()
    test_fnl1()


main()
