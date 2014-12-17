""" Compiler for the LED Intermediate Language for generating led binary files
"""

import argparse
import sys
import logging

from ledil.compiler import Compiler

def usage(args):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verbose", "-v", action="store_true", default=False)
    parser.add_argument("file", nargs="+")

    return parser.parse_args(args)

def main(args=sys.argv[1:]):
    logging.basicConfig(level=logging.INFO)
    args = usage(args)

    if args.verbose:
        logging.getLogger().setLevel(level=logging.DEBUG)

    [Compiler(x).compile() for x in args.file]
