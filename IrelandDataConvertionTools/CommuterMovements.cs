using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace IrelandDataConversionTools
{

    public enum MovementType { ToOsi, NoFixed, StayAtHome }
    public class CommuterMovement
    {
        public UInt32 FromOsiID { get; set; }
        public string FromDistrictName { get; set; }
        public string FromCounty { get; set; }

        public UInt32? ToOsiID { get; set; }
        public string ToDistrictName { get; set; }
        public string ToCounty { get; set; }
        public UInt32 NumberOfCommuters { get; set; }
        public double Distance { get; set; }

        public MovementType Type { get; set; }

        public static IEnumerable<CommuterMovement> LoadMovements(Stream pInput)
        {
            using var reader = new StreamReader(pInput);

            reader.ReadLine();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var splits = line.Split(",");
                var item = new CommuterMovement
                {
                    FromOsiID = UInt32.Parse(splits[0].Split(" ")[0]),
                    FromDistrictName = splits[0].Split(" ")[2],
                    FromCounty = splits[1],
                    
                    NumberOfCommuters = UInt32.Parse(splits[4]),
                    Distance = double.Parse(splits[5])
                };

                switch (splits[2])
                {
                    case "No fixed place of work":
                        item.Type = MovementType.NoFixed;
                        break;
                    case "Work/school from home":
                        item.Type = MovementType.StayAtHome;
                        break;
                    default:
                        item.ToOsiID = UInt32.Parse(splits[2].Split(" ")[0]);
                        item.ToDistrictName = splits[02].Split(" ")[2];
                        item.ToCounty = splits[3];
                        break;
                }

                yield return item;
            }
        }
    }
}