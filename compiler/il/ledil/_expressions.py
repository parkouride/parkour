import pyparsing as pp

Symbol = pp.Word(pp.alphas, pp.alphanums).setResultsName("symbol")
Number = pp.Word('123456789', '0123456789').setResultsName("integer")
Byte = pp.Word('012345678', '0123456789', exact=2).setResultsName("byte")
RGB = pp.Group(pp.Literal("#").suppress() + Byte + Byte + Byte).setResultsName("color")
