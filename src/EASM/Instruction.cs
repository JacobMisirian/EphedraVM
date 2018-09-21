using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EASM
{
    public class Instruction
    {
        public byte OpCode { get; private set; }
        public byte Operand1 { get; private set; }
        public byte Operand2 { get; private set; }
        public UInt16 Immediate { get; private set; }

        public Instruction(byte opcode, byte operand1, byte operand2, UInt16 immediate)
        {
            OpCode = opcode;
            Operand1 = operand1;
            Operand2 = operand2;
            Immediate = immediate;
        }

        public UInt32 Serialize()
        {
            UInt32 i = Immediate;
            i ^= ((UInt32)Operand1 << 17);
            i ^= ((UInt32)Operand2 << 23);
            i ^= ((UInt32)OpCode << 28);
            return i;
        }

        private void printBinary(UInt32 i)
        {
            Console.WriteLine(Convert.ToString(i, 2));
        }
    }
}
