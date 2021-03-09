using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.Xml;

namespace IrelandDataConversionTools
{
    class GlassaryColumn
    {
        public string Name { get; set; }
        public string Description { get; set; }

        public string StructName
        {
            get
            {
                var sb = new StringBuilder();
                var lastWasSpace = true;
                for(var i = 0; i < Description.Length; i++)
                {
                    var ch = Description[i];
                    if (ch == ' ') lastWasSpace = true;
                    else if (ch == '-' && i < Description.Length - 2 && char.IsDigit(Description[i+2]))
                    {
                        sb.Append("To");
                        lastWasSpace = true;
                    } else
                    {
                        if ((char.ToUpper(ch) >= 'A' && char.ToUpper(ch) <= 'Z') || (ch >= '0' && ch <= '9'))
                        {

                            sb.Append(lastWasSpace ? char.ToUpper(ch) : char.ToLower(ch));
                            lastWasSpace = false;
                        }
                    }
                }

                if (char.IsDigit(sb[0]))
                {
                    if (!char.IsDigit(sb[1]))
                    {
                        Dictionary<char, string> replacements = new Dictionary<char, string>
                        {
                            {'0', "Zero"},
                            {'1', "One"},
                            {'2', "Two"},
                            {'3', "Three"},
                            {'4', "Four"},
                            {'5', "Five"}, 
                            {'6', "Six"},
                            {'7', "Seven"},
                            {'8', "Eight"},
                            {'9', "Nine"}
                        };
                        var c = sb[0];
                        sb.Remove(0, 1);
                        sb.Insert(0,replacements[c]);
                    }
                    else
                    {
                        sb.Insert(0, "R");
                    }
                }
                return sb.ToString();
            }
        }

        public override string ToString()
        {
            return StructName;
        }
    }
}