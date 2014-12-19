import struct


class OpCodes(object):
    NOP = 0x00
    PUSH = 0x01
    POP = 0x02

    SET_ALL = 0x10
    DELAY = 0x11


class TypeCodes(object):
    BYTE = 0x01
    SHORT = 0x02
    COLOR = 0x03


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

