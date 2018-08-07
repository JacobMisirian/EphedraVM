using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LibEphedra.VM
{
    public class CPU
    {
        private RAM ram;
        private List<Register> registers;

        public Register GetRegister(byte identifier)
        {
            if (identifier >= 0 && registers.Count < identifier)
                return registers[identifier];
            return null;
        }
    }
}
