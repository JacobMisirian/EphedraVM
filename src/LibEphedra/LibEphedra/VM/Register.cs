using System;
using System.Collections.Generic;

namespace LibEphedra.VM
{
    public abstract class Register
    {
        public CPU CPU { get; }

        public byte Identifier { get; }

        public string Name { get; }

        public UInt32 Value { get; set; }

        public Register(CPU cpu, byte identifier, string name)
        {
            CPU = cpu;
            Identifier = identifier;
            Name = name;
        } 
    }
}
