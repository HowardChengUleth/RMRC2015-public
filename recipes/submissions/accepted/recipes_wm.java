import java.io.*;
import java.util.*;

class Ingredient
{
    Ingredient(Scanner scanner) {
        name=scanner.next();
        weight=scanner.nextDouble();
        percentage=scanner.nextDouble();
    }
    String name;
    double weight;
    double percentage;
    public String toString() { return name + " " + weight + " " + percentage; }
}

class Recipe
{
    ArrayList<Ingredient> ingredients = new ArrayList<Ingredient>();
    int servings;
    int desiredServings;

    Recipe(Scanner scanner)
    {
        int numIngredients = scanner.nextInt();
        servings = scanner.nextInt();
        desiredServings = scanner.nextInt();
        for (int i=0; i<numIngredients; ++i) {
            ingredients.add(new Ingredient(scanner));
        }
    }

    Ingredient main()
    {
        Ingredient ans = null;
        for (Ingredient i : ingredients) {
            if (ans == null || Math.abs(i.percentage-100.0) < Math.abs(ans.percentage-100.0)) {
                ans = i;
            }
        }
        return ans;
    }

    public void resize(PrintStream out) {
        Ingredient m=main();
        double factor = m.weight/m.percentage*desiredServings/servings;

        for (Ingredient i : ingredients) {
            out.println(i.name + " " + String.format("%.1f",i.percentage*factor));
        }
        out.println("----------------------------------------");
    }
}

public class recipes_wm
{
    public static void main(String [] args) throws Exception
    {
        Scanner scanner = new Scanner(System.in);
        int recipes = scanner.nextInt();
        for (int irecipe=1; irecipe<=recipes; ++irecipe) {
            System.out.println("Recipe # " + irecipe);
            Recipe recipe = new Recipe(scanner);
            recipe.resize(System.out);
        }
    }
}
