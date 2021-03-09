using System;
using System.IO;

namespace IrelandDataConversionTools
{
    class PopulationAgeSex
    {
        public Sex Sex { get; set; }
        public int Age { get; set; }
        public int Count { get; set; }

        private const UInt32 MAGIC = 0xBAADBEEF;
        public static void WriteTo(Stream pOutput, PopulationAgeSex[] pAgeSexes)
        {
            using var writer = new BinaryWriter(pOutput);

            writer.Write(MAGIC);
            writer.Write(pAgeSexes.Length);

            foreach (var ageSex in pAgeSexes)
            {
                writer.Write((int)ageSex.Sex);
                writer.Write(ageSex.Age);
                writer.Write(ageSex.Count);
            }

            writer.Flush();
        }
    }
}