import os.path
import logging

from pyparsing import *

from ledil._expressions import *
from ledil._program import *


logger = logging.getLogger(__name__)

LedFile = Forward()





class Compiler(object):
    current_compiler = None

    def __init__(self, filename):
        Compiler.current_compiler = self
        self._directives = {}
        self._requirements = set()
        self._source = filename
        self._states = {}
        output, _ = os.path.splitext(filename)
        self._output = "{0}.ledprog".format(output)

    def compile(self):
        logger.info("{0} -> {1}".format(self._source, self._output))
        [logger.debug("TOKEN: {}".format(x)) for x in self._tokenize()]

        logger.debug("Directives and Symbols")
        [logger.debug("{0}=>{1}".format(k, v)) for k, v in self._directives.items()]

        logger.debug("Requirements: {}".format(", ".join((str(x) for x in self._requirements))))

    def _tokenize(self):
        value = LedFile.parseFile(self._source)

        for token in value:
            yield token

    @classmethod
    def add_compiler_directive(cls, toks):
        for tok in toks:
            symbol_name = tok.directive.symbol.value
            value = tok.value
            if symbol_name in cls.current_compiler._directives:
                logger.error("Redefinition of {}".format(symbol_name))
            cls.current_compiler._directives[symbol_name] = value

        return None

    @classmethod
    def add_requirement(cls, toks):
        for tok in toks:
            cls.current_compiler._requirements.add(tok.value.value)

    @classmethod
    def add_states(cls, toks):
        try:
            for tok in toks:
                cls.current_compiler.add_state(tok.state_name.value, tok.code)
        except:
            logger.error("Unable to parse states", exc_info=True)

    def add_state(self, state_name, code):
        logger.debug("Adding {}".format(state_name))
        if state_name in self._states:
            logging.error("Duplicate state {}".format(state_name))
            return

        self._states[state_name] = _StateProgram()
        [self._states[state_name].add_line(x) for x in code]


def debug(tok):
    logger.debug("ParseAction:{}".format(tok))


RequireDirective = Combine(Literal("%").suppress() + Keyword("require")).setResultsName("require")
CompilerDirective = Combine(Literal("%").suppress() + Symbol).setResultsName("directive")
DirectiveValue = (Number ^ Symbol).setResultsName("value")
FullCompilerDirective = Group(
    CompilerDirective +
    DirectiveValue
)
FullRequireDirective = Group(
    RequireDirective +
    DirectiveValue
)
Header = OneOrMore(FullRequireDirective ^ FullCompilerDirective)

States = CaselessKeyword("states").setName("states block").suppress()
State = CaselessKeyword("state").setName("state").suppress()
Decisions = Keyword("decisions").setName("decisions block")
StartBlock = Keyword("{").suppress()
EndBlock = Keyword("}").suppress()

# OpCodes
SetAllOpCode = CaselessKeyword("SetAll").setResultsName('opcode')
SetAllOpCodeArguments = (RGB ^ CompilerDirective).setResultsName('arguments')
SetAll = Group(SetAllOpCode + SetAllOpCodeArguments)

Codes = Forward().setResultsName('code')
Codes << SetAll ^ Codes ^ Empty()

StateName = Symbol.setResultsName("state_name")
StateEntry = Group(State + StateName + StartBlock + Codes + EndBlock)
StateBlock = Group(States + StartBlock) + OneOrMore(StateEntry) + EndBlock
DecisionBlock = Group(Decisions + StartBlock + EndBlock)
LedFile << Optional(Header) + StateBlock + DecisionBlock

FullCompilerDirective.addParseAction(Compiler.add_compiler_directive)
FullRequireDirective.addParseAction(Compiler.add_requirement)
StateEntry.addParseAction(Compiler.add_states)

