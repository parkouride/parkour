import os.path
import logging

from pyparsing import *


Symbol = Word(alphas, alphanums).setName("symbol")
Number = Word('123456789', '0123456789').setName("integer")
RGB = Group(CaselessKeyword("RGB") + "(" + Number + "," + Number + "," + Number + ")").setName("color")
CompilerDirective = Combine("%" + Symbol).setName("directive")
FullCompilerDirective = Group(CompilerDirective + (Number ^ Symbol))

Header = OneOrMore(FullCompilerDirective)

States = CaselessKeyword("states").setName("states block")
State = CaselessKeyword("state").setName("state")
Decisions = Keyword("decisions").setName("decisions block")
StartBlock = Keyword("{").suppress()
EndBlock = Keyword("}").suppress()

# OpCodes
SetAll = Group(CaselessKeyword("SetAll") + (RGB | CompilerDirective ))


Codes = SetAll

StateEntry = Group(State + Symbol + StartBlock + Optional(Codes) + EndBlock)

StateBlock = Group(States + StartBlock) + OneOrMore(StateEntry) + EndBlock
DecisionBlock = Group(Decisions + StartBlock + EndBlock)

LedFile = Optional(Header) + StateBlock + DecisionBlock

logger = logging.getLogger(__name__)


class Compiler(object):
    def __init__(self, filename):
        self._source = filename
        output, _ = os.path.splitext(filename)
        self._output = "{0}.ledprog".format(output)

    def compile(self):
        logger.info("{0} -> {1}".format(self._source, self._output))
        for token in self._tokenize():
            if isinstance(token, ParseResults):
                pass  # handle all real tokens
            else:
                pass  # handle strings where is really just state

    def _tokenize(self):
        value = LedFile.parseFile(self._source)

        for token in value:
            print(token)
            yield token
