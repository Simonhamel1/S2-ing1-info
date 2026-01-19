package base;
class test{

   
   public void sampleMethod() {
      System.out.println("This is a sample method.");
      int x = 10;
      int y = 20;
      float z = 5.5f;
      System.out.println("Sum: " + (x + y));
      System.out.println("Multiplication: " + (x * y));
      System.out.println("End of sample method.");
      System.out.println("Value of z * x + y : " + (z * x + y));
      int value = (int)(z*x+y);
      System.out.println("Value of int z * x + y : " + value );
   }

   public void unusedMethod(int a , float b) {
      double c = a + b;
      System.out.println("This method is not used anywhere. Value of c : " + c);
   }

   public void affichage_nom(String Prenom, String nom) {
      System.out.println("Bonjour " + Prenom + " " + nom + "!");
   }

   public static void main(String[] args) {
      System.out.println("test java");
      test obj = new test();
      obj.sampleMethod();
      obj.unusedMethod(5, 3.2f);
      String Prenom = "John";
      String nom = "Doe";
      obj.affichage_nom(Prenom, nom);
   }

}