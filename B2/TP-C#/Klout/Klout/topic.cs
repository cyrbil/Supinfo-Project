using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace Klout
{
    /*
        {
            "status": 200,
            "users": [
                {
                    "twitter_screen_name": "za",
                    "topics": [
                        "blogging",
                        "transportation",
                        "apa",
                        "cuma",
                        "smartphones"
                    ]
                }
            ]
        }
    */
    [DataContract]
    class topic : AbstractModel
    {
        [DataMember]
        public IEnumerable<topic_users> users { get; set; }
    }

    [DataContract]
    class topic_users : AbstractModel
    {
        [DataMember]
        public string twitter_screen_name { get; set; }
        [DataMember]
        public IEnumerable<string> topics;
    }
}
