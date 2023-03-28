from caddie_py.layout.lyt1_block import LYT1Block
from caddie_py.layout.txl1_block import TXL1Block
from caddie_py.layout.fnl1_block import FNL1Block
from caddie_py.stream.file_stream import *
from caddie_py.stream.stream_base import Endian


def test_lyt1():
    strm = FileStream(Endian.Big)
    strm.open("test_lyt1.bin", OpenMode.Write, DataMode.Binary)

    blk = LYT1Block(res={
        "centered": True,
        "size": {"width": 640.0, "height": 480.0}
    })
    blk.write(strm)

    strm.close()


def test_txl1():
    strm = FileStream(Endian.Big)
    strm.open("test_txl1.bin", OpenMode.Write, DataMode.Binary)

    blk = TXL1Block()
    blk.add_texture("tt_eventName_baloon_01.tpl")
    blk.add_texture("tt_eventName_baloon_01_shadow.tpl")
    blk.add_texture("tt_remo_00.tpl")
    blk.add_texture("tt_remo_nun_00.tpl")
    blk.write(strm)

    strm.close()


def test_fnl1():
    strm = FileStream(Endian.Big)
    strm.open("test_fnl1.bin", OpenMode.Write, DataMode.Binary)

    blk = FNL1Block()
    blk.add_font("00_WS2_nRodB_32_IA4.brfnt")
    blk.add_font("01_WS2_nRodEb_60_IA4.brfnt")
    blk.write(strm)

    strm.close()


def main():
    test_lyt1()
    test_txl1()
    test_fnl1()


main()
