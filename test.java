class ManipulationVariables {
   
   public static void main(String[] args) {
      int epargne = 500;
      int revenus = 2000;
      //Ajoutez 100 à votre épargne (Yeah!)
      epargne = epargne + 100;

      //Enlevez 50 à votre indemnité (Snif)
      revenus = revenus - 50;
      //Faites une mise à jour sur votre délai d'épargne
      int nombreDeJoursEpargne = (5000 - revenus) / 500;
    
      //Mettez à jour à nouveau votre indemnité (encore)
      revenus = revenus + (30 - 10) * 7;

      System.out.println("Votre épargne est de : " + epargne + " euros");
      System.out.println("Votre revenu est de : " + revenus + " euros");
      System.out.println("Il vous reste " + nombreDeJoursEpargne + " jours pour atteindre votre objectif d'épargne.");
   }
}