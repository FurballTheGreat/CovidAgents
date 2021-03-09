using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text.Json;
using System.Xml.Serialization;

namespace IrelandDataConversionTools
{
    class ShapeFileConverter
    {
        private const UInt32 MAGIC = 0xBAADBE1F;
        public static void ConvertShapeFile(string pJson, Stream pOutput, CommuterMovement[] pMovements)
        {
            using var doc = JsonDocument.Parse(pJson);
            using var writer = new BinaryWriter(pOutput);
            var feautresEl = doc.RootElement.EnumerateObject().FirstOrDefault(pX => pX.Name == "features");
            var features = feautresEl.Value.EnumerateArray().ToArray();

            writer.Write(MAGIC);
            var allRegions = new List<(string, string)>();
            var allSubRegions = new List<(string, string)>();
            var allCounties = new List<(string, string)>();
            var allEds = new List<(UInt32,string)>();
            var osiEdDict = new Dictionary<UInt32, List<UInt32>>();
            var edOsiDict = new Dictionary<UInt32, List<UInt32>>();
            foreach (var featureEl in features)
            {
                var property = featureEl.EnumerateObject().FirstOrDefault(pX => pX.Name == "properties");
                var allProps = property.Value.EnumerateObject().ToDictionary(pX => pX.Name, pX => pX.Value);
                var region = (allProps["NUTS2"].ToString(),allProps["NUTS2NAME"].ToString());
                var subRegion = (allProps["NUTS3"].ToString(), allProps["NUTS3NAME"].ToString());
                var county = (allProps["COUNTY"].ToString(), allProps["COUNTYNAME"].ToString());
                var edName = allProps["EDNAME"].ToString();
                
                if (!allRegions.Contains(region)) allRegions.Add(region);
                if (!allSubRegions.Contains(subRegion)) allSubRegions.Add(subRegion);
                if (!allCounties.Contains(county)) allCounties.Add(county);
                
                var osiids = allProps["OSIED"].ToString().Split("/").Select(pX => UInt32.Parse(pX)).ToArray();
                var osiId = osiids.Length == 1
                    ? osiids[0]
                    : osiids.First(pOsi => pMovements.Any(pX => pX.FromOsiID == pOsi));
                var currentObjId = UInt32.Parse(allProps["OBJECTID"].ToString());
                if (!allEds.Contains((osiId,edName))) allEds.Add((osiId, edName));
            }


            
            
            

            writer.Write(allRegions.Count);
            
            foreach (var item in allRegions)
            {
                var (code, val) = item;
                writer.Write(code);
                writer.Write(val);
            }

            writer.Write(allSubRegions.Count);
            foreach (var item in allSubRegions)
            {
                var (code, val) = item;
                writer.Write(code);
                writer.Write(val);
            }

            writer.Write(allCounties.Count);
            foreach (var item in allCounties)
            {
                var (code, val) = item;
                writer.Write(code);
                writer.Write(val);
            }

            writer.Write(allEds.Count);
            foreach (var ed in allEds)
            {
                var (code, name) = ed;
                
                writer.Write(code);
                writer.Write(name);

                var movementsFrom = pMovements.Where(pX => pX.FromOsiID == code).ToArray();
                writer.Write(movementsFrom.Length);
                foreach (var movement in movementsFrom)
                {
                    writer.Write((int)movement.Type);
                    writer.Write(movement.ToOsiID ?? 0);
                    writer.Write(movement.NumberOfCommuters);
                    writer.Write(movement.Distance);
                }

            }

            writer.Write(features.Length);

            foreach (var featureEl in features)
            {
                var property = featureEl.EnumerateObject().FirstOrDefault(pX => pX.Name == "properties");

                var allProps = property.Value.EnumerateObject().ToDictionary(pX => pX.Name, pX => pX.Value);
                var region = (allProps["NUTS2"].ToString(), allProps["NUTS2NAME"].ToString());
                var subRegion = (allProps["NUTS3"].ToString(), allProps["NUTS3NAME"].ToString());
                var county = (allProps["COUNTY"].ToString(), allProps["COUNTYNAME"].ToString());
                var edName = allProps["EDNAME"].ToString();
                var osiids = allProps["OSIED"].ToString().Split("/").Select(pX => UInt32.Parse(pX)).ToArray();
                var osiId = osiids.Length == 1
                    ? osiids[0]
                    : osiids.First(pOsi => pMovements.Any(pX => pX.FromOsiID == pOsi));

                writer.Write(Int32.Parse(allProps["OBJECTID"].ToString()));
                writer.Write(allRegions.IndexOf(region));
                writer.Write(allSubRegions.IndexOf(subRegion));
                writer.Write(allCounties.IndexOf(county));
                writer.Write(allEds.IndexOf((osiId, edName)));
                writer.Write(double.Parse(allProps["Shape__Area"].ToString()));
                writer.Write(allProps.ContainsKey("T1_1AGE0M") ? Int32.Parse(allProps["T1_1AGE0M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE1M") ? Int32.Parse(allProps["T1_1AGE1M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE2M") ? Int32.Parse(allProps["T1_1AGE2M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE3M") ? Int32.Parse(allProps["T1_1AGE3M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE4M") ? Int32.Parse(allProps["T1_1AGE4M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE5M") ? Int32.Parse(allProps["T1_1AGE5M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE6M") ? Int32.Parse(allProps["T1_1AGE6M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE7M") ? Int32.Parse(allProps["T1_1AGE7M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE8M") ? Int32.Parse(allProps["T1_1AGE8M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE9M") ? Int32.Parse(allProps["T1_1AGE9M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE10M") ? Int32.Parse(allProps["T1_1AGE10M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE11M") ? Int32.Parse(allProps["T1_1AGE11M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE12M") ? Int32.Parse(allProps["T1_1AGE12M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE13M") ? Int32.Parse(allProps["T1_1AGE13M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE14M") ? Int32.Parse(allProps["T1_1AGE14M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE15M") ? Int32.Parse(allProps["T1_1AGE15M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE16M") ? Int32.Parse(allProps["T1_1AGE16M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE17M") ? Int32.Parse(allProps["T1_1AGE17M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE18M") ? Int32.Parse(allProps["T1_1AGE18M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE19M") ? Int32.Parse(allProps["T1_1AGE19M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE20_24M")
                    ? Int32.Parse(allProps["T1_1AGE20_24M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE25_29M")
                    ? Int32.Parse(allProps["T1_1AGE25_29M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE30_34M")
                    ? Int32.Parse(allProps["T1_1AGE30_34M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE35_39M")
                    ? Int32.Parse(allProps["T1_1AGE35_39M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE40_44M")
                    ? Int32.Parse(allProps["T1_1AGE40_44M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE45_49M")
                    ? Int32.Parse(allProps["T1_1AGE45_49M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE50_54M")
                    ? Int32.Parse(allProps["T1_1AGE50_54M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE55_59M")
                    ? Int32.Parse(allProps["T1_1AGE55_59M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE60_64M")
                    ? Int32.Parse(allProps["T1_1AGE60_64M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE65_69M")
                    ? Int32.Parse(allProps["T1_1AGE65_69M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE70_74M")
                    ? Int32.Parse(allProps["T1_1AGE70_74M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE75_79M")
                    ? Int32.Parse(allProps["T1_1AGE75_79M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE80_84M")
                    ? Int32.Parse(allProps["T1_1AGE80_84M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGEGE_85M")
                    ? Int32.Parse(allProps["T1_1AGEGE_85M"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGETM") ? Int32.Parse(allProps["T1_1AGETM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE0F") ? Int32.Parse(allProps["T1_1AGE0F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE1F") ? Int32.Parse(allProps["T1_1AGE1F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE2F") ? Int32.Parse(allProps["T1_1AGE2F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE3F") ? Int32.Parse(allProps["T1_1AGE3F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE4F") ? Int32.Parse(allProps["T1_1AGE4F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE5F") ? Int32.Parse(allProps["T1_1AGE5F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE6F") ? Int32.Parse(allProps["T1_1AGE6F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE7F") ? Int32.Parse(allProps["T1_1AGE7F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE8F") ? Int32.Parse(allProps["T1_1AGE8F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE9F") ? Int32.Parse(allProps["T1_1AGE9F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE10F") ? Int32.Parse(allProps["T1_1AGE10F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE11F") ? Int32.Parse(allProps["T1_1AGE11F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE12F") ? Int32.Parse(allProps["T1_1AGE12F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE13F") ? Int32.Parse(allProps["T1_1AGE13F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE14F") ? Int32.Parse(allProps["T1_1AGE14F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE15F") ? Int32.Parse(allProps["T1_1AGE15F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE16F") ? Int32.Parse(allProps["T1_1AGE16F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE17F") ? Int32.Parse(allProps["T1_1AGE17F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE18F") ? Int32.Parse(allProps["T1_1AGE18F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE19F") ? Int32.Parse(allProps["T1_1AGE19F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE20_24F")
                    ? Int32.Parse(allProps["T1_1AGE20_24F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE25_29F")
                    ? Int32.Parse(allProps["T1_1AGE25_29F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE30_34F")
                    ? Int32.Parse(allProps["T1_1AGE30_34F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE35_39F")
                    ? Int32.Parse(allProps["T1_1AGE35_39F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE40_44F")
                    ? Int32.Parse(allProps["T1_1AGE40_44F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE45_49F")
                    ? Int32.Parse(allProps["T1_1AGE45_49F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE50_54F")
                    ? Int32.Parse(allProps["T1_1AGE50_54F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE55_59F")
                    ? Int32.Parse(allProps["T1_1AGE55_59F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE60_64F")
                    ? Int32.Parse(allProps["T1_1AGE60_64F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE65_69F")
                    ? Int32.Parse(allProps["T1_1AGE65_69F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE70_74F")
                    ? Int32.Parse(allProps["T1_1AGE70_74F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE75_79F")
                    ? Int32.Parse(allProps["T1_1AGE75_79F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE80_84F")
                    ? Int32.Parse(allProps["T1_1AGE80_84F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGEGE_85F")
                    ? Int32.Parse(allProps["T1_1AGEGE_85F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGETF") ? Int32.Parse(allProps["T1_1AGETF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE0T") ? Int32.Parse(allProps["T1_1AGE0T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE1T") ? Int32.Parse(allProps["T1_1AGE1T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE2T") ? Int32.Parse(allProps["T1_1AGE2T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE3T") ? Int32.Parse(allProps["T1_1AGE3T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE4T") ? Int32.Parse(allProps["T1_1AGE4T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE5T") ? Int32.Parse(allProps["T1_1AGE5T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE6T") ? Int32.Parse(allProps["T1_1AGE6T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE7T") ? Int32.Parse(allProps["T1_1AGE7T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE8T") ? Int32.Parse(allProps["T1_1AGE8T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE9T") ? Int32.Parse(allProps["T1_1AGE9T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE10T") ? Int32.Parse(allProps["T1_1AGE10T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE11T") ? Int32.Parse(allProps["T1_1AGE11T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE12T") ? Int32.Parse(allProps["T1_1AGE12T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE13T") ? Int32.Parse(allProps["T1_1AGE13T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE14T") ? Int32.Parse(allProps["T1_1AGE14T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE15T") ? Int32.Parse(allProps["T1_1AGE15T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE16T") ? Int32.Parse(allProps["T1_1AGE16T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE17T") ? Int32.Parse(allProps["T1_1AGE17T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE18T") ? Int32.Parse(allProps["T1_1AGE18T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE19T") ? Int32.Parse(allProps["T1_1AGE19T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE20_24T")
                    ? Int32.Parse(allProps["T1_1AGE20_24T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE25_29T")
                    ? Int32.Parse(allProps["T1_1AGE25_29T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE30_34T")
                    ? Int32.Parse(allProps["T1_1AGE30_34T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE35_39T")
                    ? Int32.Parse(allProps["T1_1AGE35_39T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE40_44T")
                    ? Int32.Parse(allProps["T1_1AGE40_44T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE45_49T")
                    ? Int32.Parse(allProps["T1_1AGE45_49T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE50_54T")
                    ? Int32.Parse(allProps["T1_1AGE50_54T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE55_59T")
                    ? Int32.Parse(allProps["T1_1AGE55_59T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE60_64T")
                    ? Int32.Parse(allProps["T1_1AGE60_64T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE65_69T")
                    ? Int32.Parse(allProps["T1_1AGE65_69T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE70_74T")
                    ? Int32.Parse(allProps["T1_1AGE70_74T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE75_79T")
                    ? Int32.Parse(allProps["T1_1AGE75_79T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGE80_84T")
                    ? Int32.Parse(allProps["T1_1AGE80_84T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGEGE_85T")
                    ? Int32.Parse(allProps["T1_1AGEGE_85T"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T1_1AGETT") ? Int32.Parse(allProps["T1_1AGETT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SGLM") ? Int32.Parse(allProps["T1_2SGLM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2MARM") ? Int32.Parse(allProps["T1_2MARM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SEPM") ? Int32.Parse(allProps["T1_2SEPM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2DIVM") ? Int32.Parse(allProps["T1_2DIVM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2WIDM") ? Int32.Parse(allProps["T1_2WIDM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2TM") ? Int32.Parse(allProps["T1_2TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SGLF") ? Int32.Parse(allProps["T1_2SGLF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2MARF") ? Int32.Parse(allProps["T1_2MARF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SEPF") ? Int32.Parse(allProps["T1_2SEPF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2DIVF") ? Int32.Parse(allProps["T1_2DIVF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2WIDF") ? Int32.Parse(allProps["T1_2WIDF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2TF") ? Int32.Parse(allProps["T1_2TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SGLT") ? Int32.Parse(allProps["T1_2SGLT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2MART") ? Int32.Parse(allProps["T1_2MART"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2SEPT") ? Int32.Parse(allProps["T1_2SEPT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2DIVT") ? Int32.Parse(allProps["T1_2DIVT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2WIDT") ? Int32.Parse(allProps["T1_2WIDT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T1_2T") ? Int32.Parse(allProps["T1_2T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1IEBP") ? Int32.Parse(allProps["T2_1IEBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1UKBP") ? Int32.Parse(allProps["T2_1UKBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1PLBP") ? Int32.Parse(allProps["T2_1PLBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1LTBP") ? Int32.Parse(allProps["T2_1LTBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1EUBP") ? Int32.Parse(allProps["T2_1EUBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1RWBP") ? Int32.Parse(allProps["T2_1RWBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1TBP") ? Int32.Parse(allProps["T2_1TBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1IEN") ? Int32.Parse(allProps["T2_1IEN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1UKN") ? Int32.Parse(allProps["T2_1UKN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1PLN") ? Int32.Parse(allProps["T2_1PLN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1LTN") ? Int32.Parse(allProps["T2_1LTN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1EUN") ? Int32.Parse(allProps["T2_1EUN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1RWN") ? Int32.Parse(allProps["T2_1RWN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1NSN") ? Int32.Parse(allProps["T2_1NSN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_1TN") ? Int32.Parse(allProps["T2_1TN"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2WI") ? Int32.Parse(allProps["T2_2WI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2WIT") ? Int32.Parse(allProps["T2_2WIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2OW") ? Int32.Parse(allProps["T2_2OW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2BBI") ? Int32.Parse(allProps["T2_2BBI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2AAI") ? Int32.Parse(allProps["T2_2AAI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2OTH") ? Int32.Parse(allProps["T2_2OTH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2NS") ? Int32.Parse(allProps["T2_2NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_2T") ? Int32.Parse(allProps["T2_2T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_3SA") ? Int32.Parse(allProps["T2_3SA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_3EC") ? Int32.Parse(allProps["T2_3EC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_3EI") ? Int32.Parse(allProps["T2_3EI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_3OI") ? Int32.Parse(allProps["T2_3OI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_3T") ? Int32.Parse(allProps["T2_3T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_4CA") ? Int32.Parse(allProps["T2_4CA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_4OR") ? Int32.Parse(allProps["T2_4OR"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_4NR") ? Int32.Parse(allProps["T2_4NR"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_4NS") ? Int32.Parse(allProps["T2_4NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_4T") ? Int32.Parse(allProps["T2_4T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_5PL") ? Int32.Parse(allProps["T2_5PL"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_5FR") ? Int32.Parse(allProps["T2_5FR"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_5LT") ? Int32.Parse(allProps["T2_5LT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_5OTH") ? Int32.Parse(allProps["T2_5OTH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_5T") ? Int32.Parse(allProps["T2_5T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6VW") ? Int32.Parse(allProps["T2_6VW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6W") ? Int32.Parse(allProps["T2_6W"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6NW") ? Int32.Parse(allProps["T2_6NW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6NAA") ? Int32.Parse(allProps["T2_6NAA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6NS") ? Int32.Parse(allProps["T2_6NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T2_6T") ? Int32.Parse(allProps["T2_6T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_1YES") ? Int32.Parse(allProps["T3_1YES"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_1NO") ? Int32.Parse(allProps["T3_1NO"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_1NS") ? Int32.Parse(allProps["T3_1NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_1T") ? Int32.Parse(allProps["T3_1T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIM") ? Int32.Parse(allProps["T3_2DIM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIDOM") ? Int32.Parse(allProps["T3_2DIDOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIWOM") ? Int32.Parse(allProps["T3_2DIWOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DILOOM") ? Int32.Parse(allProps["T3_2DILOOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DINOM") ? Int32.Parse(allProps["T3_2DINOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DOESM") ? Int32.Parse(allProps["T3_2DOESM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2WOESM") ? Int32.Parse(allProps["T3_2WOESM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2LOOESM") ? Int32.Parse(allProps["T3_2LOOESM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NOESM") ? Int32.Parse(allProps["T3_2NOESM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NSM") ? Int32.Parse(allProps["T3_2NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2ALLM") ? Int32.Parse(allProps["T3_2ALLM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIF") ? Int32.Parse(allProps["T3_2DIF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIDOF") ? Int32.Parse(allProps["T3_2DIDOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIWOF") ? Int32.Parse(allProps["T3_2DIWOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DILOOF") ? Int32.Parse(allProps["T3_2DILOOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DINOF") ? Int32.Parse(allProps["T3_2DINOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DOESF") ? Int32.Parse(allProps["T3_2DOESF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2WOESF") ? Int32.Parse(allProps["T3_2WOESF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2LOOESF") ? Int32.Parse(allProps["T3_2LOOESF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NOESF") ? Int32.Parse(allProps["T3_2NOESF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NSF") ? Int32.Parse(allProps["T3_2NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2ALLF") ? Int32.Parse(allProps["T3_2ALLF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIT") ? Int32.Parse(allProps["T3_2DIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIDOT") ? Int32.Parse(allProps["T3_2DIDOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DIWOT") ? Int32.Parse(allProps["T3_2DIWOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DILOOT") ? Int32.Parse(allProps["T3_2DILOOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DINOT") ? Int32.Parse(allProps["T3_2DINOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2DOEST") ? Int32.Parse(allProps["T3_2DOEST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2WOEST") ? Int32.Parse(allProps["T3_2WOEST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2LOOEST") ? Int32.Parse(allProps["T3_2LOOEST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NOEST") ? Int32.Parse(allProps["T3_2NOEST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2NST") ? Int32.Parse(allProps["T3_2NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T3_2ALLT") ? Int32.Parse(allProps["T3_2ALLT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_2PF") ? Int32.Parse(allProps["T4_1_2PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_3PF") ? Int32.Parse(allProps["T4_1_3PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_4PF") ? Int32.Parse(allProps["T4_1_4PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_5PF") ? Int32.Parse(allProps["T4_1_5PF"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_1_GRE_6PF") ? Int32.Parse(allProps["T4_1_GRE_6PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_TF") ? Int32.Parse(allProps["T4_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_2PP") ? Int32.Parse(allProps["T4_1_2PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_3PP") ? Int32.Parse(allProps["T4_1_3PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_4PP") ? Int32.Parse(allProps["T4_1_4PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_5PP") ? Int32.Parse(allProps["T4_1_5PP"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_1_GRE_6PP") ? Int32.Parse(allProps["T4_1_GRE_6PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_TP") ? Int32.Parse(allProps["T4_1_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_2PC") ? Int32.Parse(allProps["T4_1_2PC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_3PC") ? Int32.Parse(allProps["T4_1_3PC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_4PC") ? Int32.Parse(allProps["T4_1_4PC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_5PC") ? Int32.Parse(allProps["T4_1_5PC"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_1_GRE_6PC") ? Int32.Parse(allProps["T4_1_GRE_6PC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_1_TC") ? Int32.Parse(allProps["T4_1_TC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_1CU15") ? Int32.Parse(allProps["T4_2_1CU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_2CU15") ? Int32.Parse(allProps["T4_2_2CU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_3CU15") ? Int32.Parse(allProps["T4_2_3CU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_4CU15") ? Int32.Parse(allProps["T4_2_4CU15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_2_GE5CU15") ? Int32.Parse(allProps["T4_2_GE5CU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_TCU15") ? Int32.Parse(allProps["T4_2_TCU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_1CO15") ? Int32.Parse(allProps["T4_2_1CO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_2CO15") ? Int32.Parse(allProps["T4_2_2CO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_3CO15") ? Int32.Parse(allProps["T4_2_3CO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_4CO15") ? Int32.Parse(allProps["T4_2_4CO15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_2_GE5CO15") ? Int32.Parse(allProps["T4_2_GE5CO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_TCO15") ? Int32.Parse(allProps["T4_2_TCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_2CUO15") ? Int32.Parse(allProps["T4_2_2CUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_3CUO15") ? Int32.Parse(allProps["T4_2_3CUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_4CUO15") ? Int32.Parse(allProps["T4_2_4CUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_GE5CUO15")
                    ? Int32.Parse(allProps["T4_2_GE5CUO15"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_2_TCUO15") ? Int32.Parse(allProps["T4_2_TCUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_NCT") ? Int32.Parse(allProps["T4_2_NCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_1CT") ? Int32.Parse(allProps["T4_2_1CT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_2CT") ? Int32.Parse(allProps["T4_2_2CT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_3CT") ? Int32.Parse(allProps["T4_2_3CT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_4CT") ? Int32.Parse(allProps["T4_2_4CT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_GE5CT") ? Int32.Parse(allProps["T4_2_GE5CT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_2_TCT") ? Int32.Parse(allProps["T4_2_TCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FCCU15") ? Int32.Parse(allProps["T4_3FCCU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FCCO15") ? Int32.Parse(allProps["T4_3FCCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FCCUO15") ? Int32.Parse(allProps["T4_3FCCUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FCCT") ? Int32.Parse(allProps["T4_3FCCT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3FOPMCU15") ? Int32.Parse(allProps["T4_3FOPMCU15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3FOPMCO15") ? Int32.Parse(allProps["T4_3FOPMCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FOPMCUO15")
                    ? Int32.Parse(allProps["T4_3FOPMCUO15"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_3FOPMCT") ? Int32.Parse(allProps["T4_3FOPMCT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3FOPFCU15") ? Int32.Parse(allProps["T4_3FOPFCU15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3FOPFCO15") ? Int32.Parse(allProps["T4_3FOPFCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3FOPFCUO15")
                    ? Int32.Parse(allProps["T4_3FOPFCUO15"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_3FOPFCT") ? Int32.Parse(allProps["T4_3FOPFCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3CCCU15") ? Int32.Parse(allProps["T4_3CCCU15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3CCCO15") ? Int32.Parse(allProps["T4_3CCCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3CCCUO15") ? Int32.Parse(allProps["T4_3CCCUO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3CCCT") ? Int32.Parse(allProps["T4_3CCCT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3COPMCU15") ? Int32.Parse(allProps["T4_3COPMCU15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3COPMCO15") ? Int32.Parse(allProps["T4_3COPMCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3COPMCUO15")
                    ? Int32.Parse(allProps["T4_3COPMCUO15"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_3COPMCT") ? Int32.Parse(allProps["T4_3COPMCT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3COPFCU15") ? Int32.Parse(allProps["T4_3COPFCU15"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T4_3COPFCO15") ? Int32.Parse(allProps["T4_3COPFCO15"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_3COPFCUO15")
                    ? Int32.Parse(allProps["T4_3COPFCUO15"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_3COPFCT") ? Int32.Parse(allProps["T4_3COPFCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE0_4F") ? Int32.Parse(allProps["T4_4AGE0_4F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE5_9F") ? Int32.Parse(allProps["T4_4AGE5_9F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE10_14F")
                    ? Int32.Parse(allProps["T4_4AGE10_14F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE15_19F")
                    ? Int32.Parse(allProps["T4_4AGE15_19F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE_GE20F")
                    ? Int32.Parse(allProps["T4_4AGE_GE20F"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4TF") ? Int32.Parse(allProps["T4_4TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE0_4P") ? Int32.Parse(allProps["T4_4AGE0_4P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE5_9P") ? Int32.Parse(allProps["T4_4AGE5_9P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE10_14P")
                    ? Int32.Parse(allProps["T4_4AGE10_14P"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE15_19P")
                    ? Int32.Parse(allProps["T4_4AGE15_19P"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4AGE_GE20P")
                    ? Int32.Parse(allProps["T4_4AGE_GE20P"].ToString())
                    : 0);
                writer.Write(allProps.ContainsKey("T4_4TP") ? Int32.Parse(allProps["T4_4TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PFF") ? Int32.Parse(allProps["T4_5PFF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ENF") ? Int32.Parse(allProps["T4_5ENF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5RF") ? Int32.Parse(allProps["T4_5RF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PSF") ? Int32.Parse(allProps["T4_5PSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ESF") ? Int32.Parse(allProps["T4_5ESF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PAF") ? Int32.Parse(allProps["T4_5PAF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ADOF") ? Int32.Parse(allProps["T4_5ADOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ADUF") ? Int32.Parse(allProps["T4_5ADUF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5TF") ? Int32.Parse(allProps["T4_5TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PFP") ? Int32.Parse(allProps["T4_5PFP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ENP") ? Int32.Parse(allProps["T4_5ENP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5RP") ? Int32.Parse(allProps["T4_5RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PSP") ? Int32.Parse(allProps["T4_5PSP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ESP") ? Int32.Parse(allProps["T4_5ESP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5PAP") ? Int32.Parse(allProps["T4_5PAP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ADOP") ? Int32.Parse(allProps["T4_5ADOP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5ADUP") ? Int32.Parse(allProps["T4_5ADUP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_5TP") ? Int32.Parse(allProps["T4_5TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6_0C") ? Int32.Parse(allProps["T4_6_0C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6_1C") ? Int32.Parse(allProps["T4_6_1C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6_2C") ? Int32.Parse(allProps["T4_6_2C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6_3C") ? Int32.Parse(allProps["T4_6_3C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6_GE4C") ? Int32.Parse(allProps["T4_6_GE4C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T4_6T") ? Int32.Parse(allProps["T4_6T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OP_H") ? Int32.Parse(allProps["T5_1OP_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1MC_H") ? Int32.Parse(allProps["T5_1MC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CC_H") ? Int32.Parse(allProps["T5_1CC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1MCC_H") ? Int32.Parse(allProps["T5_1MCC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CCC_H") ? Int32.Parse(allProps["T5_1CCC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPFC_H") ? Int32.Parse(allProps["T5_1OPFC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPMC_H") ? Int32.Parse(allProps["T5_1OPMC_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CO_H") ? Int32.Parse(allProps["T5_1CO_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CCO_H") ? Int32.Parse(allProps["T5_1CCO_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPFCO_H") ? Int32.Parse(allProps["T5_1OPFCO_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPMCO_H") ? Int32.Parse(allProps["T5_1OPMCO_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1GETFU_H") ? Int32.Parse(allProps["T5_1GETFU_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1NHR_H") ? Int32.Parse(allProps["T5_1NHR_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1GENP_H") ? Int32.Parse(allProps["T5_1GENP_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1T_H") ? Int32.Parse(allProps["T5_1T_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OP_P") ? Int32.Parse(allProps["T5_1OP_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1MC_P") ? Int32.Parse(allProps["T5_1MC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CC_P") ? Int32.Parse(allProps["T5_1CC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1MCC_P") ? Int32.Parse(allProps["T5_1MCC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CCC_P") ? Int32.Parse(allProps["T5_1CCC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPFC_P") ? Int32.Parse(allProps["T5_1OPFC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPMC_P") ? Int32.Parse(allProps["T5_1OPMC_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CO_P") ? Int32.Parse(allProps["T5_1CO_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1CCO_P") ? Int32.Parse(allProps["T5_1CCO_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPFCO_P") ? Int32.Parse(allProps["T5_1OPFCO_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1OPMCO_P") ? Int32.Parse(allProps["T5_1OPMCO_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1GETFU_P") ? Int32.Parse(allProps["T5_1GETFU_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1NHR_P") ? Int32.Parse(allProps["T5_1NHR_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1GENP_P") ? Int32.Parse(allProps["T5_1GENP_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_1T_P") ? Int32.Parse(allProps["T5_1T_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_1PH") ? Int32.Parse(allProps["T5_2_1PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_2PH") ? Int32.Parse(allProps["T5_2_2PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_3PH") ? Int32.Parse(allProps["T5_2_3PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_4PH") ? Int32.Parse(allProps["T5_2_4PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_5PH") ? Int32.Parse(allProps["T5_2_5PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_6PH") ? Int32.Parse(allProps["T5_2_6PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_7PH") ? Int32.Parse(allProps["T5_2_7PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_GE8PH") ? Int32.Parse(allProps["T5_2_GE8PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_TH") ? Int32.Parse(allProps["T5_2_TH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_1PP") ? Int32.Parse(allProps["T5_2_1PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_2PP") ? Int32.Parse(allProps["T5_2_2PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_3PP") ? Int32.Parse(allProps["T5_2_3PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_4PP") ? Int32.Parse(allProps["T5_2_4PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_5PP") ? Int32.Parse(allProps["T5_2_5PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_6PP") ? Int32.Parse(allProps["T5_2_6PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_7PP") ? Int32.Parse(allProps["T5_2_7PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_GE8PP") ? Int32.Parse(allProps["T5_2_GE8PP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T5_2_TP") ? Int32.Parse(allProps["T5_2_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_HB_H") ? Int32.Parse(allProps["T6_1_HB_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_FA_H") ? Int32.Parse(allProps["T6_1_FA_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_BS_H") ? Int32.Parse(allProps["T6_1_BS_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_CM_H") ? Int32.Parse(allProps["T6_1_CM_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_NS_H") ? Int32.Parse(allProps["T6_1_NS_H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_TH") ? Int32.Parse(allProps["T6_1_TH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_HB_P") ? Int32.Parse(allProps["T6_1_HB_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_FA_P") ? Int32.Parse(allProps["T6_1_FA_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_BS_P") ? Int32.Parse(allProps["T6_1_BS_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_CM_P") ? Int32.Parse(allProps["T6_1_CM_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_NS_P") ? Int32.Parse(allProps["T6_1_NS_P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_1_TP") ? Int32.Parse(allProps["T6_1_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_PRE19H") ? Int32.Parse(allProps["T6_2_PRE19H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_19_45H") ? Int32.Parse(allProps["T6_2_19_45H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_46_60H") ? Int32.Parse(allProps["T6_2_46_60H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_61_70H") ? Int32.Parse(allProps["T6_2_61_70H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_71_80H") ? Int32.Parse(allProps["T6_2_71_80H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_81_90H") ? Int32.Parse(allProps["T6_2_81_90H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_91_00H") ? Int32.Parse(allProps["T6_2_91_00H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_01_10H") ? Int32.Parse(allProps["T6_2_01_10H"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_11LH") ? Int32.Parse(allProps["T6_2_11LH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_NSH") ? Int32.Parse(allProps["T6_2_NSH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_TH") ? Int32.Parse(allProps["T6_2_TH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_PRE19P") ? Int32.Parse(allProps["T6_2_PRE19P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_19_45P") ? Int32.Parse(allProps["T6_2_19_45P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_46_60P") ? Int32.Parse(allProps["T6_2_46_60P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_61_70P") ? Int32.Parse(allProps["T6_2_61_70P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_71_80P") ? Int32.Parse(allProps["T6_2_71_80P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_81_90P") ? Int32.Parse(allProps["T6_2_81_90P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_91_00P") ? Int32.Parse(allProps["T6_2_91_00P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_01_10P") ? Int32.Parse(allProps["T6_2_01_10P"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_11LP") ? Int32.Parse(allProps["T6_2_11LP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_NSP") ? Int32.Parse(allProps["T6_2_NSP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_2_TP") ? Int32.Parse(allProps["T6_2_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OMLH") ? Int32.Parse(allProps["T6_3_OMLH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OOH") ? Int32.Parse(allProps["T6_3_OOH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RPLH") ? Int32.Parse(allProps["T6_3_RPLH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RLAH") ? Int32.Parse(allProps["T6_3_RLAH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RVCHBH") ? Int32.Parse(allProps["T6_3_RVCHBH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OFRH") ? Int32.Parse(allProps["T6_3_OFRH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_NSH") ? Int32.Parse(allProps["T6_3_NSH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_TH") ? Int32.Parse(allProps["T6_3_TH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OMLP") ? Int32.Parse(allProps["T6_3_OMLP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OOP") ? Int32.Parse(allProps["T6_3_OOP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RPLP") ? Int32.Parse(allProps["T6_3_RPLP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RLAP") ? Int32.Parse(allProps["T6_3_RLAP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_RVCHBP") ? Int32.Parse(allProps["T6_3_RVCHBP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_OFRP") ? Int32.Parse(allProps["T6_3_OFRP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_NSP") ? Int32.Parse(allProps["T6_3_NSP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_3_TP") ? Int32.Parse(allProps["T6_3_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_1RH") ? Int32.Parse(allProps["T6_4_1RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_2RH") ? Int32.Parse(allProps["T6_4_2RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_3RH") ? Int32.Parse(allProps["T6_4_3RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_4RH") ? Int32.Parse(allProps["T6_4_4RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_5RH") ? Int32.Parse(allProps["T6_4_5RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_6RH") ? Int32.Parse(allProps["T6_4_6RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_7RH") ? Int32.Parse(allProps["T6_4_7RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_GE8RH") ? Int32.Parse(allProps["T6_4_GE8RH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_NSH") ? Int32.Parse(allProps["T6_4_NSH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_TH") ? Int32.Parse(allProps["T6_4_TH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_1RP") ? Int32.Parse(allProps["T6_4_1RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_2RP") ? Int32.Parse(allProps["T6_4_2RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_3RP") ? Int32.Parse(allProps["T6_4_3RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_4RP") ? Int32.Parse(allProps["T6_4_4RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_5RP") ? Int32.Parse(allProps["T6_4_5RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_6RP") ? Int32.Parse(allProps["T6_4_6RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_7RP") ? Int32.Parse(allProps["T6_4_7RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_GE8RP") ? Int32.Parse(allProps["T6_4_GE8RP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_NSP") ? Int32.Parse(allProps["T6_4_NSP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_4_TP") ? Int32.Parse(allProps["T6_4_TP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_NCH") ? Int32.Parse(allProps["T6_5_NCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_OCH") ? Int32.Parse(allProps["T6_5_OCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_NGCH") ? Int32.Parse(allProps["T6_5_NGCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_ECH") ? Int32.Parse(allProps["T6_5_ECH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_CCH") ? Int32.Parse(allProps["T6_5_CCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_PCH") ? Int32.Parse(allProps["T6_5_PCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_LPGCH") ? Int32.Parse(allProps["T6_5_LPGCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_WCH") ? Int32.Parse(allProps["T6_5_WCH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_OTH") ? Int32.Parse(allProps["T6_5_OTH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_NS") ? Int32.Parse(allProps["T6_5_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_5_T") ? Int32.Parse(allProps["T6_5_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_PM") ? Int32.Parse(allProps["T6_6_PM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_GSLA") ? Int32.Parse(allProps["T6_6_GSLA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_GSP") ? Int32.Parse(allProps["T6_6_GSP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_OP") ? Int32.Parse(allProps["T6_6_OP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_N") ? Int32.Parse(allProps["T6_6_N"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_NS") ? Int32.Parse(allProps["T6_6_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_6_T") ? Int32.Parse(allProps["T6_6_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_PS") ? Int32.Parse(allProps["T6_7_PS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_IST") ? Int32.Parse(allProps["T6_7_IST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_OIT") ? Int32.Parse(allProps["T6_7_OIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_OTH") ? Int32.Parse(allProps["T6_7_OTH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_NSF") ? Int32.Parse(allProps["T6_7_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_NS") ? Int32.Parse(allProps["T6_7_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_7_T") ? Int32.Parse(allProps["T6_7_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_8_O") ? Int32.Parse(allProps["T6_8_O"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_8_TA") ? Int32.Parse(allProps["T6_8_TA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_8_UHH") ? Int32.Parse(allProps["T6_8_UHH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_8_OVD") ? Int32.Parse(allProps["T6_8_OVD"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T6_8_T") ? Int32.Parse(allProps["T6_8_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T7_1_NE") ? Int32.Parse(allProps["T7_1_NE"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T7_1_NP") ? Int32.Parse(allProps["T7_1_NP"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_WM") ? Int32.Parse(allProps["T8_1_WM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LFFJM") ? Int32.Parse(allProps["T8_1_LFFJM"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T8_1_ULGUPJM") ? Int32.Parse(allProps["T8_1_ULGUPJM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_SM") ? Int32.Parse(allProps["T8_1_SM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LAHFM") ? Int32.Parse(allProps["T8_1_LAHFM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_RM") ? Int32.Parse(allProps["T8_1_RM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_UTWSDM") ? Int32.Parse(allProps["T8_1_UTWSDM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_OTHM") ? Int32.Parse(allProps["T8_1_OTHM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_TM") ? Int32.Parse(allProps["T8_1_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_WF") ? Int32.Parse(allProps["T8_1_WF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LFFJF") ? Int32.Parse(allProps["T8_1_LFFJF"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T8_1_ULGUPJF") ? Int32.Parse(allProps["T8_1_ULGUPJF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_SF") ? Int32.Parse(allProps["T8_1_SF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LAHFF") ? Int32.Parse(allProps["T8_1_LAHFF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_RF") ? Int32.Parse(allProps["T8_1_RF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_UTWSDF") ? Int32.Parse(allProps["T8_1_UTWSDF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_OTHF") ? Int32.Parse(allProps["T8_1_OTHF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_TF") ? Int32.Parse(allProps["T8_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_WT") ? Int32.Parse(allProps["T8_1_WT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LFFJT") ? Int32.Parse(allProps["T8_1_LFFJT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T8_1_ULGUPJT") ? Int32.Parse(allProps["T8_1_ULGUPJT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_ST") ? Int32.Parse(allProps["T8_1_ST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_LAHFT") ? Int32.Parse(allProps["T8_1_LAHFT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_RT") ? Int32.Parse(allProps["T8_1_RT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_UTWSDT") ? Int32.Parse(allProps["T8_1_UTWSDT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_OTHT") ? Int32.Parse(allProps["T8_1_OTHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T8_1_TT") ? Int32.Parse(allProps["T8_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_PWM") ? Int32.Parse(allProps["T9_1_PWM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_MTM") ? Int32.Parse(allProps["T9_1_MTM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_NMM") ? Int32.Parse(allProps["T9_1_NMM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_SM") ? Int32.Parse(allProps["T9_1_SM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_SSM") ? Int32.Parse(allProps["T9_1_SSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_USM") ? Int32.Parse(allProps["T9_1_USM"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T9_1_OTHGEUM") ? Int32.Parse(allProps["T9_1_OTHGEUM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_TM") ? Int32.Parse(allProps["T9_1_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_PWF") ? Int32.Parse(allProps["T9_1_PWF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_MTF") ? Int32.Parse(allProps["T9_1_MTF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_NMF") ? Int32.Parse(allProps["T9_1_NMF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_SF") ? Int32.Parse(allProps["T9_1_SF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_SSF") ? Int32.Parse(allProps["T9_1_SSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_USF") ? Int32.Parse(allProps["T9_1_USF"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T9_1_OTHGEUF") ? Int32.Parse(allProps["T9_1_OTHGEUF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_TF") ? Int32.Parse(allProps["T9_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_PWT") ? Int32.Parse(allProps["T9_1_PWT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_MTT") ? Int32.Parse(allProps["T9_1_MTT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_NMT") ? Int32.Parse(allProps["T9_1_NMT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_ST") ? Int32.Parse(allProps["T9_1_ST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_SST") ? Int32.Parse(allProps["T9_1_SST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_UST") ? Int32.Parse(allProps["T9_1_UST"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T9_1_OTHGEUT") ? Int32.Parse(allProps["T9_1_OTHGEUT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_1_TT") ? Int32.Parse(allProps["T9_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HA") ? Int32.Parse(allProps["T9_2_HA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HB") ? Int32.Parse(allProps["T9_2_HB"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HC") ? Int32.Parse(allProps["T9_2_HC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HD") ? Int32.Parse(allProps["T9_2_HD"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HE") ? Int32.Parse(allProps["T9_2_HE"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HF") ? Int32.Parse(allProps["T9_2_HF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HG") ? Int32.Parse(allProps["T9_2_HG"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HH") ? Int32.Parse(allProps["T9_2_HH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HI") ? Int32.Parse(allProps["T9_2_HI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HJ") ? Int32.Parse(allProps["T9_2_HJ"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HZ") ? Int32.Parse(allProps["T9_2_HZ"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_HT") ? Int32.Parse(allProps["T9_2_HT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PA") ? Int32.Parse(allProps["T9_2_PA"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PB") ? Int32.Parse(allProps["T9_2_PB"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PC") ? Int32.Parse(allProps["T9_2_PC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PD") ? Int32.Parse(allProps["T9_2_PD"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PE") ? Int32.Parse(allProps["T9_2_PE"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PF") ? Int32.Parse(allProps["T9_2_PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PG") ? Int32.Parse(allProps["T9_2_PG"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PH") ? Int32.Parse(allProps["T9_2_PH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PI") ? Int32.Parse(allProps["T9_2_PI"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PJ") ? Int32.Parse(allProps["T9_2_PJ"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PZ") ? Int32.Parse(allProps["T9_2_PZ"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T9_2_PT") ? Int32.Parse(allProps["T9_2_PT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_LT15M") ? Int32.Parse(allProps["T10_1_LT15M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_15M") ? Int32.Parse(allProps["T10_1_15M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_16M") ? Int32.Parse(allProps["T10_1_16M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_17M") ? Int32.Parse(allProps["T10_1_17M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_18M") ? Int32.Parse(allProps["T10_1_18M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_19M") ? Int32.Parse(allProps["T10_1_19M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_20M") ? Int32.Parse(allProps["T10_1_20M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_GE21M") ? Int32.Parse(allProps["T10_1_GE21M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_NSM") ? Int32.Parse(allProps["T10_1_NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_TM") ? Int32.Parse(allProps["T10_1_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_LT15F") ? Int32.Parse(allProps["T10_1_LT15F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_15F") ? Int32.Parse(allProps["T10_1_15F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_16F") ? Int32.Parse(allProps["T10_1_16F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_17F") ? Int32.Parse(allProps["T10_1_17F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_18F") ? Int32.Parse(allProps["T10_1_18F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_19F") ? Int32.Parse(allProps["T10_1_19F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_20F") ? Int32.Parse(allProps["T10_1_20F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_GE21F") ? Int32.Parse(allProps["T10_1_GE21F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_NSF") ? Int32.Parse(allProps["T10_1_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_TF") ? Int32.Parse(allProps["T10_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_LT15T") ? Int32.Parse(allProps["T10_1_LT15T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_15T") ? Int32.Parse(allProps["T10_1_15T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_16T") ? Int32.Parse(allProps["T10_1_16T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_17T") ? Int32.Parse(allProps["T10_1_17T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_18T") ? Int32.Parse(allProps["T10_1_18T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_19T") ? Int32.Parse(allProps["T10_1_19T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_20T") ? Int32.Parse(allProps["T10_1_20T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_GE21T") ? Int32.Parse(allProps["T10_1_GE21T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_NST") ? Int32.Parse(allProps["T10_1_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_1_TT") ? Int32.Parse(allProps["T10_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_SASM") ? Int32.Parse(allProps["T10_2_SASM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_OTHM") ? Int32.Parse(allProps["T10_2_OTHM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_SASF") ? Int32.Parse(allProps["T10_2_SASF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_OTHF") ? Int32.Parse(allProps["T10_2_OTHF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_SAST") ? Int32.Parse(allProps["T10_2_SAST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_2_OTHT") ? Int32.Parse(allProps["T10_2_OTHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_EDUM") ? Int32.Parse(allProps["T10_3_EDUM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ARTM") ? Int32.Parse(allProps["T10_3_ARTM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HUMM") ? Int32.Parse(allProps["T10_3_HUMM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SOCM") ? Int32.Parse(allProps["T10_3_SOCM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SCIM") ? Int32.Parse(allProps["T10_3_SCIM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ENGM") ? Int32.Parse(allProps["T10_3_ENGM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_AGRM") ? Int32.Parse(allProps["T10_3_AGRM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HEAM") ? Int32.Parse(allProps["T10_3_HEAM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SERM") ? Int32.Parse(allProps["T10_3_SERM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_OTHM") ? Int32.Parse(allProps["T10_3_OTHM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_NSM") ? Int32.Parse(allProps["T10_3_NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_TM") ? Int32.Parse(allProps["T10_3_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_EDUF") ? Int32.Parse(allProps["T10_3_EDUF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ARTF") ? Int32.Parse(allProps["T10_3_ARTF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HUMF") ? Int32.Parse(allProps["T10_3_HUMF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SOCF") ? Int32.Parse(allProps["T10_3_SOCF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SCIF") ? Int32.Parse(allProps["T10_3_SCIF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ENGF") ? Int32.Parse(allProps["T10_3_ENGF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_AGRF") ? Int32.Parse(allProps["T10_3_AGRF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HEAF") ? Int32.Parse(allProps["T10_3_HEAF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SERF") ? Int32.Parse(allProps["T10_3_SERF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_OTHF") ? Int32.Parse(allProps["T10_3_OTHF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_NSF") ? Int32.Parse(allProps["T10_3_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_TF") ? Int32.Parse(allProps["T10_3_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_EDUT") ? Int32.Parse(allProps["T10_3_EDUT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ARTT") ? Int32.Parse(allProps["T10_3_ARTT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HUMT") ? Int32.Parse(allProps["T10_3_HUMT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SOCT") ? Int32.Parse(allProps["T10_3_SOCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SCIT") ? Int32.Parse(allProps["T10_3_SCIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_ENGT") ? Int32.Parse(allProps["T10_3_ENGT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_AGRT") ? Int32.Parse(allProps["T10_3_AGRT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_HEAT") ? Int32.Parse(allProps["T10_3_HEAT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_SERT") ? Int32.Parse(allProps["T10_3_SERT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_OTHT") ? Int32.Parse(allProps["T10_3_OTHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_NST") ? Int32.Parse(allProps["T10_3_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_3_TT") ? Int32.Parse(allProps["T10_3_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NFM") ? Int32.Parse(allProps["T10_4_NFM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PM") ? Int32.Parse(allProps["T10_4_PM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_LSM") ? Int32.Parse(allProps["T10_4_LSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_USM") ? Int32.Parse(allProps["T10_4_USM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TVM") ? Int32.Parse(allProps["T10_4_TVM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ACCAM") ? Int32.Parse(allProps["T10_4_ACCAM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HCM") ? Int32.Parse(allProps["T10_4_HCM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ODNDM") ? Int32.Parse(allProps["T10_4_ODNDM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HDPQM") ? Int32.Parse(allProps["T10_4_HDPQM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PDM") ? Int32.Parse(allProps["T10_4_PDM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_DM") ? Int32.Parse(allProps["T10_4_DM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NSM") ? Int32.Parse(allProps["T10_4_NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TM") ? Int32.Parse(allProps["T10_4_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NFF") ? Int32.Parse(allProps["T10_4_NFF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PF") ? Int32.Parse(allProps["T10_4_PF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_LSF") ? Int32.Parse(allProps["T10_4_LSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_USF") ? Int32.Parse(allProps["T10_4_USF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TVF") ? Int32.Parse(allProps["T10_4_TVF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ACCAF") ? Int32.Parse(allProps["T10_4_ACCAF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HCF") ? Int32.Parse(allProps["T10_4_HCF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ODNDF") ? Int32.Parse(allProps["T10_4_ODNDF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HDPQF") ? Int32.Parse(allProps["T10_4_HDPQF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PDF") ? Int32.Parse(allProps["T10_4_PDF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_DF") ? Int32.Parse(allProps["T10_4_DF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NSF") ? Int32.Parse(allProps["T10_4_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TF") ? Int32.Parse(allProps["T10_4_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NFT") ? Int32.Parse(allProps["T10_4_NFT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PT") ? Int32.Parse(allProps["T10_4_PT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_LST") ? Int32.Parse(allProps["T10_4_LST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_UST") ? Int32.Parse(allProps["T10_4_UST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TVT") ? Int32.Parse(allProps["T10_4_TVT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ACCAT") ? Int32.Parse(allProps["T10_4_ACCAT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HCT") ? Int32.Parse(allProps["T10_4_HCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_ODNDT") ? Int32.Parse(allProps["T10_4_ODNDT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_HDPQT") ? Int32.Parse(allProps["T10_4_HDPQT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_PDT") ? Int32.Parse(allProps["T10_4_PDT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_DT") ? Int32.Parse(allProps["T10_4_DT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_NST") ? Int32.Parse(allProps["T10_4_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T10_4_TT") ? Int32.Parse(allProps["T10_4_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_FW") ? Int32.Parse(allProps["T11_1_FW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BIW") ? Int32.Parse(allProps["T11_1_BIW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BUW") ? Int32.Parse(allProps["T11_1_BUW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TDLW") ? Int32.Parse(allProps["T11_1_TDLW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_MW") ? Int32.Parse(allProps["T11_1_MW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CDW") ? Int32.Parse(allProps["T11_1_CDW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CPW") ? Int32.Parse(allProps["T11_1_CPW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_VW") ? Int32.Parse(allProps["T11_1_VW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_OTHW") ? Int32.Parse(allProps["T11_1_OTHW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_WMFHW") ? Int32.Parse(allProps["T11_1_WMFHW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_NSW") ? Int32.Parse(allProps["T11_1_NSW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TW") ? Int32.Parse(allProps["T11_1_TW"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_FS") ? Int32.Parse(allProps["T11_1_FS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BIS") ? Int32.Parse(allProps["T11_1_BIS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BUS") ? Int32.Parse(allProps["T11_1_BUS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TDLS") ? Int32.Parse(allProps["T11_1_TDLS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_MS") ? Int32.Parse(allProps["T11_1_MS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CDS") ? Int32.Parse(allProps["T11_1_CDS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CPS") ? Int32.Parse(allProps["T11_1_CPS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_VS") ? Int32.Parse(allProps["T11_1_VS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_OTHS") ? Int32.Parse(allProps["T11_1_OTHS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_WMFHS") ? Int32.Parse(allProps["T11_1_WMFHS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_NSS") ? Int32.Parse(allProps["T11_1_NSS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TS") ? Int32.Parse(allProps["T11_1_TS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_FT") ? Int32.Parse(allProps["T11_1_FT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BIT") ? Int32.Parse(allProps["T11_1_BIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_BUT") ? Int32.Parse(allProps["T11_1_BUT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TDLT") ? Int32.Parse(allProps["T11_1_TDLT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_MT") ? Int32.Parse(allProps["T11_1_MT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CDT") ? Int32.Parse(allProps["T11_1_CDT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_CPT") ? Int32.Parse(allProps["T11_1_CPT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_VT") ? Int32.Parse(allProps["T11_1_VT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_OTHT") ? Int32.Parse(allProps["T11_1_OTHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_WMFHT") ? Int32.Parse(allProps["T11_1_WMFHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_NST") ? Int32.Parse(allProps["T11_1_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_1_TT") ? Int32.Parse(allProps["T11_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T1") ? Int32.Parse(allProps["T11_2_T1"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T2") ? Int32.Parse(allProps["T11_2_T2"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T3") ? Int32.Parse(allProps["T11_2_T3"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T4") ? Int32.Parse(allProps["T11_2_T4"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T5") ? Int32.Parse(allProps["T11_2_T5"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T6") ? Int32.Parse(allProps["T11_2_T6"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T7") ? Int32.Parse(allProps["T11_2_T7"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T8") ? Int32.Parse(allProps["T11_2_T8"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_NS") ? Int32.Parse(allProps["T11_2_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_2_T") ? Int32.Parse(allProps["T11_2_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D1") ? Int32.Parse(allProps["T11_3_D1"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D2") ? Int32.Parse(allProps["T11_3_D2"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D3") ? Int32.Parse(allProps["T11_3_D3"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D4") ? Int32.Parse(allProps["T11_3_D4"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D5") ? Int32.Parse(allProps["T11_3_D5"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_D6") ? Int32.Parse(allProps["T11_3_D6"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_NS") ? Int32.Parse(allProps["T11_3_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T11_3_T") ? Int32.Parse(allProps["T11_3_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_1_M") ? Int32.Parse(allProps["T12_1_M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_1_F") ? Int32.Parse(allProps["T12_1_F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_1_T") ? Int32.Parse(allProps["T12_1_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_2_M") ? Int32.Parse(allProps["T12_2_M"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_2_F") ? Int32.Parse(allProps["T12_2_F"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_2_T") ? Int32.Parse(allProps["T12_2_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VGM") ? Int32.Parse(allProps["T12_3_VGM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VGF") ? Int32.Parse(allProps["T12_3_VGF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VGT") ? Int32.Parse(allProps["T12_3_VGT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_GM") ? Int32.Parse(allProps["T12_3_GM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_GF") ? Int32.Parse(allProps["T12_3_GF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_GT") ? Int32.Parse(allProps["T12_3_GT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_FM") ? Int32.Parse(allProps["T12_3_FM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_FF") ? Int32.Parse(allProps["T12_3_FF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_FT") ? Int32.Parse(allProps["T12_3_FT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_BM") ? Int32.Parse(allProps["T12_3_BM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_BF") ? Int32.Parse(allProps["T12_3_BF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_BT") ? Int32.Parse(allProps["T12_3_BT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VBM") ? Int32.Parse(allProps["T12_3_VBM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VBF") ? Int32.Parse(allProps["T12_3_VBF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_VBT") ? Int32.Parse(allProps["T12_3_VBT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_NSM") ? Int32.Parse(allProps["T12_3_NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_NSF") ? Int32.Parse(allProps["T12_3_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_NST") ? Int32.Parse(allProps["T12_3_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_TM") ? Int32.Parse(allProps["T12_3_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_TF") ? Int32.Parse(allProps["T12_3_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T12_3_TT") ? Int32.Parse(allProps["T12_3_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_MDSOM") ? Int32.Parse(allProps["T13_1_MDSOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_POM") ? Int32.Parse(allProps["T13_1_POM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_APTOM") ? Int32.Parse(allProps["T13_1_APTOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_ASOM") ? Int32.Parse(allProps["T13_1_ASOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_STOM") ? Int32.Parse(allProps["T13_1_STOM"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T13_1_CLOSOM") ? Int32.Parse(allProps["T13_1_CLOSOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_SCSOM") ? Int32.Parse(allProps["T13_1_SCSOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_PPMOM") ? Int32.Parse(allProps["T13_1_PPMOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_EOM") ? Int32.Parse(allProps["T13_1_EOM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_NSM") ? Int32.Parse(allProps["T13_1_NSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_TM") ? Int32.Parse(allProps["T13_1_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_MDSOF") ? Int32.Parse(allProps["T13_1_MDSOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_POF") ? Int32.Parse(allProps["T13_1_POF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_APTOF") ? Int32.Parse(allProps["T13_1_APTOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_ASOF") ? Int32.Parse(allProps["T13_1_ASOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_STOF") ? Int32.Parse(allProps["T13_1_STOF"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T13_1_CLOSOF") ? Int32.Parse(allProps["T13_1_CLOSOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_SCSOF") ? Int32.Parse(allProps["T13_1_SCSOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_PPMOF") ? Int32.Parse(allProps["T13_1_PPMOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_EOF") ? Int32.Parse(allProps["T13_1_EOF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_NSF") ? Int32.Parse(allProps["T13_1_NSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_TF") ? Int32.Parse(allProps["T13_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_MDSOT") ? Int32.Parse(allProps["T13_1_MDSOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_POT") ? Int32.Parse(allProps["T13_1_POT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_APTOT") ? Int32.Parse(allProps["T13_1_APTOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_ASOT") ? Int32.Parse(allProps["T13_1_ASOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_STOT") ? Int32.Parse(allProps["T13_1_STOT"].ToString()) : 0);
                writer.Write(
                    allProps.ContainsKey("T13_1_CLOSOT") ? Int32.Parse(allProps["T13_1_CLOSOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_SCSOT") ? Int32.Parse(allProps["T13_1_SCSOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_PPMOT") ? Int32.Parse(allProps["T13_1_PPMOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_EOT") ? Int32.Parse(allProps["T13_1_EOT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_NST") ? Int32.Parse(allProps["T13_1_NST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T13_1_TT") ? Int32.Parse(allProps["T13_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_AFFM") ? Int32.Parse(allProps["T14_1_AFFM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_BCM") ? Int32.Parse(allProps["T14_1_BCM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_MIM") ? Int32.Parse(allProps["T14_1_MIM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_CTM") ? Int32.Parse(allProps["T14_1_CTM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TCM") ? Int32.Parse(allProps["T14_1_TCM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PAM") ? Int32.Parse(allProps["T14_1_PAM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PSM") ? Int32.Parse(allProps["T14_1_PSM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_OTHM") ? Int32.Parse(allProps["T14_1_OTHM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TM") ? Int32.Parse(allProps["T14_1_TM"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_AFFF") ? Int32.Parse(allProps["T14_1_AFFF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_BCF") ? Int32.Parse(allProps["T14_1_BCF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_MIF") ? Int32.Parse(allProps["T14_1_MIF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_CTF") ? Int32.Parse(allProps["T14_1_CTF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TCF") ? Int32.Parse(allProps["T14_1_TCF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PAF") ? Int32.Parse(allProps["T14_1_PAF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PSF") ? Int32.Parse(allProps["T14_1_PSF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_OTHF") ? Int32.Parse(allProps["T14_1_OTHF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TF") ? Int32.Parse(allProps["T14_1_TF"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_AFFT") ? Int32.Parse(allProps["T14_1_AFFT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_BCT") ? Int32.Parse(allProps["T14_1_BCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_MIT") ? Int32.Parse(allProps["T14_1_MIT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_CTT") ? Int32.Parse(allProps["T14_1_CTT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TCT") ? Int32.Parse(allProps["T14_1_TCT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PAT") ? Int32.Parse(allProps["T14_1_PAT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_PST") ? Int32.Parse(allProps["T14_1_PST"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_OTHT") ? Int32.Parse(allProps["T14_1_OTHT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T14_1_TT") ? Int32.Parse(allProps["T14_1_TT"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_NC") ? Int32.Parse(allProps["T15_1_NC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_1C") ? Int32.Parse(allProps["T15_1_1C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_2C") ? Int32.Parse(allProps["T15_1_2C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_3C") ? Int32.Parse(allProps["T15_1_3C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_GE4C") ? Int32.Parse(allProps["T15_1_GE4C"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_NSC") ? Int32.Parse(allProps["T15_1_NSC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_1_TC") ? Int32.Parse(allProps["T15_1_TC"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_2_Y") ? Int32.Parse(allProps["T15_2_Y"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_2_N") ? Int32.Parse(allProps["T15_2_N"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_2_NS") ? Int32.Parse(allProps["T15_2_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_2_T") ? Int32.Parse(allProps["T15_2_T"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_3_B") ? Int32.Parse(allProps["T15_3_B"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_3_OTH") ? Int32.Parse(allProps["T15_3_OTH"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_3_N") ? Int32.Parse(allProps["T15_3_N"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_3_NS") ? Int32.Parse(allProps["T15_3_NS"].ToString()) : 0);
                writer.Write(allProps.ContainsKey("T15_3_T") ? Int32.Parse(allProps["T15_3_T"].ToString()) : 0);



                var gemoetricEl = featureEl.EnumerateObject().FirstOrDefault(pX => pX.Name == "geometry");
                var geoType = gemoetricEl.Value.EnumerateObject().FirstOrDefault(pX => pX.Name == "type").Value
                    .ToString();
                var cordsEl = gemoetricEl.Value.EnumerateObject().FirstOrDefault(pX => pX.Name == "coordinates");
                var cordsArr = cordsEl.Value.EnumerateArray().ToArray();

            
                if (geoType == "Polygon")
                {
                    cordsArr = cordsArr[0].EnumerateArray().ToArray();
                    writer.Write(1);
                    writer.Write(cordsArr.Length);
                    Console.WriteLine(cordsArr.Length);
                    foreach (var coordEl in cordsArr)
                    {
                        var innArr = coordEl.EnumerateArray().ToArray();
                        Console.WriteLine(innArr.Length + "pp");
                        foreach (var val in innArr)
                        {
                            var v = val.ToString();
                            writer.Write(double.Parse(v));
                        }
                    }
                } else if (geoType == "MultiPolygon")
                {
                    writer.Write(cordsArr.Length);
                   
                    foreach (var coordEl in cordsArr)
                    {
                        var innArr = coordEl.EnumerateArray().ToArray()[0].EnumerateArray().ToArray();
                        
                        writer.Write(innArr.Length);
                        foreach (var val in innArr)
                        {
                            var val2arr = val.EnumerateArray().ToArray();
                        
                            foreach (var v2 in val2arr)
                            {
                                var v = v2.ToString();
                                writer.Write(double.Parse(v));
                            }
                        }
                    }
                }
            }

        }
    }
}