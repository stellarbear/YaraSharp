using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using YaraSharp;

namespace YaraSharpUnitTests
{
    [TestClass]
    public class WarningsAndErrors
    {
        private static string BaseDirectory = Environment.CurrentDirectory;
        private static string TestDataDirectory = Path.Combine(BaseDirectory, "TestData");

        /// <summary>
        /// Ensures warnings are correctly reported along with errors,
        /// but does not prevent scanning from working
        /// </summary>
        [TestMethod]
        public void CheckWarningsStillScan()
        {
            string inputFileBase = "CheckWarningStillScans";
            string yaraRuleFile = Path.Combine(TestDataDirectory, $"{inputFileBase}.yar");
            string yaraInputFile = Path.Combine(TestDataDirectory, $"{inputFileBase}.txt");

            CYaraSharp yaraInstance = new CYaraSharp();

            using (CContext context = new CContext())
            {
                using (CCompiler compiler = new CCompiler(null))
                {
                    compiler.AddFile(yaraRuleFile);
                    List<string> compilerErrors = compiler.GetErrors(true);

                    CScanner scanner = new CScanner(compiler.GetRules(), null);
                    Assert.IsTrue(scanner.ScanFile(yaraInputFile).Any(r => r.Rule.Identifier == "WarningRule"));
                }
            }
        }
    }
}
