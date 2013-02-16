using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Klout;
using System.Net;
using System.Threading;
using System.ComponentModel;
using System.IO;
using System.Windows.Forms;

namespace Klout
{
    class kloutConnection
    {
        Person user { get; set; }                               // Return info of the user here
        topic topic { get; set; }                               // Return info of the user's topics here
        private HttpWebRequest request;                         // To generate the request
        private BackgroundWorker bgw;                           // Worker
        Label label;

        public void BeginGetUserInfo(string username, Label l)
        {
            label = l;
            Person principal = new Person();
            //Code HERE with a thread or background worker
            bgw = new BackgroundWorker();
            bgw.DoWork += new System.ComponentModel.DoWorkEventHandler(this.LoadUserInfo);
            bgw.RunWorkerAsync(username);
        }

        private void LoadUserInfo(object sender, DoWorkEventArgs e)
        {
            //Code here, with JSON deserialization, try/catch, hire of the event…
            try
            {
                // get user data
                request = (HttpWebRequest)WebRequest.Create(Info.ShowUser + e.Argument.ToString().ToLower());
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                Stream streamer = response.GetResponseStream();
                StreamReader reader = new StreamReader(streamer);
                String json = reader.ReadToEnd();
                user = Json.Deserialize<Person>(json);

                if (user.users == null) // see if error value is set and throw error
                    throw new Exception("Api return error:\n" + user.body.error);
                


                // get user topic
                request = (HttpWebRequest)WebRequest.Create(Info.ShowTopic + e.Argument.ToString().ToLower());
                response = (HttpWebResponse)request.GetResponse();
                streamer = response.GetResponseStream();
                reader = new StreamReader(streamer);
                json = reader.ReadToEnd();
                topic = Json.Deserialize<topic>(json);

                if (topic.users == null) // see if error value is set and throw error
                    throw new Exception("Api return error:\n" + topic.body.error);
                
                string text = "Twitter Id: " + user.users.ElementAt(0).twitter_id + "\n" +
                    "Twitter name: " + user.users.ElementAt(0).twitter_screen_name + "\n" +
                    "Score: " + user.users.ElementAt(0).score.kscore + "\n" +
                    "Score description: " + user.users.ElementAt(0).score.kscore_description + "\n" +
                    "Slope: " + user.users.ElementAt(0).score.slope + "\n" +
                    "Description: " + user.users.ElementAt(0).score.description + "\n" +
                    "Class: " + user.users.ElementAt(0).score.kclass + "\n" +
                    "Class id: " + user.users.ElementAt(0).score.kclass_id + "\n" +
                    "Class description: " + user.users.ElementAt(0).score.kclass_description + "\n" +
                    "Network score: " + user.users.ElementAt(0).score.network_score + "\n" +
                    "Amplification score: " + user.users.ElementAt(0).score.amplification_score + "\n" +
                    "True reach: " + user.users.ElementAt(0).score.true_reach + "\n" +
                    "Delta1: " + user.users.ElementAt(0).score.delta_1day + "\n" +
                    "Delta5: " + user.users.ElementAt(0).score.delta_5day + "\n\n" +
                    "Topics: ";
                foreach (string tmp in topic.users.ElementAt(0).topics)
                {
                    text += tmp + ", ";
                }
                set_text(text);
            }
            catch (Exception ex) // error handler
            {
                System.Windows.Forms.MessageBox.Show("Error when trying to get data:\n\n" + ex.Message);
                set_text("Some wild errors appears");
            }
        }

        private void set_text(string msg)
        {
            label.Invoke(new Action(() =>
            {
                label.Text = msg;
            }));
        }
    }
}
