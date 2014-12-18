import pyparsing as pp


class _StateType(object):
    def __init__(self, type_name, value):
        self.type = type_name
        self._value = value[0]
        try:
            self._keys = self._attach_value()
        except:
            logger.error("Unable to parse type: {}".format(self.type), exc_info=True)

    def _attach_value(self):
        setattr(self, "value", self._value)
        return ["value"]

    def keys(self):
        return self._keys

    def __repr__(self):
        pairs = list(("=".join((k, str(getattr(self, k)))) for k in self._keys))
        params = " ".join(pairs)

        return "<{}: {}>".format(self.type, params)


class _RGBType(_StateType):
    DEC = 10
    HEX = 16

    def __init__(self, base, value):
        self._base = base
        super(_RGBType, self).__init__("RGB", value)

    def _attach_value(self):
        value = self._value
        setattr(self, 'red', int(value[0], self._base))
        setattr(self, 'green', int(value[1], self._base))
        setattr(self, 'blue', int(value[2], self._base))
        return ["red", "green", "blue"]


Symbol = pp.Word(pp.alphas, pp.alphanums) \
    .setResultsName("symbol") \
    .addParseAction(lambda tok: _StateType("symbol", tok))

Number = pp.Word('123456789', '0123456789').setResultsName("integer")
Byte = pp.Word('0123456789abcdef', exact=2).setResultsName("byte")
RGB_EXPRESSION = pp.Group(
    pp.CaselessKeyword("RGB").suppress() +
    pp.Literal("(").suppress() +
    Number + pp.Literal(",").suppress() +
    Number + pp.Literal(",").suppress() +
    Number +
    pp.Literal(")").suppress()
).setResultsName("rgb_expr").addParseAction(lambda tok: _RGBType(_RGBType.DEC, tok))

RGB_LITERAL = pp.Group(
    pp.Literal("#").suppress() +
    Byte + Byte + Byte
).setResultsName("rgb_literal").addParseAction(lambda tok: _RGBType(_RGBType.HEX, tok))

RGB = RGB_EXPRESSION ^ RGB_LITERAL
