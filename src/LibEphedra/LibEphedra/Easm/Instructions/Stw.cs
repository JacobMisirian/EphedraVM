using LibEphedra.VM;

using System;

namespace LibEphedra.Easm.Instructions
{
    public class Stw : Instruction
    {
        public Stw(string name, byte opcode, ushort operand1, ushort operand2, uint immediate) : base(name, opcode, operand1, operand2, immediate)
        {
        }

        public override void Execute(CPU cpu)
        {
            var rx = cpu.GetRegister(Operand1);
            rx.Value = cpu.GetRegister(Operand2).Value;
        }
    }
}
