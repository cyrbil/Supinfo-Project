using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace Klout
{
    /**
     * {
            "status": 200,
            "users": [
                {
                    "twitter_id": "40447914",
                    "twitter_screen_name": "juliendollon",
                    "score": {
                        "kscore": 72.95,
                        "slope": 0.05,
                        "description": "generates actions and discussions with nearly every message",
                        "kclass_id": 13,
                        "kclass": "Thought Leader",
                        "kclass_description": "You are a thought leader in your industry. Your followers rely on you, not only to share the relevant news, but to give your opinion on the issues. People look to you to help them understand the day's developments. You understand what's important and what your audience values that.",
                        "kscore_description": "generates actions and discussions with nearly every message",
                        "network_score": 65.44,
                        "amplification_score": 100,
                        "true_reach": 9024,
                        "delta_1day": -0.02,
                        "delta_5day": 0.31
                    }
                }
            ]
        }
     */
    [DataContract]
    class Person : AbstractModel
    {
        [DataMember]
        public IEnumerable<users> users { get; set; }
    }

    [DataContract]
    class users : AbstractModel
    {
        [DataMember]
        public string twitter_id { get; set; }
        [DataMember]
        public string twitter_screen_name { get; set; }
        [DataMember]
        public score score { get; set; }
    }
}
