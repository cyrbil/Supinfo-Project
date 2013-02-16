using System.Text;
using System.ComponentModel;
using System.IO;
using System.Runtime.Serialization.Json;

namespace Klout
{
    public static class Json
    {
        /// <summary>
        /// Serializes an object to a UTF-8 encoded JSON string.
        /// </summary>
        /// <param name="obj">object to serialize</param>
        /// <returns>JSON string result</returns>
        public static string Serialize(object obj)
        {
            // Serialize to a memory stream....
            MemoryStream ms = new MemoryStream();

            // Serialize to memory stream with DataContractJsonSerializer
            DataContractJsonSerializer s = new DataContractJsonSerializer(obj.GetType());
            s.WriteObject(ms, obj);
            byte[] json = ms.ToArray();
            ms.Close();

            // return utf8 encoded json string
            return Encoding.UTF8.GetString(json, 0, json.Length);
        }

        /// <summary>
        /// Deserializes an object from a UTF-8 encoded JSON string.
        /// </summary>
        /// <typeparam name="T">type of object to deserialize as</typeparam>
        /// <param name="json">UTF-8 encoded JSON string</param>
        /// <returns>deserialized object</returns>
        public static T Deserialize<T>(string json)
        {
            T result = default(T);

            // load json into memorystream and deserialize
            MemoryStream ms = new MemoryStream(Encoding.UTF8.GetBytes(json));
            DataContractJsonSerializer s = new DataContractJsonSerializer(typeof(T));
            
            result = (T)s.ReadObject(ms);
            ms.Close();

            return result;
        }
    }

    public static class Info
    {
        public static string Key = "jpyqxh8p7mepvexhc2fqxkqq";
        public static string auth  = "?key=" + Key + "&users=";
        public static string ShowUser = "http://api.klout.com/1/users/show.json" + auth;
        public static string ShowScore = "http://api.klout.com/1/klout.json" + auth;
        public static string ShowTopic = "http://api.klout.com/1/users/topics.json" + auth;
        public static string ShowInfluenceBy = "http://api.klout.com/1/soi/influenced_by.json" + auth;
        public static string ShowInfluenceOf = "http://api.klout.com/1/soi/influencer_of.json" + auth;

    }

}
