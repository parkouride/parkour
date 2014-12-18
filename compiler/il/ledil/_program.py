import re

from _bytecode import ByteCodeGenerator as bcg

INSERT_UNDERSCORE_RE = re.compile('(.)([A-Z][a-z]+)')
FIRST_UNDERSCORE_RE = re.compile('([a-z0-9])([A-Z])')

__all__ = ['_StateProgram']


def functionize(obj, opcode, default_=None):
    s1 = INSERT_UNDERSCORE_RE.sub(r'\1_\2', opcode)
    func_name = "_add_{}".format(FIRST_UNDERSCORE_RE.sub('\1_\2', s1).lower())

    return getattr(obj, func_name, default_)

class _StateProgram(object):
    def __init__(self):
        self._buffer = []

    def add_line(self, tokens):
        func = functionize(self, tokens.opcode)
        if callable(func):
            self._buffer.extend(func(tokens.arguments))

    def _add_set_all(self, arguments):
        if arguments.type == "RGB":
            return (
                bcg.set_all(),
                bcg.color_type(arguments.red, arguments.green, arguments.blue)
            )
        else:
            return ()
