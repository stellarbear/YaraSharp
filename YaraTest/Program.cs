using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

using YaraSharp;

namespace YaraTest
{
    class Program
    {
        static void Main(string[] args)
        {
            //  Get Version
            Version DllVersion = CYaraSharp.GetVersion();

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
                using (YaraSharp.CRules YSRules = YSInstance.CompileFromFiles(Directory.GetFiles(@"C:\Users\root\source\repos\aptscan-sources\APTScan\Build\Debug\AnyCPU\signatures\yara", "*.yar", SearchOption.AllDirectories).ToList(), Externals, out Errors))
                {
                    //  Some file to test yara rules
                    string Filename = @"\\?\D:\Test\DWS.pdf";

                    //  Get matches
                    List<YaraSharp.CMatches> Matches = YSInstance.ScanFile(Filename, YSRules,
                            new Dictionary<string, object>()
                            {
                                { "filename", Alphaleonis.Win32.Filesystem.Path.GetFileName(Filename) },
                                { "filepath", Alphaleonis.Win32.Filesystem.Path.GetFullPath(Filename) },
                                { "extension", Alphaleonis.Win32.Filesystem.Path.GetExtension(Filename) }
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
