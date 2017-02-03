using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.IoT.Gateway;
using System.Threading;
using System.Collections.Concurrent;
using Common;

namespace InventoryModule
{
    public class DotNetInventoryModule : IGatewayModule, IGatewayModuleStart
    {
        private Broker broker;
        private string configuration;
        private object _synchRoot = new object();
        private DateTime startTime = DateTime.Now;
        private Dictionary<string, InvTracking> inventoryQualityTracking;

        public void Create(Broker broker, byte[] configuration)
        {
            this.broker = broker;
            this.configuration = System.Text.Encoding.UTF8.GetString(configuration);
            this.inventoryQualityTracking = new Dictionary<string, InvTracking>();
        }

        public void Start()
        {
            Thread oThread = new Thread(new ThreadStart(this.threadBody));
            // Start the thread
            oThread.Start();
        }

        public void Destroy()
        {
        }

        public void Receive(Message received_message)
        {
            if (received_message.Properties["source"] == "sensor")
            {
                var sku = BOM.Skus.First(x => x.name == received_message.Properties["sku"]);
                var quality = System.Text.Encoding.UTF8.GetString(received_message.Content, 0, received_message.Content.Length) == "1" ? true : false;
                BOM.ConvertSku(sku.name, quality);
                
                if (!inventoryQualityTracking.ContainsKey(sku.name))
                {
                    inventoryQualityTracking.Add(sku.name, new InvTracking());
                }
                inventoryQualityTracking[sku.name].CurrentIdx++;
                inventoryQualityTracking[sku.name].Tracking[inventoryQualityTracking[sku.name].CurrentIdx % 10] = quality ? 1 : 0;

            }
        }

        public void threadBody()
        {
            while (true)
            {
                foreach (var sku in BOM.Skus)
                {
                    Dictionary<string, string> thisIsMyProperty = new Dictionary<string, string>();
                    thisIsMyProperty.Add("source", "inventory");
                    thisIsMyProperty.Add("sku", sku.name);
                    float qualityScore = -1f;
                    if (this.inventoryQualityTracking.ContainsKey(sku.name))
                    {
                        qualityScore = (float)(this.inventoryQualityTracking[sku.name].Tracking.Sum()) / 10f;
                    }
                    thisIsMyProperty.Add("qualityScore", qualityScore.ToString());
                    Message messageToPublish = new Message(sku.onhand.ToString(), thisIsMyProperty);

                    this.broker.Publish(messageToPublish);
                }

                //Publish a message every 5 seconds. 
                Thread.Sleep(5000);
            }
        }
        public class InvTracking
        {
            public int CurrentIdx = -1;
            public int[] Tracking = new int[10];
        }
    }
}
