using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Common
{

    public class BOM
    {
        private static object _synchRoot = new object();
        private static System.Timers.Timer _dataRefresh;
        static BOM()
        {
            Skus = ReadBOM();

            //set timer to refresh production values periodically
            //so we can tweak them while the module is running
            _dataRefresh = new System.Timers.Timer(2000);
            _dataRefresh.Elapsed += (s, e) => { ReadProductionParameters(); };
            _dataRefresh.Start();
        }


        public static List<SKU> Skus;
        public static void ConvertSku(string sku, bool qualityCheck)
        {
            lock (_synchRoot)
            {
                var incremented = Skus.First(x => x.name == sku);
                if(qualityCheck)
                    incremented.onhand += 1;
                foreach(var part in incremented.parts)
                {
                    var decremented = Skus.First(x => x.name == part.Key);
                    decremented.onhand -= part.Value;
                }
            }
        }
        public static bool CanMakeSku(string sku)
        {
            lock (_synchRoot)
            {
                var incremented = Skus.First(x => x.name == sku);
                foreach (var part in incremented.parts)
                {
                    var decremented = Skus.First(x => x.name == part.Key);
                    if (decremented.onhand < part.Value)
                        return false;
                }
                return true;
            }
        }
        private static void ReadProductionParameters()
        {
            if (File.Exists("bom.json"))
            {
                var bom = File.ReadAllText("bom.json");
                var skus = JsonConvert.DeserializeObject<List<SKU>>(bom);
                foreach (var sku in skus)
                {
                    var bom_sku = Skus.First(x => x.name == sku.name);
                    bom_sku.productionRatePerHour = sku.productionRatePerHour;
                    bom_sku.avgYieldPerHour = sku.avgYieldPerHour;
                }
            }
        }
        private static List<SKU> ReadBOM()
        {
            if (File.Exists("bom.json"))
            {
                var bom = File.ReadAllText("bom.json");
                return JsonConvert.DeserializeObject<List<SKU>>(bom);
            }
            else throw new Exception("bom.json not found!");
        }
    }
    public class SKU
    {
        
        public int onhand = 0;
        public string name;
        public int productionRatePerHour = 0;
        public int avgYieldPerHour = 0;
        public Dictionary<string, int> parts;
        
    }
    

}
