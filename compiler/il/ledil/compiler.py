import os.path
import logging

from pyparsing import *


logger = logging.getLogger(__name__)

Symbol = Word(alphas, alphanums).setResultsName("symbol")
Number = Word('123456789', '0123456789').setResultsName("integer")
RGB = Group(CaselessKeyword("RGB") + "(" + Number + "," + Number + "," + Number + ")").setResultsName("color")
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
Header = OneOrMore(FullRequireDirective | FullCompilerDirective)

States = CaselessKeyword("states").setName("states block").suppress()
State = CaselessKeyword("state").setName("state").suppress()
Decisions = Keyword("decisions").setName("decisions block")
StartBlock = Keyword("{").suppress()
EndBlock = Keyword("}").suppress()

# OpCodes
SetAllOpCode = CaselessKeyword("SetAll").setResultsName('opcode')
SetAllOpCodeArguments = (RGB | CompilerDirective).setResultsName('arguments')
SetAll = Group(SetAllOpCode + SetAllOpCodeArguments)

Codes = Optional(OneOrMore(SetAll)).setResultsName('code')

StateName = Symbol.setResultsName("state_name")
StateEntry = Group(State + StateName + StartBlock + Codes + EndBlock)
StateBlock = Group(States + StartBlock) + OneOrMore(StateEntry) + EndBlock
DecisionBlock = Group(Decisions + StartBlock + EndBlock)
LedFile = Optional(Header) + StateBlock + DecisionBlock


class Compiler(object):
    current_compiler = None

    def __init__(self, filename):
        Compiler.current_compiler = self
        self._directives = {}
        self._requirements = set()
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

        logger.debug("Directives and Symbols")
        [logger.debug("{0}=>{1}".format(k, v)) for k, v in self._directives.items()]

        logger.debug("Requirements: {}".format(", ".join(self._requirements)))

    def _tokenize(self):
        value = LedFile.parseFile(self._source)

        for token in value:
            yield token

    @classmethod
    def add_compiler_directive(cls, toks):
        for tok in toks:
            if tok.directive in cls.current_compiler._directives:
                logger.error("Redefinition of {}".format(tok.directive))
            cls.current_compiler._directives[tok.directive] = tok.value

        return None

    @classmethod
    def add_requirement(cls, toks):
        for tok in toks:
            cls.current_compiler._requirements.add(tok.value)

    @classmethod
    def add_states(cls, toks):
        for tok in toks:
            cls.current_compiler.add_state(tok.state_name, tok.code)

    def add_state(self, state_name, code):
        logger.debug("Adding {}".format(state_name))
        print(code)


FullCompilerDirective.addParseAction(Compiler.add_compiler_directive)
FullRequireDirective.addParseAction(Compiler.add_requirement)
StateEntry.addParseAction(Compiler.add_states)
