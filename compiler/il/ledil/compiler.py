import os
import os.path
import logging

from pyparsing import *

from ledil._expressions import *
from ledil._program import *
from ledil._bytecode import ByteCodeGenerator as bcg


logger = logging.getLogger(__name__)

LedFile = Forward()


class Compiler(object):
    current_compiler = None
    HEADER_STATIC_SIZE = 18

    def __init__(self, filename):
        Compiler.current_compiler = self
        self._directives = {}
        self._requirements = set()
        self._source = filename
        self._states = {}
        output, _ = os.path.splitext(filename)
        self._output = "{0}.ledprog".format(output)

    def _calculate_header_size(self, state_count):
        header_size = self.HEADER_STATIC_SIZE + 2 * state_count
        logger.debug("Header Size = {}".format(header_size))
        return header_size

    def _get_start_state(self, offset):
        if 'start' in self._directives:
            start_state = self._directives['start'].value
            logger.debug("Start State: {} at offset {}".format(start_state, offset))
            state = self._states[start_state]
            state.offset = offset
            offset += len(state)
        else:
            start_state = None
        return offset, start_state

    def _dump_debug_info(self):
        logger.debug("Directives and Symbols")
        [logger.debug("{0}=>{1}".format(k, v)) for k, v in self._directives.items()]
        logger.debug("Requirements: {}".format(", ".join((str(x) for x in self._requirements))))
        logger.debug("States: {}".format(", ".join(self._states.keys())))

    def _calculate_state_offsets(self, offset, start_state):
        for state_name, prog in self._states.items():
            if state_name == start_state:
                continue
            logger.debug("Start {} at offset {}".format(state_name, offset))
            prog.offset = offset
            offset += len(prog)

        return offset

    def compile(self):
        logger.info("{0} -> {1}".format(self._source, self._output))
        list(self._tokenize())

        self._dump_debug_info()

        state_count = len(self._states)
        header_size = self._calculate_header_size(state_count)
        offset = header_size
        offset, start_state = self._get_start_state(offset)
        offset = self._calculate_state_offsets(offset, start_state)

        # Calculate Decision offset - TODO
        length_of_state_name_table = sum((
            len(x) + 1 for x in self._states.keys()
        ))

        logger.debug("Total Expected File Length: {} bytes".format(
            offset + length_of_state_name_table
        ))

        header_arguments = {
            'states': self._states,
            'requirements': list(self._requirements),
            'decision_offset': 0,  # TODO: Implement Decision Table
            'debug_offset': offset,
        }
        if 'version' in self._directives:
            header_arguments['version'] = int(self._directives['version'].value)

        if 'numleds' in self._directives:
            header_arguments['pixel_count'] = int(self._directives['numleds'].value)

        order_state_keys = sorted(self._states.keys(), key=lambda x: self._states[x].offset)

        # Generate symbol table for states
        symbol_table = {}
        for i in range(len(order_state_keys)):
            symbol_table[order_state_keys[i]] = i

        import pprint
        pprint.pprint(symbol_table, indent=2)

        with open(self._output, "wb") as f:
            f.write(bcg.header(**header_arguments))
            for state_name in order_state_keys:
                self._states[state_name].write(f, symbol_table)
            for state_name in order_state_keys:
                data = bcg.str(state_name)
                f.write(data)

        final_size = os.stat(self._output).st_size
        logger.info("Final File Output: {0} bytes".format(final_size))

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
DirectiveValue = (Number ^ Symbol ^ Duration).setResultsName("value")
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

DelayOpCode = CaselessKeyword("Delay").setResultsName('opcode')
DelayOpCodeArguments = (Duration ^ CompilerDirective).setResultsName('arguments')
Delay = Group(DelayOpCode + DelayOpCodeArguments)

NextStateOpCode = CaselessKeyword("Next").setResultsName('opcode')
NextStateOpCodeArguments = (Symbol).setResultsName('arguments')
NextState = Group(NextStateOpCode + NextStateOpCodeArguments)

Statements = SetAll ^ Delay ^ NextState
StatementBlock = StartBlock + ZeroOrMore(Statements) + EndBlock

# Control statements
ForeachCode = CaselessKeyword("ForEach").setResultsName('opcode')
ForeachMain = ForeachCode + StatementBlock.setResultsName('main')
ForeachFirst = CaselessKeyword("first").suppress() + StatementBlock.setResultsName('first')
ForeachLast = CaselessKeyword("last").suppress() + StatementBlock.setResultsName('last')
Foreach = Group(ForeachMain + Optional(ForeachFirst) + Optional(ForeachLast))

Controls = Foreach


Codes = ZeroOrMore(Statements ^ Controls).setResultsName('code')

StateName = Symbol.setResultsName("state_name")
StateEntry = Group(State + StateName + StartBlock + Codes + EndBlock)
StateBlock = Group(States + StartBlock) + OneOrMore(StateEntry) + EndBlock
DecisionBlock = Group(Decisions + StartBlock + EndBlock)
LedFile << Optional(Header) + StateBlock + DecisionBlock

FullCompilerDirective.addParseAction(Compiler.add_compiler_directive)
FullRequireDirective.addParseAction(Compiler.add_requirement)
StateEntry.addParseAction(Compiler.add_states)

