package texte;

import java.util.Scanner;

public class texte {
    
    public static String userInput() {
        // Simuler la saisie utilisateur pour le prénom et le nom
        Scanner lecteur = new Scanner(System.in);

        System.out.println("Comment vous appelez-vous ?");
        String Prenom = lecteur.nextLine();
        System.out.println("Quel est votre nom de famille ?");
        String nom = lecteur.nextLine();
        lecteur.close();
        return Prenom + " " + nom;
    }

    public static void main(String[] args) {
        System.out.println("Bienvenue dans le programme texte.");
        String Reponse = userInput();
        System.out.println(Reponse);
    }
}
