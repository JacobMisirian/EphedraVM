using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace EASM
{
    class Program
    {
        static void Main(string[] args)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(args[0], FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.ReadWrite)))
            {
                Instruction i;
                i = new Instruction(3, 2, 1, 69);
                writer.Write(i.Serialize());
                i = new Instruction(1, 2, 1, 420);
                writer.Write(i.Serialize());
                i = new Instruction(4, 4, 2, 1);
                writer.Write(i.Serialize());
                i = new Instruction(2, 6, 7, 1234);
                writer.Write(i.Serialize());
                writer.Flush();
            }
        }
    }
}
