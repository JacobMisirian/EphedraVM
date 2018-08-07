using System;

namespace LibEphedra.VM
{
    public class RAM
    {
        private byte[] data;

        public RAM(int size)
        {
            data = new byte[size];
        }

        public byte ReadByte(UInt32 addr)
        {
            return data[addr];
        }

        public byte[] ReadBytes(UInt32 addr, int length)
        {
            byte[] ret = new byte[length];

            for (UInt32 i = addr; i < length; i++)
                ret[i - addr] = data[i];

            return ret;
        }

        public UInt16 ReadWord(UInt32 addr)
        {
            return BitConverter.ToUInt16(data, (int)addr);
        }

        public UInt32 ReadDWord(UInt32 addr)
        {
            return BitConverter.ToUInt32(data, (int)addr);
        }

        public byte WriteByte(UInt32 addr, byte b)
        {
            data[addr] = b;
            return b;
        }

        public void WriteBytes(UInt32 addr, byte[] arr, int startIndex, int length)
        {
            for (int i = startIndex; i < startIndex + length; i++)
                data[addr + (i - startIndex)] = arr[i];
        }

        public UInt16 WriteWord(UInt32 addr, UInt16 w)
        {
            WriteBytes(addr, BitConverter.GetBytes(w), 0, sizeof(UInt16));
            return w;
        }

        public UInt32 WriteDWord(UInt32 addr, UInt32 dw)
        {
            WriteBytes(addr, BitConverter.GetBytes(dw), 0, sizeof(UInt32));
            return dw;
        }
    }
}
