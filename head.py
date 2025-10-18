"""
this is a crappy script to help me generate the header part
"""

from pathlib import Path


def gen_c_header():
    cfile = Path(__file__).with_name("pacts.c")

    with cfile.open() as fp:
        for line in fp:
            if line.startswith((" ", "/", "*", "#")):
                continue
            header = (
                line
                .strip("\n")
                .replace("{", "")
                .replace("}", "")
                .strip()
            )
            if len(header) < 2:
                continue
            # functions
            if header.endswith(";"):
                continue
            header += ";"
            print(header)


if __name__ == "__main__":
    gen_c_header()

