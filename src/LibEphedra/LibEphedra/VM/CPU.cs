using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LibEphedra.VM
{
    public class CPU
    {
        private List<Register> registers;

        public Register GetRegister(SpecialRegister identifier)
        {
            return GetRegister((UInt16)identifier);
        }
        public Register GetRegister(UInt16 identifier)
        {
            if (identifier >= 0 && registers.Count < identifier)
                return registers[identifier];
            return null;
        }
    }
}
