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

    @staticmethod
    def _add_set_all(arguments):
        if arguments.type == "RGB":
            return [bcg.set_all(arguments.red, arguments.green, arguments.blue)]
        else:
            return ()

    @staticmethod
    def _add_delay(arguments):
        if arguments.type == "duration":
            duration = arguments.value
            value = int(duration.integer.value)
            units = duration.units

            if units == "s":
                value *= 1000
            return [bcg.delay(value)]

        return ()

    @staticmethod
    def _add_next(arguments):

        def _generate(state_name, symbol_table):
            return bcg.next_state(symbol_table[state_name])

        if arguments.type == "symbol":
            state = arguments.value

            return [lambda x: _generate(state, x)]

        return ()

    def write(self, stream, symbol_table):
        for buf in self._buffer:
            if callable(buf):
                buf = buf(symbol_table)

            stream.write(buf)
        stream.write(bcg.end())

    def __len__(self):
        retval = sum((len(x) for x in self._buffer if not callable(x))) 
        retval += sum(4 for x in self._buffer if callable(x))  # Callables are always push, need to figure out how to calculate this
        retval += 1  # End of State Marker

        return retval

    @property
    def offset(self):
        return self._offset

    @offset.setter
    def offset(self, value):
        self._offset = value
