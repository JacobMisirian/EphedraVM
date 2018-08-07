using LibEphedra.VM;

using System;
using System.Collections.Generic;
using System.IO;

namespace LibEphedra.Easm
{
    public abstract class Instruction
    {
        public const int INSTRUCTION_LENGTH = sizeof(byte) + sizeof(UInt16) + sizeof(UInt16) + sizeof(UInt32);

        public string Name { get; }

        public byte Opcode { get; }

        public UInt16 Operand1 { get; }

        public UInt16 Operand2 { get; }

        public UInt32 Immediate { get; }

        public Instruction(string name, byte opcode, UInt16 operand1, UInt16 operand2, UInt32 immediate)
        {
            Name = name;
            Opcode = opcode;
            Operand1 = operand1;
            Operand2 = operand2;
            Immediate = immediate;
        }

        public abstract void Execute(CPU cpu);

        public static Instruction Deserialize(BinaryReader br)
        {
            UInt16 opcodeAndFirstOperand = br.ReadUInt16();
            byte opcode = (byte)(opcodeAndFirstOperand >> 8);
            UInt16 firstOperand = (UInt16)(opcodeAndFirstOperand & 0xF);
            if (opcode >= 0 && opcode < instructionCodes.Count)
            {
                Type t = instructionCodes[opcode];
                return (Instruction)Activator.CreateInstance(t, new object[]
                {
                    opcode,
                    firstOperand,
                    br.ReadUInt16(),
                    br.ReadUInt32()
                });
            }

            return null;
        }

        public static void Serialize(BinaryWriter bw, Instruction i)
        {
            bw.Write(i.Opcode);
            bw.Write(i.Operand1);
            bw.Write(i.Operand2);
            bw.Write(i.Immediate);

            bw.Flush();
        }

        private static List<Type> instructionCodes = new List<Type>();

        private static Dictionary<string, Instruction> instructionNames = new Dictionary<string, Instruction>();
    }
}
