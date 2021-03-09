using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace IrelandDataConversionTools
{
    class GlossaryTheme
    {
        public string Name { get; set; }
        public string Description { get; set; }

        public List<GlassaryColumn> Columns { get; set; } = new List<GlassaryColumn>();


        public override string ToString()
        {
            return StructName;
        }

        public string StructName
        {
            get
            {
                var sb = new StringBuilder();
                var lastWasSpace = true;
                foreach (var ch in Description)
                {
                    if (ch == ' ') lastWasSpace = true;
                    else
                    {
                        if ((char.ToUpper(ch) >= 'A' && char.ToUpper(ch) <= 'Z') || (ch >= '0' && ch <= '9'))
                        {
                            
                            sb.Append(lastWasSpace ? char.ToUpper(ch) : char.ToLower(ch));
                            lastWasSpace = false;
                        }
                    }
                }

                return sb.ToString();
            }
        }

        /// <summary>
        /// This assumes that all comma have been replaced by spaces before saving the XLSX as CSV.
        /// </summary>
        /// <param name="pSourceCSV"></param>
        /// <returns></returns>
        public static IEnumerable<GlossaryTheme> LoadThemes(string pSourceCSV)
        {
            using var input = File.OpenText(pSourceCSV);
            GlossaryTheme item = new GlossaryTheme();

            input.ReadLine();
            while (!input.EndOfStream)
            {
                var splits = input.ReadLine().Split(",");
                if (!string.IsNullOrEmpty(splits[0]))
                {
                    if (item.Name == null) 
                        item.Name = splits[0];
                    else
                    {
                        yield return item;
                        item = new GlossaryTheme();
                        item.Name = splits[0];
                    }


                }

                if (!string.IsNullOrEmpty(splits[1]))
                {
                    item.Description = splits[1];
                }

                item.Columns.Add(new GlassaryColumn
                {
                    Name = splits[2],
                    Description = splits[3]
                });
            }

            yield return item;
        }
    }
}