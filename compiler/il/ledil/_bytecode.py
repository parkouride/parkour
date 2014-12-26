import struct
import logging

logger = logging.getLogger(__name__)

BYTE_CODE_VERSION = 1


class OpCodes(object):
    NOP = 0x00
    PUSH = 0x01
    POP = 0x02

    SET_ALL = 0x10
    DELAY = 0x11

    NEXT_STATE = 0xFE
    END_STATE = 0xFF


class TypeCodes(object):
    BYTE = 0x01
    SHORT = 0x02
    COLOR = 0x03


class RequirementCodes(object):
    ACCEL = 0x01
    GYRO = 0x02
    MAG = 0x04
    BAROMETER = 0x08

    @classmethod
    def IMU(cls):
        return cls.ACCEL | cls.GYRO | cls.MAG

    @classmethod
    def IMUB(cls):
        return cls.IMU() | cls.BAROMETER


def requirements_mask(requirements):
    retval = 0

    for requirement in requirements:
        if (hasattr(RequirementCodes, requirement.upper())):
            value = getattr(RequirementCodes, requirement.upper())
            if callable(value):
                value = value()
            retval |= value
        else:
            logger.warning("Requirement {0} unknown".format(requirement))

    return retval


class ByteCodeGenerator(object):
    @staticmethod
    def set_all(r, g, b):
        return ByteCodeGenerator.push_color(r, g, b) + struct.pack("B", OpCodes.SET_ALL)

    @staticmethod
    def delay(value):
        return ByteCodeGenerator.push_short(value) + struct.pack("B", OpCodes.DELAY)

    @staticmethod
    def push_color(r, g, b):
        return struct.pack("BBBBB", OpCodes.PUSH, TypeCodes.COLOR, r, g, b)

    @staticmethod
    def push_byte(value):
        return struct.pack("BBB", OpCodes.PUSH, TypeCodes.BYTE, value)

    @staticmethod
    def push_short(value):
        return struct.pack("<BBh", OpCodes.PUSH, TypeCodes.SHORT, value)

    @staticmethod
    def str(value):
        fmt = "{}p".format(len(value) + 1)
        return struct.pack(fmt, value)

    @staticmethod
    def end():
        return struct.pack("B", OpCodes.END_STATE)

    @staticmethod
    def next_state(value):
        return ByteCodeGenerator.push_byte(value) + struct.pack("B", OpCodes.NEXT_STATE)

    @staticmethod
    def header(states, requirements, decision_offset, debug_offset, version=BYTE_CODE_VERSION, pixel_count=8):
        print("header")
        static_fmt = "<ccccBBhhhh"
        retval = struct.pack(
            static_fmt, 'P', 'A', 'R', 'K',
            len(states),
            pixel_count,
            version,
            requirements_mask(requirements),
            debug_offset,
            decision_offset,
        )

        order_state_keys = sorted(states.keys(), key=lambda x: states[x].offset)
        for key in order_state_keys:
            retval += struct.pack('<h', states[key].offset)

        retval += struct.pack('cccc', 'H', 'E', 'N', 'D')
        return retval
