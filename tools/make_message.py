from argparse import ArgumentParser
from sys import argv
from json import loads
from datetime import datetime
from os import makedirs

from caddieutil.stream import OutputStream, StreamEndian
from caddieutil.message import CMSGBlock, DESCBlock, DATABlock

CMSG_HEADER_ROOT = "include/caddie/cmsg"


def write_binary(messages: list[str], args):
    """Write specified messages to CMSG binary"""
    try:
        strm = OutputStream(args.cmsg, StreamEndian.BIG)
    except OSError:
        print(f"[FATAL] Could not open CMSG file for writing: {args.cmsg}")
        return

    # Create blocks
    data = DATABlock(messages)
    desc = data.gen_desc()
    cmsg = CMSGBlock([desc, data])

    # Write to file
    cmsg.write(strm)

    strm.close()


def write_header(message_keys: list[str], args):
    """Write C++ header file for use with the CMSG binary"""

    # Create header file path using JSON file name
    last_dir_idx = max(args.json.rfind("/"), args.json.rfind("\\"))
    file_ext_idx = args.json.rfind(".")
    file_name = args.json[last_dir_idx+1:file_ext_idx]
    header_path = f"{CMSG_HEADER_ROOT}/{file_name}.h"

    # Create header directory if it doesn't exist
    makedirs(CMSG_HEADER_ROOT, exist_ok=True)

    with open(header_path, "w+") as f:
        # Comment from tool
        now = datetime.now()
        f.write("/**\n")
        f.write(
            f" * Auto-generated by make_message.py on {now.strftime('%m/%d/%Y (%H:%M:%S)')}\n")
        f.write(" * Don't edit this unless you know what you are doing,\n")
        f.write(" * as manual changes will be overwritten on the next build.\n")
        f.write(" */\n")

        f.write("\n")

        # Begin header guard
        f.write(f"#ifndef CMSG_{file_name.upper()}_H\n")
        f.write(f"#define CMSG_{file_name.upper()}_H\n")

        f.write("\n")

        # Begin caddie namespace
        f.write("namespace caddie {\n")

        f.write("\n")

        f.write(f"enum {file_name} {{\n")
        for msg_key in message_keys:
            f.write(f"    {msg_key},\n")
        f.write("};\n")

        f.write("\n")

        # End caddie namespace
        f.write("} // namespace caddie\n")

        f.write("\n")

        # End header guard
        f.write(f"#endif\n")


def convert_json(args):
    """Parse and validate JSON message file, before converting it to binary form"""

    # Attempt to decode JSON data
    try:
        with open(args.json, "rb") as f:
            json_data = loads(f.read())
    except FileNotFoundError:
        print(f"[FATAL] JSON file could not be opened: {args.json}")
        return
    except UnicodeDecodeError:
        print(f"[FATAL] JSON data could not be decoded: {args.json}")
        return

    # Message data
    msg_messages = json_data.get("messages", [])
    if len(msg_messages) == 0:
        print("[FATAL] No messages exist in the JSON file")
        return

    # CMSG binary
    write_binary(msg_messages.values(), args)
    # Generate C++ header
    write_header(msg_messages.keys(), args)


def main():
    # Parse command-line arguments
    parser = ArgumentParser()
    parser.add_argument("--json", type=str, required=True,
                        help="JSON file from which to create message binary")
    parser.add_argument("--cmsg", type=str, required=True,
                        help="Path to output message binary")
    args = parser.parse_args(argv[1:])

    convert_json(args)


if __name__ == "__main__":
    main()
