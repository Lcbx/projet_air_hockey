using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace InterfaceGraphique.Utility
{
    /// @brief Permet de gérer la conversion entre le c# et le c++ pour les noms de fichier
    public class Fichier
    {
        public const string ZONES_FILEPATH = "zones";
        public const string DEFAULT_FILENAME = "defaut";
        public const string XML_EXTENSION = "xml";

        /// @brief Nom du fichier cible
        public string NomFichier {
            get; set;
        }

        /// @brief Nom du dossier cible
        public string PathFichier {
            get; set;
        }

        /// @brief Extension du fichier
        public string ExtensionFichier {
            get; set;
        }

        /// @brief Nom complet du fichier terminé par un null byte
        public char[] PathNameFichier {
            get {
                return Path.Combine(PathFichier, NomFichier + "." + ExtensionFichier).ToCCharArray();
            }
        }

        /// @fn public Fichier(string nomFichier, string pathFichier, string extensionFichier)
        /// @brief Création de l'objet fichier par paramètres
        /// @param nomFichier : Nom du fichier sans chemin ni extension
        /// @param pathFichier : Chemin vers le fichier
        /// @param extension : Extension du fichier
        public Fichier(string nomFichier, string pathFichier, string extensionFichier) {
            this.NomFichier = nomFichier;
            this.PathFichier = pathFichier;
            this.ExtensionFichier = extensionFichier;
        }

        /// @fn public static List<Fichier> getListFichier()
        /// @brief Permet d'obtenir la liste des fichiers de zone
        /// @return La liste des fichiers de zone
        public static List<Fichier> getListFichierZones()
        {
            List<Fichier> result = new List<Fichier>();

            if (!Directory.Exists(Fichier.ZONES_FILEPATH))
                Directory.CreateDirectory(Fichier.ZONES_FILEPATH);

            string[] loadFiles = Directory.GetFiles(Edition.SAVE_FILEPATH, "*." + Fichier.XML_EXTENSION);
            loadFiles = loadFiles.Select(filepath => Path.GetFileNameWithoutExtension(filepath)).ToArray();
            foreach (string file in loadFiles)
            {
                result.Add(new Fichier(file, Fichier.ZONES_FILEPATH, Fichier.XML_EXTENSION));
            }

            return result;
        }
    }
}
