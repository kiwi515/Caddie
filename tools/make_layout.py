from caddie_py.layout.lyt1_block import LYT1Block
from caddie_py.layout.txl1_block import TXL1Block
from caddie_py.layout.fnl1_block import FNL1Block
from caddie_py.layout.pan1_block import PAN1Block
from caddie_py.layout.pas1_block import PAS1Block
from caddie_py.layout.pae1_block import PAE1Block
from caddie_py.layout.mat1_block import MAT1Block
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


def test_mat1():
    strm = FileStream(Endian.Big)
    strm.open("test_mat1.bin", OpenMode.Write, DataMode.Binary)

    blk = MAT1Block([
        {
            "name": "M_materialA_00",
            "tev_colors": [
                {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 255,
                },
                {
                    "r": 128,
                    "g": 128,
                    "b": 128,
                    "a": 255,
                },
                {
                    "r": 255,
                    "g": 255,
                    "b": 255,
                    "a": 255,
                }
            ],
            "tev_k_colors": [
                {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 255,
                },
                {
                    "r": 128,
                    "g": 128,
                    "b": 128,
                    "a": 255,
                },
                {
                    "r": 255,
                    "g": 255,
                    "b": 255,
                    "a": 255,
                },
                {
                    "r": 1,
                    "g": 2,
                    "b": 3,
                    "a": 255,
                }
            ],
            "bit_gx_nums": {
                "num_tex_map": 0,
                "num_tex_srt": 1,
                "num_tex_coord_gen": 0,
                "num_ind_srt": 1,
                "num_ind_stage": 0,
                "has_tev_swap": 1,
                "num_tev_stage": 0,
                "has_chan_ctrl": 1,
                "has_mat_color": 0,
                "has_alpha_comp": 1,
                "has_blend_mode": 0
            }
        },
        {
            "name": "M_materialB_00",
            "tev_colors": [
                {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 255,
                },
                {
                    "r": 128,
                    "g": 128,
                    "b": 128,
                    "a": 255,
                },
                {
                    "r": 255,
                    "g": 255,
                    "b": 255,
                    "a": 255,
                }
            ],
            "tev_k_colors": [
                {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 255,
                },
                {
                    "r": 128,
                    "g": 128,
                    "b": 128,
                    "a": 255,
                },
                {
                    "r": 255,
                    "g": 255,
                    "b": 255,
                    "a": 255,
                },
                {
                    "r": 1,
                    "g": 2,
                    "b": 3,
                    "a": 255,
                }
            ],
            "bit_gx_nums": {
                "num_tex_map": 0,
                "num_tex_srt": 1,
                "num_tex_coord_gen": 0,
                "num_ind_srt": 1,
                "num_ind_stage": 0,
                "has_tev_swap": 1,
                "num_tev_stage": 0,
                "has_chan_ctrl": 1,
                "has_mat_color": 0,
                "has_alpha_comp": 1,
                "has_blend_mode": 0
            }
        }
    ])
    blk.write(strm)

    strm.close()


def test_pan1():
    strm = FileStream(Endian.Big)
    strm.open("test_pan1.bin", OpenMode.Write, DataMode.Binary)

    blk = PAN1Block(res={
        "flags": 0x11,
        "base_position": 0x22,
        "alpha": 0x33,
        "name": "N_myPane_00",
        "user_data": "01234567",
        "translate": {
            "x": 0.0,
            "y": 1.0,
            "z": 2.0
        },
        "rotate": {
            "x": 3.0,
            "y": 4.0,
            "z": 5.0
        },
        "scale": {
            "x": 6.0,
            "y": 7.0
        },
        "size": {
            "width": 8.0,
            "height": 9.0
        }
    })

    blk.write(strm)
    strm.close()


def test_pas1():
    strm = FileStream(Endian.Big)
    strm.open("test_pas1.bin", OpenMode.Write, DataMode.Binary)

    blk = PAS1Block(children=[
        {
            "flags": 0x11,
            "base_position": 0x22,
            "alpha": 0x33,
            "name": "N_myChild_00",
            "user_data": "",
            "translate": {
                "x": 0.0,
                "y": 1.0,
                "z": 2.0
            },
            "rotate": {
                "x": 3.0,
                "y": 4.0,
                "z": 5.0
            },
            "scale": {
                "x": 6.0,
                "y": 7.0
            },
            "size": {
                "width": 8.0,
                "height": 9.0
            }
        },
        {
            "flags": 0x44,
            "base_position": 0x55,
            "alpha": 0x66,
            "name": "N_myChild_01",
            "user_data": "",
            "translate": {
                "x": 0.0,
                "y": 1.0,
                "z": 2.0
            },
            "rotate": {
                "x": 3.0,
                "y": 4.0,
                "z": 5.0
            },
            "scale": {
                "x": 6.0,
                "y": 7.0
            },
            "size": {
                "width": 8.0,
                "height": 9.0
            }
        }
    ])

    blk.write(strm)
    strm.close()


def test_pae1():
    strm = FileStream(Endian.Big)
    strm.open("test_pae1.bin", OpenMode.Write, DataMode.Binary)

    blk = PAE1Block()
    blk.write(strm)

    strm.close()


def main():
    test_lyt1()

    # Resources
    test_txl1()
    test_fnl1()
    test_mat1()

    # Panes
    test_pan1()
    test_pas1()
    test_pae1()


main()
