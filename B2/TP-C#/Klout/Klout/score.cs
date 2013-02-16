using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace Klout
{
    [DataContract]
    class score : AbstractModel
    {
        [DataMember]
        public string kscore { get; set; }
        [DataMember]
        public string slope { get; set; }
        [DataMember]
        public string description { get; set; }
        [DataMember]
        public string kclass_id { get; set; }
        [DataMember]
        public string kclass { get; set; }
        [DataMember]
        public string kclass_description { get; set; }
        [DataMember]
        public string kscore_description { get; set; }
        [DataMember]
        public string network_score { get; set; }
        [DataMember]
        public string amplification_score { get; set; }
        [DataMember]
        public string true_reach { get; set; }
        [DataMember]
        public string delta_1day { get; set; }
        [DataMember]
        public string delta_5day { get; set; }
    }
}
