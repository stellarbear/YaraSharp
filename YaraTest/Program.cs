using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using YaraSharp;

namespace YaraTest
{
    class Program
    {
        static void Main(string[] args)
        {
            //  All API calls happens here
            YaraSharp.CYaraSharp YSInstance = new CYaraSharp();

            //  Declare external variables (could be null)
            Dictionary<string, object> Externals = new Dictionary<string, object>()
            {
                { "filename", string.Empty },
                { "filepath", string.Empty },
                { "extension", string.Empty }
            };

            //  Errors occured during rule compilation: ignored_file : List<reasons>
            Dictionary<string, List<string>> Errors = new Dictionary<string, List<string>>();

            //  Context is where yara is initialized
            //  From yr_initialize() to yr_finalize()
            using (YaraSharp.CContext YSContext = new YaraSharp.CContext())
            {
                //	Compiling rules
                using (YaraSharp.CRules YSRules = YSInstance.CompileFromFiles(Directory.GetFiles(Path.Combine(Directory.GetCurrentDirectory(), "..\\..\\signatures"), "*.yar", SearchOption.AllDirectories).ToList(), Externals, out Errors))
                {
                    //  Some file to test yara rules
                    string Filename = "<some_file>";

                    //  Get matches
                    List<YaraSharp.CMatches> Matches = YSInstance.ScanFile(Filename, YSRules,
                            new Dictionary<string, object>()
                            {
                                { "filename", System.IO.Path.GetFileName(Filename) },
                                { "filepath", System.IO.Path.GetFullPath(Filename) },
                                { "extension", System.IO.Path.GetExtension(Filename) }
                            },
                            0);

                    //  Iterate over matches
                    foreach (YaraSharp.CMatches Match in Matches)
                    {
                        //...
                    }
                }
                //  Log errors
            }
        }
    }
}
