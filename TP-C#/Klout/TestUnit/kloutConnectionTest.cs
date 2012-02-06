using Klout;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Windows.Forms;
using System.ComponentModel;

namespace TestUnit
{
    
    
    /// <summary>
    ///Classe de test pour kloutConnectionTest, destinée à contenir tous
    ///les tests unitaires kloutConnectionTest
    ///</summary>
    [TestClass()]
    public class kloutConnectionTest
    {


        private TestContext testContextInstance;

        /// <summary>
        ///Obtient ou définit le contexte de test qui fournit
        ///des informations sur la série de tests active ainsi que ses fonctionnalités.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Attributs de tests supplémentaires
        // 
        //Vous pouvez utiliser les attributs supplémentaires suivants lorsque vous écrivez vos tests :
        //
        //Utilisez ClassInitialize pour exécuter du code avant d'exécuter le premier test dans la classe
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //Utilisez ClassCleanup pour exécuter du code après que tous les tests ont été exécutés dans une classe
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //Utilisez TestInitialize pour exécuter du code avant d'exécuter chaque test
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //Utilisez TestCleanup pour exécuter du code après que chaque test a été exécuté
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion


        /// <summary>
        ///Test pour Constructeur kloutConnection
        ///</summary>
        [TestMethod()]
        public void kloutConnectionConstructorTest()
        {
            kloutConnection target = new kloutConnection();
            Assert.Inconclusive("TODO: implémentez le code pour vérifier la cible");
        }

        /// <summary>
        ///Test pour BeginGetUserInfo
        ///</summary>
        [TestMethod()]
        public void BeginGetUserInfoTest()
        {
            kloutConnection target = new kloutConnection(); // TODO: initialisez à une valeur appropriée
            string username = string.Empty; // TODO: initialisez à une valeur appropriée
            Label l = null; // TODO: initialisez à une valeur appropriée
            target.BeginGetUserInfo(username, l);
            Assert.Inconclusive("Une méthode qui ne retourne pas une valeur ne peut pas être vérifiée.");
        }

        /// <summary>
        ///Test pour LoadUserInfo
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Klout.exe")]
        public void LoadUserInfoTest()
        {
            kloutConnection_Accessor target = new kloutConnection_Accessor(); // TODO: initialisez à une valeur appropriée
            object sender = null; // TODO: initialisez à une valeur appropriée
            DoWorkEventArgs e = null; // TODO: initialisez à une valeur appropriée
            target.LoadUserInfo(sender, e);
            Assert.Inconclusive("Une méthode qui ne retourne pas une valeur ne peut pas être vérifiée.");
        }

        /// <summary>
        ///Test pour set_text
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Klout.exe")]
        public void set_textTest()
        {
            kloutConnection_Accessor target = new kloutConnection_Accessor(); // TODO: initialisez à une valeur appropriée
            string msg = string.Empty; // TODO: initialisez à une valeur appropriée
            target.set_text(msg);
            Assert.Inconclusive("Une méthode qui ne retourne pas une valeur ne peut pas être vérifiée.");
        }

        /// <summary>
        ///Test pour topic
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Klout.exe")]
        public void topicTest()
        {
            kloutConnection_Accessor target = new kloutConnection_Accessor(); // TODO: initialisez à une valeur appropriée
            topic_Accessor expected = null; // TODO: initialisez à une valeur appropriée
            topic_Accessor actual;
            target.topic = expected;
            actual = target.topic;
            Assert.AreEqual(expected, actual);
            Assert.Inconclusive("Vérifiez l\'exactitude de cette méthode de test.");
        }

        /// <summary>
        ///Test pour user
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Klout.exe")]
        public void userTest()
        {
            kloutConnection_Accessor target = new kloutConnection_Accessor(); // TODO: initialisez à une valeur appropriée
            Person_Accessor expected = null; // TODO: initialisez à une valeur appropriée
            Person_Accessor actual;
            target.user = expected;
            actual = target.user;
            Assert.AreEqual(expected, actual);
            Assert.Inconclusive("Vérifiez l\'exactitude de cette méthode de test.");
        }
    }
}
