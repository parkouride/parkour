import logging
import re

logger = logging.getLogger(__name__)

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
        self._offset = -1

    def add_line(self, tokens):
        try:
            func = functionize(self, tokens.opcode)
            if callable(func):
                self._buffer.extend(func(tokens.arguments))
        except:
            logger.error("Unable to add line: {}".format(tokens), exc_info=True)

    def _add_set_all(self, arguments):
        if arguments.type == "RGB":
            return (
                bcg.set_all(),
                bcg.color_type(arguments.red, arguments.green, arguments.blue)
            )
        else:
            return ()

    def _add_delay(self, arguments):
        if arguments.type == "duration":
            duration = arguments.value
            value = duration.integer.value
            units = duration.units

            if units == "s":
                value *= 1000

            bcg.delay()

        return ()

    def write(self, stream):
        for buf in self._buffer:
            stream.write(buf)

    def __len__(self):
        return sum((len(x) for x in self._buffer))

    @property
    def offset(self):
        return self._offset

    @offset.setter
    def offset(self, value):
        self._offset = value
