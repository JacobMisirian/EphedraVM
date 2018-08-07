using LibEphedra.VM;

namespace LibEphedra.Easm.Instructions
{
    public class Mov : Instruction
    {
        public Mov(string name, byte opcode, ushort operand1, ushort operand2, uint immediate) : base(name, opcode, operand1, operand2, immediate)
        {
        }

        public override void Execute(CPU cpu)
        {
            Register dest = cpu.GetRegister(Operand1);
            Register src = cpu.GetRegister(Operand2);

            dest.Value = src.Value;
        }
    }
}
