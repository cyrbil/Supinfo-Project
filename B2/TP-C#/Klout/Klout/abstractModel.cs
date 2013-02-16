using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace Klout
{
    [DataContract]
    public abstract class AbstractModel : IExtensibleDataObject
    {
        private ExtensionDataObject extensionDataObjectValue;
        public ExtensionDataObject ExtensionData
        {
            get { return extensionDataObjectValue; }
            set { extensionDataObjectValue = value; }
        }
        /*
            "body": {
                "error": "No users"
            }
        */
        [DataMember]
        public string status { get; set; }
        [DataMember]
        public body body { get; set; }

    }

    public class body : AbstractModel
    {
        public string error { get; set; }
    }
}
