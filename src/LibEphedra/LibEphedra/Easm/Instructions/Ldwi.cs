﻿using LibEphedra.VM;

namespace LibEphedra.Easm.Instructions
{
    public class Ldwi : Instruction
    {
        public Ldwi(string name, byte opcode, ushort operand1, ushort operand2, uint immediate) : base(name, opcode, operand1, operand2, immediate)
        {
        }

        public override void Execute(CPU cpu)
        {
            var rx = cpu.GetRegister(Operand1);
            rx.Value = RAM.Instance.ReadWord(Immediate);
        }
    }
}
