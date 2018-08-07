using LibEphedra.VM;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LibEphedra.Easm.Instructions
{
    public class Jmp : Instruction
    {
        public Jmp(string name, byte opcode, ushort operand1, ushort operand2, uint immediate) : base(name, opcode, operand1, operand2, immediate)
        {
        }

        public override void Execute(CPU cpu)
        {
            var ip = cpu.GetRegister((byte)SpecialRegister.IP);
            ip.Value = Immediate;
        }
    }
}
