using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60;

        public static Object unLock = new Object();
        public static bool peutAfficher = true;

        
        private static MenuPrincipal menuPrincipal;
        private static Edition edition;
        private static Configuration configuration;
        private static Profil joueurVirtuel;
        private static TimeSpan dernierTemps;
        private static TimeSpan tempsAccumule;
        private static Stopwatch chrono = Stopwatch.StartNew();
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);

        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    if (FonctionsNatives.executerTests())
                        System.Console.WriteLine("Échec d'un ou plusieurs tests.");
                    else
                        System.Console.WriteLine("Tests réussis.");

                    return;
                }

            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            menuPrincipal = new MenuPrincipal();
            edition = new Edition();
            configuration = new Configuration();
            joueurVirtuel = new Profil();

            //Application.Run(edition);
           
            menuPrincipal.setMenu(edition, configuration);
            edition.setMenuPrincipal(menuPrincipal);
            configuration.setMenuPrincipalConfig(menuPrincipal);

            Application.Run(menuPrincipal);
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn    static void ExecuterQuandInactif(object sender, EventArgs e)
        ///
        /// @brief refraichir le contexte OpenGl
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        /////////////////////////////////////////////////////////////////////////////////////////
        static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;

            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                TimeSpan currentTime = chrono.Elapsed;
                TimeSpan elapsedTime = currentTime - dernierTemps;
                dernierTemps = currentTime;

                tempsAccumule += elapsedTime;

                if (tempsAccumule >= tempsEcouleVoulu)
                {
                    lock (unLock)
                    {
                        if (edition != null && peutAfficher)
                            edition.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);

                    
                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
        }
    }
    static partial class FonctionsNatives
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint Msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint Time;
            public System.Drawing.Point Point;
        }

        [DllImport("User32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool executerTests();
    }
}
