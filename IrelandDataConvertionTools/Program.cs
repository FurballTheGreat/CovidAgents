using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text.Json;

namespace IrelandDataConversionTools
{
    class Program
    {
        static void ConvertCensusPopulationByAge(string pInputFile, string pOutputFile, int pYear)
        {
            using var file = File.OpenText(pInputFile);
            using var output = File.Create(pOutputFile);
            

            var ages = new List<PopulationAgeSex>();
            var first = true;
            while (!file.EndOfStream)
            {
                
                var line = file.ReadLine();
                if (first)
                {
                    first = false;
                    continue;
                }
                var splits = line.Split(",").Select(pX=>pX.Trim('"')).ToArray();

                if(Int32.Parse(splits[1])!=pYear) continue;
                if (splits[3] == "All ages") continue;
                if (splits[2] == "Both sexes") continue;

                if (splits[4] == "Population")
                {
                    var entry = new PopulationAgeSex
                    {
                        Age = splits[3] == "Under 1 year" ? 0 : Int32.Parse(splits[3].Split(" ")[0]),
                        Sex = splits[2] == "Male" ? Sex.Male : Sex.Female,
                        Count = Int32.Parse(splits[6])
                    };

                    ages.Add(entry);
                }
            }
            PopulationAgeSex.WriteTo(output, ages.ToArray());
        }

        static void Main(string[] args)
        {
            var actions = new Dictionary<string, Action>
            {
                {
                    "glossaryconv",
                    blah
                },
                {
                    "shapefile",
                    () =>
                    {
                        var commuterMovements =
                            CommuterMovement.LoadMovements(
                                File.OpenRead(@"C:\personal\coviddocs\ED_Used_Link_Info.csv")).ToArray();
                        ShapeFileConverter.ConvertShapeFile(File.ReadAllText(@"C:\personal\Small_Areas_Generalised_100m_-_OSi_National_Statistical_Boundaries_-_2015_w_data.geojson"), File.Create("output.smallareas"), commuterMovements );
                       //
                       //JsonDocument doc;
                       
                       // var gemoetricEl = doc.RootElement.EnumerateObject().FirstOrDefault(pX=>pX.Name=="geometry");
                       // var cordsEl = doc.RootElement.EnumerateObject().FirstOrDefault(pX=>pX.Name=="coordinates");
                       // var count = cordsEl.Value.EnumerateArray().Count();

                       
                       // foreach (var coordEl in cordsEl.Value.EnumerateArray())
                       // {
                       //     foreach (var val in coordEl.EnumerateArray())
                       //         val.GetDouble();
                       // }

                        //using var writer = File.CreateText(@"C:\personal\smallarea.csv");
                        //allPropNames.Sort();
                        //var first = true;
                        //foreach (var propName in allPropNames)
                        //{
                        //    if (first) first = false; else writer.Write(",");
                        //    writer.Write(propName);
                        //}

                        //writer.WriteLine();

                        //foreach (var featureEl in feautresEl.Value.EnumerateArray())
                        //{
                        //    var property = featureEl.EnumerateObject().FirstOrDefault(pX=>pX.Name=="properties");

                        //    var allProps = property.Value.EnumerateObject().ToDictionary(pX=>pX.Name, pX=>pX.Value);
                        //    first = true;
                        //    foreach (var prop in allPropNames)
                        //    {
                        //        if (first) first = false; else writer.Write(",");
                                
                        //        writer.Write(allProps.ContainsKey(prop) ? allProps[prop].ToString() : "");
                        //    }
                        //    writer.WriteLine();
                        //}


                    }
                },
                {
                    "convertpopdist", 
                    () =>
                    {
                        if (args.Length < 4)
                            Console.WriteLine("SYNTAX: iedataconv convertpopdist input.csv output.popdistbyage year");
                        else if(!File.Exists(args[1]))
                            Console.WriteLine($"{args[1]} does not exist");
                        else if(Int32.TryParse(args[3], out var year))
                        {
                            ConvertCensusPopulationByAge(args[1], args[2],year);
                        }
                        else
                        {
                            Console.WriteLine($"{args[2]} is not an integer");
                        }

                    }
                }
            };

            if (actions.ContainsKey(args[0])) actions[args[0]]();
            else
            {
                Console.WriteLine($"{args[0]} is not a valid command");
                Console.WriteLine("SYNTAX: convertpopdist iedataconv input.csv output.popdistbyage year");
            }

        }

        private static void blah()
        {
            var themes = GlossaryTheme.LoadThemes(@"C:\personal\SAPSGlos.csv").ToList();
            var cppHeaderTemplate = new CppHeaderGlossary()
            {
                Session = new Dictionary<string, object> { { "Themes", themes } }
            };
            cppHeaderTemplate.Initialize();
            var cppHeaderText = cppHeaderTemplate.TransformText();
            var csharpTemplate = new CSharpGlossaryConverter()
            {
                Session = new Dictionary<string, object> { { "Themes", themes } }
            };
            csharpTemplate.Initialize();
            var c = csharpTemplate.TransformText();
        }
    }
}
