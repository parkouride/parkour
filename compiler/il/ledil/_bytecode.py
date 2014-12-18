import struct


class OpCodes(object):
    SET_ALL = 0x01
    COLOR_TYPE = 0xA0


class ByteCodeGenerator(object):
    @staticmethod
    def push_byte(value):
        pass

    @staticmethod
    def set_all():
        return struct.pack("B", OpCodes.SET_ALL)

    @staticmethod
    def color_type(r, g, b):
        return struct.pack("BBBB", OpCodes.COLOR_TYPE, r, g, b)
