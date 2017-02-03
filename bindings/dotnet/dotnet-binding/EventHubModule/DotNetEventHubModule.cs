using Microsoft.Azure.IoT.Gateway;
using Microsoft.ServiceBus.Messaging;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EventHubModule
{
    public class DotNetEventHubModule : IGatewayModule, IGatewayModuleStart
    {
        private Broker broker;
        private Configuration configuration;
        private EventHubClient _sensorClient;
        private EventHubClient _inventoryClient;

        public void Create(Broker broker, byte[] configuration)
        {
            this.broker = broker;
            this.configuration = JsonConvert.DeserializeObject<Configuration>(System.Text.Encoding.UTF8.GetString(configuration));
            this._sensorClient = MessagingFactory
                .CreateFromConnectionString(this.configuration.connectionString + ";TransportType=Amqp")
                .CreateEventHubClient(this.configuration.sensorEventHubName);
            this._inventoryClient = MessagingFactory
                .CreateFromConnectionString(this.configuration.connectionString + ";TransportType=Amqp")
                .CreateEventHubClient(this.configuration.inventoryEventHubName);
        }
        public void Start()
        {
            EventHubClient c = MessagingFactory.Create("").CreateEventHubClient("");
            

        }
        public void Destroy()
        {
        }

        public void Receive(Message received_message)
        {
            if (received_message.Properties["source"] == "inventory")
            {
                var inventoryMessage = new
                {
                    sku = received_message.Properties["sku"],
                    onhand = Convert.ToInt32(System.Text.Encoding.UTF8.GetString(received_message.Content, 0, received_message.Content.Length)),
                    qualityScore = Convert.ToDecimal(received_message.Properties["qualityScore"])
                };
                _inventoryClient.SendAsync(new EventData(Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(inventoryMessage))));
            }
            else if (received_message.Properties["source"] == "sensor")
            {
                var sensorMessage = new
                {
                    sku = received_message.Properties["sku"],
                    qty = Convert.ToInt32(System.Text.Encoding.UTF8.GetString(received_message.Content, 0, received_message.Content.Length))
                };
                _sensorClient.SendAsync(new EventData(Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(sensorMessage))));
                
            }
        }
        public class Configuration
        {
            public string connectionString;
            public string sensorEventHubName;
            public string inventoryEventHubName;
        }
    }
}
